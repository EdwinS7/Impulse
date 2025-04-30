#include "Win32.hpp"
#include "../Input/Input.hpp"
#include "../Graphics/Include.hpp"

std::unordered_map<HWND, bool> Resizing;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
    switch ( msg ) {
    case WM_ENTERSIZEMOVE:
        Resizing[ hwnd ] = true;

        return 0;
    case WM_EXITSIZEMOVE:
        Resizing[ hwnd ] = false;

        Graphics.ResizeSwapChainBuffers( ( int ) LOWORD( lParam ), ( int ) HIWORD( lParam ) );

        return 0;
    case WM_MOUSEMOVE:
        Input.SetCursorPosition( Vector2( ( int ) LOWORD( lParam ), ( int ) HIWORD( lParam ) ), false );

        break;
    case WM_SETCURSOR:
        SetCursor( LoadCursorA( 0, LPCSTR( Input.GetCursorStyle( ) ) ) );

        break;
    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hwnd, msg, wParam, lParam );
}

HWND CWin32::CreateWindow_( const char* title, Vector2 position, Vector2 size, bool full_screen ) {
    WNDCLASSEX WindowClass = {
        sizeof( WindowClass ), CS_CLASSDC, WndProc,
        0L, 0L, GetModuleHandle( NULL ),
        NULL, NULL, NULL,
        NULL, title, NULL
    };

    RegisterClassEx( &WindowClass );

    DWORD WindowStyle = full_screen ? WS_POPUP : WS_OVERLAPPEDWINDOW;

    RECT DesktopRect;
    GetWindowRect( GetDesktopWindow( ), &DesktopRect );

    int W = static_cast< int16_t >( DesktopRect.right );
    int H =static_cast< int16_t >( DesktopRect.bottom );

    HWND Hwnd = CreateWindow( WindowClass.lpszClassName, title, WindowStyle,
        position.x, position.y, size.x, size.y, NULL, NULL, WindowClass.hInstance, NULL
    );

    if ( Hwnd ) {
        ShowWindow( Hwnd, SW_SHOWNORMAL );
        UpdateWindow( Hwnd );
    }

    return Hwnd;
}

void CWin32::DestroyWindow( HWND window ) {
    if ( !window )
        return;

    PostMessage( window, WM_CLOSE, 0, 0 );
}

bool CWin32::DispatchMessages( ) {
    MSG Message;

    if ( PeekMessage( &Message, nullptr, 0, 0, PM_REMOVE ) ) {
        TranslateMessage( &Message );
        DispatchMessage( &Message );

        if ( Message.message == WM_QUIT )
            return false;
    }

    return true;
}

HWND CWin32::CreateConsole( const char* title, Vector2 position, Vector2 size ) {
    if ( !AllocConsole( ) )
        return nullptr;

    HWND Hwnd = GetConsoleWindow( );

    SetConsoleTitleA( title );
    MoveWindow( Hwnd, 
        position.x, position.y, 
        size.x, size.y, 
        TRUE
    );

    FILE* fp = nullptr;
    freopen_s( &fp, "CONIN$", "r", stdin );
    freopen_s( &fp, "CONOUT$", "w", stdout );
    freopen_s( &fp, "CONOUT$", "w", stderr );

    return Hwnd;
}

void CWin32::DestroyConsole( HWND window ) {
    if ( !window )
        return;

    FreeConsole( );
}

void CWin32::MessageBox_( HWND window, const char* title, const char* content, int type ) {
    MessageBoxA( window, content, title, type );
}

Vector2 CWin32::GetScreenSize( ) {
    return Vector2( GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ) );
}

Vector2 CWin32::GetWindowPosition( HWND window_handle ) {
    RECT Rect;

    if ( GetWindowRect( window_handle, &Rect ) )
        return Vector2( static_cast< int >( Rect.left ), static_cast< int >( Rect.top ) );

    return Vector2( );
}

Vector2 CWin32::GetWindowSize( HWND window_handle ) {
    RECT Rect;

    if ( GetClientRect( window_handle, &Rect ) )
        return Vector2( static_cast< int >( Rect.right - Rect.left ), static_cast< int >( Rect.bottom - Rect.top ) );

    return Vector2( );
}

bool CWin32::IsResizing( HWND window_handle ) {
    return Resizing[ window_handle ];
}

CWin32 Win32;