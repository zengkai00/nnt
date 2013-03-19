
# ifndef MAIN_CTLR
# define MAIN_CTLR

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();
    
    ui::BevelButton btn_a, btn_b;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    void view_loaded();
    
protected:
    
    void act_a();
    void act_b();
    
};

WSIAPP_END

# endif