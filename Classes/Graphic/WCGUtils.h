
# ifndef __WSI_WSICG_UTIS_49F810F07E464EC7879F55748470B3A0_H_INCLUDED
# define __WSI_WSICG_UTIS_49F810F07E464EC7879F55748470B3A0_H_INCLUDED

# import "WCGDefines.h"

WSI_BEGIN_HEADER_OBJC

WCGRGBAColor WCGRGBAColorFromCGColor(CGColorRef color);

void WCGPushCGContext(CGContextRef context);
void WCGPopCGContext(void);

WSI_END_HEADER_OBJC

# endif