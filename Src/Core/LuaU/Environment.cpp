#include "Environment.hpp"

#include "LuaBinds.hpp"
#include "Wrapper.hpp"

bool CEnvironment::Initiate( ) {
    if ( m_State ) {
        MessageBox( NULL, "Lua state is already initialized", "Error", MB_OK | MB_ICONERROR );
        return false;
    }

    m_State = luaL_newstate( );

    if ( !m_State ) {
        MessageBox( NULL, "Failed to create Lua state", "Error", MB_OK | MB_ICONERROR );
        return false;
    }

    luaL_openlibs( m_State );

    // Usertypes
    RegisterUsertype( m_State, "vector2", {
        {"__index", LuaBind::LuaUsertypes::LuaVector2::__Index},
        {"__newindex", LuaBind::LuaUsertypes::LuaVector2::__NewIndex},
        {"__add", LuaBind::LuaUsertypes::LuaVector2::__Add},
        {"__sub", LuaBind::LuaUsertypes::LuaVector2::__Sub},
        {"__mul", LuaBind::LuaUsertypes::LuaVector2::__Mul},
        {"__div", LuaBind::LuaUsertypes::LuaVector2::__Div},
        {"__unm", LuaBind::LuaUsertypes::LuaVector2::__Unm},
    }, LuaBind::LuaUsertypes::LuaVector2::New, LuaBind::LuaUsertypes::LuaVector2::Destroy );

    RegisterUsertype( m_State, "vector3", {
        {"__index", LuaBind::LuaUsertypes::LuaVector3::__Index},
        {"__newindex", LuaBind::LuaUsertypes::LuaVector3::__NewIndex},
        {"__add", LuaBind::LuaUsertypes::LuaVector3::__Add},
        {"__sub", LuaBind::LuaUsertypes::LuaVector3::__Sub},
        {"__mul", LuaBind::LuaUsertypes::LuaVector3::__Mul},
        {"__div", LuaBind::LuaUsertypes::LuaVector3::__Div},
        {"__unm", LuaBind::LuaUsertypes::LuaVector3::__Unm},
    }, LuaBind::LuaUsertypes::LuaVector3::New, LuaBind::LuaUsertypes::LuaVector3::Destroy );

    RegisterUsertype( m_State, "vertex", {
        {"__index", LuaBind::LuaUsertypes::LuaVertex::__Index},
        {"__newindex", LuaBind::LuaUsertypes::LuaVertex::__NewIndex},
        {"__add", LuaBind::LuaUsertypes::LuaVertex::__Add},
        {"__sub", LuaBind::LuaUsertypes::LuaVertex::__Sub},
        {"__mul", LuaBind::LuaUsertypes::LuaVertex::__Mul},
        {"__div", LuaBind::LuaUsertypes::LuaVertex::__Div},
        {"__unm", LuaBind::LuaUsertypes::LuaVertex::__Unm},
    }, LuaBind::LuaUsertypes::LuaVertex::New, LuaBind::LuaUsertypes::LuaVertex::Destroy );

    RegisterUsertype( m_State, "texture", {
        {"__index", LuaBind::LuaUsertypes::LuaTexture::__Index},
        {"__newindex", LuaBind::LuaUsertypes::LuaTexture::__NewIndex}
    }, LuaBind::LuaUsertypes::LuaTexture::New, LuaBind::LuaUsertypes::LuaTexture::Destroy );

    RegisterUsertype( m_State, "glyph", {
        {"__index", LuaBind::LuaUsertypes::LuaGlyph::__Index},
        {"__newindex", LuaBind::LuaUsertypes::LuaGlyph::__NewIndex}
    }, LuaBind::LuaUsertypes::LuaGlyph::New, LuaBind::LuaUsertypes::LuaGlyph::Destroy );

    RegisterUsertype( m_State, "font", {
        {"__index", LuaBind::LuaUsertypes::LuaFont::__Index},
        {"__newindex", LuaBind::LuaUsertypes::LuaFont::__NewIndex}
    }, LuaBind::LuaUsertypes::LuaFont::New, LuaBind::LuaUsertypes::LuaFont::Destroy );

    RegisterUsertype( m_State, "color", {
        {"__index", LuaBind::LuaUsertypes::LuaColor::__Index},
        {"__newindex", LuaBind::LuaUsertypes::LuaColor::__NewIndex},

        {"to_grayscale", LuaBind::LuaUsertypes::LuaColor::ToGrayscale},
        {"invert", LuaBind::LuaUsertypes::LuaColor::Invert},
        {"lerp", LuaBind::LuaUsertypes::LuaColor::Lerp},
    }, LuaBind::LuaUsertypes::LuaColor::New, LuaBind::LuaUsertypes::LuaColor::Destroy );

    RegisterUsertype( m_State, "draw_command", {
        {"__index", LuaBind::LuaUsertypes::LuaDrawCommand::__Index},
        {"__newindex", LuaBind::LuaUsertypes::LuaDrawCommand::__NewIndex}
    }, LuaBind::LuaUsertypes::LuaDrawCommand::New, LuaBind::LuaUsertypes::LuaDrawCommand::Destroy );

    // Libraries
    RegisterTable( m_State, "client",
        std::make_pair( "get_username", LuaBind::LuaClient::GetUsername ),
        std::make_pair( "get_delta_time", LuaBind::LuaClient::GetDeltaTime ),
        std::make_pair( "get_real_time", LuaBind::LuaClient::GetRealTime ),
        std::make_pair( "get_fps", LuaBind::LuaClient::GetFps )
    );

    RegisterTable( m_State, "win32",
        std::make_pair( "create_window", LuaBind::LuaWin32::CreateWindow_ ),
        std::make_pair( "destroy_window", LuaBind::LuaWin32::DestroyWindow ),
        std::make_pair( "create_console", LuaBind::LuaWin32::CreateConsole ),
        std::make_pair( "destroy_console", LuaBind::LuaWin32::DestroyConsole ),
        std::make_pair( "create_message_box", LuaBind::LuaWin32::MessageBox_ ),
        std::make_pair( "get_screen_size", LuaBind::LuaWin32::GetScreenSize )
    );

    RegisterTable( m_State, "graphics",
        std::make_pair( "initiate", LuaBind::LuaGraphics::Initiate ),
        std::make_pair( "cleanup", LuaBind::LuaGraphics::Cleanup ),
        std::make_pair( "set_projection_matrix", LuaBind::LuaGraphics::SetProjectionMatrix ),
        std::make_pair( "set_viewport", LuaBind::LuaGraphics::SetViewport ),
        std::make_pair( "create_texture", LuaBind::LuaGraphics::CreateTexture ),
        std::make_pair( "destroy_texture", LuaBind::LuaGraphics::DestroyTexture ),
        std::make_pair( "create_font", LuaBind::LuaGraphics::_CreateFont ),
        std::make_pair( "destroy_font", LuaBind::LuaGraphics::DestroyFont )
    );

    RegisterTable( m_State, "renderer",
        std::make_pair( "write_to_buffer", LuaBind::LuaRenderer::WriteToBuffer )
    );

    RegisterTable( m_State, "input",
        std::make_pair( "is_active", LuaBind::LuaInput::IsActive ),
        std::make_pair( "is_key_pressed", LuaBind::LuaInput::IsKeyPressed ),
        std::make_pair( "is_key_held", LuaBind::LuaInput::IsKeyHeld ),
        std::make_pair( "get_cursor_position", LuaBind::LuaInput::GetCursorPosition ),
        std::make_pair( "set_cursor_position", LuaBind::LuaInput::SetCursorPosition ),
        std::make_pair( "get_cursor_style", LuaBind::LuaInput::GetCursorStyle ),
        std::make_pair( "set_cursor_style", LuaBind::LuaInput::SetCursorStyle )
    );

    RegisterTable( m_State, "file_system",
        std::make_pair( "list_files", LuaBind::LuaFileSystem::ListFiles ),
        std::make_pair( "file_exists", LuaBind::LuaFileSystem::FileExists ),
        std::make_pair( "read_file", LuaBind::LuaFileSystem::ReadFile ),
        std::make_pair( "write_file", LuaBind::LuaFileSystem::WriteFile ),
        std::make_pair( "rename_file", LuaBind::LuaFileSystem::RenameFile ),
        std::make_pair( "delete_file", LuaBind::LuaFileSystem::DeleteFile_ ),
        std::make_pair( "list_directories", LuaBind::LuaFileSystem::ListDirectories ),
        std::make_pair( "directory_exists", LuaBind::LuaFileSystem::DirectoryExists ),
        std::make_pair( "create_directory", LuaBind::LuaFileSystem::CreateDirectory_ ),
        std::make_pair( "delete_directory", LuaBind::LuaFileSystem::DeleteDirectory ),
        std::make_pair( "load_image", LuaBind::LuaFileSystem::_LoadImage )
    );

    RegisterTable( m_State, "crypt",
        std::make_pair( "sha256_encode", LuaBind::LuaCrypt::SHA256Encode ),
        std::make_pair( "base64_encode", LuaBind::LuaCrypt::Base64Encode ),
        std::make_pair( "base64_decode", LuaBind::LuaCrypt::Base64Decode ),
        std::make_pair( "json_encode", LuaBind::LuaCrypt::JsonEncode ),
        std::make_pair( "json_decode", LuaBind::LuaCrypt::JsonDecode )
    );

    ExtendTable( m_State, "debug",
        std::make_pair( "get_registry", LuaBind::LuaDebug::GetRegistry ),
        std::make_pair( "get_upvalues", LuaBind::LuaDebug::GetUpvalues ),
        std::make_pair( "get_upvalue", LuaBind::LuaDebug::GetUpvalue ),
        std::make_pair( "set_upvalue", LuaBind::LuaDebug::SetUpvalue )
    );

    // Globals
    RegisterFunction( m_State, LuaBind::LuaGlobals::Print, "print", true );

    RegisterFunction( m_State, LuaBind::LuaGlobals::AddConnection, "add_connection", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::RemoveConnection, "remove_connection", true );

    RegisterFunction( m_State, LuaBind::LuaGlobals::LoadString_, "load_string", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::NewCClosure, "new_c_closure", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::IsLuaClosure, "is_l_closure", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::IsCClosure, "is_c_closure", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::GetWrappedOriginal, "get_wrapped_original", true );

    RegisterFunction( m_State, LuaBind::LuaGlobals::SetReadOnly, "set_read_only", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::GetReadOnly, "is_read_only", true );

    RegisterFunction( m_State, LuaBind::LuaGlobals::RandomString, "random_string", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::SetClipboard, "set_clipboard", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::GetClipboard, "get_clipboard", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::HasInternet, "has_internet", true );

    RegisterFunction( m_State, LuaBind::LuaGlobals::Get, "http_get", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::Post, "http_post", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::Put, "http_put", true );
    RegisterFunction( m_State, LuaBind::LuaGlobals::Delete, "http_delete", true );

    std::vector<std::string> ScriptDirectories = {
        "Game/Lua/Core",
        "Game/Lua/Core/Libraries"
    };

    for ( const auto& directory : ScriptDirectories ) {
        for ( const auto& file_name : FileSystem.ListFiles( directory.c_str( ) ) ) {
            std::string file_path = directory + "/" + file_name;

            if ( !LoadFile( file_path.c_str( ) ) ) {
                return false;
            }
        }
    }

    return true;
}

bool CEnvironment::Cleanup( ) {
    if ( !m_State )
        return false;

    lua_close( m_State );

    return true;
}

bool CEnvironment::LoadScript( const char* name, std::string source_code ) {
    if ( !m_State )
        return false;

    if ( source_code.empty( ) ) {
        MessageBoxA( NULL, std::format( "Script '{}' is empty", name ).c_str( ), "Error", MB_OK | MB_ICONERROR );
        return false;
    }

    // TODO: Use another bytecode builder
    size_t BytecodeSize = 0;
    char* CompiledBytecode = luau_compile(
        source_code.data( ),
        source_code.size( ),
        nullptr,
        &BytecodeSize
    );

    if ( !CompiledBytecode ) {
        MessageBoxA( NULL, std::format( "Failed to compile script '{}'", name ).c_str( ), "Error", MB_OK | MB_ICONERROR );
        return "";
    }

    std::string BytecodeData( CompiledBytecode, BytecodeSize );
    free( CompiledBytecode );

    if ( BytecodeData.empty( ) )
        return false;

    if ( luau_load( m_State, m_ChunkName, BytecodeData.data( ), BytecodeData.size( ), 0 ) || lua_pcall( m_State, 0, LUA_MULTRET, 0 ) ) {
        MessageBoxA( NULL, std::format( "{}:{}", name, lua_tostring( m_State, -1 ) ).c_str( ), "Error", MB_OK | MB_ICONERROR );
        lua_pop( m_State, 1 );

        return false;
    }

    return true;
}

bool CEnvironment::LoadFile( const char* file_path ) {
    if ( !m_State )
        return false;

    const char* file_name = strrchr( file_path, '/' );
    file_name = file_name ? file_name + 1 : file_path;

    const std::string Source = FileSystem.ReadFile( file_path );

    if ( !Environment.LoadScript( file_name, Source ) ) {
        return false;
    }

    return true;
}

lua_State* CEnvironment::GetState( ) {
    return m_State;
}

CEnvironment Environment;