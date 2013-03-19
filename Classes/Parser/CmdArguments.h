
# ifndef __WSI_CMDARGUMENTS_8d75c9578a2944b8b50e8f054bba511a_H_INCLUDED
# define __WSI_CMDARGUMENTS_8d75c9578a2944b8b50e8f054bba511a_H_INCLUDED

WSI_BEGIN_HEADER_CXX

class CmdArguments
{
public:

    CmdArguments(int argc = 0, char* argv[] = NULL);

    void set(int argc, char* argv[]);
    void clear();

    usize size() const;
    core::string& operator [] (int idx);

    core::string cmd;
    core::vector<core::string> arguments;

};

WSI_END_HEADER_CXX

# endif
