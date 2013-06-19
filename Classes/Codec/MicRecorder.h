
# ifndef __NNT_MIC_RECORDER_253CED61B8274FACA4BB2BFA57B86A4F_H_INCLUDED
# define __NNT_MIC_RECORDER_253CED61B8274FACA4BB2BFA57B86A4F_H_INCLUDED

# include "../Drivers/MicDevice.h"
# include "AudioFile.h"

# ifdef NNT_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(mic)

NNTDECL_PRIVATE_HEAD_CXX(Recorder);

class Recorder
: public cxx::Object<>
{
    
    NNTDECL_PRIVATE_CXX(Recorder);
  
public:
    
    Recorder(Device&);
    ~Recorder();
    
    bool start();
    bool stop();

    audio::FileType type;
    audio::FormatType format;
    
protected:
    
    Device& _dev;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# endif