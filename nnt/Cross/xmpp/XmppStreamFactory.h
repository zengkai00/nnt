
# ifndef __XMPP_STREAM_FACTORY_12E86F5B54C046F6B2B485032DA4B87F_H_INCLUDED
# define __XMPP_STREAM_FACTORY_12E86F5B54C046F6B2B485032DA4B87F_H_INCLUDED

# include "XmppResponseFactory.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(xmpp)

class StreamFactory
: public AbstractResponseFactory
{
    typedef AbstractResponseFactory super;
    
public:
    
    StreamFactory();
    ~StreamFactory();
    
    virtual bool process(xmlnode_t const*);
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif