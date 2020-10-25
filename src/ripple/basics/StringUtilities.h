

#ifndef RIPPLE_BASICS_STRINGUTILITIES_H_INCLUDED
#define RIPPLE_BASICS_STRINGUTILITIES_H_INCLUDED

#include <ripple/basics/Blob.h>
#include <ripple/basics/strHex.h>

#include <boost/format.hpp>
#include <boost/optional.hpp>
#include <sstream>
#include <string>

namespace ripple {
inline static std::string sqlEscape (std::string const& strSrc)
{
    static boost::format f ("X'%s'");
    return str (boost::format (f) % strHex (strSrc));
}

inline static std::string sqlEscape (Blob const& vecSrc)
{
    size_t size = vecSrc.size ();

    if (size == 0)
        return "X''";

    std::string j (size * 2 + 3, 0);

    unsigned char* oPtr = reinterpret_cast<unsigned char*> (&*j.begin ());
    const unsigned char* iPtr = &vecSrc[0];

    *oPtr++ = 'X';
    *oPtr++ = '\'';

    for (int i = size; i != 0; --i)
    {
        unsigned char c = *iPtr++;
        *oPtr++ = charHex (c >> 4);
        *oPtr++ = charHex (c & 15);
    }

    *oPtr++ = '\'';
    return j;
}

uint64_t uintFromHex (std::string const& strSrc);

std::pair<Blob, bool> strUnHex (std::string const& strSrc);

struct parsedURL
{
    explicit parsedURL() = default;

    std::string scheme;
    std::string username;
    std::string password;
    std::string domain;
    boost::optional<std::uint16_t> port;
    std::string path;

    bool
    operator == (parsedURL const& other) const
    {
        return scheme == other.scheme &&
            domain == other.domain &&
            port == other.port &&
            path == other.path;
    }
};

bool parseUrl (parsedURL& pUrl, std::string const& strUrl);

std::string trim_whitespace (std::string str);

boost::optional<std::uint64_t> to_uint64(std::string const& s);

} 

#endif







