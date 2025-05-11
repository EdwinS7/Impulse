#include "Environment.hpp"
#include "LuaBinds.hpp"

CEnvironment::CEnvironment( ) {
    m_State = luaL_newstate( );

    if ( !m_State )
        throw std::runtime_error( "Failed to initialize m_State" );

    luaL_openlibs( m_State );

    { // User types registration
        register_usertype( m_State,
            LuaBind::LuaUsertypes::LuaVector2::New,
            LuaBind::LuaUsertypes::LuaVector2::Destroy,
            LuaBind::LuaUsertypes::LuaVector2::Index,
            LuaBind::LuaUsertypes::LuaVector2::NewIndex,
        "vector2" );

        register_usertype( m_State,
            LuaBind::LuaUsertypes::LuaVector3::New,
            LuaBind::LuaUsertypes::LuaVector3::Destroy,
            LuaBind::LuaUsertypes::LuaVector3::Index,
            LuaBind::LuaUsertypes::LuaVector3::NewIndex,
        "vector3" );

        register_usertype( m_State,
            LuaBind::LuaUsertypes::LuaVertex::New,
            LuaBind::LuaUsertypes::LuaVertex::Destroy,
            LuaBind::LuaUsertypes::LuaVertex::Index,
            LuaBind::LuaUsertypes::LuaVertex::NewIndex,
        "vertex" );

        register_usertype( m_State,
            LuaBind::LuaUsertypes::LuaTexture::New,
            LuaBind::LuaUsertypes::LuaTexture::Destroy,
            LuaBind::LuaUsertypes::LuaTexture::Index,
            LuaBind::LuaUsertypes::LuaTexture::NewIndex,
        "texture" );

        register_usertype( m_State,
            LuaBind::LuaUsertypes::LuaGlyph::New,
            LuaBind::LuaUsertypes::LuaGlyph::Destroy,
            LuaBind::LuaUsertypes::LuaGlyph::Index,
            LuaBind::LuaUsertypes::LuaGlyph::NewIndex,
        "glyph" );

        register_usertype( m_State,
            LuaBind::LuaUsertypes::LuaFont::New,
            LuaBind::LuaUsertypes::LuaFont::Destroy,
            LuaBind::LuaUsertypes::LuaFont::Index,
            LuaBind::LuaUsertypes::LuaFont::NewIndex,
        "font" );

        register_usertype( m_State,
            LuaBind::LuaUsertypes::LuaColor::New,
            LuaBind::LuaUsertypes::LuaColor::Destroy,
            LuaBind::LuaUsertypes::LuaColor::Index,
            LuaBind::LuaUsertypes::LuaColor::NewIndex,
        "color" );

        register_usertype( m_State,
            LuaBind::LuaUsertypes::LuaDrawCommand::New,
            LuaBind::LuaUsertypes::LuaDrawCommand::Destroy,
            LuaBind::LuaUsertypes::LuaDrawCommand::Index,
            LuaBind::LuaUsertypes::LuaDrawCommand::NewIndex,
        "draw_command" );
    }

    { // Libraries
        { lua_createtable( m_State, 0, 6 );
            register_function( m_State, LuaBind::LuaWin32::CreateWindow_, "create_window" );
            register_function( m_State, LuaBind::LuaWin32::DestroyWindow, "destroy_window" );
            register_function( m_State, LuaBind::LuaWin32::CreateConsole, "create_console" );
            register_function( m_State, LuaBind::LuaWin32::DestroyConsole, "destroy_console" );
            register_function( m_State, LuaBind::LuaWin32::MessageBox_, "create_message_box" );
            register_function( m_State, LuaBind::LuaWin32::GetScreenSize, "get_screen_size" );
        } lua_setglobal( m_State, "win32" );

        { lua_createtable( m_State, 0, 6 );
            register_function( m_State, LuaBind::LuaGraphics::Initiate, "initiate" );
            register_function( m_State, LuaBind::LuaGraphics::Cleanup, "cleanup" );
            register_function( m_State, LuaBind::LuaGraphics::SetProjectionMatrix, "set_projection_matrix" );
            register_function( m_State, LuaBind::LuaGraphics::SetViewport, "set_viewport" );
            register_function( m_State, LuaBind::LuaGraphics::CreateTexture, "create_texture" );
            register_function( m_State, LuaBind::LuaGraphics::DestroyTexture, "destroy_texture" );
            register_function( m_State, LuaBind::LuaGraphics::_CreateFont, "create_font" );
            register_function( m_State, LuaBind::LuaGraphics::DestroyFont, "destroy_font" );
        } lua_setglobal( m_State, "graphics" );

        { lua_createtable( m_State, 0, 1 );
            register_function( m_State, LuaBind::LuaRenderer::WriteToBuffer, "write_to_buffer" );
        } lua_setglobal( m_State, "renderer" );

        { lua_createtable( m_State, 0, 7 );
            register_function( m_State, LuaBind::LuaInput::IsActive, "is_active" );
            register_function( m_State, LuaBind::LuaInput::IsKeyPressed, "is_key_pressed" );
            register_function( m_State, LuaBind::LuaInput::IsKeyHeld, "is_key_held" );
            register_function( m_State, LuaBind::LuaInput::GetCursorPosition, "get_cursor_position" );
            register_function( m_State, LuaBind::LuaInput::SetCursorPosition, "set_cursor_position" );
            register_function( m_State, LuaBind::LuaInput::GetCursorStyle, "get_cursor_style" );
            register_function( m_State, LuaBind::LuaInput::SetCursorStyle, "set_cursor_style" );
        } lua_setglobal( m_State, "input" );

        { lua_createtable( m_State, 0, 11 );
            register_function( m_State, LuaBind::LuaFileSystem::ListFiles, "list_files" );
            register_function( m_State, LuaBind::LuaFileSystem::FileExists, "file_exists" );
            register_function( m_State, LuaBind::LuaFileSystem::ReadFile, "read_file" );
            register_function( m_State, LuaBind::LuaFileSystem::WriteFile, "write_file" );
            register_function( m_State, LuaBind::LuaFileSystem::RenameFile, "rename_file" );
            register_function( m_State, LuaBind::LuaFileSystem::DeleteFile_, "delete_file" );
            register_function( m_State, LuaBind::LuaFileSystem::ListDirectories, "list_directories" );
            register_function( m_State, LuaBind::LuaFileSystem::DirectoryExists, "directory_exists" );
            register_function( m_State, LuaBind::LuaFileSystem::CreateDirectory_, "create_directory" );
            register_function( m_State, LuaBind::LuaFileSystem::DeleteDirectory, "delete_directory" );
            register_function( m_State, LuaBind::LuaFileSystem::_LoadImage, "load_image" );
        } lua_setglobal( m_State, "file_system" );

        { lua_createtable( m_State, 0, 5 );
            register_function( m_State, LuaBind::LuaCrypt::SHA256Encode, "sha256_encode" );
            register_function( m_State, LuaBind::LuaCrypt::Base64Encode, "base64_encode" );
            register_function( m_State, LuaBind::LuaCrypt::Base64Decode, "base64_decode" );
            register_function( m_State, LuaBind::LuaCrypt::JsonEncode, "json_encode" );
            register_function( m_State, LuaBind::LuaCrypt::JsonDecode, "json_decode" );
        } lua_setglobal( m_State, "crypt" );

        { lua_getglobal( m_State, "debug" );
            register_function( m_State, LuaBind::LuaDebug::GetRegistry, "get_registry" );
            register_function( m_State, LuaBind::LuaDebug::GetUpvalues, "get_upvalues" );
            register_function( m_State, LuaBind::LuaDebug::GetUpvalue, "get_upvalue" );
            register_function( m_State, LuaBind::LuaDebug::SetUpvalue, "set_upvalue" );
        } lua_pop( m_State, 1 );
    }

    { // Globals
        register_function( m_State, LuaBind::LuaGlobals::Print, "print", true );

        register_function( m_State, LuaBind::LuaGlobals::AddConnection, "add_connection", true );
        register_function( m_State, LuaBind::LuaGlobals::RemoveConnection, "remove_connection", true );

        register_function( m_State, LuaBind::LuaGlobals::LoadString_, "load_string", true );
        register_function( m_State, LuaBind::LuaGlobals::NewCClosure, "new_c_closure", true );
        register_function( m_State, LuaBind::LuaGlobals::IsLuaClosure, "is_lua_closure", true );
        register_function( m_State, LuaBind::LuaGlobals::IsCClosure, "is_c_closure", true );
        register_function( m_State, LuaBind::LuaGlobals::GetWrappedOriginal, "get_wrapped_original", true );

        register_function( m_State, LuaBind::LuaGlobals::SetReadOnly, "set_read_only", true );
        register_function( m_State, LuaBind::LuaGlobals::GetReadOnly, "is_read_only", true );

        register_function( m_State, LuaBind::LuaUtils::RandomString, "random_string", true );
        register_function( m_State, LuaBind::LuaUtils::SetClipboard, "set_clipboard", true );
        register_function( m_State, LuaBind::LuaUtils::GetClipboard, "get_clipboard", true );
        register_function( m_State, LuaBind::LuaUtils::IsInternetConnected, "is_internet_connected", true );

        register_function( m_State, LuaBind::LuaHttp::Get, "http_get", true );
        register_function( m_State, LuaBind::LuaHttp::Post, "http_post", true );
        register_function( m_State, LuaBind::LuaHttp::Put, "http_put", true );
        register_function( m_State, LuaBind::LuaHttp::Delete, "http_delete", true );
    }

    { // Initiation scripts
        std::string Error;

        if ( !RunScripts( "Game/Lua/Libraries", Error ) ) {
            throw std::runtime_error( Error );

            return;
        }

        if ( !RunScripts( "Game/Lua/Startup", Error ) ) {
            throw std::runtime_error( Error );

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
                        value.texture, value.z_index
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