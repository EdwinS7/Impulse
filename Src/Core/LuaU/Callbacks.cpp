#include "Callbacks.hpp"
#include "Environment.hpp"

void CCallbacks::RunConnection( const char* connection_name, const Args& args ) {
    lua_State* L = Environment.GetState( );
    
    if ( !L )
        return;

    for ( const auto& connection : m_Connections[ connection_name ] ) {
        if ( !connection.second )
            continue;  // Don't return early — just skip this connection

        lua_rawgeti( L, LUA_REGISTRYINDEX, connection.second );

        for ( const auto& argument : args ) {
            std::visit( [ L ] ( auto&& value ) {
                using T = std::decay_t<decltype( value )>;

                if constexpr ( std::is_same_v<T, int> )
                    lua_pushinteger( L, value );
                else if constexpr ( std::is_same_v<T, float> || std::is_same_v<T, double> )
                    lua_pushnumber( L, static_cast< lua_Number >( value ) );
                else if constexpr ( std::is_same_v<T, std::string> )
                    lua_pushstring( L, value.c_str( ) );
                else if constexpr ( std::is_same_v<T, Vector2> ) {
                    auto* vec = static_cast< Vector2* >( lua_newuserdata( L, sizeof( Vector2 ) ) );
                    new ( vec ) Vector2( value.x, value.y );
                    luaL_getmetatable( L, "vector2" );
                    lua_setmetatable( L, -2 );
                }
                else if constexpr ( std::is_same_v<T, Vector3> ) {
                    auto* vec = static_cast< Vector3* >( lua_newuserdata( L, sizeof( Vector3 ) ) );
                    new ( vec ) Vector3( value.x, value.y, value.z );
                    luaL_getmetatable( L, "vector3" );
                    lua_setmetatable( L, -2 );
                }
                else if constexpr ( std::is_same_v<T, Vertex> ) {
                    auto* v = static_cast< Vertex* >( lua_newuserdata( L, sizeof( Vertex ) ) );
                    new ( v ) Vertex( value.x, value.y, value.z, value.rhw, value.u, value.v, value.color );
                    luaL_getmetatable( L, "vertex" );
                    lua_setmetatable( L, -2 );
                }
                else if constexpr ( std::is_same_v<T, DrawCommand> ) {
                    auto* cmd = static_cast< DrawCommand* >( lua_newuserdata( L, sizeof( DrawCommand ) ) );
                    new ( cmd ) DrawCommand( value.primitive_topology, value.vertices, value.indices, value.texture, value.z_index );
                    luaL_getmetatable( L, "draw_command" );
                    lua_setmetatable( L, -2 );
                }
                else if constexpr ( std::is_same_v<T, Color> ) {
                    auto* color = static_cast< Color* >( lua_newuserdata( L, sizeof( Color ) ) );
                    new ( color ) Color( value.r, value.g, value.b, value.a );
                    luaL_getmetatable( L, "color" );
                    lua_setmetatable( L, -2 );
                }
            }, argument );
        }

        if ( lua_pcall( L, args.size( ), 0, 0 ) != LUA_OK ) {
            std::cerr << "Error running connection '" << connection_name << "': "
                << lua_tostring( L, -1 ) << "\n";
            lua_pop( L, 1 );
        }
    }
}

int CCallbacks::AddConnection( const char* connection_name, int function_reference ) {
    static int ConnectionCount = 1;

    m_Connections[ connection_name ].push_back( std::make_pair( ConnectionCount, function_reference ) );

    return ConnectionCount++;
}

void CCallbacks::RemoveConnection( int connection_id ) {
    std::vector<std::string> EmptyKeys;

    for ( auto& [connection_name, connections] : m_Connections ) {
        auto it = std::remove_if( connections.begin( ), connections.end( ), [ connection_id ] ( const auto& pair ) {
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

CCallbacks Callbacks;