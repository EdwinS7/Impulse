#ifndef HTTP_H
#define HTTP_H

#include "../Common.hpp"

class Http {
public:
    static std::string Get( const char* url );
    static std::string Post( const char* url, const char* post_data );
    static std::string Put( const char* url, const char* put_data );
    static std::string Delete( const char* url );
};

#endif