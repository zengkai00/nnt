
# ifndef __MAIN_CONTROLLER_27F429B047B34550AA5792F89BA9377E_H_INCLUDED
# define __MAIN_CONTROLLER_27F429B047B34550AA5792F89BA9377E_H_INCLUDED

WSIAPP_BEGIN

using namespace ::wsi;

class ShakeGrid
: public ui::Grid
{
public:
    
    ShakeGrid();
    
};

class MainController
: public ui::Controller<MainController, ShakeGrid>
{
public:
    
    void view_loaded();
    
};

WSIAPP_END

# endif