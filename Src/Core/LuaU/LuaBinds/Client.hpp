#pragma once

#include "../../Client/Client.hpp"

namespace LuaBind::LuaClient {
    int GetUsername( lua_State* lua_state ) {
        lua_pushstring( lua_state, Client.Username );

        return 1;
    }

    int GetDeltaTime( lua_State* lua_state ) {
        lua_pushnumber( lua_state, Client.DeltaTime );

        return 1;
    }

    int GetRealTime( lua_State* lua_state ) {
        lua_pushnumber( lua_state, Client.RealTime );

        return 1;
    }

    int GetFps( lua_State* lua_state ) {
        lua_pushinteger( lua_state, Client.Fps );

        return 1;
    }
}