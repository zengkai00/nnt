
# ifndef __WSI_PAY_UNIPAY_IPAD_3EA98E8E67804B19A1549DE14EE57E13_H_INCLUDED
# define __WSI_PAY_UNIPAY_IPAD_3EA98E8E67804B19A1549DE14EE57E13_H_INCLUDED

# import "ByPayApi.prv.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(ByPayApiPad);

@interface ByPayApiPad : ByPayApiController {
    WSIDECL_PRIVATE(ByPayApiPad);
}

- (void)send:(NSData*)data;

@end

WSI_END_HEADER_OBJC

# endif
