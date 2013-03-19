
# import "Core.h"
# import "UISlider+WSI.h"
# import "Layout.h"

WSI_BEGIN_OBJC

@implementation WSIUISlider

WSIOBJECT_IMPL_NOSIGNALS;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    [self addTarget:self action:@selector(_value_changed) forControlEvents:UIControlEventValueChanged];
    
    return self;
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalValueChanged);
}

- (void)setValue:(float)val {
    [super setValue:val];
    [self emit:kSignalValueChanged];
}

- (void)changeValue:(float)val {
    [super setValue:val];
}

- (void)_value_changed {
    [self emit:kSignalValueChanged];
}

@end

@interface UISliderTitleValue ()
- (void)__init;
@end

@implementation UISliderTitleValue

@synthesize title, value, slider;
@dynamic maximumValue, minimumValue, currentValue;

- (void)__init {
    title = [[WSIUILabel alloc] initWithZero];
    slider = [[WSIUISlider alloc] initWithZero];
    value = [[WSIUILabel alloc] initWithZero];
    
    [slider connect:kSignalValueChanged sel:@selector(_act_value_changed) obj:self];
    
    [self addSubview:title];
    [self addSubview:slider];
    [self addSubview:value];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    [self __init];
    return self;
}

- (id)initWith:(NSString*)__title max:(float)max min:(float)min cur:(float)cur {
    self = [super initWithZero];
    self.title.text = __title;
    self.maximumValue = max;
    self.minimumValue = min;
    self.currentValue = cur;
    
    value.text = wsi::tostr(cur);
    [self setNeedsLayout];
    
    return self;
}

+ (id)sliderWith:(NSString*)title max:(float)max min:(float)min cur:(float)cur {
    return [[[UISliderTitleValue alloc] initWith:title max:max min:min cur:cur] autorelease];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalValueChanged)
WSIEVENT_END

- (void)dealloc {
    zero_release(title);
    zero_release(value);
    zero_release(slider);
    
    [super dealloc];
}

- (void)_act_value_changed {
    value.text = wsi::tostr(slider.value);
    
    // changed.
    [self emit:kSignalValueChanged];
    
    [self setNeedsLayout];
}

- (void)layoutSubviews {
    wsi::CGRectLayoutHBox lyt(self.bounds);
    wsi::CGRectLayoutLinear lnr(lyt);
    lnr << (wsi::pixel)[title textSize].width << (wsi::flex)1 << (wsi::pixel)[value textSize].width;
    title.frame = lyt.add_pixel(lnr.start());
    slider.frame = lyt.add_pixel(lnr.next());
    value.frame = lyt.add_pixel(lnr.next());
}

- (void)setMaximumValue:(float)val {
    slider.maximumValue = val;
}

- (float)maximumValue {
    return slider.maximumValue;
}

- (void)setMinimumValue:(float)val {
    slider.minimumValue = val;
}

- (float)minimumValue {
    return slider.minimumValue;
}

- (void)setCurrentValue:(float)val {
    slider.value = val;
    value.text = wsi::tostr(val);
}

- (float)currentValue {
    return slider.value;
}

@end

@implementation UISliderTitleValueReset

@synthesize reset;
@synthesize defaultValue;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    reset = [[UIBevelButton alloc] initWithZero];
    reset.text = @"RESET";
    reset.backgroundColor = [UIColor blueColor];
    [reset connect:kSignalButtonClicked sel:@selector(_act_reset) obj:self];
    [self addSubview:reset];
    
    return self;
}

+ (id)sliderWith:(NSString *)__title max:(float)max min:(float)min cur:(float)cur {
    return [[[UISliderTitleValueReset alloc] initWith:__title max:max min:min cur:cur] autorelease];
}

- (void)dealloc {
    zero_release(reset);
    
    [super dealloc];
}

- (void)setCurrentValue:(float)val {
    defaultValue = val;
    
    [super setCurrentValue:val];
}

- (void)layoutSubviews {
    wsi::CGRectLayoutHBox lyt(self.bounds);
    wsi::CGRectLayoutLinear lnr(lyt);
    lnr << (wsi::pixel)[title textSize].width << (wsi::flex)1 << (wsi::pixel)[value textSize].width;
    lnr << (wsi::pixel)[reset textSize].width;
    title.frame = lyt.add_pixel(lnr.start());
    slider.frame = lyt.add_pixel(lnr.next());
    value.frame = lyt.add_pixel(lnr.next());
    reset.frame = lyt.add_pixel(lnr.next());
}

- (void)_act_reset {
    slider.value = defaultValue;
    //[self emit:kSignalValueChanged];
    [self performSelector:@selector(_act_value_changed)];
}

@end

WSI_END_OBJC