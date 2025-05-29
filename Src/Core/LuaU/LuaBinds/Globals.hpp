#pragma once

#include "../../Http/Http.hpp"
#include "Win32.hpp"

namespace LuaBind::LuaGlobals {
    int Print( lua_State* lua_state ) {
        HWND ConsoleHandle = LuaWin32::ConsoleHandles[ luaL_checkinteger( lua_state, 1 ) ];

        if ( !ConsoleHandle )
            return 0;

        Win32.RedirectConsole( ConsoleHandle );

        int ArgCount = lua_gettop( lua_state );

        for ( int i = 2; i <= ArgCount; ++i ) {
            const char* String = lua_tostring( lua_state, i );

            if ( String )
                std::cout << String;

            if ( i < ArgCount )
                std::cout << "\t";
        }

        std::cout << "\n";

        return 0;
    }

    int AddConnection( lua_State* lua_state ) {
        lua_pushinteger( lua_state, Callbacks.AddConnection(
            luaL_checkstring( lua_state, 1 ),
            lua_ref( lua_state, 2 )
        ) );

        return 1;
    }

    int RemoveConnection( lua_State* lua_state ) {
        Callbacks.RemoveConnection( luaL_checkinteger( lua_state, 1 ) );

        return 0;
    }

    int LoadString_( lua_State* lua_state ) {
        const char* Source = luaL_checkstring( lua_state, 1 );

        size_t BytecodeSize;
        char* Bytecode = luau_compile( Source, strlen( Source ), nullptr, &BytecodeSize );

        if ( !Bytecode ) {
            lua_pushnil( lua_state );
            lua_pushstring( lua_state, "failed to compile" );
            return 2;
        }

        int Status = luau_load( lua_state, luaL_optstring( lua_state, 2, "chunk" ), Bytecode, BytecodeSize, 0 );
        free( Bytecode );

        if ( Status != LUA_OK ) {
            lua_pushnil( lua_state );
            lua_insert( lua_state, -2 );
            return 2;
        }

        lua_pushvalue( lua_state, LUA_GLOBALSINDEX );
        lua_setfenv( lua_state, -2 );

        return 1;
    }

    int NewCClosure( lua_State* lua_state ) {
        lua_pushvalue( lua_state, 1 );

        lua_pushcclosure( lua_state, [ ] ( lua_State* L ) -> int {
            lua_getupvalue( L, lua_upvalueindex( 1 ), 1 );
            lua_insert( L, 1 );

            lua_call( L, lua_gettop( L ) - 1, LUA_MULTRET );

            return lua_gettop( L );
        }, Utils.RandomString( 16 ), 1 );

        return 1;
    }

    int IsLuaClosure( lua_State* lua_state ) {
        lua_pushboolean( lua_state, lua_isLfunction( lua_state, 1 ) );

        return 1;
    }

    int IsCClosure( lua_State* lua_state ) {
        lua_pushboolean( lua_state, lua_iscfunction( lua_state, 1 ) );

        return 1;
    }

    int GetWrappedOriginal( lua_State* lua_state ) {
        lua_getupvalue( lua_state, 1, 1 );

        if ( !lua_isfunction( lua_state, -1 ) ) {
            lua_pop( lua_state, 1 );
            lua_pushnil( lua_state );
        }

        return 1;
    }

    int SetReadOnly( lua_State* lua_state ) {
        lua_setreadonly( lua_state, 1, luaL_checkboolean( lua_state, 1 ) );

        return 1;
    }

    int GetReadOnly( lua_State* lua_state ) {
        lua_pushboolean( lua_state, lua_getreadonly( lua_state, 1 ) );

        return 1;
    }

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

    int HasInternet( lua_State* lua_state ) {
        lua_pushboolean( lua_state, Utils.IsInternetConnected( ) );

        return 1;
    }

    int Get( lua_State* lua_state ) {
        lua_pushstring( lua_state, Http.Get( luaL_checkstring( lua_state, 1 ) ).c_str( ) );

        return 0;
    }

    int Post( lua_State* lua_state ) {
        lua_pushstring( lua_state, Http.Post( luaL_checkstring( lua_state, 1 ), luaL_checkstring( lua_state, 2 ) ).c_str( ) );

        return 0;
    }

    int Put( lua_State* lua_state ) {
        lua_pushstring( lua_state, Http.Put( luaL_checkstring( lua_state, 1 ), luaL_checkstring( lua_state, 2 ) ).c_str( ) );

        return 0;
    }

    int Delete( lua_State* lua_state ) {
        lua_pushstring( lua_state, Http.Delete( luaL_checkstring( lua_state, 1 ) ).c_str( ) );

        return 0;
    }
}