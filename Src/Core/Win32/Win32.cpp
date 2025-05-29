#include "Win32.hpp"
#include "../Input/Input.hpp"
#include "../Graphics/Include.hpp"
#include "../LuaU/Environment.hpp"

std::unordered_map<HWND, bool> Resizing;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
    switch ( msg ) {
        case WM_SIZE: {
            if ( !Resizing[ hwnd ] && wParam != SIZE_MINIMIZED )
                Graphics.ResizeSwapChainBuffers( ( int ) LOWORD( lParam ), ( int ) HIWORD( lParam ) );
            break;
        }

        case WM_ENTERSIZEMOVE: {
            Resizing[ hwnd ] = true;
            break;
        }

        case WM_EXITSIZEMOVE: {
            Resizing[ hwnd ] = false;
            Graphics.ResizeSwapChainBuffers( ( int ) LOWORD( lParam ), ( int ) HIWORD( lParam ) );
            break;
        }

        case WM_MOUSEMOVE: {
            Vector2 Position( 
                ( int ) LOWORD( lParam ), 
                ( int ) HIWORD( lParam )
            );

            Input.SetCursorPosition( Position, false );
            Callbacks.RunConnection( "cursor_move", { Position } );

            break;
        }

        case WM_SETCURSOR: {
            SetCursor( LoadCursorA( 0, LPCSTR( Input.GetCursorStyle( ) ) ) );
            break;
        }

        case WM_DESTROY:{
            PostQuitMessage( 0 );
            return 0;
        }
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

    RECT DesktopRect;
    GetWindowRect( GetDesktopWindow( ), &DesktopRect );

    DWORD WindowStyle = full_screen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
    HWND Hwnd = CreateWindow( WindowClass.lpszClassName, title, WindowStyle,
        position.x, position.y, size.x, size.y, NULL, NULL, WindowClass.hInstance, NULL
    );
    if ( !Hwnd )
        return NULL;

    ShowWindow( Hwnd, SW_SHOWNORMAL );
    UpdateWindow( Hwnd );

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

    SetConsoleTitleA( title );

    HWND Hwnd = GetConsoleWindow( );
    MoveWindow( Hwnd,
        position.x, position.y,
        size.x, size.y,
        TRUE
    );
    RedirectConsole( Hwnd );

    return Hwnd;
}

void CWin32::DestroyConsole( HWND window ) {
    if ( !window )
        return;

    FreeConsole( );
}

void CWin32::RedirectConsole( HWND hwnd ) {
    DWORD ConsolePID = 0;
    GetWindowThreadProcessId( hwnd, &ConsolePID );
    AttachConsole( ConsolePID );

    FILE* fp = nullptr;
    freopen_s( &fp, "CONIN$", "r", stdin );
    freopen_s( &fp, "CONOUT$", "w", stdout );
    freopen_s( &fp, "CONOUT$", "w", stderr );
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