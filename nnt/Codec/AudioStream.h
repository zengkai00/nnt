
# ifndef __NNT_AUDIOSTREAM_994260C3757F40CB958C6BAAE2670905_H_INCLUDED
# define __NNT_AUDIOSTREAM_994260C3757F40CB958C6BAAE2670905_H_INCLUDED

# ifdef NNT_MACH

class AudioStreamBasicDescription;

# endif

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(audio)

class AbstractPCMAudioStream
: public cxx::Object<>
{
public:
    
    AbstractPCMAudioStream();
    ~AbstractPCMAudioStream();
    
    // 读取一个文件
    virtual bool load(core::string const&) = 0;
    
};

# ifdef NNT_MACH

class PCMAudioStreamMach
: public AbstractPCMAudioStream
{
public:
    
    PCMAudioStreamMach();
    ~PCMAudioStreamMach();
    
    virtual bool load(core::string const&);
    
protected:
    
    AudioStreamBasicDescription* _ofmt;
    core::data _buf;
    
    friend class OpenALAudioPlayer;
};

typedef PCMAudioStreamMach PCMAudioStream;

# endif

# ifdef NNT_TARGET_ANDROID

class PCMAudioStreamAndroid
: public AbstractPCMAudioStream
{
public:
    
    PCMAudioStreamAndroid();
    ~PCMAudioStreamAndroid();
    
    virtual bool load(core::string const&);
    
};

typedef PCMAudioStreamAndroid PCMAudioStream;

# endif

NNT_END_NS
NNT_END_HEADER_CXX

# endif
