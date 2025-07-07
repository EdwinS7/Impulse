#include "Utils.hpp"

const char* CUtils::RandomString( int length ) {
    std::random_device RandomDevice;
    std::mt19937 generator( RandomDevice( ) );
    std::uniform_int_distribution<int> Distribution( 0, sizeof( m_Alphabet ) - 2 );

    char* RandomString = new char[ length + 1 ];
    for ( int i = 0; i < length; ++i ) {
        RandomString[ i ] = m_Alphabet[ Distribution( generator ) ];
    }
    RandomString[ length ] = '\0';

    return RandomString;
}

void CUtils::SetClipboard( const char* content ) {
    if ( !content ) 
        return;

    if ( !OpenClipboard( nullptr ) ) 
        return;

    EmptyClipboard( );

    size_t ContentLength = strlen( content ) + 1;
    HGLOBAL GlobalMemory = GlobalAlloc( GMEM_MOVEABLE, ContentLength );

    if ( GlobalMemory ) {
        char* ClipboardData = ( char* ) GlobalLock( GlobalMemory );

        if ( ClipboardData ) {
            strcpy_s( ClipboardData, ContentLength, content );

            GlobalUnlock( GlobalMemory );
            SetClipboardData( CF_TEXT, GlobalMemory );
        }
    }

    CloseClipboard( );
}

const char* CUtils::GetClipboard( ) {
    if ( !OpenClipboard( nullptr ) ) 
        return nullptr;

    HANDLE ClipboardHandle = GetClipboardData( CF_TEXT );
    if ( !ClipboardHandle ) {
        CloseClipboard( );
        return nullptr;
    }

    char* ClipboardText = static_cast< char* >( GlobalLock( ClipboardHandle ) );
    if ( !ClipboardText ) {
        CloseClipboard( );
        return nullptr;
    }

    static std::string StoredClipboardContent;
    StoredClipboardContent = ClipboardText;

    GlobalUnlock( ClipboardHandle );
    CloseClipboard( );

    return StoredClipboardContent.c_str( );
}

std::string CUtils::SHA256Encode( const std::string& data ) {
    m_SHA256.update( data );

    return SHA256::toString( m_SHA256.digest( ) );
}

std::string CUtils::Base64Encode( const std::string& data ) {
    return base64::to_base64( data );
}

std::string CUtils::Base64Decode( const std::string& data ) {
    return base64::from_base64( data );
}

std::string CUtils::JsonEncode( const std::string& data ) {
    m_JsonObject[ "data" ] = data;

    return m_JsonObject.dump( );
}

std::string CUtils::JsonDecode( const std::string& encoded_data ) {
    return cppcodec::base64_rfc4648::decode<std::string>( encoded_data );
}

std::string CUtils::ToLowercase( const char* input ) {
    std::string Result = input;

    for ( char& _char : Result ) {
        _char = static_cast< char >( std::tolower(
            static_cast< unsigned char >( _char )
        ) );
    }

    return Result;
}

void CUtils::_MessageBox( const char* title, const char* content, UINT flags ) {
    MessageBox( NULL, content, title, flags );
}

bool CUtils::IsInternetConnected( ) {
    DWORD Flags;

    return InternetGetConnectedState( &Flags, 0 );
}

CUtils Utils;