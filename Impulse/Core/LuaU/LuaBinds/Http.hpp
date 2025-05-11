#pragma once

#include "../../Http/Http.hpp"

namespace LuaBind::LuaHttp {
    int Get( lua_State* lua_state ) {
        lua_pushstring( lua_state, Http::Get( luaL_checkstring( lua_state, 1 ) ).c_str( ) );

        return 0;
    }

    int Post( lua_State* lua_state ) {
        lua_pushstring( lua_state, Http::Post( luaL_checkstring( lua_state, 1 ), luaL_checkstring( lua_state, 2 ) ).c_str( ) );

        return 0;
    }

    int Put( lua_State* lua_state ) {
        lua_pushstring( lua_state, Http::Put( luaL_checkstring( lua_state, 1 ), luaL_checkstring( lua_state, 2 ) ).c_str( ) );

        return 0;
    }

    int Delete( lua_State* lua_state ) {
        lua_pushstring( lua_state, Http::Delete( luaL_checkstring( lua_state, 1 ) ).c_str( ) );

        return 0;
    }
}