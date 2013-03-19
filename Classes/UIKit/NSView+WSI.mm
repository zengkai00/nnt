
# import "Core.h"
# import "NSView+WSI.h"
# import "CoreGraphic+WSI.h"

WSI_BEGIN_OBJC

@implementation NSView (WSI)

- (id)initWithZero {
    self = [self initWithFrame:NSZeroRect];
    return self;
}

- (void)moveToCenter:(NSPoint)pos {
    NSRect rc = self.frame;
    pos.x -= rc.size.width * .5f;
    pos.y -= rc.size.height * .5f;
    [self moveTo:pos];
}

- (void)moveTo:(NSPoint)pos {
    NSRect rc = self.frame;
    rc.origin = pos;
    [self setFrame:rc];
}

@end

@implementation WSINSView

@synthesize backgroundFill;

WSIOBJECT_IMPL;

- (void)dealloc {
    [backgroundFill release];
    
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)drawRect:(NSRect)dirtyRect {
    CGContextRef ctx = WCGGetCurrentContext();
    
    if (backgroundFill) {
        [backgroundFill fillRect: ::wsi::cg::conv(dirtyRect)
                       inContext:ctx];
    }
}

- (void)resizeSubviewsWithOldSize:(NSSize)oldBoundsSize {    
    [self layoutSubviews];
}

- (void)layoutSubviews {
    PASS;
}

@end

@implementation _cxx_nsview_wrapper

@synthesize _cxxobj;

- (void)dealloc {
    if (_cxxobj)
        _cxxobj->Destroy();
    [super dealloc];
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    if (_cxxobj)
        _cxxobj->layout_subviews();
}

- (void)drawRect:(NSRect)rect {
    [super drawRect:rect];
    
    if (_cxxobj)
        _cxxobj->draw(WCGGetCurrentContext(), rect);
}

- (void*)object {
    return _cxxobj->cxxobject();
}

@end

WSI_END_OBJC