
# import "Core.h"
# import "InAppPurchase.h"
# import <StoreKit/StoreKit.h>
# import "App.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

@interface WSISKProduct : SKProduct {
    NSString* _identifier;
}

@property (nonatomic, copy) NSString* identifier;

@end

@implementation WSISKProduct

@synthesize identifier = _identifier;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_release(_identifier);
    [super dealloc];
}

- (NSString*)productIdentifier {
    NSString* ret = super.productIdentifier;
    if (ret == nil)
        ret = _identifier;
    return ret;
}

@end

@implementation InAppPurchaseItem

@synthesize product = _product;
@synthesize payment = _payment;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_release(_product);
    safe_release(_payment);
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_END

- (BOOL)downloadable {
    if ([_product respondsToSelector:@selector(downloadable)])
        return _product.downloadable;
    return NO;
}

- (NSArray*)downloadContentLengths {
    if ([_product respondsToSelector:@selector(downloadContentLengths)])
        return _product.downloadContentLengths;
    return [NSArray array];
}

- (NSString*)downloadContentVersion {
    if ([_product respondsToSelector:@selector(downloadContentVersion)])
        return _product.downloadContentVersion;
    return @"";
}

@end

WSIDECL_PRIVATE_BEGIN(InAppPurchaseService, WSIObject)
<SKPaymentTransactionObserver>
{
}

WSIDECL_PRIVATE_IMPL(InAppPurchaseService)

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

# pragma mark observer

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
    for (SKPaymentTransaction* each in transactions) {
        SKPayment* obj = each.payment;
        WSISKProduct* produ = [[WSISKProduct alloc] init];
        produ.identifier = obj.productIdentifier;
        InAppPurchaseItem* item = [[InAppPurchaseItem alloc] init];
        item.product = produ;
        item.payment = obj;
        safe_release(produ);
        
        switch (each.transactionState)
        {
            case SKPaymentTransactionStateFailed: {
                [d_owner emit:kSignalPayFailed result:item];
                [queue finishTransaction:each];
            } break;
            case SKPaymentTransactionStatePurchased: {
                [d_owner emit:kSignalPaySuccess result:item];
                [queue finishTransaction:each];
            } break;
            case SKPaymentTransactionStatePurchasing: {
                [d_owner emit:kSignalPaying result:item];
            } break;
            case SKPaymentTransactionStateRestored: {
                [d_owner emit:kSignalPayRestore result:item];
                [queue finishTransaction:each];
            } break;
        }
        
        safe_release(item);
    }
}

- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray *)transactions {
    
}

- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error {
    
}

- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue {
    
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray *)downloads {
    
}

WSIDECL_PRIVATE_END

@implementation InAppPurchaseService

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(InAppPurchaseService);
    
    _queue = [SKPaymentQueue defaultQueue];
    [_queue addTransactionObserver:d_ptr];
    
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalPaying)
WSIEVENT_SIGNAL(kSignalPayFailed)
WSIEVENT_SIGNAL(kSignalPaySuccess)
WSIEVENT_SIGNAL(kSignalPayRestore)
WSIEVENT_END

+ (BOOL)Payable {
    return [SKPaymentQueue canMakePayments];
}

+ (InAppPurchaseService*)shared {
    static InAppPurchaseService* ret = nil;
    WSI_SYNCHRONIZED(self)
    if (ret == nil)
        ret = [[[self class] alloc] init];
    WSI_SYNCHRONIZED_END
    return ret;
}

- (void)addItem:(InAppPurchaseItem *)item {
    SKPayment* obj = [SKPayment paymentWithProduct:item.product];
    item.payment = obj;
    [_queue addPayment:obj];
}

@end

WSIDECL_PRIVATE_BEGIN(InAppPurchaseItems, WSIObject)
<SKProductsRequestDelegate>

{
    @public
    bool _is_block;
}

WSIDECL_PRIVATE_IMPL(InAppPurchaseItems)

- (id)init {
    self = [super init];
    
    _is_block = false;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

# pragma mark delegate

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    ns::MutableArray arr;
    for (SKProduct* each in response.products) {
        InAppPurchaseItem* item = [[InAppPurchaseItem alloc] init];
        item.product = each;
        arr.add(item);
        safe_release(item);
    }
    
    d_owner.products = arr;
    
    // signal.
    [d_owner emit:kSignalSuccess result:d_owner.products];
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error {
    [d_owner emit:kSignalFailed result:error];
}

- (void)requestDidFinish:(SKRequest *)request {
    if (_is_block)
        [self unblock];
    
    // clear.
    [d_owner release];
}

WSIDECL_PRIVATE_END

@implementation InAppPurchaseItems

@synthesize identifiers = _identifiers;
@synthesize products = _products;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(InAppPurchaseItems);    
    return self;
}

- (void)dealloc {
    safe_release(_identifiers);
    safe_release(_products);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalFailed)
WSIEVENT_SIGNAL(kSignalSuccess)
WSIEVENT_END

- (void)update {
    // retain for async update.
    [self retain];
    
    SKProductsRequest* req = [[SKProductsRequest alloc] initWithProductIdentifiers:_identifiers];
    req.delegate = d_ptr;
    [req start];
    safe_release(req);
}

- (void)fetch {
    [self update];
    
    d_ptr->_is_block = true;
    [d_ptr block];
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(purchase)
WSI_BEGIN_NS(inapp)

Item::Item()
{
    
}

Item::Item(id obj)
: super(obj)
{
    
}

Item::~Item()
{
    
}

ns::String Item::description() const
{
    return this->_self.product.localizedDescription;
}

ns::String Item::title() const
{
    return this->_self.product.localizedTitle;
}

ns::String Item::identifier() const
{
    return this->_self.product.productIdentifier;
}

bool Item::is_downloadable() const
{
    return this->_self.downloadable;
}

ns::Array Item::content_lengths() const
{
    return this->_self.downloadContentLengths;
}

ns::String Item::content_version() const
{
    return this->_self.downloadContentVersion;
}

ns::Locale Item::locale() const
{
    return this->_self.product.priceLocale;
}

ns::Decimal Item::price() const
{
    return this->_self.product.price;
}

Items::Items()
{
    
}

Items::Items(ns::Set const& st)
{
    set_identifier(st);
}

Items::Items(ns::String const& str)
{
    set_identifier(str);
}

Items::~Items()
{
    
}

void Items::update()
{
    [this->_self update];
}

void Items::fetch()
{
    [this->_self fetch];
}

void Items::set_identifier(ns::Set const& idrs)
{
    this->_self.identifiers = idrs;
}

void Items::set_identifier(ns::String const& str)
{
    this->_self.identifiers = [NSSet setWithObject:str];
}

uint Items::count() const
{
    return this->_self.products.count;
}

Item Items::at(uint idx) const
{
    return [this->_self.products objectAtIndex:idx];
}

Service::Service()
{
    
}

Service::Service(id obj)
: super(obj)
{
    
}

Service::~Service()
{
    
}

bool Service::Payable()
{
    return [InAppPurchaseService Payable];
}

Service& Service::getInstance()
{
    static Service obj([objc_type shared]);
    return obj;
}

void Service::add(Item& item)
{
    [this->_self addItem:item];
}

WSI_END_NS
WSI_END_NS
WSI_END_CXX
