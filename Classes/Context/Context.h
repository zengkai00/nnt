
# ifndef __WSI_CTX_CONTEXT_F05CA46B11ED47B491A1761A0C5A509A_H_INCLUDED
# define __WSI_CTX_CONTEXT_F05CA46B11ED47B491A1761A0C5A509A_H_INCLUDED

# include "Preferences.h"
# include "Server.h"
# include "User.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(Context);

//! @class Context of app use singleton design pattern
@interface Context : WSIObject {
    
    Class _classPrefs;
    Class _classServ;
    Class _classUser;
    
	WSIDECL_PRIVATE(Context);
}

@property (nonatomic, assign) Class classPrefs, classServ, classUser;

//! @function get instance
+ (Context*)getInstance;

//! @function get prefs
- (Preferences*)getPrefs;

//! @function get server
- (Server*)getSrv;

//! @function get user
- (User*)getUser;

//! default
+ (void)setDefaultContext:(Context*)__ctx;
+ (Context*)defaultContext;

//! set class.
+ (void)SetContextClass:(Class)cls;

@end

void ContextInit();
void ContextFin();

extern Context *__gs_context;

# ifdef WSI_CXX
# define CTX()   [::Context getInstance]
# else
# define CTX()   [Context getInstance]
# endif

# define SERV()  [CTX() getSrv]
# define USER()  [CTX() getUser]
# define PREFS() [CTX() getPrefs]

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

class Context
{
    WSIDECL_NOCOPY(Context);
    
public:
    
    Context(::Context* ctx)
    : _ctx(ctx)
    {
        PASS;
    }
    
    static Context& getInstance()
    {
        static Context __gs_ctx(CTX());
        return __gs_ctx;
    }
    
    template <typename T>
    static Context& getInstance()
    {
        static Context __gs_ctx([T getInstance]);
        return __gs_ctx;
    }
    
    Server& server()
    {
        _srv._set([_ctx getSrv]);
        return _srv;
    }
    
    User& user()
    {
        _usr._set([_ctx getUser]);
        return _usr;
    }
    
    Preferences& prefs()
    {
        _pref._set([_ctx getPrefs]);
        return _pref;
    }
    
    template <typename T>
    static void SetClass()
    {
        [::Context SetContextClass:[T class]];
    }
    
protected:
    
    ::Context* _ctx;
    Server _srv;
    User _usr;
    Preferences _pref;
    
};

WSI_END_NS

WSI_BEGIN_NS(context)

inline_impl ns::Server& Serv()
{
    return ns::Context::getInstance().server();
}

inline_impl ns::User& User()
{
    return ns::Context::getInstance().user();
}

inline_impl ns::Preferences& Prefs()
{
    return ns::Context::getInstance().prefs();
}

WSI_END_NS

WSI_END_HEADER_CXX

# endif
// end cxx

# endif
// end objc

# endif
