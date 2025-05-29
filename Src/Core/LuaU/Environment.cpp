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
    register_usertype( m_State,
        LuaBind::LuaUsertypes::LuaVector2::New, LuaBind::LuaUsertypes::LuaVector2::Destroy,
        LuaBind::LuaUsertypes::LuaVector2::Index, LuaBind::LuaUsertypes::LuaVector2::NewIndex,
    "vector2" );

    register_usertype( m_State,
        LuaBind::LuaUsertypes::LuaVector3::New, LuaBind::LuaUsertypes::LuaVector3::Destroy,
        LuaBind::LuaUsertypes::LuaVector3::Index, LuaBind::LuaUsertypes::LuaVector3::NewIndex,
    "vector3" );

    register_usertype( m_State,
        LuaBind::LuaUsertypes::LuaVertex::New, LuaBind::LuaUsertypes::LuaVertex::Destroy,
        LuaBind::LuaUsertypes::LuaVertex::Index, LuaBind::LuaUsertypes::LuaVertex::NewIndex,
    "vertex" );

    register_usertype( m_State,
        LuaBind::LuaUsertypes::LuaTexture::New, LuaBind::LuaUsertypes::LuaTexture::Destroy,
        LuaBind::LuaUsertypes::LuaTexture::Index, LuaBind::LuaUsertypes::LuaTexture::NewIndex,
    "texture" );

    register_usertype( m_State,
        LuaBind::LuaUsertypes::LuaGlyph::New, LuaBind::LuaUsertypes::LuaGlyph::Destroy,
        LuaBind::LuaUsertypes::LuaGlyph::Index, LuaBind::LuaUsertypes::LuaGlyph::NewIndex,
    "glyph" );

    register_usertype( m_State,
        LuaBind::LuaUsertypes::LuaFont::New, LuaBind::LuaUsertypes::LuaFont::Destroy,
        LuaBind::LuaUsertypes::LuaFont::Index, LuaBind::LuaUsertypes::LuaFont::NewIndex,
    "font" );

    register_usertype( m_State,
        LuaBind::LuaUsertypes::LuaColor::New, LuaBind::LuaUsertypes::LuaColor::Destroy,
        LuaBind::LuaUsertypes::LuaColor::Index, LuaBind::LuaUsertypes::LuaColor::NewIndex,
    "color" );

    register_usertype( m_State,
        LuaBind::LuaUsertypes::LuaDrawCommand::New, LuaBind::LuaUsertypes::LuaDrawCommand::Destroy,
        LuaBind::LuaUsertypes::LuaDrawCommand::Index, LuaBind::LuaUsertypes::LuaDrawCommand::NewIndex,
    "draw_command" );

    // Libraries
    register_table( m_State, "win32",
        std::make_pair( "create_window", LuaBind::LuaWin32::CreateWindow_ ),
        std::make_pair( "destroy_window", LuaBind::LuaWin32::DestroyWindow ),
        std::make_pair( "create_console", LuaBind::LuaWin32::CreateConsole ),
        std::make_pair( "destroy_console", LuaBind::LuaWin32::DestroyConsole ),
        std::make_pair( "create_message_box", LuaBind::LuaWin32::MessageBox_ ),
        std::make_pair( "get_screen_size", LuaBind::LuaWin32::GetScreenSize )
    );

    register_table( m_State, "graphics",
        std::make_pair( "initiate", LuaBind::LuaGraphics::Initiate ),
        std::make_pair( "cleanup", LuaBind::LuaGraphics::Cleanup ),
        std::make_pair( "set_projection_matrix", LuaBind::LuaGraphics::SetProjectionMatrix ),
        std::make_pair( "set_viewport", LuaBind::LuaGraphics::SetViewport ),
        std::make_pair( "create_texture", LuaBind::LuaGraphics::CreateTexture ),
        std::make_pair( "destroy_texture", LuaBind::LuaGraphics::DestroyTexture ),
        std::make_pair( "create_font", LuaBind::LuaGraphics::_CreateFont ),
        std::make_pair( "destroy_font", LuaBind::LuaGraphics::DestroyFont )
    );

    register_table( m_State, "renderer",
        std::make_pair( "write_to_buffer", LuaBind::LuaRenderer::WriteToBuffer )
    );

    register_table( m_State, "input",
        std::make_pair( "is_active", LuaBind::LuaInput::IsActive ),
        std::make_pair( "is_key_pressed", LuaBind::LuaInput::IsKeyPressed ),
        std::make_pair( "is_key_held", LuaBind::LuaInput::IsKeyHeld ),
        std::make_pair( "get_cursor_position", LuaBind::LuaInput::GetCursorPosition ),
        std::make_pair( "set_cursor_position", LuaBind::LuaInput::SetCursorPosition ),
        std::make_pair( "get_cursor_style", LuaBind::LuaInput::GetCursorStyle ),
        std::make_pair( "set_cursor_style", LuaBind::LuaInput::SetCursorStyle )
    );

    register_table( m_State, "file_system",
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

    register_table( m_State, "crypt",
        std::make_pair( "sha256_encode", LuaBind::LuaCrypt::SHA256Encode ),
        std::make_pair( "base64_encode", LuaBind::LuaCrypt::Base64Encode ),
        std::make_pair( "base64_decode", LuaBind::LuaCrypt::Base64Decode ),
        std::make_pair( "json_encode", LuaBind::LuaCrypt::JsonEncode ),
        std::make_pair( "json_decode", LuaBind::LuaCrypt::JsonDecode )
    );

    extend_table( m_State, "debug",
        std::make_pair( "get_registry", LuaBind::LuaDebug::GetRegistry ),
        std::make_pair( "get_upvalues", LuaBind::LuaDebug::GetUpvalues ),
        std::make_pair( "get_upvalue", LuaBind::LuaDebug::GetUpvalue ),
        std::make_pair( "set_upvalue", LuaBind::LuaDebug::SetUpvalue )
    );

    // Globals
    register_function( m_State, LuaBind::LuaGlobals::Print, "print", true );

    register_function( m_State, LuaBind::LuaGlobals::AddConnection, "add_connection", true );
    register_function( m_State, LuaBind::LuaGlobals::RemoveConnection, "remove_connection", true );

    register_function( m_State, LuaBind::LuaGlobals::LoadString_, "load_string", true );
    register_function( m_State, LuaBind::LuaGlobals::NewCClosure, "new_c_closure", true );
    register_function( m_State, LuaBind::LuaGlobals::IsLuaClosure, "is_l_closure", true );
    register_function( m_State, LuaBind::LuaGlobals::IsCClosure, "is_c_closure", true );
    register_function( m_State, LuaBind::LuaGlobals::GetWrappedOriginal, "get_wrapped_original", true );

    register_function( m_State, LuaBind::LuaGlobals::SetReadOnly, "set_read_only", true );
    register_function( m_State, LuaBind::LuaGlobals::GetReadOnly, "is_read_only", true );

    register_function( m_State, LuaBind::LuaGlobals::RandomString, "random_string", true );
    register_function( m_State, LuaBind::LuaGlobals::SetClipboard, "set_clipboard", true );
    register_function( m_State, LuaBind::LuaGlobals::GetClipboard, "get_clipboard", true );
    register_function( m_State, LuaBind::LuaGlobals::HasInternet, "has_internet", true );

    register_function( m_State, LuaBind::LuaGlobals::Get, "http_get", true );
    register_function( m_State, LuaBind::LuaGlobals::Post, "http_post", true );
    register_function( m_State, LuaBind::LuaGlobals::Put, "http_put", true );
    register_function( m_State, LuaBind::LuaGlobals::Delete, "http_delete", true );

    std::vector<std::string> ScriptDirectories = {
        "Game/Lua/Core/Libraries",
        "Game/Lua/Core"
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