#pragma once

namespace LuaBind::LuaDebug {
    int GetRegistry( lua_State* lua_state ) {
        lua_pushvalue( lua_state, LUA_REGISTRYINDEX );

        return 1;
    }

    int GetUpvalues( lua_State* lua_state ) {
        if ( !lua_isfunction( lua_state, 1 ) ) {
            luaL_argerror( lua_state, 1, "Must be a function" );
            return 0;
        }

        lua_newtable( lua_state );

        int TableIndex = lua_gettop( lua_state ), Index = 1;

        while ( 1 ) {
            const char* Upvalue = lua_getupvalue( lua_state, 1, Index );

            if ( Upvalue == NULL )
                break;

            // NOTE: Value is pushed back from stack, its pushed by 'lua_getupvalue' above.

            lua_pushinteger( lua_state, Index );
            lua_pushvalue( lua_state, -2 );

            lua_settable( lua_state, TableIndex );

            lua_pop( lua_state, 1 );

            Index++;
        }

        return 1;
    }

    int GetUpvalue( lua_State* lua_state ) {
        if ( !lua_isfunction( lua_state, 1 ) ) {
            luaL_argerror( lua_state, 1, "Must be a function" );
            return 0;
        }

        if ( !lua_isnumber( lua_state, 2 ) ) {
            luaL_argerror( lua_state, 2, "Must be a number" );
            return 0;
        }

        int Index = luaL_checkinteger( lua_state, 2 );
        const char* Upvalue = lua_getupvalue( lua_state, 1, Index );

        if ( Upvalue == NULL ) {
            lua_settop( lua_state, 2 );
            lua_pushnil( lua_state );

            return 1;
        }

        return 1;
    }

    int SetUpvalue( lua_State* lua_state ) {
        if ( !lua_isfunction( lua_state, 1 ) ) {
            luaL_argerror( lua_state, 1, "Must be a function" );
            return 0;
        }

        if ( !lua_isnumber( lua_state, 2 ) ) {
            luaL_argerror( lua_state, 2, "Must be a number" );
            return 0;
        }

        if ( lua_gettop( lua_state ) < 3 ) {
            luaL_argerror( lua_state, 3, "Missing new value" );
            return 0;
        }

        int Index = luaL_checkinteger( lua_state, 2 );

        lua_pushvalue( lua_state, 3 );

        const char* Upvalue = lua_setupvalue( lua_state, 1, Index );

        if ( Upvalue == NULL )
            luaL_error( lua_state, ( "Upvalue at index: " + std::to_string( Index ) + " doesn't exist!" ).c_str( ) );

        return 0;
    }
}