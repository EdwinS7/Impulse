#include "Common.hpp"

#include "Core/FileSystem/FileSystem.hpp"
#include "Core/LuaU/Environment.hpp"
#include "Core/Win32/Win32.hpp"
#include "Core/Graphics/Include.hpp"
#include "Core/Input/Input.hpp"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR pCmdLine, _In_ int nCmdShow ) {
    try {
        if ( !FileSystem.DirectoryExists( "Lua" ) ) {
            MessageBox( NULL, "Failed to find Lua folder", "Error", MB_OK | MB_ICONERROR );
            return 1;
        }

        const std::string Script = FileSystem.ReadFile("Main.lua");

        if ( Script.empty( ) ) {
            MessageBox( NULL, "Failed to read Main.lua", "Error", MB_OK | MB_ICONERROR );
            return 1;
        }

        std::string ScriptError;
        if ( !Environment.RunScript( Script, ScriptError ) ) {
            MessageBox( NULL, ScriptError.c_str( ), "Error", MB_OK | MB_ICONERROR );
            return 1;
        }

        while ( Win32.DispatchMessages( ) ) {
            Input.PoolInput( );

            if ( Graphics.IsDeviceInitialized( ) && Graphics.Present( ) ) {
                Environment.RunConnection( "present", {
                    /* Parameters */
                } );
            }
        }
    } catch ( const std::exception& e ) {
        MessageBox( NULL, e.what( ), "Error", MB_OK | MB_ICONERROR );
        return 1;
    } catch ( ... ) {
        MessageBox( NULL, "Unknown error occurred", "Error", MB_OK | MB_ICONERROR );
        return 1;
    }

    Environment.RunConnection( "shutdown", { 
        /* Parameters */
    } );

    return 0;
}