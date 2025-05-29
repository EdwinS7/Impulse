#include "Common.hpp"

#include "Core/FileSystem/FileSystem.hpp"
#include "Core/LuaU/Environment.hpp"
#include "Core/Win32/Win32.hpp"
#include "Core/Graphics/Include.hpp"
#include "Core/Input/Input.hpp"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR pCmdLine, _In_ int nCmdShow ) {
    try {
        if ( !FileSystem.DirectoryExists( "Game" ) ) {
            MessageBox( NULL, "Failed to find 'Game' folder", "Error", MB_OK | MB_ICONERROR );
            return 1;
        }

        if ( !Environment.Initiate( ) ) {
            return 1;
        }

        if ( !Environment.LoadFile( "Game/Lua/Main.lua" ) ) {
            return 1;
        }

        while ( Win32.DispatchMessages( ) ) {
            Input.PoolInput( );

            if ( Graphics.GetDevice( ) && Graphics.Present( ) ) {
                Callbacks.RunConnection( "present", {
                    /* Parameters */
                } );
            }
        }

        Environment.Cleanup( );
    } catch ( const std::exception& e ) {
        MessageBox( NULL, e.what( ), "Error", MB_OK | MB_ICONERROR );
        return 1;
    } catch ( ... ) {
        MessageBox( NULL, "Unknown error occurred", "Error", MB_OK | MB_ICONERROR );
        return 1;
    }

    Callbacks.RunConnection( "shutdown", {
        /* Parameters */
    } );

    return 0;
}