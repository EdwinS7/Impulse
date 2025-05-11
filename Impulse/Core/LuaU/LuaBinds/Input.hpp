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

    int IsKeyHeld( lua_State* lua_state ) {
        lua_pushboolean( lua_state, Input.IsKeyHeld( luaL_checkinteger( lua_state, 1 ) ) );

        return 1;
    }

    int SetCursorPosition( lua_State* lua_state ) {
        Input.SetCursorPosition( *( Vector2* ) luaL_checkudata( lua_state, 1, "vector2" ), true );

        return 1;
    }

    int GetCursorPosition( lua_State* lua_state ) {
        Vector2 MousePosition = Input.GetCursorPosition( );

        auto Vector = ( Vector2* ) lua_newuserdata( lua_state, sizeof( Vector2 ) );

        new ( Vector ) Vector2(
            static_cast< double >( MousePosition.x ),
            static_cast< double >( MousePosition.y )
        );

        luaL_getmetatable( lua_state, "vector2" );
        lua_setmetatable( lua_state, -2 );

        return 1;
    }

    int SetCursorStyle( lua_State* lua_state ) {
        Input.SetCursorStyle( ( PointerStyle ) luaL_checknumber( lua_state, 1 ) );

        return 0;
    }

    int GetCursorStyle( lua_State* lua_state ) {
        lua_pushnumber( lua_state, ( double ) Input.GetCursorStyle( ) );

        return 1;
    }
}