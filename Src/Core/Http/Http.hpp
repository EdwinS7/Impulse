#ifndef HTTP_H
#define HTTP_H

#include "../Common.hpp"

class CHttp {
public:
    std::string Get( const char* url );
    std::string Post( const char* url, const char* post_data );
    std::string Put( const char* url, const char* put_data );
    std::string Delete( const char* url );
} extern Http;

#endif