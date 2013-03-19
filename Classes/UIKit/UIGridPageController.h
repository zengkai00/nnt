
# ifndef __WSI_UIKIT_GRIDPAGECONTROLLER_D78D551A3473423B985E8DFAA0CDB074_H_INCLUDED
# define __WSI_UIKIT_GRIDPAGECONTROLLER_D78D551A3473423B985E8DFAA0CDB074_H_INCLUDED

# import "UISwitchController.h"

WSI_BEGIN_HEADER_OBJC

@interface UIGridPage : UISwitchPage {
    //! rows, cols.
    uint rows, cols;
    
    //! grid.
    UIGridView* gridView;
    
}

@property (nonatomic, readonly) UIGridView* gridView;

- (id)initWithRows:(uint)rows cols:(uint)cols;

@end

WSIDECL_PRIVATE_HEAD(UIGridPageController);

@protocol UIGridPageController <UISwitchDelegate>

@optional

- (void)gridpagePageCreate:(UIGridPageController*)ctlr page:(UIGridPage*)page;
- (void)gridpagePageDidCreated:(UIGridPageController*)ctlr page:(UIGridPage*)page;

@end

@interface UIGridPageController : UISwitchController {
    
    //! array of items. (WSIUIView or other view).
    NSArray* items;
    
    //! rows, cols.
    uint rows, cols;
    
    //! class of page. default is UIGridPage.
    Class pageClass;
    
    //! page control.
    WSIUIPageControl* pageControl;
    
    //! delegate.
    id<UIGridPageController> delegate;
    
    WSIDECL_PRIVATE(UIGridPageController);
}

@property (nonatomic, retain) NSArray* items;
@property (nonatomic, assign) uint rows, cols;
@property (nonatomic, assign) Class pageClass;
@property (nonatomic, readonly) WSIUIPageControl* pageControl;
@property (nonatomic, assign) id<UIGridPageController> delegate;

@end

WSI_END_HEADER_OBJC

# endif