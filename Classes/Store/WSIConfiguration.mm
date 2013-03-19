
# import "Core.h"
# import "WSIConfiguration.h"
# import "WSIBdb.h"

WSI_BEGIN_OBJC

# define kConfFileName @".wsi.config"

WSIDECL_PRIVATE_BEGIN(WSIConfiguration, NSObject)
{
    WSIBdb *_db;
}

@property (nonatomic, retain) WSIBdb *db;

- (BOOL)open:(NSString*)file;

WSIDECL_PRIVATE_IMPL(WSIConfiguration)

@synthesize db = _db;

- (id)init {
    self = [super init];
    
    d_owner.readonly = NO;
    
    return self;
}

- (void)dealloc {
    zero_release(_db);
    
    [super dealloc];
}

- (BOOL)open:(NSString *)file {
    zero_release(_db);
    
    _db = [[WSIBdb alloc] init];
    _db.readonly = d_owner.readonly;
    _db.dup = false;
    if (NO == [_db openDbWith:file type:(NSVariableDirectory | WSIDirectoryTypeSystem)]) {
        zero_release(_db);
    }
    
    trace_if(!_db, "failed to open database");
    return _db != nil;
}

WSIDECL_PRIVATE_END

@implementation WSIConfiguration

@synthesize readonly = _readonly;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSIConfiguration);
    return self;
}

- (id)initWithFile:(NSString *)file {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSIConfiguration);
    
    if (NO == [d_ptr open:file]) {
        [self release];
        return nil;
    }
    
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

static WSIConfiguration *__gs_confcenter = nil;

+ (WSIConfiguration*)shared {   
    WSI_SYNCHRONIZED(self)
    if (__gs_confcenter == nil) {
        WSI *wsiobj = [WSI shared];
        __gs_confcenter = [[self alloc] init];
        if (NO == [__gs_confcenter open:kConfFileName]) {
            trace_msg(@"failed to open config data.");
            zero_release(__gs_confcenter);
        }
        if (__gs_confcenter && wsiobj) {
            [wsiobj storeSet:@"::wsi::gs::confcenter" obj:__gs_confcenter];
        }
    }
    WSI_SYNCHRONIZED_END
    return __gs_confcenter;
}

- (BOOL)del:(NSString *)key {
    NSData* dk = [key dataUsingEncoding:NSUTF8StringEncoding];
    return [d_ptr.db remove:dk];
}

- (void)set:(NSString*)key val:(NSString*)val {
    NSData *dv = [val dataUsingEncoding:NSUTF8StringEncoding];
    NSData *dk = [key dataUsingEncoding:NSUTF8StringEncoding];
    trace_if(!d_ptr.db, "database is nil");
    [d_ptr.db over:dv key:dk];
    [d_ptr.db sync];
}

- (void)set:(NSString*)key data:(NSData*)data {
    NSData *dk = [key dataUsingEncoding:NSUTF8StringEncoding];
    [d_ptr.db over:data key:dk];
    [d_ptr.db sync];
}

- (void)set:(NSString*)key data:(void*)data dlen:(usize)dlen {
    NSData *dk = [key dataUsingEncoding:NSUTF8StringEncoding];
    NSData *dv = [NSData dataWithBytes:data length:dlen];
    [d_ptr.db over:dv key:dk];
    [d_ptr.db sync];
}

- (void)set:(NSString*)key obj:(id)obj {
    NSString* val = @"";
    if (obj)
        val = [WSIObject json_encode:obj];
    [self set:key val:val];
}

- (NSString*)get:(NSString *)key {
    NSData *dk = [key dataUsingEncoding:NSUTF8StringEncoding];
    NSArray *arr = [d_ptr.db get:dk];
    NSData *dv = [arr objectAtIndex:0 null:nil];
    if (dv == nil)
        return nil;
    NSString *ret = [[NSString alloc] initWithData:dv encoding:NSUTF8StringEncoding];
    return [ret autorelease];
}

- (NSString*)get:(NSString *)key null:(NSString *)val {
    NSString* ret = [self get:key];
    if (ret)
        return ret;
    return val;
}

- (NSString*)ava:(NSString *)key null:(NSString *)val {
    NSString* ret = [self get:key];
    if (ret)
        return ret;
    [self set:key val:val];
    return val;
}

- (NSData*)getAsData:(NSString *)key {
    NSData *dk = [key dataUsingEncoding:NSUTF8StringEncoding];
    NSArray *arr = [d_ptr.db get:dk];
    NSData *dv = [arr objectAtIndex:0 null:nil];
    if (dv == nil) {
        return nil;
    }
    return dv;
}

- (byte*)getAsBytes:(NSString*)key {
    NSData* data = [self getAsData:key];
    if (data) {
        return (byte*)[data bytes];
    }
    return nil;
}

- (byte*)getAsBytes:(NSString*)key dlen:(usize*)dlen {
    NSData* data = [self getAsData:key];
    if (data) {
        *dlen = [data length];
        return (byte*)[data bytes];
    }
    return nil;
}

- (id)getAsObject:(NSString*)key {
    NSString* str = [self get:key];
    if (str == nil)
        return nil;
    return [WSIObject json_decode:str];
}

- (id)getAsObject:(NSString *)key null:(id)obj {
    id ret = [self getAsObject:key];
    if (ret)
        return ret;
    return obj;
}

- (id)avaAsObject:(NSString *)key null:(id)obj {
    id ret = [self getAsObject:key];
    if (ret)
        return ret;
    [self set:key obj:obj];
    return obj;
}

- (BOOL)open:(NSString *)file {
    return [d_ptr open:file];
}

+ (WSIConfiguration*)configuration:(NSString*)file {
    return [[[WSIConfiguration alloc] initWithFile:file] autorelease];
}

- (void)set:(NSString*)key boolValue:(bool)val {
    [self set:key data:&val dlen:sizeof(val)];
}

- (void)set:(NSString*)key intValue:(int)val {
    [self set:key data:&val dlen:sizeof(val)];
}

- (void)set:(NSString*)key floatValue:(float)val {
    [self set:key data:&val dlen:sizeof(val)];
}

- (void)set:(NSString*)key doubleValue:(double)val {
    [self set:key data:&val dlen:sizeof(val)];
}

- (void)set:(NSString*)key realValue:(real)val {
    [self set:key data:&val dlen:sizeof(val)];
}

- (bool)getBool:(NSString*)key null:(bool)val {
    byte* bytes = [self getAsBytes:key];
    if (bytes) {
        return *(bool*)bytes;
    }
    return val;
}

- (bool)avaBool:(NSString*)key null:(bool)val {
    byte* bytes = [self getAsBytes:key];
    if (bytes) {
        return *(bool*)bytes;
    }
    [self set:key boolValue:val];
    return val;
}

- (int)getInt:(NSString*)key null:(int)val {
    byte* bytes = [self getAsBytes:key];
    if (bytes) {
        return *(int*)bytes;
    }
    return val;
}

- (int)avaInt:(NSString*)key null:(int)val {
    byte* bytes = [self getAsBytes:key];
    if (bytes) {
        return *(int*)bytes;
    }
    [self set:key intValue:val];
    return val;
}

- (float)getFloat:(NSString*)key null:(float)val {
    byte* bytes = [self getAsBytes:key];
    if (bytes) {
        return *(float*)bytes;
    }
    return val;
}

- (float)avaFloat:(NSString*)key null:(float)val {
    byte* bytes = [self getAsBytes:key];
    if (bytes) {
        return *(float*)bytes;
    }
    [self set:key floatValue:val];
    return val;
}

- (double)getDouble:(NSString*)key null:(double)val {
    byte* bytes = [self getAsBytes:key];
    if (bytes) {
        return *(double*)bytes;
    }
    return val;
}

- (double)avaDouble:(NSString*)key null:(double)val {
    byte* bytes = [self getAsBytes:key];
    if (bytes) {
        return *(double*)bytes;
    }
    [self set:key doubleValue:val];
    return val;
}

- (real)getReal:(NSString*)key null:(real)val {
    byte* bytes = [self getAsBytes:key];
    if (bytes) {
        return *(real*)bytes;
    }
    return val;
}

- (real)avaReal:(NSString*)key null:(real)val {
    byte* bytes = [self getAsBytes:key];
    if (bytes) {
        return *(real*)bytes;
    }
    [self set:key realValue:val];
    return val;
}

- (void)clear {
    [d_ptr.db clear];
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(store)

Configuration::Configuration(ns::String const& file)
{
    _init();
    
    this->open(file);
}

Configuration& Configuration::shared()
{
    static Configuration __gs_configuration(ns::String(@".wsi.config"));
    return __gs_configuration;
}

bool Configuration::open(ns::String const& file)
{
    NSURL *url = WSIDirectoryCreateWithType(@"", (NSVariableDirectory | WSIDirectoryTypeSystem));
    if (url == nil)
        return NO;
    url = [url URLByAppendingPathComponent:file];
    if (url == nil)
        return NO;
        
    store::connection_info info;
    info.url = core::type_cast<core::string>(url.relativePath);
    
    return _connect(info);
}

bool Configuration::set_obj(ns::String const& key, id obj)
{
    if (obj == nil)
        return true;
    NSString* val = @"";
    if (obj)
        val = [::WSIObject json_encode:obj];
    return this->set(ns::String(key), ns::String(val));
}

id Configuration::get_obj(ns::String const& key, id null) const
{
    ns::String str = this->get(key, ns::null_string);
    if (str == ns::null_string)
        return null;
    id obj = [::WSIObject json_decode:str];
    return obj;
}

bool Configuration::remove(ns::String const& key)
{
    core::data da = core::type_cast<core::data>(key);
    return this->remove(da);
}

WSI_END_NS
WSI_END_CXX