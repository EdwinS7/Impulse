#include "Environment.hpp"
#include "Wrapper.hpp"

#define lua_pushfunction(state, wrapper_function) lua_pushcfunction( state, wrapper_function, nullptr )

void register_usertype( lua_State* state, lua_CFunction wrapper_function, const std::string& name, bool global ) {
    lua_pushfunction( state, wrapper_function );
    lua_setglobal( state, name.c_str( ) );

    lua_pop( state, 1 );
}

void register_table( lua_State* state, const std::string& name, bool global ) {
    if ( global )
        lua_setglobal( state, name.c_str( ) );
    else
        lua_setfield( state, -2, name.c_str( ) );
}

void register_function( lua_State* state, lua_CFunction wrapper_function, const std::string& name, bool global ) {
    lua_pushfunction( state, wrapper_function );

    if ( global )
        lua_setglobal( state, name.c_str( ) );
    else
        lua_setfield( state, -2, name.c_str( ) );
}

CEnvironment::CEnvironment( ) {
    m_State = luaL_newstate( );

    if ( !m_State )
        throw std::runtime_error( "Failed to initialize Lua state." );

    luaL_openlibs( m_State );

    // TODO: Make these NOT metatables lol
    { // Usertypes
        { luaL_newmetatable( m_State, "vector2" );
            register_function( m_State, Wrapper::Types::Vector2_::Index, "__index", false );
            register_function( m_State, Wrapper::Types::Vector2_::NewIndex, "__newindex", false );
        } register_usertype( m_State, Wrapper::Types::Vector2_::New, "vector2", false );

        { luaL_newmetatable( m_State, "vector3" );
            register_function( m_State, Wrapper::Types::Vector3_::Index, "__index", false );
            register_function( m_State, Wrapper::Types::Vector3_::NewIndex, "__newindex", false );
        }  register_usertype( m_State, Wrapper::Types::Vector3_::New, "vector3", false );

        { luaL_newmetatable( m_State, "vertex" );
            register_function( m_State, Wrapper::Types::Vertex_::Index, "__index", false );
            register_function( m_State, Wrapper::Types::Vertex_::NewIndex, "__newindex", false );
        } register_usertype( m_State, Wrapper::Types::Vertex_::New, "vertex", false );

        { luaL_newmetatable( m_State, "color" );
            register_function( m_State, Wrapper::Types::Color_::Index, "__index", false );
            register_function( m_State, Wrapper::Types::Color_::NewIndex, "__newindex", false );
        } register_usertype( m_State, Wrapper::Types::Color_::New, "color", false );

        { luaL_newmetatable( m_State, "draw_command" );
            register_function( m_State, Wrapper::Types::DrawCommand_::Index, "__index", false );
            register_function( m_State, Wrapper::Types::DrawCommand_::NewIndex, "__newindex", false );
        } register_usertype( m_State, Wrapper::Types::DrawCommand_::New, "draw_command", false );
    }

    { // Libraries
        { lua_createtable( m_State, 0, 6 );
            register_function( m_State, Wrapper::Win32_::CreateWindow_, "create_window", false );
            register_function( m_State, Wrapper::Win32_::DestroyWindow, "destroy_window", false );
            register_function( m_State, Wrapper::Win32_::CreateConsole, "create_console", false );
            register_function( m_State, Wrapper::Win32_::DestroyConsole, "destroy_console", false );
            register_function( m_State, Wrapper::Win32_::MessageBox_, "create_message_box", false );
            register_function( m_State, Wrapper::Win32_::GetScreenSize, "get_screen_size", false );
        } register_table( m_State, "win32", true );

        { lua_createtable( m_State, 0, 2 );
            register_function( m_State, Wrapper::Graphics_::Initiate, "initiate", false );
            register_function( m_State, Wrapper::Graphics_::Cleanup, "cleanup", false );
        } register_table( m_State, "directx", true );

        { lua_createtable( m_State, 0, 5 ); // NOTE: WIP, Major changes in the next coming versions.
            register_function( m_State, Wrapper::Renderer_::WriteToBuffer, "write_to_buffer", false );
            register_function( m_State, Wrapper::Renderer_::Line, "line", false );
            register_function( m_State, Wrapper::Renderer_::Polyline, "polyline", false );
            register_function( m_State, Wrapper::Renderer_::Polygon, "polygon", false );
            register_function( m_State, Wrapper::Renderer_::Rectangle, "rectangle", false );
            register_function( m_State, Wrapper::Renderer_::FilledRectangle, "filled_rectangle", false );
        } register_table( m_State, "renderer", true );

        { lua_createtable( m_State, 0, 6 );
            register_function( m_State, Wrapper::Input_::IsKeyPressed, "is_key_pressed", false );
            register_function( m_State, Wrapper::Input_::IsKeyHeld, "is_key_held", false );
            register_function( m_State, Wrapper::Input_::GetCursorPosition, "get_cursor_position", false );
            register_function( m_State, Wrapper::Input_::SetCursorPosition, "set_cursor_position", false );
            register_function( m_State, Wrapper::Input_::GetCursorStyle, "get_cursor_style", false );
            register_function( m_State, Wrapper::Input_::SetCursorStyle, "set_cursor_style", false );
        } register_table( m_State, "input", true );

        { lua_createtable( m_State, 0, 4 );
        register_function( m_State, Wrapper::Memory_::SetTarget, "set_target", false );
            register_function( m_State, Wrapper::Memory_::Read, "read", false );
            register_function( m_State, Wrapper::Memory_::Write, "write", false );
            register_function( m_State, Wrapper::Memory_::ScanPattern, "scan_pattern", false );
        } register_table( m_State, "memory", true );

        { lua_getglobal( m_State, "debug" );
            register_function( m_State, Wrapper::Debug::GetUpvalue_, "get_upvalue", false );
        } lua_pop( m_State, 1 );
    }

    { // Globals
        register_function( m_State, Wrapper::AddConnection, "add_connection", true );
        register_function( m_State, Wrapper::RemoveConnection, "remove_connection", true );

        register_function( m_State, Wrapper::LoadString_, "load_string", true );
        register_function( m_State, Wrapper::NewCClosure, "new_c_closure", true );
        register_function( m_State, Wrapper::IsLuaClosure, "is_lua_closure", true );
        register_function( m_State, Wrapper::IsCClosure, "is_c_closure", true ); 
        register_function( m_State, Wrapper::GetWrappedOriginal, "get_wrapped_original", true );

        register_function( m_State, Wrapper::SetReadOnly, "set_read_only", true );
        register_function( m_State, Wrapper::GetReadOnly, "get_read_only", true );

        register_function( m_State, Wrapper::Utils_::RandomString, "random_string", true );
        register_function( m_State, Wrapper::Utils_::SetClipboard, "set_clipboard", true );
        register_function( m_State, Wrapper::Utils_::GetClipboard, "get_clipboard", true );
        register_function( m_State, Wrapper::Utils_::SHA256Encode, "sha256_encode", true );
        register_function( m_State, Wrapper::Utils_::Base64Encode, "base64_encode", true );
        register_function( m_State, Wrapper::Utils_::Base64Decode, "base64_decode", true );
        register_function( m_State, Wrapper::Utils_::IsInternetConnected, "is_internet_connected", true );

        register_function( m_State, Wrapper::FileSystem_::ListFiles, "list_files", true );
        register_function( m_State, Wrapper::FileSystem_::FileExists, "file_exists", true );
        register_function( m_State, Wrapper::FileSystem_::ReadFile, "read_file", true );
        register_function( m_State, Wrapper::FileSystem_::WriteFile, "write_file", true );
        register_function( m_State, Wrapper::FileSystem_::RenameFile, "rename_file", true );
        register_function( m_State, Wrapper::FileSystem_::DeleteFile_, "delete_file", true );
        register_function( m_State, Wrapper::FileSystem_::ListDirectories, "list_directories", true );
        register_function( m_State, Wrapper::FileSystem_::DirectoryExists, "directory_exists", true );
        register_function( m_State, Wrapper::FileSystem_::CreateDirectory_, "create_directory", true );
        register_function( m_State, Wrapper::FileSystem_::DeleteDirectory, "delete_directory", true );

        register_function( m_State, Wrapper::Http_::Get, "http_get", true );
        register_function( m_State, Wrapper::Http_::Post, "http_post", true );
        register_function( m_State, Wrapper::Http_::Put, "http_put", true );
        register_function( m_State, Wrapper::Http_::Delete, "http_delete", true );
    }

    { // Initiation scripts
        std::vector<std::string> Scripts = FileSystem.ListFiles( "Scripts" );

        for ( size_t i = 0; i < Scripts.size( ); i++ ) {
            if ( Scripts[ i ].length( ) < 4 || Scripts[ i ].substr( Scripts[ i ].length( ) - 4 ) != ".lua" )
                continue;

            std::string FilePath = "Scripts/" + Scripts[ i ];
            std::string FileContent = FileSystem.ReadFile( FilePath.c_str( ) );

            if ( FileContent.empty( ) ) {
                MessageBox( NULL, ( "Failed to read " + FilePath ).c_str( ), "Error", MB_OK | MB_ICONERROR );
                return;
            }

            std::string Error;

            if ( !RunScript( FileContent, Error ) )
                MessageBox( NULL, Error.c_str( ), "Error", MB_OK | MB_ICONERROR );
        }
    }
}

CEnvironment::~CEnvironment( ) {
    if ( m_State ) {
        lua_close( m_State );
    }
}

lua_State* CEnvironment::GetState( ) {
    return m_State;
}

std::string CEnvironment::CompileScript( std::string script, std::string& error ) {
    size_t BytecodeSize;
    char* CompiledBytecode = luau_compile( script.data( ), script.size( ), nullptr, &BytecodeSize );

    if ( !CompiledBytecode ) {
        error = "luau_compile: Memory allocation failed";
        return "";
    }

    std::string Result( CompiledBytecode, BytecodeSize );

    free( CompiledBytecode );

    return Result;
}

bool CEnvironment::RunScript( std::string script, std::string& error ) {
    if ( script.empty( ) ) {
        error = "Script is empty";
        return false;
    }

    std::string Bytecode = CompileScript( script, error );

    if ( Bytecode.empty( ) )
        return false;

    if ( luau_load( m_State, m_ChunkName, Bytecode.data( ), Bytecode.size( ), 0 ) != LUA_OK ||
        lua_pcall( m_State, 0, LUA_MULTRET, 0 ) != LUA_OK ) {

        error = lua_tostring( m_State, -1 );
        lua_pop( m_State, 1 );

        return false;
    }

    return true;
}

// NOTE: Make sure to define any new connections in m_Connections
void CEnvironment::RunConnection( const char* connection_name ) {
    if ( !m_State )
        return;

    for ( const auto& connection : m_Connections[ connection_name ] ) {
        if ( !connection.second )
            return;

        lua_rawgeti( m_State, LUA_REGISTRYINDEX, connection.second );

        if ( lua_pcall( m_State, 0, 0, 0 ) != LUA_OK ) {
            std::cerr << "Error running connection '" << connection_name << "': " << lua_tostring( m_State, -1 ) << "\n";

            lua_pop( m_State, 1 );
        }
    }
}

int CEnvironment::AddConnection( const char* connection_name, int function_reference ) {
    static int ConnectionCount = 1;

    m_Connections[ connection_name ].push_back( std::make_pair( ConnectionCount, function_reference ) );

    return ConnectionCount++;
}

void CEnvironment::RemoveConnection( int connection_id ) {
    std::vector<std::string> EmptyKeys;

    for ( auto& [connection_name, connections] : m_Connections ) {
        auto it = std::remove_if( connections.begin( ), connections.end( ),
            [ connection_id ] ( const auto& pair ) {
            return pair.first == connection_id;
        } );

        if ( it != connections.end( ) ) {
            connections.erase( it, connections.end( ) );
            if ( connections.empty( ) ) {
                EmptyKeys.push_back( connection_name );
            }
            return;
        }
    }

    for ( const auto& key : EmptyKeys ) {
        m_Connections.erase( key );
    }
}

CEnvironment Environment;