#include "Utils.hpp"

const char* CUtils::RandomString( int length ) {
    std::random_device rd;
    std::mt19937 generator( rd( ) );
    std::uniform_int_distribution<int> distribution( 0, sizeof( m_Alphabet ) - 2 );

    char* random_str = new char[ length + 1 ];

    for ( int i = 0; i < length; ++i ) {
        random_str[ i ] = m_Alphabet[ distribution( generator ) ];
    }

    random_str[ length ] = '\0';

    return random_str;
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

bool CUtils::IsInternetConnected( ) {
    DWORD Flags;

    return InternetGetConnectedState( &Flags, 0 );
}

CUtils Utils;