
# ifndef __WSI_UIKIT_INITIALVIEW_A0FDB9F5567A4EF49AC20861ADF8454D_H_INCLUDED
# define __WSI_UIKIT_INITIALVIEW_A0FDB9F5567A4EF49AC20861ADF8454D_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UIScreenImage);
WSIDECL_EXTERN_CLASS(UIInitialView);

@protocol UIInitialViewDelegate <NSObject>

@optional

- (void)initialViewWork:(UIInitialView*)view;

@end

@interface UIInitialView : WSIUIView <UIInitialViewDelegate> {
    WSIUIImageView* _image;
    WSIUIWindow* _win;
    //CFRunLoopRef _loop;
    real _delay;
    int _counter;
    UIOrientationEnable _orientationEnable;
    id<UIInitialViewDelegate> _delegate;
}

@property (nonatomic, readonly) WSIUIImageView* imageView;
@property (nonatomic, assign) id<UIInitialViewDelegate> delegate;
@property (nonatomic, assign) real delay;
@property (nonatomic, assign) UIOrientationEnable orientationEnable;

//! get screen image.
+ (UIScreenImage*)ScreenImage;

//! show.
- (void)show;

//! hide.
- (void)hide:(BOOL)animated;
- (void)hide;
- (void)hideImmed;

@end

WSI_EXTERN signal_t kSignalInitialWillComplete;
WSI_EXTERN signal_t kSignalInitialComplete;

# ifdef WSI_CXX

_CXXVIEW_DECL(UIInitialView);

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class IInitialView
: public IView
{
public:
    
    virtual void show() = 0;
    virtual void hide(bool) = 0;
    virtual void work() = 0;
    
};

class InitialView
: public View<InitialView, _CXXVIEW(UIInitialView), IInitialView>
{
    typedef View<InitialView, _CXXVIEW(UIInitialView), IInitialView> super;
    
public:
    
    InitialView()
    {
        PASS;
    }
    
    ~InitialView()
    {
        PASS;
    }
    
    virtual void show()
    {
        [this->_self show];
    }
    
    virtual void hide(bool animate = ui::animate)
    {
        [this->_self hide:animate];
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
    virtual void work()
    {
        PASS;
    }
    
    void set_delay(real d)
    {
        this->_self.delay = d;
    }
    
    real delay() const
    {
        return this->_self.delay;
    }
    
    void enable_orientation(UIOrientationEnable val)
    {
        this->_self.orientationEnable = val;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif