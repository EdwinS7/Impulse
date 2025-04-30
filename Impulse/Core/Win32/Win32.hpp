#ifndef WIN32_H
#define WIN32_H

#include "../Common.hpp"
#include "../Graphics/Types.hpp"

class CWin32 {
public:
    // NOTE: C and their stupid fucking bs are the reason for the _
    HWND CreateWindow_( const char* title, Vector2 position, Vector2 size, bool full_screen );
    void DestroyWindow( HWND window );
    bool DispatchMessages( );

    HWND CreateConsole( const char* title, Vector2 position, Vector2 size );

    void DestroyConsole( HWND window );

    void MessageBox_( HWND window, const char* title, const char* content, int type );

    Vector2 GetScreenSize( );

    Vector2 GetWindowPosition( HWND window_handle );
    Vector2 GetWindowSize( HWND window_handle );

    bool IsResizing( HWND window_handle );
} extern Win32;

#endif