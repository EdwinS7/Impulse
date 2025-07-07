#pragma once

#include "../../Graphics/Renderer/Renderer.hpp"

namespace LuaBind::LuaRenderer {
    int WriteToBuffer( lua_State* lua_state )  {
        if ( !lua_istable( lua_state, 2 ) || !lua_istable( lua_state, 3 ) ) {
            luaL_error( lua_state, "Expected tables at argument 2 (vertices) and 3 (indices)" );
            return 0;
        }

        std::vector<Vertex> Vertices;
        lua_pushnil( lua_state );
        while ( lua_next( lua_state, 2 ) != 0 ) {
            if ( lua_isuserdata( lua_state, -1 ) ) {
                Vertex* _Vertex = static_cast< Vertex* >(
                    luaL_checkudata( lua_state, -1, "vertex" )
                );

                Vertices.push_back( *_Vertex );
            }

            lua_pop( lua_state, 1 );
        }

        std::vector<std::int32_t> Indices;
        lua_pushnil( lua_state );
        while ( lua_next( lua_state, 3 ) != 0 ) {
            if ( lua_isnumber( lua_state, -1 ) ) {
                Indices.push_back( static_cast< std::int32_t >(
                    lua_tointeger( lua_state, -1 )
                    ) );
            }

            lua_pop( lua_state, 1 );
        }

        DrawCommand** _DrawCommand = static_cast< DrawCommand** >(
           lua_newuserdata( lua_state, sizeof( DrawCommand* ) )
        );

        Texture* _Texture = nullptr;
        void* UserData = lua_touserdata( lua_state, 4 );
        if ( UserData != nullptr ) {
            if ( lua_getmetatable( lua_state, 4 ) ) {
                luaL_getmetatable( lua_state, "texture" );

                if ( lua_rawequal( lua_state, -1, -2 ) ) {
                    _Texture = *static_cast< Texture** >( UserData );
                }

                lua_pop( lua_state, 2 );
            }
        }

        *_DrawCommand = Renderer.WriteToBuffer(
            D3D_PRIMITIVE_TOPOLOGY( luaL_checkinteger( lua_state, 1 ) ),
            &Vertices, &Indices, _Texture,
            luaL_optinteger( lua_state, 5, 0 )
        );

        luaL_getmetatable( lua_state, "draw_command" );
        lua_setmetatable( lua_state, -2 );

        return 1;
    }
}