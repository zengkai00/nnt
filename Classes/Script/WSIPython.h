
# ifndef __NNT_SCRIPT_PYTHON_F355F4C98E2F47739353521115BA507D_H_INCLUDED
# define __NNT_SCRIPT_PYTHON_F355F4C98E2F47739353521115BA507D_H_INCLUDED

# import "NNTScript.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(NNTPython);

@interface NNTPython : NNTObject <NNTScript> {
    NNTDECL_PRIVATE(NNTPython);
}

- (BOOL)executeUTF8String:(char const*)expr;

@end

NNT_END_HEADER_OBJC

# endif