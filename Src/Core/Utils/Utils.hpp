#ifndef UTILS_H
#define UTILS_H

#include "../Common.hpp"

#include "SHA256.h"
#include "base64/include/base64.hpp"

class CUtils {
private:
    SHA256 m_SHA256;

    nlohmann::json m_JsonObject;

    const char m_Alphabet[ 63 ] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

public:
    const char* RandomString( int length );

    void SetClipboard( const char* content );
    const char* GetClipboard( );

    std::string SHA256Encode( const std::string& data );

    std::string Base64Encode( const std::string& data );
    std::string Base64Decode( const std::string& data );

    std::string JsonEncode( const std::string& inputStr );
    std::string JsonDecode( const std::string& encoded_data );

    bool IsInternetConnected( );

} extern Utils;

#endif