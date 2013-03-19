
# ifndef __WSI_EVENT_B0FAA1EB4E8D45EC8CE2DF04845E7E60_H_INCLUDED
# define __WSI_EVENT_B0FAA1EB4E8D45EC8CE2DF04845E7E60_H_INCLUDED

# ifdef WSI_CXX_OBJC

WSI_BEGIN_HEADER_CXX

class Object;
class EventObj;

# ifndef WSIOBJECT_DEFINED

typedef void (Object::*objevent_func)(EventObj&);

# endif

WSI_END_HEADER_CXX

# endif

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WSISignal);
WSIDECL_EXTERN_CLASS(WSISlot);
WSIDECL_EXTERN_CLASS(NSDatePeriod);
WSIDECL_EXTERN_CLASS(WSIEventObj);

typedef NSString *signal_t;

typedef void (*slot_function_callback)(WSIEventObj*);

# ifdef WSI_BLOCKS

typedef void (^slot_block_callback)(WSIEventObj*);

# endif

@interface WSISlot : NSObject < NSCopying > {
    
    //! selector.
    SEL _sel;
    
    //! the handler.
    NSObject *_handler;
    
    //! sender,
    void *_sender;
    
    //! result obj, if u want retain result, use [evtobj grab] and [evtobj drop] instead.
    id _result;
    
    //! shot count, -1 is not count, 0 is end.
    int _shotcount;
    
    //! the slot's signal when emit.
    WSISignal *_signal;
    
    //! drop the event, default is NO.
    BOOL _veto;
    
# ifdef WSI_BLOCKS
    
    //! block
    slot_block_callback _block;
    
# endif
    
    //! ptr function.
    slot_function_callback _function;
    
    //! redirect signal.
    signal_t _redirect;
    
    //! delay, default is 0.
    real _delay;
    
    //! u can bind everything on data.
    void* _data;
    
# ifdef WSI_CXX
    
    ::wsi::Object* _cxx_target;
    ::wsi::objevent_func _cxx_action;
    
# endif
    
    //! callback in main thread.
    BOOL _inMainThread;
    
    //! callback in backgrond thread.
    BOOL _inBackgroundThread;
    
    //! fixsender. default is NO.
    BOOL _fixsender;
    
    //! frequency limit for call. default is 0, for no limit.
    real _frequency;
    BOOL _waitFrequency;
    
    //! period.
    NSDatePeriod *_period;
    
}

@property (nonatomic, assign) SEL sel;
@property (nonatomic, assign) NSObject *handler;
@property (nonatomic, assign) void *sender;
@property (nonatomic, retain) id result;
@property (nonatomic, assign) void* data;
@property (nonatomic, assign) int shotcount;
@property (nonatomic, assign) WSISignal *signal;
@property (nonatomic, assign) BOOL veto;
@property (nonatomic, assign) slot_function_callback function;
@property (nonatomic, copy)   signal_t redirect;
@property (nonatomic, assign) BOOL fixsender;
@property (nonatomic, assign) real frequency;
@property (nonatomic, readonly) BOOL waitFrequency;
@property (nonatomic, retain) NSDatePeriod* period;

# ifdef WSI_CXX

@property (nonatomic, assign) ::wsi::Object* cxx_target;
@property (nonatomic, assign) ::wsi::objevent_func cxx_action;

# endif

# ifdef WSI_BLOCKS

@property (nonatomic, assign) slot_block_callback block;

# endif

@property (nonatomic, assign) real delay;
@property (nonatomic, assign) BOOL inMainThread, inBackgroundThread;

//! grab.
- (void)grab;

//! drop.
- (void)drop;

//! oneshot.
- (void)oneshot;

//! mainthread.
- (id)mainThread;

//! background.
- (id)backgroundThread;

//! same thread.
- (id)sameThread;

@end

@interface WSIEventObj : NSObject {
    WSISlot *_slot, *_origin;
}

@property (nonatomic, readonly) WSISlot* slot;

- (id)initWithSlot:(WSISlot*)slot;

@property (nonatomic, readonly) SEL sel;
@property (nonatomic, readonly) NSObject *handler;
@property (nonatomic, readonly) void *sender;
@property (nonatomic, readonly) id result;
@property (nonatomic, readonly) void* data;
@property (nonatomic, readonly) int shotcount;
@property (nonatomic, readonly) WSISignal *signal;
@property (nonatomic, readonly) signal_t redirect;
@property (nonatomic, readonly) real frequency;
@property (nonatomic, readonly) BOOL waitFrequency;
@property (nonatomic, readonly) NSDatePeriod* period;

- (void)veto;

@end

typedef WSISlot slot_t;

# ifdef WSI_CXX

# ifndef WSI_PURE_CXX
#   define _action(act) (::wsi::objevent_func)&act
# endif

WSIDECL_EXTERN_CLASS(NSDatePeriod);

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

class Slot
{
public:
    
    Slot(slot_t* slot)
    : _slot(slot)
    {
        PASS;
    }
    
    Slot(Slot const& r)
    : _slot(r._slot)
    {
        PASS;
    }
    
    void mainthread()
    {
        _slot.inMainThread = YES;
    }
    
    void background()
    {
        _slot.inMainThread = NO;
        _slot.inBackgroundThread = YES;
    }
    
    void veto()
    {
        _slot.veto = YES;
    }
    
    int shotcount() const
    {
        return _slot.shotcount;
    }
    
    void set_shotcount(int cnt)
    {
        _slot.shotcount = cnt;
    }
    
    void oneshot()
    {
        [_slot oneshot];
    }
    
    void set_period(NSDatePeriod *obj)
    {
        _slot.period = obj;
    }
    
protected:
    
    slot_t* _slot;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# define WSIDECL_SIGNAL(signal) SPACE

@interface WSISignal : NSObject {
    
    //! name of signal.
    NSString *_name;
    
    //! slots of signal.
    NSMutableArray *_slots;
    
    //! enable of signal. default is YES.
    BOOL _enable;
    
    @private
    NSLock* _lock;
}

@property (nonatomic, readonly) NSMutableArray *slots;
@property (nonatomic, copy) NSString *name;
@property (/*atomic, */assign) BOOL enable;

//! register a slot.
- (WSISlot*)register_slot:(SEL)sel obj:(NSObject*)obj delay:(real)delay;

//! find slot.
- (WSISlot*)find_slot:(SEL)sel obj:(NSObject*)obj delay:(real)delay;

# ifdef WSI_BLOCKS

- (WSISlot*)register_block:(slot_block_callback)block delay:(real)delay;

# endif

# ifdef WSI_CXX

- (WSISlot*)register_action:(::wsi::objevent_func)action target:(::wsi::Object*)target delay:(real)delay;

# endif

//! register a slot use static function.
- (WSISlot*)register_function:(slot_function_callback)function delay:(real)delay;

//! register a slot will redirect signal.
- (WSISlot*)register_redirect:(signal_t)sig obj:(NSObject*)obj delay:(real)delay;

//! remove slot.
- (void)remove_slot:(SEL)sel obj:(NSObject*)obj;
- (void)remove_slot:(NSObject*)obj;
- (void)remove_slots;

# ifdef WSI_CXX

- (void)remove_action:(::wsi::objevent_func)action target:(::wsi::Object*)target;
- (void)remove_target:(::wsi::Object*)target;

# endif

//! emit slot.
- (void)emit:(void*)obj result:(id)result;
- (void)emit:(void*)obj data:(void*)data;
- (void)emit:(void*)obj result:(id)result data:(void*)data;

//! index of slot.
- (NSUInteger)indexOfSlot:(WSISlot*)slot;

//! count.
- (NSUInteger)count;

@end

@interface WSIEvent : NSObject {
    
    //! store for all signals.
    NSMutableDictionary *_signals;
    
    //! enable. default is YES.
    BOOL _enable;
    
    //! force enable. default is NO.
    BOOL _forceEnable;
    
    //! redirect event.
    NSMutableArray *_redirects;
    
}

@property (nonatomic,  readonly) NSMutableDictionary *signals;
@property (/*atomic, */  assign) BOOL enable, forceEnable;
@property (nonatomic,    assign) NSMutableArray *redirects;

//! register a signal with name.
- (WSISignal*)_register_signal:(signal_t)name;

//! has signal.
- (BOOL)_hasSignal:(signal_t)sig;

//! find signal.
- (WSISignal*)_find_signal:(signal_t)sig;

//! remove a signal.
- (void)_remove_signal:(signal_t)name;

//! emit a signal.
- (void)_emit:(signal_t)sig sender:(void*)sender result:(id)result;
- (void)_emit:(signal_t)sig sender:(void*)sender data:(void*)data;
- (void)_emit:(signal_t)sig sender:(void*)sender result:(id)result data:(void*)data;
- (void)_emit:(signal_t)sig sender:(void*)sender;

//! enable signal.
- (void)_enable:(signal_t)sig tog:(BOOL)tog;

//! connect a signal with slot.
- (WSISlot*)_connect:(signal_t)sig sel:(SEL)sel obj:(NSObject*)obj;
- (WSISlot*)_connect:(signal_t)sig sel:(SEL)sel obj:(NSObject*)obj delay:(real)delay;
- (WSISlot*)_connect:(signal_t)sig sig:(signal_t)sig2 obj:(NSObject*)obj;
- (WSISlot*)_connect:(signal_t)sig sig:(signal_t)sig2 obj:(NSObject*)obj delay:(real)delay;

//! redirect to.
- (void)_redirect:(WSIEvent*)evt;
- (void)_disredirect:(WSIEvent*)evt;

# ifdef WSI_BLOCKS

- (WSISlot*)_connect:(signal_t)sig block:(slot_block_callback)block;
- (WSISlot*)_connect:(signal_t)sig block:(slot_block_callback)block delay:(real)delay;

# endif

- (WSISlot*)_connect:(signal_t)sig func:(slot_function_callback)func;
- (WSISlot*)_connect:(signal_t)sig func:(slot_function_callback)func delay:(real)delay;

# ifdef WSI_CXX

- (WSISlot*)_connect:(signal_t)sig action:(::wsi::objevent_func)action target:(::wsi::Object*)target;
- (WSISlot*)_connect:(signal_t)sig action:(::wsi::objevent_func)action target:(::wsi::Object*)target delay:(real)delay;

# endif

//! break connect.
- (void)_disconnect:(signal_t)sig sel:(SEL)sel obj:(NSObject*)obj;
- (void)_disconnect:(signal_t)sig obj:(NSObject *)obj;
- (void)_disconnect:(NSObject*)obj;
- (void)_disconnect_signal:(signal_t)sig;
- (void)_disconnect_all;

# ifdef WSI_CXX

- (void)_disconnect:(signal_t)sig target:(::wsi::Object*)target action:(::wsi::objevent_func)action;
- (void)_disconnect_target:(::wsi::Object*)target;
- (void)_disconnect_target:(::wsi::Object*)target signal:(signal_t)sig;

# endif

//! find connect.
- (WSISlot*)_find_connect:(signal_t)sig sel:(SEL)sel obj:(NSObject*)obj;
- (WSISlot*)_find_connect:(signal_t)sig sel:(SEL)sel obj:(NSObject*)obj delay:(real)delay;

//! global.
+ (void)EnableEverywhere;
+ (void)DisableEverywhere;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

class EventObj
{
    
protected:
    
    class _pointer_wrapper
    {
    public:
        
        _pointer_wrapper(void* obj)
        : _ptr(obj)
        {
            PASS;
        }
        
        operator void* () const
        {
            return (void*)_ptr;
        }
        
        template <typename T>
        operator T& () const
        {
            return *(T*)(void*)_ptr;
        }
        
        template <typename T>
        operator T* () const
        {
            return (T*)(void*)_ptr;
        }
        
        void* _ptr;
        
    };
    
public:
    
    EventObj(WSIEventObj* evt)
    : _evt(evt)
    {
        [_evt retain];
    }
    
    ~EventObj()
    {
        safe_release(_evt);
    }
    
    _pointer_wrapper sender() const
    {
        return _evt.sender;
    }
    
    id result() const
    {
        return (id)[_evt.result object];
    }
    
    _pointer_wrapper data() const
    {
        return _evt.data;
    }
    
    template <typename T>
    operator T const* () const
    {
        return (T const*)(void*)result();
    }
    
    template <typename T>
    operator T* () const
    {
        return (T*)(void*)result();
    }
    
    template <typename T>
    operator T const& () const
    {
        return *(T const*)(void*)result();
    }
    
    template <typename T>
    operator T& () const
    {
        return *(T*)(void*)result();
    }
        
protected:

    WSIEventObj* _evt;

};

WSI_EXTERN EventObj null_eventobj;

WSI_END_HEADER_CXX

# endif

# endif

# ifdef WSI_CXX

# include <map>
# include <string>
# include <vector>
# include <list>

# include "../WTL/Exception+WSI.h"

WSI_BEGIN_HEADER_CXX

# ifdef WSI_OBJC

WSI_BEGIN_NS(ns)

using ::signal_t;

WSI_END_NS

# endif

WSI_BEGIN_NS(cxx)

typedef ::std::string signal_t;

template <class ObjectT>
struct EventObj
{
    typedef EventObj<ObjectT> _class;
	typedef EventObj<ObjectT> eventobj_t;
	typedef void (ObjectT::*event_func)(eventobj_t&);
	typedef void (*pure_event)(eventobj_t&);
    
	EventObj()
		: 
	    target(NULL), 
		action(0), 
		pure_action(0), 
		sender(NULL), 
		data(NULL),
		result(NULL),
		shotcount(-1), 
		veto(false), 
		status(0),
		fixsender(false),
		background(false)
	{
        PASS;
	}
    
    static _class Data(void* da, void* result = NULL)
    {
        _class evt;
        evt.data = da;
        evt.result = result;
        return evt;
    }

	//! run in background. default is false.
	bool background;
    
    //! target for run action.
	ObjectT     *target;
    
    //! action on target.
	event_func   action;
    
    //! static event.
	pure_event   pure_action;
    
    //! sender.
	void*        sender;
    
    //! sender is fix.
    bool         fixsender;
    
    //! data.
	void*        data;
    
    //! result.
    void*        result;
    
    //! which signal.
	signal_t  signal;
    
    //! redirect to signal.
    signal_t  redirect_signal;
    
    //! shot count.
    int          shotcount;
    
    //! status.
    int          status;
    
    //! veto to suspend.
    bool         veto;
    
    //! to value.
    operator void* () const
    {
        return (void*)data;
    }

    template <typename valT>
    operator valT* () const
    {
        return (valT*)(void*)data;
    }

    template <typename valT>
    operator valT& () const
    {
        return *(valT*)*this;
    }

    operator eventobj_t& () const
    {
        return *(eventobj_t*)this;
    }

    operator eventobj_t* () const
    {
        return (eventobj_t*)this;
    }
    
    void oneshot()
    {
        this->shotcount = 1;
    }

	void in_background()
	{
		this->background = true;
	}

};

# define EVENT_TPL_DECL template <class ObjectT>
# define EVENT_TPL_IMPL ObjectT

template <class ObjectT>
class Event
{
public:

	typedef EventObj<ObjectT> eventobj_t, slot_t;
	typedef ObjectT object_t;
	typedef typename eventobj_t::event_func event_func;
	typedef typename eventobj_t::pure_event event_pure;
    
	Event();
	~Event();
    
	//! clear
	void clear();
    
	//! register
	void register_signal(signal_t const&);
    
	//! connect
	slot_t* connect(signal_t const&, object_t*, event_func);
	slot_t* connect(signal_t const&, event_pure);
    
    //! disconnect.
    void disconnect(object_t*);
    void disconnect(signal_t const&, object_t*, event_func);
	void disconnect(signal_t const&, event_pure);
    void disconnect(signal_t const&, object_t*);
    
    //! redirect signal.
    slot_t* redirect(signal_t const&, signal_t const&, object_t*);
    
    //! block.
    void block(signal_t const&);
    void unblock(signal_t const&);
    
    //! exist signal.
    bool exist(signal_t const&) const;
    
	//! emit
	void emit(signal_t const&, eventobj_t&, void* sender) const;
    
protected:    
    
    void _do_emit(signal_t const&, eventobj_t&, void* sender) const;
    
	typedef ::std::list<eventobj_t*> slots_type;
	typedef ::std::map<std::string, slots_type> store_type;
    typedef ::std::vector<std::string> block_type;
    
	store_type _store;
    block_type _block;

};

EVENT_TPL_DECL
template_impl Event<EVENT_TPL_IMPL>::Event()
{
	PASS;
}

EVENT_TPL_DECL
template_impl Event<EVENT_TPL_IMPL>::~Event()
{
	this->clear();
}

EVENT_TPL_DECL
template_impl void Event<EVENT_TPL_IMPL>::clear()
{
	for (typename_ store_type::iterator iter = _store.begin(); iter != _store.end(); ++iter)
	{
        slots_type& slots = iter->second;
		for (typename slots_type::iterator iter = slots.begin(); iter != slots.end(); ++iter)
		{
			delete *iter;
		}
	}
	_store.clear();
}

EVENT_TPL_DECL
template_impl void Event<EVENT_TPL_IMPL>::register_signal(signal_t const& sig)
{
	typename_ store_type::const_iterator found = _store.find(sig);
	if (found == _store.end())
	{
		_store.insert(std::make_pair(sig, slots_type()));
	}
}

EVENT_TPL_DECL
template_impl typename Event<EVENT_TPL_IMPL>::slot_t* 
Event<EVENT_TPL_IMPL>::connect(signal_t const& sig, object_t* tgt, event_func func)
{
	typename_ store_type::iterator found = _store.find(sig);
	if (found == _store.end())
    {
# ifdef WSI_DEBUG
        ::std::string msg = "failed to connect signal: [";
        msg += sig;
        msg += "] .";
        throw exception::message(msg);
# endif
		return NULL;
    }
    
	slots_type& slots = found->second;
	eventobj_t *evtobj = new eventobj_t();
	evtobj->target = tgt;
	evtobj->action = func;
	slots.push_back(evtobj);
    return evtobj;
}

EVENT_TPL_DECL
template_impl typename Event<EVENT_TPL_IMPL>::slot_t* 
Event<EVENT_TPL_IMPL>::connect(signal_t const&  sig, event_pure act)
{
	typename_ store_type::iterator found = _store.find(sig);
	if (found == _store.end())
    {
# ifdef WSI_DEBUG
        ::std::string msg = "failed to connect signal: [";
        msg += sig;
        msg += "] .";
        throw exception::message(msg);
# endif
		return NULL;
    }
    
	slots_type& slots = found->second;
	eventobj_t *evtobj = new eventobj_t();
	evtobj->pure_action = act;
	slots.push_back(evtobj);
    return evtobj;
}

EVENT_TPL_DECL
template_impl typename Event<EVENT_TPL_IMPL>::slot_t*
Event<EVENT_TPL_IMPL>::redirect(signal_t const& sig, signal_t const& sigto, object_t *tgt)
{
    typename_ store_type::iterator found = _store.find(sig);
	if (found == _store.end())
    {
# ifdef WSI_DEBUG
        ::std::string msg = "failed to redirect signal: [";
        msg += sig;
        msg += "] .";
        throw exception::message(msg);
# endif
		return NULL;
    }
    
    slots_type& slots = found->second;
	eventobj_t *evtobj = new eventobj_t();
	evtobj->redirect_signal = sigto;
    evtobj->target = tgt;
	slots.push_back(evtobj);
    return evtobj;
}

EVENT_TPL_DECL
template_impl void Event<EVENT_TPL_IMPL>::disconnect(object_t* tgt)
{
    for (typename_ store_type::iterator each = _store.begin();
         each != _store.end();
         ++each)
    {
        slots_type& slots = each->second;
        
        typename_ slots_type::iterator iter = slots.begin();
        while (iter != slots.end())
        {
            if ((*iter)->target == tgt)
            {
                slots.erase(iter++);
                continue;
            }
            
            ++iter;
        }

    }
}

EVENT_TPL_DECL
template_impl void Event<EVENT_TPL_IMPL>::disconnect(signal_t const& sig, object_t* tgt, event_func func)
{
	typename_ store_type::iterator found = _store.find(sig);
	if (found == _store.end())
    {
# ifdef WSI_DEBUG
        ::std::string msg = "failed to disconnect signal: [";
        msg += sig;
        msg += "] .";
        throw exception::message(msg);
# endif
		return;
    }
    
	slots_type& slots = found->second;
    for (typename_ slots_type::iterator iter = slots.begin();
         iter != slots.end();
         ++iter)
    {
        if ((*iter)->target == tgt &&
            (*iter)->action == func)
        {
            slots.erase(iter);
            break;
        }
    }
}

EVENT_TPL_DECL
template_impl void Event<EVENT_TPL_IMPL>::disconnect(signal_t const& sig, object_t* tgt)
{
    typename_ store_type::iterator found = _store.find(sig);
	if (found == _store.end())
    {
# ifdef WSI_DEBUG
        ::std::string msg = "failed to disconnect signal: [";
        msg += sig;
        msg += "] .";
        throw exception::message(msg);
# endif
		return;
    }
    
	slots_type& slots = found->second;
    for (typename_ slots_type::iterator iter = slots.begin();
         iter != slots.end();
         ++iter)
    {
        if ((*iter)->target == tgt)
        {
            slots.erase(iter);
            break;
        }
    }
}

EVENT_TPL_DECL
template_impl void Event<EVENT_TPL_IMPL>::disconnect(signal_t const& sig, event_pure act)
{
	typename_ store_type::iterator found = _store.find(sig);
	if (found == _store.end())
    {
# ifdef WSI_DEBUG
        ::std::string msg = "failed to disconnect signal: [";
        msg += sig;
        msg += "] .";
        throw exception::message(msg);
# endif
		return;
    }
    
	slots_type& slots = found->second;
    for (typename_ slots_type::iterator iter = slots.begin();
         iter != slots.end();
         ++iter)
    {
        if ((*iter)->pure_action == act)
        {
            slots.erase(iter);
            break;
        }
    }
}

EVENT_TPL_DECL
template_impl void Event<EVENT_TPL_IMPL>::block(signal_t const& sig)
{
    this->_block.push_back(sig);
}

EVENT_TPL_DECL
template_impl void Event<EVENT_TPL_IMPL>::unblock(signal_t const& sig)
{
    typename_ block_type::iterator found = ::std::find(_block.begin(), _block.end(), sig);
    if (found == _block.end())
    {
# ifdef WSI_DEBUG
        ::std::string msg = "failed to connect signal: [";
        msg += sig;
        msg += "] .";
        throw exception::message(msg);
# endif
        return;
    }
    _block.erase(found);
}

EVENT_TPL_DECL
template_impl bool Event<EVENT_TPL_IMPL>::exist(signal_t const& sig) const
{
	typename_ store_type::const_iterator found = _store.find(sig);
    return found != _store.end();
}

EVENT_TPL_DECL
template_impl void Event<EVENT_TPL_IMPL>::emit(signal_t const& sig, eventobj_t& evt, void* sender) const
{
# ifdef WSI_OBJC
    NSAutoreleasePool *__tmp_autoreleasepool = [[NSAutoreleasePool alloc] init];
# endif
    
    _do_emit(sig, evt, sender);
    
# ifdef WSI_OBJC
    [__tmp_autoreleasepool drain];
# endif
}

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif