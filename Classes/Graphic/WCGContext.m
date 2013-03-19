
# import "Core.h"
# import "WCGContext.h"
# import "WCGUtils.h"
# import "CoreGraphic+WSI.h"

WSI_BEGIN_OBJC

void CGContextAddTextAtPoint(CGContextRef context, CGPoint point, NSString *str, WCGTextStyle *style) {
    if ( style.color == nil ) 
        return;
    
    WCGPushCGContext(context);    
    CGContextSaveGState(context);
	CGColorRef textColor = style.color.cgColor;
	
	CGContextSetStrokeColorWithColor(context, textColor);	
	CGContextSetFillColorWithColor(context, textColor);    
             
# ifdef WSI_TARGET_IOS
	UIFont *theFont = [style uiFont];
	[str drawAtPoint:point withFont:theFont];
# endif
    
# ifdef WSI_TARGET_MAC
    CGContextAddTextAtPoint(context, point, str, style);
# endif
	
	CGContextRestoreGState(context);
	WCGPopCGContext();
}

void CGContextAddTextInRect(CGContextRef context, CGRect rc, NSString *str, WCGTextStyle *style) {
    if ( style.color == nil )
        return;
    //rc = CGRectIntegral(rc);
    
    WCGPushCGContext(context);
    CGContextSaveGState(context);
	CGColorRef textColor = style.color.cgColor;
	
	CGContextSetStrokeColorWithColor(context, textColor);	
	CGContextSetFillColorWithColor(context, textColor);			
	[style.textShadow setInContext:context];
        
    WCGTextStyle *theStyle = nil;
    
    if (style.scaleToFit) {
        theStyle = [style copy];
        real val = MIN(rc.size.height, rc.size.width);
        real nfsz = val - theStyle.scaleToFitOffset - theStyle.scaleToFitOffset;
        if (nfsz > theStyle.fontSize) {
            if (nfsz > theStyle.scaleToFitMax)
                nfsz = theStyle.scaleToFitMax;
            ((WCGMutableTextStyle*)theStyle).fontSize = nfsz;
        }
    } else {
        theStyle = [style retain];
    }        
        
    CGSize const sz_str = [theStyle sizeOfString:str];
    CGSize const sz_org = rc.size;
    uint x = 0, y = 0, width = 0;
    
    if (MASK_CHECK(WCGAlignmentLeft, theStyle.alignment)) {
        x = 0;
        width = sz_org.width;
    } else if (MASK_CHECK(WCGAlignmentRight, theStyle.alignment)) {
        if (sz_org.width < sz_str.width) {
            x = 0;
            width = sz_org.width;
        }
        else {
            x = sz_org.width - sz_str.width;
            width = sz_str.width;
        }
    } else if (MASK_CHECK(WCGAlignmentCenterH, theStyle.alignment)) {
        if (sz_org.width < sz_str.width) {
            x = 0;
            width = sz_org.width;
        } else {
            x = (sz_org.width - sz_str.width) * .5f;
            width = sz_str.width;
        }
    }
    
    if (MASK_CHECK(WCGAlignmentTop, theStyle.alignment)) {
        y = 0;
    } else if (MASK_CHECK(WCGAlignmentBottom, theStyle.alignment)) {
        if (sz_org.height < sz_str.height) {
            y = 0;
        }
        else {
            y = sz_org.height - sz_str.height;
        }
    } else if (MASK_CHECK(WCGAlignmentCenterV, theStyle.alignment)) {
        if (sz_org.height < sz_str.height) {
            y = 0;
        } else {
            y = (sz_org.height - sz_str.height) * .5f;
        }
    }    
    
# ifdef WSI_TARGET_IOS
    CGPoint pt = CGPointAddXY(rc.origin, x, y);
# else
    NSPoint pt = NSMakePoint(rc.origin.x + x, rc.origin.y + y);
# endif
    
# ifdef WSI_TARGET_IOS
    UIFont *theFont = [theStyle uiFont];
# endif
    
    if (style.charRotation == 0) {
        
# ifdef WSI_TARGET_IOS        
        [str drawAtPoint:pt 
                forWidth:width 
                withFont:theFont 
                fontSize:theStyle.fontSize 
           lineBreakMode:theStyle.linebreak 
      baselineAdjustment:UIBaselineAdjustmentNone];
# else
        [str drawAtPoint:pt withAttributes:[theStyle uiFontAttributes]];
# endif
        
    } else {
        // for each char.
# ifdef WSI_TARGET_IOS
        CGPoint cur_pt = pt;
# else
        NSPoint cur_pt = pt;
# endif
        
        for (int i = 0; i < [str length]; ++i) {
            unichar ch = [str characterAtIndex:i];
            NSString *cur_str = [NSString stringWithCharacters:&ch length:1];
            
# ifdef WSI_TARGET_IOS
            CGSize cur_sz = [cur_str sizeWithFont:theFont];
# else
            NSSize cur_sz = [cur_str sizeWithAttributes:[theStyle uiFontAttributes]];
# endif
            
            real const sz_half_w = cur_sz.width * .5f;
            real const sz_half_h = cur_sz.height * .5f;
            
            CGContextSaveGState(context);
            CGContextTranslateCTM(context, cur_pt.x + sz_half_w, cur_pt.y + sz_half_h);
            CGContextRotateCTM(context, theStyle.charRotation);    
            
# ifdef WSI_TARGET_IOS
            [cur_str drawAtPoint:CGPointMake(-sz_half_w, -sz_half_h) 
                        withFont:theFont];
# else
            [cur_str drawAtPoint:NSMakePoint(-sz_half_w, -sz_half_h)
                  withAttributes:[theStyle uiFontAttributes]];
# endif
            
            CGContextRestoreGState(context);
            
            cur_pt.x += cur_sz.width;
        }
    }
	
	CGContextRestoreGState(context);
	WCGPopCGContext();
    
    [theStyle release];
}

void CGContextAddBoundsRect(CGContextRef ctx, CGRect rect, CGFloat radius, BOOL lt, BOOL rt, BOOL lb, BOOL rb) {
    CGFloat x = rect.origin.x, y = rect.origin.y, w = rect.size.width, h = rect.size.height;
    if (radius) {
        CGFloat lt_w = 0, lt_h = 0, rt_w = 0, rt_h = 0, lb_w = 0, lb_h = 0, rb_w = 0, rb_h = 0;
        if (lt) {
            lt_w = radius;
            lt_h = radius;
        }
        if (rt) {
            rt_w = radius;
            rt_h = radius;
        }
        if (lb) {
            lb_w = radius;
            lb_h = radius;
        }
        if (rb) {
            rb_w = radius;
            rb_h = radius;
        }
        
        if (lt)
            CGContextAddArc(ctx, x + radius, y + radius, radius, M_PI, M_PI + M_PI_2, 0);
        
        CGContextMoveToPoint(ctx, x + lt_w, y);
        CGContextAddLineToPoint(ctx, x + w - rt_w, y);
        
        if (rt)
            CGContextAddArc(ctx, x + w - radius, y + radius, radius, M_PI + M_PI_2, M_PI + M_PI, 0);
        
        CGContextMoveToPoint(ctx, x + w, y + rt_h);
        CGContextAddLineToPoint(ctx, x + w, y + h - rb_h);
        
        if (rb)
            CGContextAddArc(ctx, x + w - radius, y + h - radius, radius, 0, M_PI_2, 0);
        
        CGContextMoveToPoint(ctx, x + w - rb_w , y + h);
        CGContextAddLineToPoint(ctx, x + lb_w, y + h);
        
        if (lb)
            CGContextAddArc(ctx, x + radius, y + h - radius, radius, M_PI_2, M_PI, 0);
        
        CGContextMoveToPoint(ctx, x, y + h - lb_h);
        CGContextAddLineToPoint(ctx, x, y + lt_h);
        
    } else {
        CGContextAddRect(ctx, rect);
    }
}

void CGPathAddBoundsRect(CGMutablePathRef path, CGRect rect, CGFloat radius, BOOL lt, BOOL rt, BOOL lb, BOOL rb) {
    CGFloat x = rect.origin.x, y = rect.origin.y, w = rect.size.width, h = rect.size.height;
    if (radius) {
        CGFloat lt_w = 0, lt_h = 0, rt_w = 0, rt_h = 0, lb_w = 0, lb_h = 0, rb_w = 0, rb_h = 0;
        if (lt) {
            lt_w = radius;
            lt_h = radius;
        }
        if (rt) {
            rt_w = radius;
            rt_h = radius;
        }
        if (lb) {
            lb_w = radius;
            lb_h = radius;
        }
        if (rb) {
            rb_w = radius;
            rb_h = radius;
        }
        
        if (lt)
            CGPathAddArc(path, nil, x + radius, y + radius, radius, M_PI, M_PI + M_PI_2, 0);
        
        CGPathMoveToPoint(path, nil, x + lt_w, y);
        CGPathAddLineToPoint(path, nil, x + w - rt_w, y);
        
        if (rt)
            CGPathAddArc(path, nil, x + w - radius, y + radius, radius, M_PI + M_PI_2, M_PI + M_PI, 0);
        
        CGPathMoveToPoint(path, nil, x + w, y + rt_h);
        CGPathAddLineToPoint(path, nil, x + w, y + h - rb_h);
        
        if (rb)
            CGPathAddArc(path, nil, x + w - radius, y + h - radius, radius, 0, M_PI_2, 0);
        
        CGPathMoveToPoint(path, nil, x + w - rb_w , y + h);
        CGPathAddLineToPoint(path, nil, x + lb_w, y + h);
        
        if (lb)
            CGPathAddArc(path, nil, x + radius, y + h - radius, radius, M_PI_2, M_PI, 0);
        
        CGPathMoveToPoint(path, nil, x, y + h - lb_h);
        CGPathAddLineToPoint(path, nil, x, y + lt_h);
        
    } else {
        CGPathAddRect(path, nil, rect);
    }
}

void CGContextDrawShadowLine(CGContextRef ctx, CGPoint pt0, CGPoint pt1, CGColorRef __color, CGFloat len, CGSize offset) {
    CGContextSaveGState(ctx);
    
    CGContextSetLineWidth(ctx, 1);

    WCGColor *color = [WCGColor colorWithCGColor:__color];
    uint rgba = [color valueRGBA];
    real alpha_offset = RGBA_ALPHA_P(rgba) / len;
    int offset_x = 0;
    if (offset.width < 0) 
        offset_x = 1;
    else if (offset.width > 0) 
        offset_x = -1;
    int offset_y = 0;
    if (offset.height < 0) 
        offset_y = 1;
    else if (offset.height > 0) 
        offset_y = -1;
    
    WCGColor *tgt_color = [WCGColor colorWithCGColor:color.cgColor];
    for (uint i = 0; i < len; ++i) {                
        CGContextSetStrokeColorWithColor(ctx, tgt_color.cgColor);
        CGContextMoveToPoint(ctx, pt0.x, pt0.y);
        CGContextAddLineToPoint(ctx, pt1.x, pt1.y);
        CGContextStrokePath(ctx);
        
        tgt_color = [WCGColor addWith:tgt_color r:0 g:0 b:0 a:-alpha_offset];
                
        pt0.x += offset_x;
        pt1.x += offset_x;
        pt0.y += offset_y;
        pt1.y += offset_y;
    }
    
    CGContextRestoreGState(ctx);
}

void CGContextDrawImageOri(CGContextRef c, CGRect rect, CGImageRef image) {
    CGContextSaveGState(c);
    CGContextTranslateCTM(c, rect.origin.x, rect.origin.y + rect.size.height);
	CGContextScaleCTM(c, 1.0f, -1.0f);
	CGContextDrawImage(c, CGRectMake(0, 0, rect.size.width, rect.size.height), image);
    CGContextRestoreGState(c);
}

void CGContextFillImageMask(CGContextRef c, CGRect rect, CGImageRef image, CGColorRef color) {
    CGSize img_sz = CGSizeMake(CGImageGetWidth(image), CGImageGetHeight(image));
    
    WCGBeginImageContext(img_sz);

    CGContextRef ctx = WCGGetCurrentContext();
    CGRect img_rc = CGRectMakeSz(img_sz);
    
    // mask.
    CGContextDrawImage(ctx, img_rc, image);
    
    // replace color.
    CGContextSetFillColorWithColor(ctx, color);
    CGContextSetBlendMode(ctx, kCGBlendModeColor);
    CGContextFillRect(ctx, img_rc);
    
    // clip.
    CGContextSetBlendMode(ctx, kCGBlendModeDestinationIn);
    CGContextDrawImage(ctx, img_rc, image);
    
    MAC_IOS_SELECT(NSImage, UIImage)* tgt = WCGGetImageFromCurrentImageContext();
    WCGEndImageContext();
    
# ifdef WSI_TARGET_IOS
    CGContextDrawImage(c, rect, tgt.CGImage);
# endif
    
    tgt = nil;
}

void WCGBeginImageContext(CGSize size) {
# ifdef WSI_TARGET_IOS
     UIGraphicsBeginImageContext(size);
# endif
}

void WCGEndImageContext() {
# ifdef WSI_TARGET_IOS
    UIGraphicsEndImageContext();
# endif
}

CGContextRef WCGGetCurrentContext() {
# ifdef WSI_TARGET_IOS
    return UIGraphicsGetCurrentContext();
# endif
    
# ifdef WSI_TARGET_MAC
    return (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
# endif
    
    return 0;
}

MAC_IOS_SELECT(NSImage, UIImage)* WCGGetImageFromCurrentImageContext() {
# ifdef WSI_TARGET_IOS
    return UIGraphicsGetImageFromCurrentImageContext();
# endif
    
# ifdef WSI_TARGET_MAC
# endif
    
    return 0;
}

WSI_END_OBJC