#ifndef UTILS_H
#define UTILS_H

#include "../Common.hpp"

namespace Utils {
    const char* RandomString(int length);

    void SetClipboard( const char* content );
    const char* GetClipboard( );
}

#endif