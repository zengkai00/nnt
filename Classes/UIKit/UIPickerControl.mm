
# import "Core.h"
# import "UIPickerControl.h"
# import "UIPickerView+WSI.h"

WSI_BEGIN_OBJC

CGFloat kUIPickerControlHeight = 44;
CGFloat kUIPickerControlItemFontSize = 22;

@interface DefaultPickerLabel : WSIUILabel

@end

@implementation DefaultPickerLabel

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.font = [UIFont boldSystemFontOfSize:kUIPickerControlItemFontSize];
    self.textAlignment = UITextAlignmentCenter;
    
    return self;
}

/*
- (void)layoutSubviews {
    [super layoutSubviews];
    
    real fz = MIN(self.bounds.size.height, self.bounds.size.width);
    fz *= .5f;
    self.font = [UIFont boldSystemFontOfSize:fz];
}
 */

- (void)dealloc {
    [super dealloc];
}

@end

@implementation UIPickerControl

@synthesize pickerView = _pickerView;
@synthesize componentItems = _componentItems;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];

    _pickerView = [[WSIUIPickerView alloc] initWithZero];
    [self addSubview:_pickerView];
    [_pickerView release];
    
    _pickerView.delegate = self;
    _pickerView.dataSource = self;
    
    return self;
}

- (void)dealloc {
    zero_release(_componentItems);
    [super dealloc];
}

- (void)reloadAllComponents {
    [self.pickerView reloadAllComponents];
}

- (void)reloadComponent:(NSInteger)component {
    [self.pickerView reloadComponent:component];
}

- (void)selectRow:(NSInteger)row inComponent:(NSInteger)component animated:(BOOL)animated {
    [self.pickerView selectRow:row inComponent:component animated:animated];
}

- (NSInteger)selectedRowInComponent:(NSInteger)component {
    return [self.pickerView selectedRowInComponent:component];
}

- (void)layoutSubviews {
    _pickerView.frame = self.bounds;
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalSelectChanged)
WSIEVENT_END

# pragma mark datasource.

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return [self.componentItems count];
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    NSArray* arr = (NSArray*)[self.componentItems objectAtIndex:component];
    return [arr count];
}

# pragma mark delegate.

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    NSArray* arr = (NSArray*)[self.componentItems objectAtIndex:component];
    id obj = [arr objectAtIndex:row];
    if ([obj isKindOfClass:[NSString class]])
        return (NSString*)obj;
    return nil;
}

- (UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view {
    DefaultPickerLabel* lbl = nil;
    if ([view isKindOfClass:[DefaultPickerLabel class]])
        lbl = (DefaultPickerLabel*)view;
    if (view == nil)
        lbl = [[[DefaultPickerLabel alloc] initWithZero] autorelease];
    lbl.text = [self pickerView:pickerView titleForRow:row forComponent:component];
    return lbl;
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    WSINSIndexPath* ip = [[WSINSIndexPath alloc] init];
    ip.row = row;
    ip.section = component;
    [self emit:kSignalSelectChanged result:ip];
    safe_release(ip);
}

- (CGFloat)pickerView:(UIPickerView *)pickerView rowHeightForComponent:(NSInteger)component {
    return kUIPickerControlHeight;
}

- (CGFloat)pickerView:(UIPickerView *)pickerView widthForComponent:(NSInteger)component {
    CGRect rc = self.bounds;
    CGFloat width = rc.size.width;
    width -= 28;
    NSUInteger cnt = [self numberOfComponentsInPickerView:pickerView];
    return width / cnt;
}

@end

_CXXCONTROL_IMPL_BEGIN(UIPickerControl)

- (NSArray*)componentItems {
    return nil;
}

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    ::wsi::ui::IPickerControl* obj = (::wsi::ui::IPickerControl*)self._cxxobj;
    return obj->count_components();
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    ::wsi::ui::Picker* obj = interface_cast(self._cxxobj, ::wsi::ui::Picker);
    return obj->at(component).count();
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    ::wsi::ui::Picker* obj = interface_cast(self._cxxobj, ::wsi::ui::Picker);
    ::wsi::ui::PickerSection& sec = obj->at(component);
    id da = sec.at(row);
    if ([da isKindOfClass:[NSString class]])
        return (NSString*)da;
    return nil;
}

- (UIView*)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view {
    ::wsi::ui::Picker* obj = interface_cast(self._cxxobj, ::wsi::ui::Picker);
    ::wsi::ui::Picker::IndexPath ip(component, row);
    ::wsi::ui::PickerItem* item = obj->makeitem(ip);
    if (item) {
        // reference manage.
        ::wsi::ui::IView* view = interface_cast(item, ::wsi::ui::IView);
        UIView* ret = [view->nsobject() consign];
        view->drop();
        
        // set.
        ::wsi::ui::PickerItemObject& var = obj->at(component).object_at(row);
        var.view = item;
        item->set_object(&var);
        item->update();
        
        return ret;
    }
    
    return [super pickerView:pickerView viewForRow:row forComponent:component reusingView:view];
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    ::wsi::ui::Picker* obj = interface_cast(self._cxxobj, ::wsi::ui::Picker);
    ::wsi::ui::PickerSection& sec = obj->at(component);
    ::wsi::ui::PickerItemObject& io = sec.object_at(row);
    ::wsi::ui::PickerItem* item = (::wsi::ui::PickerItem*)io.view;
    
    // callback.
    io.emit(kSignalSelected);
    item->selected();
    
    // emit.
    WSINSIndexPath* ip = [[WSINSIndexPath alloc] init];
    ip.row = row;
    ip.section = component;
    [self emit:kSignalSelectChanged result:ip data:&io];
    safe_release(ip);
}

_CXXCONTROL_IMPL_END

@implementation UIDrumPickerControl

@synthesize items = _items;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    return self;
}

- (void)dealloc {
    safe_release(_items);
    [super dealloc];
}

@end

static void __gsf_pickerdesktop_ok(WSIEventObj* evt) {
    WSIUIDesktop* desk = (WSIUIDesktop*)[(id)evt.sender attachFind:@"desk"];
    SEL act = ((NSObjectSel*)[(id)evt.sender storeFind:@"action"]).selector;
    id target = [(id)evt.sender attachFind:@"target"];
    UIPickerControl* picker = (UIPickerControl*)[(id)evt.sender attachFind:@"picker"];
    if (act && target) {
        [target performSelector:act withObject:picker];
    }
    [desk close];
}

static void __gsf_pickerdesktop_cancel(WSIEventObj* evt) {
    WSIUIDesktop* desk = (WSIUIDesktop*)[(id)evt.sender attachFind:@"desk"];
    SEL act = ((NSObjectSel*)[(id)evt.sender storeFind:@"action"]).selector;
    id target = [(id)evt.sender attachFind:@"target"];
    UIPickerControl* picker = (UIPickerControl*)[(id)evt.sender attachFind:@"picker"];
    if (act && target) {
        [target performSelector:act withObject:picker];
    }
    [desk close];
}

UIPickerControl* WSIOpenPickerDesktop(NSArray* items, SEL ok, SEL cancel, id target) {    
    WSIUIDesktop *desk = [WSIUIDesktop desktop];
    
    wsi::CGRectLayoutVBox lyt(desk.bounds);
    wsi::CGRectLayoutLinear lnr(lyt);
    lnr.add_flex(1);
    lnr.add_pixel(kUIPickerViewHeight + 44);
    lyt.add_pixel(lnr.get_comp(0));
    
    UIViewController *picker = [[UIViewController alloc] init];        
    UIPickerControl* ctl_pick = [[UIPickerControl alloc] initWithZero];
    ctl_pick.componentItems = items;
    ctl_pick.pickerView.showsSelectionIndicator = YES;
    picker.view = ctl_pick;
    [ctl_pick release];
    
    UINavigationController *navi = [[UINavigationController alloc] initWithRootViewController:picker];
    [desk storeSet:@"navi" obj:navi];
    [desk storeSet:@"picker" obj:picker]; 
    [picker release];
    [navi release];
    
    navi.view.frame = lyt.fill();
    navi.view.backgroundColor = [UIColor blackColor];   
    [desk addSubview:navi.view];
    
    WSIUIBarButtonItem *btn_ok = [[WSIUIBarButtonItem alloc] 
                                  initWithTitle:_W(@"ok") 
                                  style:(UIBarButtonItemStyle)UIBarButtonSystemItemDone];
    picker.navigationItem.rightBarButtonItem = btn_ok;
    [btn_ok connect:kSignalButtonClicked func:__gsf_pickerdesktop_ok];
    [btn_ok attachSet:@"desk" obj:desk];
    [btn_ok storeSet:@"action" obj:[NSObjectSel objectWithSel:ok]];
    [btn_ok attachSet:@"target" obj:target];
    [btn_ok attachSet:@"picker" obj:ctl_pick];
    [btn_ok release];        
    
    WSIUIBarButtonItem *btn_cancel = [[WSIUIBarButtonItem alloc] 
                                      initWithTitle:_W(@"cancel") 
                                      style:(UIBarButtonItemStyle)UIBarButtonItemStyleDone];
    picker.navigationItem.leftBarButtonItem = btn_cancel;
    [btn_cancel connect:kSignalButtonClicked func:__gsf_pickerdesktop_cancel];
    [btn_cancel attachSet:@"desk" obj:desk];
    [btn_cancel storeSet:@"action" obj:[NSObjectSel objectWithSel:cancel]];
    [btn_cancel attachSet:@"target" obj:target];
    [btn_cancel attachSet:@"picker" obj:ctl_pick];
    [btn_cancel release];           
    
    [desk show:YES];
    return ctl_pick;
}

_CXXCONTROL_IMPL(UIDrumPickerControl);

WSI_END_OBJC