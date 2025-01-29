#ifndef WIN32_H
#define WIN32_H

#include "../Common.hpp"
#include "../Graphics/Types.hpp"

namespace Win32 {
    // NOTE: C and their stupid fucking type definition names are the reason for the _
    HWND CreateWindow_( const char* title, int w, int h, bool full_screen );
    void DestroyWindow( HWND window );
    bool DispatchMessages( );

    HWND CreateConsole( const char* title, int x, int y, int w, int h );
    void DestroyConsole( HWND window );

    void MessageBox_( HWND window, const char* title, const char* content, int type );

    Vector2 GetScreenSize( );
};

#endif