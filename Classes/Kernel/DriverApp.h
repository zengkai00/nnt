
# ifndef __NNT_KERNEL_DRIVERAPP_5fb7c4756bb245dea76e8a3035d281a1_H_INCLUDED
# define __NNT_KERNEL_DRIVERAPP_5fb7c4756bb245dea76e8a3035d281a1_H_INCLUDED

# include "./DriverObject.h"
# include "./DriverFeature.h"

# ifdef NNT_KERNEL_SPACE

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(driver)

class EntryObject
{
public:

# ifdef NNT_MSVC

    EntryObject(PDRIVER_OBJECT _0 = NULL, PUNICODE_STRING _1 = NULL);

    PDRIVER_OBJECT pDriverObject;
    core::string strRegisterPath;
    PDEVICE_OBJECT pDeviceObject;

# endif
};

# define NNT_DRIVER_MAIN \
__nnt_driver_main

enum MemoryMode
{
    MEMORY_BUFFER,
    MEMORY_MAP,
};

NNTDECL_PRIVATE_HEAD(App);

class App
    : public ::nnt::Object
{
    NNTDECL_PRIVATE(App);

public:

    App();
    ~App();

    int main();
    int install();
    void add_feature(Feature*);

    EntryObject eo;
    core::string name;
    MemoryMode memory_mode;

};

NNT_END_NS
NNT_END_HEADER_CXX

# define NNTDECL_DRIVER_APP(app) \
    NNT_BEGIN_C \
    int NNT_DRIVER_MAIN(::nnt::driver::EntryObject& eo) \
{ \
    app __nntapp_driver; \
    __nntapp_driver.eo = eo; \
    int sta = __nntapp_driver.install(); \
    if (::nnt::driver::Status::Failed(sta)) \
    return sta; \
    sta = __nntapp_driver.main(); \
    return sta; \
} \
    NNT_END_C

NNT_BEGIN_HEADER_C

NNT_EXTERN int NNT_DRIVER_MAIN(::nnt::driver::EntryObject&);

NNT_END_HEADER_C

# endif

# endif
