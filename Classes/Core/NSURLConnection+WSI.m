
# import "Core.h"
# import "NSURLConnection+WSI.h"

WSI_BEGIN_OBJC

signal_t kSignalURLConnectionSendRequest = @"::wsi::core::connection::sendrequest";
signal_t kSignalURLConnectionReceiveResponse = @"::wsi::core::connection::receive::respone";
signal_t kSignalURLConnectionReceiveData = @"::wsi::core::connection::receive::data";
signal_t kSignalURLConnectionDataChanged = @"::wsi::core::connection::data::changed";
signal_t kSignalURLConnectionFinish = @"::wsi::core::connection::finish";
signal_t kSignalURLConnectionError = @"::wsi::core::connection::error";
signal_t kSignalURLConnectionExit = @"::wsi::core::connection::exit";

signal_t kSignalURLConnectionWillRedirect = @"::wsi::core::connection::willredirect";
signal_t kSignalURLConnectionRedirected = @"::wsi::core::connection::redirected";

@interface NSSyncURLConnection : WSIObject <NSURLConnectionDelegate, NSURLConnectionDataDelegate> {
    NSURLConnection* _req;
    NSMutableData* _data;
    NSError* _err;
    NSURLResponse* _respn;
}

@property (nonatomic, readonly) NSData* data;
@property (nonatomic, readonly) NSError* err;
@property (nonatomic, readonly) NSURLResponse* respn;

- (id)initWithRequest:(NSURLRequest*)request;
- (void)start;

@end

@implementation NSSyncURLConnection

@synthesize data = _data, err = _err, respn = _respn;

- (id)initWithRequest:(NSURLRequest *)request {
    self = [super init];
    
    _req = [[NSURLConnection alloc] initWithRequest:request delegate:self];
    
    return self;
}

- (void)dealloc {
    [_req cancel];
    
    safe_release(_req);
    safe_release(_data);
    safe_release(_err);
    safe_release(_respn);
    
    [super dealloc];
}

- (void)start {
    [_req start];
    
    // block.
    CFRunLoopRun();
}

- (BOOL)connection:(NSURLConnection *)connection canAuthenticateAgainstProtectionSpace:(NSURLProtectionSpace *)protectionSpace {
    return [protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodServerTrust];
}

- (void)connection:(NSURLConnection *)connection didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge {
    if ([challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodServerTrust])
        [challenge.sender useCredential:[NSURLCredential credentialForTrust:challenge.protectionSpace.serverTrust] forAuthenticationChallenge:challenge];    
    [challenge.sender continueWithoutCredentialForAuthenticationChallenge:challenge];
}

- (NSURLRequest *)connection:(NSURLConnection *)connection willSendRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)response {
    return request;
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    safe_release(_data);
    zero_release(_err);
    zero_release(_respn);
    
    _data = [[NSMutableData alloc] init];
    _respn = [response retain];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    [_data appendData:data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    CFRunLoopStop(CFRunLoopGetCurrent());
    _err = [error retain];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
    CFRunLoopStop(CFRunLoopGetCurrent());
}

@end

@implementation NSURLConnection (WSI)

@end

WSIIMPL_CATEGORY(NSURLConnection, WSI);

@interface WSINSURLConnection ()

@property (nonatomic, retain) NSURLRequest* urlRequest;

- (void)_exit;

@end

@implementation WSINSURLConnection

@synthesize connection = _connection;
@synthesize urlRequest = _urlRequest;
@synthesize inThread = _inThread;

+ (WSINSURLConnection*)connectionWithRequest:(NSURLRequest *)request delegate:(id)delegate {
    return [[[WSINSURLConnection alloc] initWithURLRequest:request delegate:delegate start:NO] autorelease];
}

+ (WSINSURLConnection *)connectionWithRequest:(NSURLRequest *)request {
    return [[[WSINSURLConnection alloc] initWithURLRequest:request start:NO] autorelease];
}

- (id)initWithURLRequest:(NSURLRequest*)request delegate:(id)delegate {
    self = [super init];
    
    self.urlRequest = request;
    _connection = [[NSURLConnection alloc] initWithRequest:request delegate:delegate];
    
    return self;
}

- (id)initWithURLRequest:(NSURLRequest*)request {
    return [self initWithURLRequest:request delegate:self];
}

- (id)initWithURLRequest:(NSURLRequest*)request delegate:(id)delegate start:(BOOL)start {
    self = [super init];
    
    self.urlRequest = request;
    _connection = [[NSURLConnection alloc] initWithRequest:request delegate:delegate startImmediately:start];
    
    return self;
}

- (id)initWithURLRequest:(NSURLRequest*)request start:(BOOL)start {
    return [self initWithURLRequest:request delegate:self start:start];
}

- (void)dealloc {
    safe_release(_connection);
    safe_release(_urlRequest);
    
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalURLConnectionSendRequest)
WSIEVENT_SIGNAL(kSignalURLConnectionReceiveResponse)
WSIEVENT_SIGNAL(kSignalURLConnectionReceiveData)
WSIEVENT_SIGNAL(kSignalURLConnectionDataChanged)
WSIEVENT_SIGNAL(kSignalURLConnectionFinish)
WSIEVENT_SIGNAL(kSignalURLConnectionError)
WSIEVENT_SIGNAL(kSignalURLConnectionExit)
WSIEVENT_END

- (void)start {
    [WSIApplication shared].networkActivityIndicatorVisible = YES;

    // wait complete.
    [self retain];

    // connection start.
    [_connection start];

    // force thread running until end.
    _loop = CFRunLoopGetCurrent();
    CFRunLoopRun();

    // complete.
    [self release];
    [WSIApplication shared].networkActivityIndicatorVisible = NO;
}

- (void)startAsync {
    // wait complete.
    [self retain];
    
    // start async.
    [self performSelectorInBackground:@selector(doStartAsync) withObject:nil];
}

- (void)doStartAsync {
    [WSIApplication shared].networkActivityIndicatorVisible = YES;
    
    // connection start.
    [_connection start];
    
    // force thread running until end.
    _loop = CFRunLoopGetCurrent();
    CFRunLoopRun();
    
    // complete.
    [self release];
    [WSIApplication shared].networkActivityIndicatorVisible = NO;
}

- (void)cancel {
    if (_run == NO)
        return;
    
    // cancel connect.
    [_connection cancel];
    
    // exit.
    [self _exit];
}

- (void)_exit {
    // clear.
    zero_release(_data);
    
    // signal.
    [self emit:kSignalURLConnectionExit];
    
    // set flag.
    _run = NO;
    
    // will quite thread.
    if (_loop) {
        CFRunLoopStop(_loop);
        _loop = nil;
    }
}

# pragma mark delegate.

- (NSURLRequest *)connection:(NSURLConnection *)connection willSendRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)response {
    // signal.
    [self emit:kSignalURLConnectionSendRequest result:[NSPair pairWith:request second:response]];
    return request;
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    _run = YES;
    
    // signal.
    [self emit:kSignalURLConnectionReceiveResponse result:response];
    
    // prepare data.
    if (_data != nil)
        dthrow_msg(@"NSURLConnection", @"the data should be null.");
    
    _data = [[NSMutableData alloc] init];
}

- (void)connection:(WSINSURLConnection *)connection didReceiveData:(NSData *)__data {
    // signal.
    [self emit:kSignalURLConnectionReceiveData result:__data];
    
    // append received.
    [_data appendData:__data];
    
    // signal.
    [self emit:kSignalURLConnectionDataChanged result:_data];
}

- (void)connectionDidFinishLoading:(WSINSURLConnection *)connection {
    _run = NO;
    
    // signal.
    [self emit:kSignalURLConnectionFinish result:_data];
    
    // close.
    [self _exit];
}

- (void)connection:(WSINSURLConnection *)connection didFailWithError:(NSError *)error {
    _run = NO;
    
    // signal.
    [self emit:kSignalURLConnectionError result:error];
    
    // close.
    [self _exit];
}

+ (NSData *)sendSynchronousRequest:(NSURLRequest *)request returningResponse:(NSURLResponse **)response error:(NSError **)error {
    NSSyncURLConnection* cnt = [[NSSyncURLConnection alloc] initWithRequest:request];
    [cnt start];
    
    *response = [cnt.respn consign];
    *error = nil;
    
    if (cnt.err == nil)
    {
        NSData* da = [cnt.data consign];
        safe_release(cnt);
        return da;
    }
    
    *error = [cnt.err consign];
    safe_release(cnt);
    return nil;
}

@end

WSI_END_OBJC