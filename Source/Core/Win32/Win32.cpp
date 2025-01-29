#include "Win32.hpp"

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
    static bool IsResizing = false;

    switch ( msg ) {
    case WM_SIZE:
        // NOTE: DirectX stuff here.

        return 0;
    case WM_ENTERSIZEMOVE:
        IsResizing = true;

        return 0;
    case WM_EXITSIZEMOVE:
        // NOTE: DirectX stuff here.

        IsResizing = false;

        return 0;
    case WM_MOUSEMOVE:
        // NOTE: Input::SetMousePos( Vector2( LOWORD( lParam ), HIWORD( lParam ) ) );
        break;
        break;
    case WM_SETCURSOR:
        //SetCursor( LoadCursorA( 0, LPCSTR( gInput->GetCursorStyle( ) ) ) );

        break;
    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hwnd, msg, wParam, lParam );
}

HWND Win32::CreateWindow_( const char* title, int w, int h, bool full_screen ) {
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


    HWND Hwnd = CreateWindow( 
        WindowClass.lpszClassName, title, WindowStyle,
        full_screen ? 0 : ( W / 2 ) - ( w / 2 ),
        full_screen ? 0 : ( H / 2 ) - ( h / 2 ),
        w,h, NULL, NULL, WindowClass.hInstance, NULL
    );

    if ( Hwnd ) {
        ShowWindow( Hwnd, SW_SHOWNORMAL );
        UpdateWindow( Hwnd );
    }

    return Hwnd;
}

void Win32::DestroyWindow( HWND window ) {
    if ( !window )
        return;

    PostMessage( window, WM_CLOSE, 0, 0 );
}

bool Win32::DispatchMessages( ) {
    MSG Message;

    if ( PeekMessage( &Message, nullptr, 0, 0, PM_REMOVE ) ) {
        TranslateMessage( &Message );
        DispatchMessage( &Message );

        if ( Message.message == WM_QUIT )
            return false;
    }

    return true;
}

HWND Win32::CreateConsole( const char* title, int x, int y, int w, int h ) {
    if ( !AllocConsole( ) )
        return nullptr;

    HWND Hwnd = GetConsoleWindow( );

    SetConsoleTitleA( title );
    MoveWindow( Hwnd, x, y, w, h, TRUE );

    FILE* fp = nullptr;
    freopen_s( &fp, "CONIN$", "r", stdin );
    freopen_s( &fp, "CONOUT$", "w", stdout );
    freopen_s( &fp, "CONOUT$", "w", stderr );

    return Hwnd;
}

void Win32::DestroyConsole( HWND window ) {
    if ( !window )
        return;

    FreeConsole( );
}

void Win32::MessageBox_( HWND window, const char* title, const char* content, int type ) {
    MessageBoxA( window, content, title, type );
}

Vector2 Win32::GetScreenSize( ) {
    return Vector2( GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ) );
}