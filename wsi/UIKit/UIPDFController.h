
# ifndef __WSI_UIKIT_UIPDFCONTROLLER_20621E40DC2846608EAA8E15838E9F4A_H_INCLUDED
# define __WSI_UIKIT_UIPDFCONTROLLER_20621E40DC2846608EAA8E15838E9F4A_H_INCLUDED

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UIPDFController);

@interface UIPDFController : WSIUIViewController {
    
    WSIDECL_PRIVATE(UIPDFController);
}

- (id)initWithURL:(NSURL*)url;

@end

WSI_END_HEADER_OBJC

# endif