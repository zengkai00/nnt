
# ifndef __WSI_JUICECONTROLLER_62B9F4E96EB94EB2937B8B42D3A81ABB_H_INCLUDED
# define __WSI_JUICECONTROLLER_62B9F4E96EB94EB2937B8B42D3A81ABB_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(NSJuiceController)

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "JuiceImpl.h"

JUICEIMPL_BEGIN

struct _Types
{
    typedef ::juice::ColorRGBA<float> color_type;
    typedef ::juice::Vertex3d<float> vertex_type;
    typedef uint index_type;
    typedef ::juice::cocoa::Matrix matrix_type;
    typedef ::juice::Rect<vertex_type, ::juice::Size2d<float> > viewport_type;
    typedef ::juice::BoundingBox<vertex_type> bounding_type;
    typedef ::wsi::core::vector< ::juice::renderentity_wrapper> entities_type;
    typedef ::wsi::core::vector<vertex_type> vertices_type;
    typedef ::wsi::core::vector<index_type> indexies_type;
    typedef ::wsi::core::vector<color_type> colors_type;
};

class Material
: public ::juice::Material<Material, _Types>
{
};

struct Types
: _Types
{
    typedef Material material_type;
};

class Driver
: public juice::OpenGLDriver<Driver, Types>
{
    typedef juice::OpenGLDriver<Driver, Types> super;
    
public:
    Driver(Driver* obj): super(obj) {}
    
};

class Tree
: public ::juice::Tree<Tree, Types>,
public ::juice::TreeRender<Tree, Types>
{
    
};

class ScreenManager
: public ::juice::ScreenManager<ScreenManager, Driver>
{
    typedef juice::ScreenManager<ScreenManager, Driver> super;
    
public:    
    ScreenManager();
    ~ScreenManager();
        
    void next_frame();
    
protected:
    Tree* _tree;
};

JUICEIMPL_END

# endif

WSI_BEGIN_HEADER_OBJC

@interface NSJuiceController : WSINSViewController

@end

WSI_END_HEADER_OBJC

# endif