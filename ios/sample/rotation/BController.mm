
# import "WSIFoundation.h"
# import "BController.h"

WSIAPP_BEGIN_OBJC

@implementation BView

- (void)layoutSubviews {
    if (self.isLandscape) {
        trace_msg(@"bview is landscape.");
    } else if (self.isPortrait) {
        trace_msg(@"bview is portrait.");
    }
}

@end

@implementation BCtlr

- (void)loadView {
    BView* view = [[BView alloc] initWithZero];
    self.view = view;
    [view release];
    
    view.backgroundColor = [UIColor orangeColor];
}

- (void)viewController:(WSIUIViewController *)ctlr orientation:(UIInterfaceOrientation)orientation {
    trace_msg(@"BCtlr is rotated.");
}

@end

WSIAPP_END_OBJC