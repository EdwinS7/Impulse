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
                    auto* _Vector2 = static_cast< Vector2* >( lua_newuserdata( L, sizeof( Vector2 ) ) );
                    new ( _Vector2 ) Vector2( value.x, value.y );

                    luaL_getmetatable( L, "vector2" );
                    lua_setmetatable( L, -2 );
                }
                else if constexpr ( std::is_same_v<T, Vector3> ) {
                    auto* _Vector3 = static_cast< Vector3* >( lua_newuserdata( L, sizeof( Vector3 ) ) );
                    new ( _Vector3 ) Vector3( value.x, value.y, value.z );

                    luaL_getmetatable( L, "vector3" );
                    lua_setmetatable( L, -2 );
                }
                else if constexpr ( std::is_same_v<T, Vertex> ) {
                    auto* _Vertex = static_cast< Vertex* >( lua_newuserdata( L, sizeof( Vertex ) ) );
                    new ( _Vertex ) Vertex( value.x, value.y, value.z, value.rhw, value.u, value.v, value.clr );

                    luaL_getmetatable( L, "vertex" );
                    lua_setmetatable( L, -2 );
                }
                else if constexpr ( std::is_same_v<T, DrawCommand> ) {
                    auto* _DrawCommand = static_cast< DrawCommand* >( lua_newuserdata( L, sizeof( DrawCommand ) ) );
                    new ( _DrawCommand ) DrawCommand( value.PrimitiveTopology, value.Vertices, value.Indices, value._Texture, value.ZIndex );

                    luaL_getmetatable( L, "draw_command" );
                    lua_setmetatable( L, -2 );
                }
                else if constexpr ( std::is_same_v<T, Color> ) {
                    auto* _Color = static_cast< Color* >( lua_newuserdata( L, sizeof( Color ) ) );
                    new ( _Color ) Color( value.r, value.g, value.b, value.a );

                    luaL_getmetatable( L, "color" );
                    lua_setmetatable( L, -2 );
                }
            }, argument );
        }

        if ( lua_pcall( L, args.size( ), 0, 0 ) != LUA_OK ) {
            std::cerr << "Error running connection '" << connection_name << "': " << lua_tostring( L, -1 ) << "\n";
            // TODO: Remove connection to prevent spam erroring

            lua_pop( L, 1 );
        }
    }
}

int CCallbacks::AddConnection( const char* connection_name, int function_reference ) {
    m_Connections[ connection_name ].push_back( std::make_pair( m_ConnectionCount, function_reference ) );

    return m_ConnectionCount++;
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