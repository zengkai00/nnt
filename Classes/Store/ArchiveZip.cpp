
# include "Core.h"
# include "ArchiveZip.h"
# include <sys/stat.h>

WSI_BEGIN_HEADER_C
# include "../../contrib/zip/zip.h"
WSI_END_HEADER_C

WSI_BEGIN_CXX WSI_BEGIN_NS(store)

Zip::Zip()
: zp(NULL)
{
    
}

Zip::~Zip()
{
    this->close();   
}

bool Zip::target(const core::string & file, bool overwrite)
{
    zip* nzp = zip_open(file.c_str(), overwrite ? ZIP_CREATE : ZIP_EXCL, NULL);
    if (nzp == NULL)
        return false;
    this->close();
    zp = nzp;
    return true;
}

void Zip::close()
{
    if (zp) {
        zip_close((struct zip *)zp);
        zp = NULL;
    }
}

UnZip::UnZip(core::string const& file)
{
    zp = zip_open(file.c_str(), 0, NULL);
    if (zp == nil) {
        trace_msg("failed to open :" + file);
    }
}

UnZip::~UnZip()
{
    this->close();
}

bool UnZip::open(const core::string & file)
{
    zip* nzp = zip_open(file.c_str(), 0, 0);
    if (nzp == NULL)
        return false;
    this->close();
    zp = nzp;
    return true;
}

void UnZip::close() {
    if (zp) {
        zip_close((struct zip *)zp);
        zp = NULL;
    }
}

WSI_END_NS WSI_END_CXX