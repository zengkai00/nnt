
# ifndef __NNTWTL_SYSTEM_c67fe536f64a45a39cc9ca6e5f7fdc53_H_INCLUDED
# define __NNTWTL_SYSTEM_c67fe536f64a45a39cc9ca6e5f7fdc53_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)
NNT_BEGIN_NS(sys)

# ifdef NNT_KERNEL_SPACE

class IrqLevel
{
public:

    IrqLevel();

    void higher();
    void raise(ubyte);
    void back();

    static ubyte Current();
    ubyte current;

protected:

    ubyte _next;

};

# endif

NNT_END_NS
NNT_END_NS
NNT_END_NS

# endif
