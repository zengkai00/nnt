
# import "Core.h"
# import "WCABadgeIndicator.h"
# import "CoreGraphic+WSI.h"

WSI_BEGIN_OBJC

@interface WCABadgeIndicator ()

- (void)setupInstance;

@end

@implementation WCABadgeIndicator

@synthesize value, badgeColor, badgeStyle, badgeLineStyle;

- (id)init {
    self = [super init];
    [self setupInstance];
    return self;
}

- (id)initWithLayer:(id)layer {
    self = [super initWithLayer:layer];
    [self setupInstance];
    return self;
}

- (void)setupInstance {
    self.backgroundColor = [WCGColor redColor].cgColor;
    self.shadowOpacity = .5f;
    
    WCGMutableTextStyle *ts = [[WCGMutableTextStyle alloc] init];
    ts.color = [WCGColor whiteColor];
    self.badgeStyle = ts;
    [ts release];
    
    WCGMutableLineStyle *ls = [[WCGMutableLineStyle alloc] init];
    ls.lineColor = [WCGColor whiteColor];
    ls.lineWidth = 2.0f;
    self.badgeLineStyle = ls;
    [ls release];
}

- (void)dealloc {
    zero_release(value);
    zero_release(badgeColor);
    zero_release(badgeStyle);
    zero_release(badgeLineStyle);
    
    [super dealloc];
}

- (void)setBadgeStyle:(WCGMutableTextStyle *)__badgeStyle {
    [NSObject refobjSet:&badgeStyle ref:__badgeStyle];    
    
    if (value == nil)
        return;
    
    CGSize sz = [badgeStyle sizeOfString:value];
    sz = CGSizeMake(sz.width + badgeStyle.fontSize, sz.height + badgeStyle.fontSize);
    self.frame = CGRectMakePtSz(self.frame.origin, sz); 
    
    real radius = badgeStyle.fontSize;
    if (sz.width <= 2 * radius) radius *= .67f;
    self.cornerRadius = radius;
}

- (void)setValue:(NSString *)__value {
    [value release];
    value = [__value retain];
    
    CGSize sz = [badgeStyle sizeOfString:value];
    sz = CGSizeMake(sz.width + badgeStyle.fontSize, sz.height + badgeStyle.fontSize);
    self.frame = CGRectMakePtSz(self.frame.origin, sz);
    
    real radius = badgeStyle.fontSize;
    if (sz.width <= 2 * radius) radius *= .67f;
    self.cornerRadius = radius;
}

- (void)setBadgeLineStyle:(WCGLineStyle *)__badgeLineStyle {
    [badgeLineStyle release];
    badgeLineStyle = [__badgeLineStyle retain];
    
    self.borderColor = badgeLineStyle.lineColor.cgColor;
    self.borderWidth = badgeLineStyle.lineWidth;
}

- (void)setBadgeColor:(WCGColor *)__badgeColor {
    [badgeColor release];
    badgeColor = [__badgeColor retain];
    
    self.backgroundColor = badgeColor.cgColor;
}

- (void)drawInContext:(CGContextRef)ctx {   
    CGRect rect = self.bounds;
    CGContextSetShadowWithColor(ctx, CGSizeMake(0, -1), .7f, [WCGColor blackColor].cgColor);
    CGContextAddTextInRect(ctx, rect, value, badgeStyle);
}

@end

WSI_END_OBJC