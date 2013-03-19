
# ifndef __WSI_PAY_UNIPAY_IPHONE_E59B8769D38A45B3BE4EBE0D38A96939_H_INCLUDED
# define __WSI_PAY_UNIPAY_IPHONE_E59B8769D38A45B3BE4EBE0D38A96939_H_INCLUDED

# import "ByPayApi.prv.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(ByPayApiPhone);

@interface ByPayApiPhone : ByPayApiController {
    WSIDECL_PRIVATE(ByPayApiPhone);
}

- (void)send:(NSData*)data;

@end

WSI_END_HEADER_OBJC

# endif