// NOTE: This project is for fun, learning and a wip so if you see any problems please recommend your solution.
// NOTE: Everything will be heavily cleaned up later on, A LOT. I like getting everything to work first.
// NOTE: For u fucking retards, Just because this has LuaU in it does NOT mean its an executor 🤦

#include "Common.hpp"

// TODO: Organize
#include "Core/FileSystem/FileSystem.hpp"
#include "Core/LuaU/Environment.hpp"
#include "Core/Win32/Win32.hpp"
#include "Core/Graphics/Include.hpp"
#include "Core/Input/Input.hpp"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow ) {
    try {
        const std::string Script = FileSystem.ReadFile("Main.lua");

        if ( Script.empty( ) ) {
            MessageBox( NULL, "Failed to read Main.lua", "Error", MB_OK | MB_ICONERROR );
            return 1;
        }

        std::string ErrorMessage;
        if ( !Environment.RunScript( Script, ErrorMessage ) ) {
            MessageBox( NULL, ErrorMessage.c_str( ), "Error", MB_OK | MB_ICONERROR );
            return 1;
        }

        while ( Win32.DispatchMessages( ) ) {
            Input.PoolInput( );

            if ( Graphics.IsInitiated( ) )
                Graphics.Present( );

            Environment.RunConnection( "new_frame", { /* Empty*/ } );
        }
    } catch ( const std::exception& e ) {
        MessageBox( NULL, e.what( ), "Error", MB_OK | MB_ICONERROR );
        return 1;
    } catch ( ... ) {
        MessageBox( NULL, "Unknown error occurred", "Error", MB_OK | MB_ICONERROR );
        return 1;
    }

    Environment.RunConnection( "shutdown", { /* Empty*/ } );

    return 0;
}