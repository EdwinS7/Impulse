#pragma once

#include "../../Utils/Utils.hpp"

namespace LuaBind::LuaUtils {
    int RandomString( lua_State* lua_state ) {
        lua_pushstring( lua_state, Utils.RandomString( luaL_checkinteger( lua_state, 1 ) ) );

        return 0;
    }

    int SetClipboard( lua_State* lua_state ) {
        Utils.SetClipboard( luaL_checkstring( lua_state, 1 ) );

        return 0;
    }

    int GetClipboard( lua_State* lua_state ) {
        lua_pushstring( lua_state, Utils.GetClipboard( ) );

        return 0;
    }

    int IsInternetConnected( lua_State* lua_state ) {
        lua_pushboolean( lua_state, Utils.IsInternetConnected( ) );

        return 1;
    }
}