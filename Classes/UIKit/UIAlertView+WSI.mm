
# include "Core.h"
# include "UIAlertView+WSI.h"

WSI_BEGIN_OBJC

signal_t kSignalIndex0 = @"::wsi::signal::index::0";
signal_t kSignalIndex1 = @"::wsi::signal::index::1";
signal_t kSignalIndex2 = @"::wsi::signal::index::2";
signal_t kSignalIndex3 = @"::wsi::signal::index::3";
signal_t kSignalIndex4 = @"::wsi::signal::index::4";
signal_t kSignalIndex5 = @"::wsi::signal::index::5";
signal_t kSignalIndex6 = @"::wsi::signal::index::6";
signal_t kSignalIndex7 = @"::wsi::signal::index::7";
signal_t kSignalIndex8 = @"::wsi::signal::index::8";
signal_t kSignalIndex9 = @"::wsi::signal::index::9";
signal_t kSignalIndexYes = @"::wsi::signal::index::1";
signal_t kSignalIndexNo = @"::wsi::signal::index::0";

@interface WSIUIAlertView ()

+ (NSString*)lineStringByCount:(NSUInteger)cnt;

@end

@implementation WSIUIAlertView

WSIOBJECT_IMPL_NOSIGNALS;

//@synthesize showlock;
@synthesize lastSignal;

+ (NSString*)lineStringByCount:(NSUInteger)cnt {
    NSString* ret = @"";
    while (cnt--)
    {
        ret = [ret stringByAppendingString:@"\r\n"];
    };
    return ret;
}

- (id)initWithTitle:(NSString *)title message:(NSString *)message {
    self = [super initWithTitle:title message:message delegate:self cancelButtonTitle:nil otherButtonTitles:nil];
    return self;
}

- (id)initWithTitle:(NSString *)title lineCount:(NSUInteger)lineCount {
    self = [self initWithTitle:title message:[WSIUIAlertView lineStringByCount:lineCount]];
    return self;
}

- (id)initWithTitle:(NSString *)title message:(NSString *)message cancelButtonTitle:(NSString *)cancelButtonTitle okButtonTitle:(NSString *)okButtonTitle {
    self = [super initWithTitle:title message:message delegate:self cancelButtonTitle:cancelButtonTitle otherButtonTitles:okButtonTitle, nil];
    return self;
}

- (id)initWithTitle:(NSString *)title lineCount:(NSUInteger)lineCount cancelButtonTitle:(NSString*)cancelButtonTitle okButtonTitle:(NSString*)okButtonTitle {
    self = [self initWithTitle:title message:[WSIUIAlertView lineStringByCount:lineCount] cancelButtonTitle:cancelButtonTitle okButtonTitle:okButtonTitle];
    return self;
}

- (id)initWithTitle:(NSString *)title message:(NSString *)message okButtonTitle:(NSString *)okButtonTitle {
    self = [super initWithTitle:title message:message delegate:self cancelButtonTitle:nil otherButtonTitles:okButtonTitle, nil];
    return self;
}

- (id)initWithTitle:(NSString*)title lineCount:(NSUInteger)lineCount okButtonTitle:(NSString*)okButtonTitle {
    self = [self initWithTitle:title message:[WSIUIAlertView lineStringByCount:lineCount] okButtonTitle:okButtonTitle];
    return self;
}

- (void)dealloc {
    self.delegate = nil;
    //zero_release(showlock);
    
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (id)selfDelegate {
    self.delegate = self;
    return self;
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalIndex0)
    WSIEVENT_SIGNAL(kSignalIndex1)
    WSIEVENT_SIGNAL(kSignalIndex2)
    WSIEVENT_SIGNAL(kSignalIndex3)
    WSIEVENT_SIGNAL(kSignalIndex4)
    WSIEVENT_SIGNAL(kSignalIndex5)
    WSIEVENT_SIGNAL(kSignalIndex6)
    WSIEVENT_SIGNAL(kSignalIndex7)
    WSIEVENT_SIGNAL(kSignalIndex8)
    WSIEVENT_SIGNAL(kSignalIndex9)
}

/*
- (NSLock*)showlock {
    WSI_SYNCHRONIZED(self)
    if (showlock == nil)
        showlock = [[NSLock alloc] init];
    WSI_SYNCHRONIZED_END
    return showlock;
}
 */

- (void)show {
    [super show];    
    //[self.showlock lock];
}

+ (CGRect)lineRect {
    return CGRectMake(20.0f, 45.0f, 245.0f, 25.0f);
}

+ (CGRect)rectOfLine:(NSUInteger)idx {
    CGRect rc = [WSIUIAlertView lineRect];
    rc.origin.y += idx * rc.size.height;
    return rc;
}

- (void)appendSubview:(UIView*)view {
    CGRect rc = [WSIUIAlertView rectOfLine:_index++];
    view.frame = rc;
    [self addSubview:view];
}

# pragma mark delegate.

- (void)alertView:(WSIUIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    signal_t sig = nil;
    
    switch (buttonIndex) {
        case 0: sig = kSignalIndex0; break;
        case 1: sig = kSignalIndex1; break;
        case 2: sig = kSignalIndex2; break;
        case 3: sig = kSignalIndex3; break;
        case 4: sig = kSignalIndex4; break;
        case 5: sig = kSignalIndex5; break;
        case 6: sig = kSignalIndex6; break;
        case 7: sig = kSignalIndex7; break;
        case 8: sig = kSignalIndex8; break;
        case 9: sig = kSignalIndex9; break;
    }
    
    if (self.numberOfButtons == 1)
        sig = kSignalIndexYes;
    
    lastSignal = sig;
    if (sig) {
        [alertView emit:sig];
    }
    
    //[showlock unlock];
}

- (void)alertViewCancel:(UIAlertView *)alertView {
    [alertView emit:kSignalIndexNo];
    
    //[showlock unlock];
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(ui)

void AlertView::show(bool background)
{
    if (background)
    {
        //[this->_self.showlock lock];
        [this->_self performSelectorInBackground:@selector(show) withObject:nil];
    }
    else
    {
        //[this->_self show];
        [this->_self performSelectorOnMainThread:@selector(show) withObject:nil waitUntilDone:YES];
    }
}

WSI_END_NS
WSI_END_CXX