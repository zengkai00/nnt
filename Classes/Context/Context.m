
# import "Core.h"
# import "Context.h"
# import "Preferences.h"
# import "Server.h"
# import "User.h"
# import "Cache.h"

NNT_BEGIN_OBJC

void ContextInit(void);
void ContextFin(void);

static Class __gs_context_class = nil;

NNTDECL_PRIVATE_BEGIN(Context, NSObject)
{
    Preferences *prefs;
    Server *srv;
    User *user;
}

@property (nonatomic, retain) Preferences *prefs;
@property (nonatomic, retain) Server *srv;
@property (nonatomic, retain) User *user;

NNTDECL_PRIVATE_IMPL(Context)

@synthesize prefs, srv, user;

- (id)init {
	self = [super init];
	return self;
}

- (void)dealloc {
	zero_release(prefs);
	zero_release(srv);
    zero_release(user);
    
	[super dealloc];
}

- (Preferences*)prefs {
    NNT_SYNCHRONIZED(self)
    if (prefs == nil) {
        prefs = [d_owner.classPrefs new];
        prefs.ctx = d_owner;
    }
    NNT_SYNCHRONIZED_END
    return prefs;
}

- (Server*)srv {
    NNT_SYNCHRONIZED(self)
    if (srv == nil) {
        srv = [d_owner.classServ new];
        srv.ctx = d_owner;
    }
    NNT_SYNCHRONIZED_END
    return srv;
}

- (User*)user {
    NNT_SYNCHRONIZED(self)
    if (user == nil) {
        user = [d_owner.classUser new];
        user.ctx = d_owner;
    }
    NNT_SYNCHRONIZED_END
    return user;
}

NNTDECL_PRIVATE_END

Context *__gs_context = nil;

@implementation Context

@synthesize classServ = _classServ, classUser = _classUser, classPrefs = _classPrefs;

- (id)init {
	self = [super init];
	NNTDECL_PRIVATE_INIT(Context);
    
    _classPrefs = [Preferences class];
    _classServ = [Server class];
    _classUser = [User class];
    
	return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
	[super dealloc];
}

+ (Context*)getInstance {
    NNT_SYNCHRONIZED(self)
    if (__gs_context == nil) {
        if (__gs_context_class)
            __gs_context = [__gs_context_class new];
        else
            __gs_context = [Context new];
	}
    NNT_SYNCHRONIZED_END
	return __gs_context;
}

- (Preferences*)getPrefs {
	return d_ptr.prefs;
}

- (Server*)getSrv {
	return d_ptr.srv;
}

- (User*)getUser {
    return d_ptr.user;
}

+ (void)SetContextClass:(Class)cls {
    NNT_SYNCHRONIZED(self)
    __gs_context_class = cls;
    NNT_SYNCHRONIZED_END
}

+ (void)setDefaultContext:(Context *)__ctx {
    [__gs_context release];
    __gs_context = [__ctx retain];
}

+ (Context*)defaultContext {
    return __gs_context;
}

@end

void ContextInit(void) {
    PASS;
}

void ContextFin(void) {
    PASS;
}

NNT_END_OBJC
