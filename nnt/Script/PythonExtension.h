
# ifndef __NNT_PYTHON_EXTENSION_6b549a47d6514aa2afb14242a8b05ca3_H_INCLUDED
# define __NNT_PYTHON_EXTENSION_6b549a47d6514aa2afb14242a8b05ca3_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(python)

// python core object.

NNT_BEGIN_NS(core)

# ifdef NNT_PYHEADERS
#   define PYNNT_TYPE(out, in) in
# else
#   define PYNNT_TYPE(out, in) out
# endif

NNTCLASS(Object);

class Object
{
public:

    typedef PYNNT_TYPE(void*, PyObject*) rawobject_type;

    Object(rawobject_type o = NULL)
        : _obj(o), _deref(false)
    {

    }

    ~Object();

    bool is_null() const
    {
        return _obj == NULL;
    }

# ifdef NNT_PYHEADERS

    operator PyObject* () const
    {
        return (PyObject*)_obj;
    }

    PyObject* py() const
    {
        return (PyObject*)_obj;
    }

# endif

    operator void* () const
    {
        return (void*)_obj;
    }

protected:

    rawobject_type _obj;
    bool _deref;

};

NNTCLASS(Argument);

class Argument
    : public Object
{
public:

    Argument(rawobject_type o)
        : Object(o)
    {

    }

    char const* to_str() const;

};

NNTCLASS(Value);

class Value
    : public Object
{
public:

    Value(char const*);
    Value(ntl::string const&);

};

NNT_END_NS

NNTCLASS(_Method);

class _Method
{
public:

    typedef struct {} *pydef_t;

    enum 
    {
        VARARGS = 0x1,
        KEYWORDS = 0x2,
        NOARGS = 0x4,
    };

    _Method();
    ~_Method();

    void set_name(ntl::string const& str);
    void set_type(enum_t v);
    void set_doc(ntl::string const& str);
    void update();

    pydef_t def()
    {
        return _def;
    }

    static core::Object success();

protected:

    void _set_imp(void* (*func)(void*, void*));

    pydef_t _def;
    ntl::string _name, _doc;
    enum_t _type;

};

template <typename implT>
class Method
    : public _Method
{

public:

    Method()
    {
        _set_imp(_imp_method);
    }

    static void* _imp_method(void* o, void* a)
    {
        return implT::method((core::Object::rawobject_type)o, (core::Object::rawobject_type)a);
    }

    static core::Object method(core::Object const&, core::Argument const&);

};

# define PYNNT_METHOD() static ::nnt::python::core::Object method(::nnt::python::core::Object const&, ::nnt::python::core::Argument const& args)

NNTCLASS(Module);

class Module
{
public:

    Module(ntl::string const& name);
    ~Module();

    template <typename methT>
    bool add(methT& mth, typename methT::pydef_t = NULL)
    {
        mth.update();
        return add(mth.def());
    }

    bool add(_Method::pydef_t);

    operator core::Object& ()
    {
        return _module;
    }

# ifdef NNT_PYHEADERS

    operator PyObject* ()
    {
        return _module;
    }

# endif

    void add(Module&);

    ntl::string const& name() const
    {
        return _name;
    }

protected:

    ntl::string _name;
    core::Object _n, _module, _d;

};

NNTCLASS(System);

class System
{
public:

    static void Set(ntl::string const& name, core::Object&);

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif