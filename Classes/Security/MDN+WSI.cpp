
# include "Core.h"
# include "MDN+WSI.h"

WSI_BEGIN_HEADER_C

# include <openssl/md5.h>

WSI_END_HEADER_C

WSI_BEGIN_CXX

core::string md5::digest(const core::data &data)
{
    core::data re(MD5_DIGEST_LENGTH);
    MD5(data.bytes(), data.length(), core::pointer(re));
    return core::present_cast<core::string>(re);
}

core::string md5::digest(core::string const& str)
{
    core::data re(MD5_DIGEST_LENGTH);
    MD5((byte*)str.c_str(), str.length(), core::pointer(re));
    return core::present_cast<core::string>(re);
}

core::data md5::hex(core::string const& str)
{
    core::data re(MD5_DIGEST_LENGTH);
    MD5((byte*)str.c_str(), str.length(), core::pointer(re));
    return re;
}

core::data md5::hex(core::data const& da)
{
    core::data re(MD5_DIGEST_LENGTH);
    MD5(da.bytes(), da.length(), core::pointer(re));
    return re;
}

WSI_END_CXX
