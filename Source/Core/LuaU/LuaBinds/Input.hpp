#pragma once

#include "../../Input/Input.hpp"

namespace LuaBind::LuaInput {
    int IsActive( lua_State* lua_state ) {
        lua_pushboolean( lua_state, Input.IsActive( ) );

        return 1;
    }

    int IsKeyPressed( lua_State* lua_state ) {
        lua_pushboolean( lua_state, Input.IsKeyPressed( luaL_checkinteger( lua_state, 1 ) ) );

        return 1;
    }

    int IsKeyDown( lua_State* lua_state ) {
        lua_pushboolean( lua_state, Input.IsKeyDown( luaL_checkinteger( lua_state, 1 ) ) );

        return 1;
    }

    int SetMousePosition( lua_State* lua_state ) {
        Input.SetMousePosition( *( Vector2* ) luaL_checkudata( lua_state, 1, "vector2" ), true );

        return 1;
    }

    int GetMousePosition( lua_State* lua_state ) {
        Vector2 MousePosition = Input.GetMousePosition( );

        auto Vector = ( Vector2* ) lua_newuserdata( lua_state, sizeof( Vector2 ) );
        new ( Vector ) Vector2(
            MousePosition.x,
            MousePosition.y
        );

        luaL_getmetatable( lua_state, "vector2" );
        lua_setmetatable( lua_state, -2 );

        return 1;
    }

    int GetCursor( lua_State* lua_state ) {
        lua_pushinteger( lua_state, static_cast<int>( Input.GetCursor( ) ) );

        return 1;
    }

    int SetCursor( lua_State* lua_state ) {
        Input.SetCursor( static_cast< PointerStyle >( luaL_checkinteger( lua_state, 1 ) ) );

        return 0;
    }
}