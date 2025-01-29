#include "Utils.hpp"

const char Alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

const char* Utils::RandomString( int length ) {
    std::random_device rd;
    std::mt19937 generator( rd( ) );
    std::uniform_int_distribution<int> distribution( 0, sizeof( Alphabet ) - 2 );

    char* random_str = new char[ length + 1 ];

    for ( int i = 0; i < length; ++i ) {
        random_str[ i ] = Alphabet[ distribution( generator ) ];
    }

    random_str[ length ] = '\0';

    return random_str;
}

void Utils::SetClipboard( const char* content ) {
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

const char* Utils::GetClipboard( ) {
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

std::string Utils::Sha256( std::string content ) {
    SHA256 Sha256;

    return Sha256( content );
}