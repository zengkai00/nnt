
# include "WSIFoundation.h"
# include "AppDelegate.h"

WSIAPP_BEGIN

void App::load()
{
    enable_filecache();
    set_root(ctlr);
}

WSIAPP_END
