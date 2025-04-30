#include "Environment.hpp"
#include "LuaBindings.hpp"

CEnvironment::CEnvironment( ) {
    m_State = luaL_newstate( );

    if ( !m_State )
        throw std::runtime_error( "Failed to initialize Lua state." );

    luaL_openlibs( m_State );

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

        { lua_createtable( m_State, 0, 6 );
            register_function( m_State, Wrapper::Graphics_::Initiate, "initiate", false );
            register_function( m_State, Wrapper::Graphics_::Cleanup, "cleanup", false );
            register_function( m_State, Wrapper::Graphics_::SetProjectionMatrix, "set_projection_matrix", false );
            register_function( m_State, Wrapper::Graphics_::SetViewport, "set_viewport", false );
        } register_table( m_State, "graphics", true );

        { lua_createtable( m_State, 0, 3 );
            register_function( m_State, Wrapper::Renderer_::WriteToBuffer, "write_to_buffer", false );
            register_function( m_State, Wrapper::Renderer_::CreateTexture, "create_texture", false );
            register_function( m_State, Wrapper::Renderer_::DestroyResource, "destroy_texture", false );
        } register_table( m_State, "renderer", true );

        { lua_createtable( m_State, 0, 7 );
            register_function( m_State, Wrapper::Input_::IsActive, "is_active", false );
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

        { lua_createtable( m_State, 0, 10 );
            register_function( m_State, Wrapper::FileSystem_::ListFiles, "list_files", false );
            register_function( m_State, Wrapper::FileSystem_::FileExists, "file_exists", false );
            register_function( m_State, Wrapper::FileSystem_::ReadFile, "read_file", false );
            register_function( m_State, Wrapper::FileSystem_::WriteFile, "write_file", false );
            register_function( m_State, Wrapper::FileSystem_::RenameFile, "rename_file", false );
            register_function( m_State, Wrapper::FileSystem_::DeleteFile_, "delete_file", false );
            register_function( m_State, Wrapper::FileSystem_::ListDirectories, "list_directories", false );
            register_function( m_State, Wrapper::FileSystem_::DirectoryExists, "directory_exists", false );
            register_function( m_State, Wrapper::FileSystem_::CreateDirectory_, "create_directory", false );
            register_function( m_State, Wrapper::FileSystem_::DeleteDirectory, "delete_directory", false );
        } register_table( m_State, "file_system", true );

        { lua_createtable( m_State, 0, 5 );
            register_function( m_State, Wrapper::Crypt::SHA256Encode, "sha256_encode", false );
            register_function( m_State, Wrapper::Crypt::Base64Encode, "base64_encode", false );
            register_function( m_State, Wrapper::Crypt::Base64Decode, "base64_decode", false );
            register_function( m_State, Wrapper::Crypt::JsonEncode, "json_encode", false );
            register_function( m_State, Wrapper::Crypt::JsonDecode, "json_decode", false );
        } register_table( m_State, "crypt", true );

        { lua_getglobal( m_State, "debug" );
        register_function( m_State, Wrapper::Debug::GetRegistry, "get_registry", false );

            register_function( m_State, Wrapper::Debug::GetUpvalues, "get_upvalues", false );
            register_function( m_State, Wrapper::Debug::GetUpvalue, "get_upvalue", false );
            register_function( m_State, Wrapper::Debug::SetUpvalue, "set_upvalue", false );
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
        register_function( m_State, Wrapper::GetReadOnly, "is_read_only", true );

        register_function( m_State, Wrapper::Utils_::RandomString, "random_string", true );
        register_function( m_State, Wrapper::Utils_::SetClipboard, "set_clipboard", true );
        register_function( m_State, Wrapper::Utils_::GetClipboard, "get_clipboard", true );
        register_function( m_State, Wrapper::Utils_::IsInternetConnected, "is_internet_connected", true );

        register_function( m_State, Wrapper::Http_::Get, "http_get", true );
        register_function( m_State, Wrapper::Http_::Post, "http_post", true );
        register_function( m_State, Wrapper::Http_::Put, "http_put", true );
        register_function( m_State, Wrapper::Http_::Delete, "http_delete", true );
    }

    { // Initiation scripts
        std::string Error;

        if ( !RunScripts( "Lua/Libraries", Error ) ) {
            return;
        }

        if ( !RunScripts( "Lua/Startup", Error ) ) {
            return;
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

    if ( Bytecode.empty( ) ) {
        // 'error' is already set by CompileScript
        return false;
    }

    if ( luau_load( m_State, m_ChunkName, Bytecode.data( ), Bytecode.size( ), 0 ) != LUA_OK || lua_pcall( m_State, 0, LUA_MULTRET, 0 ) != LUA_OK ) {
        error = lua_tostring( m_State, -1 );
        lua_pop( m_State, 1 );

        return false;
    }

    return true;
}

bool CEnvironment::RunScripts( std::string directory, std::string& error ) {
    const auto files = FileSystem.ListFiles( directory.c_str( ) );

    for ( const std::string& script_name : files ) {
        if ( script_name.length( ) < 4 || script_name.substr( script_name.length( ) - 4 ) != ".lua" )
            continue;

        std::string FilePath = directory + "/" + script_name;
        std::string FileContent = FileSystem.ReadFile( FilePath.c_str( ) );

        if ( FileContent.empty( ) ) {
            MessageBox( NULL, ( "Failed to read " + FilePath ).c_str( ), "Error", MB_OK | MB_ICONERROR );
            return false;
        }

        if ( !RunScript( FileContent, error ) )
            return false;
    }

    return true;
}

// NOTE: Make sure to define any new connections in m_Connections
void CEnvironment::RunConnection( const char* connection_name, const Args& args ) {
    if ( !m_State )
        return;

    for ( const auto& connection : m_Connections[ connection_name ] ) {
        if ( !connection.second )
            return;

        lua_rawgeti( m_State, LUA_REGISTRYINDEX, connection.second );

        for ( const auto& argument : args ) {
            std::visit( [ this ] ( auto&& value ) {
                using T = std::decay_t<decltype( value )>;

                if constexpr ( std::is_same_v<T, int> ) 
                    lua_pushinteger( m_State, value );
                else if constexpr ( std::is_same_v<T, float> )
                    lua_pushnumber( m_State, value );
                else if constexpr ( std::is_same_v<T, double> )
                    lua_pushnumber( m_State, value );
                else if constexpr ( std::is_same_v<T, std::string> )
                    lua_pushstring( m_State, value.c_str( ) );
                else if constexpr ( std::is_same_v<T, Vector2> ) {
                    auto Vector = ( Vector2* ) lua_newuserdata( m_State, sizeof( Vector2 ) );

                    new ( Vector ) Vector2(
                        value.x, value.y
                    );

                    luaL_getmetatable( m_State, "vector2" );
                    lua_setmetatable( m_State, -2 );
                }
                else if constexpr ( std::is_same_v<T, Vector3> ) {
                    auto Vector = ( Vector3* ) lua_newuserdata( m_State, sizeof( Vector3 ) );

                    new ( Vector ) Vector3(
                        value.x, value.y, value.z
                    );

                    luaL_getmetatable( m_State, "vector3" );
                    lua_setmetatable( m_State, -2 );
                }
                else if constexpr ( std::is_same_v<T, Vertex> ) {
                    auto _Vertex = ( Vertex* ) lua_newuserdata( m_State, sizeof( Vertex ) );

                    new ( _Vertex ) Vertex(
                        value.x, value.y, value.z,
                        value.rhw, value.u, value.v,
                        value.color
                    );

                    luaL_getmetatable( m_State, "vertex" );
                    lua_setmetatable( m_State, -2 );
                }
                else if constexpr ( std::is_same_v<T, DrawCommand> ) {
                    auto _DrawCommand = ( DrawCommand* ) lua_newuserdata( m_State, sizeof( DrawCommand ) );

                    new ( _DrawCommand ) DrawCommand(
                        value.primitive_topology,
                        value.vertices, value.indices,
                        value.z_index
                    );

                    luaL_getmetatable( m_State, "draw_command" );
                    lua_setmetatable( m_State, -2 );
                }
                else if constexpr ( std::is_same_v<T, Color> ) {
                    auto _Color = ( Color* ) lua_newuserdata( m_State, sizeof( Color ) );

                    new ( _Color ) Color(
                        value.r, value.g, value.b, value.a
                    );

                    luaL_getmetatable( m_State, "color" );
                    lua_setmetatable( m_State, -2 );
                }
            }, argument );
        }

        if ( lua_pcall( m_State, args.size( ), 0, 0 ) != LUA_OK ) {
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