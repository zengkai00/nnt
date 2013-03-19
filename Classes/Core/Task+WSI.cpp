
# include "Core.h"
# include "Task+WSI.h"

WSI_BEGIN_CXX 
WSI_BEGIN_NS(core)
  
Mutex::Mutex()
{
# ifdef WSI_MSVC
    
    _hdl = ::CreateMutex(NULL, FALSE, NULL);
    
# else

    pthread_mutex_init(&_hdl, NULL);
    
# endif
}

Mutex::~Mutex()
{
# ifdef WSI_MSVC
    
    ::CloseHandle(_hdl);
    
# else
    
    pthread_mutex_destroy(&_hdl);
    
# endif
}

void Mutex::lock()
{
# ifdef WSI_MSVC
    
    ::WaitForSingleObject(_hdl, INFINITE);
    
# else
    
# ifdef WSI_DEBUG

    int sta = pthread_mutex_lock(&_hdl);
    if (sta != 0)
      trace_msg("failed to lock mutex.");

# else

    pthread_mutex_lock(&_hdl);

# endif
    
# endif
}

void Mutex::unlock()
{
# ifdef WSI_MSVC
    
    ::ReleaseMutex(_hdl);
    
# else
    
# ifdef WSI_DEBUG

	int sta = pthread_mutex_unlock(&_hdl);
	if (sta != 0)
		trace_msg("failed to unlock mutex.");

# else

    pthread_mutex_unlock(&_hdl);

# endif
    
# endif    
}

bool Mutex::try_lock()
{
# ifdef WSI_MSVC
    
    DWORD ret = ::WaitForSingleObject(_hdl, 0);
    return WAIT_OBJECT_0 == ret;
    
# else
    
    int ret = pthread_mutex_trylock(&_hdl);
    return ret == 0;
    
# endif
}

Condition::Condition()
{
# ifdef WSI_MSVC

	_hdl = ::CreateEvent(NULL, FALSE, FALSE, NULL);

# else
    
    pthread_cond_init(&_hdl, NULL);    
    pthread_mutex_init(&_mtx, NULL);
    
# endif
}

Condition::~Condition()
{
# ifdef WSI_MSVC

	::CloseHandle(_hdl);

# else
    
    pthread_cond_destroy(&_hdl);
    pthread_mutex_destroy(&_mtx);
    
# endif
}

void Condition::wait()
{
# ifdef WSI_MSVC

	::WaitForSingleObject(_hdl, INFINITE);

# else
    
    pthread_mutex_lock(&_mtx);
    pthread_cond_wait(&_hdl, &_mtx);
    pthread_mutex_unlock(&_mtx);
    
# endif
}

void Condition::signal()
{
# ifdef WSI_MSVC

	::SetEvent(_hdl);

# else
    
    pthread_cond_signal(&_hdl);
    
# endif
}

Semaphore::Semaphore(uint cnt)
{
# if defined(WSI_MSVC)
    
# elif defined(WSI_MACH)
    
    static int _gs_sem_id = 0;
    char buf[64];
    snprintf(buf, sizeof(buf), "__wsi_core_semaphore_default_%d", ++_gs_sem_id);
    _hdl = sem_open(buf, O_CREAT|O_EXCL, cnt);
    if (_hdl == SEM_FAILED)
    {        
        trace_msg("failed to create seamphore.");
    }

# endif
}

Semaphore::~Semaphore()
{
# if defined(WSI_MSVC)
# elif defined(WSI_MACH)
    
    sem_close(_hdl);
    sem_destroy(_hdl);
    
# endif
}

void Semaphore::lock()
{
# if defined(WSI_MSVC)
# elif defined(WSI_MACH)
    
    int sta = sem_wait(_hdl);
    if (sta != 0)
    {
        trace_msg("failed to lock semaphore.");
    }
    
# endif
}

void Semaphore::unlock()
{
# if defined(WSI_MSVC)
# elif defined(WSI_MACH)
    
    int sta = sem_post(_hdl);
    if (sta != 0)
    {
        trace_msg("failed to unlock semaphore.");
    }
    
# endif
}

WSIDECL_PRIVATE_BEGIN_CXX(Task)

void init()
{
    hdl_thd = 0;
    frun = 0;
    complete = false;    
    d_owner->count = 1;
}

void dealloc()
{
    d_owner->complete();    
	this->wait();
}

owner_type::func_run frun;
uint count;
bool complete;

int run_once()
{
    mtx_run.lock();
    
    int ret = 0;
    if (frun)
        ret = (*frun)(d_owner);
    if (ret)
    {
        mtx_run.unlock();
        return ret;
    }
    
    ret = d_owner->main();
    if (ret)
    {
        mtx_run.unlock();
        return ret;
    }
    
    mtx_run.unlock();
    return ret;
}

# ifdef WSI_MSVC

HANDLE hdl_thd;

# else

pthread_t hdl_thd;

# endif

Mutex mtx_ctl, mtx_run;

# ifdef WSI_MSVC
friend DWORD WINAPI wrapper_thd(LPVOID);
static DWORD WINAPI wrapper_thd(LPVOID data)
# else
friend void* wrapper_thd(void*);
static void* wrapper_thd(void* data)
# endif
{
    owner_type* d_owner = (owner_type*)data;
    
    if (d_owner->count != -1)
    {
        d_owner->d_ptr->count = d_owner->count;
        
        while (!d_owner->d_ptr->complete &&
               d_owner->d_ptr->count--)
        {
            d_owner->d_ptr->mtx_ctl.lock();
            
            if (d_owner->d_ptr->run_once())
                d_owner->d_ptr->complete = true;
            
            d_owner->d_ptr->mtx_ctl.unlock();
        }
    }
    else
    {
        while (!d_owner->d_ptr->complete)
        {
            d_owner->d_ptr->mtx_ctl.lock();
            
            if (d_owner->d_ptr->run_once())
                d_owner->d_ptr->complete = true;
            
            d_owner->d_ptr->mtx_ctl.unlock();
        }
    }
    
    d_owner->drop();
    
    trace_msg("task's thread is exited.");
    
    return NULL;
}

bool start()
{
    d_owner->grab();
    complete = false;
    
# ifdef WSI_MSVC
    
    hdl_thd = ::CreateThread(NULL, 0, wrapper_thd, d_owner, 0, NULL);
    return hdl_thd != NULL;
    
# else
    
    int ret = pthread_create(&hdl_thd, NULL, wrapper_thd, d_owner);
    return ret == 0;
    
# endif
}

void wait()
{
# ifdef WSI_MSVC
# else
    pthread_join(hdl_thd, NULL);
# endif
}

WSIDECL_PRIVATE_END_CXX

Task::Task()
{
    WSIDECL_PRIVATE_CONSTRUCT(Task);
}

Task::~Task()
{
    WSIDECL_PRIVATE_DESTROY();
}

void Task::wait()
{
    d_ptr->wait();
}

bool Task::start(func_run func)
{
    if (d_ptr->hdl_thd)
        return false;
    d_ptr->frun = func;
    return d_ptr->start();
}

bool Task::start()
{
    if (d_ptr->hdl_thd)
        return false;
    return d_ptr->start();
}

void Task::infinite()
{
    count = -1;
}

void Task::stop()
{
    d_ptr->complete = true;
}

bool Task::complete() const
{
    return d_ptr->complete;
}

void Task::suspend()
{
    d_ptr->mtx_ctl.lock();
}

void Task::resume()
{
    d_ptr->mtx_ctl.unlock();
}

WSI_END_NS 
WSI_END_CXX