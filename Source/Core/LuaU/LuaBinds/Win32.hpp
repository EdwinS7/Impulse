#pragma once

#include "../../Win32/Win32.hpp"

namespace LuaBind::LuaWin32 {
    std::unordered_map<int, HWND> WindowHandles;
    std::unordered_map<int, HWND> ConsoleHandles;

    int CreateWindow_( lua_State* lua_state ) {
        auto Position = *( Vector2* ) luaL_checkudata( lua_state, 2, "vector2" );
        auto Size = *( Vector2* ) luaL_checkudata( lua_state, 3, "vector2" );

        HWND WindowHandle = Win32.CreateWindow_(
            lua_tostring( lua_state, 1 ), Position, Size, lua_toboolean( lua_state, 4 )
        );

        if ( !WindowHandle ) {
            lua_pushnil( lua_state );
            return 1;
        }

        int WindowRef = static_cast< int >( WindowHandles.size( ) + 1 );
        WindowHandles[ WindowRef ] = WindowHandle;

        RECT ClientRect;
        GetClientRect( WindowHandle, &ClientRect );

        lua_pushinteger( lua_state, WindowRef );

        auto Vector = ( Vector2* ) lua_newuserdata( lua_state, sizeof( Vector2 ) );

        new ( Vector ) Vector2(
            static_cast< int >( ClientRect.right - ClientRect.left ),
            static_cast< int >( ClientRect.bottom - ClientRect.top )
        );

        luaL_getmetatable( lua_state, "vector2" );
        lua_setmetatable( lua_state, -2 );

        return 2;
    }

    int DestroyWindow( lua_State* lua_state ) {
        HWND WindowHandle = WindowHandles[ luaL_checkinteger( lua_state, 1 ) ];

        if ( !WindowHandle )
            return 1;

        Win32.DestroyWindow( WindowHandle );

        return 0;
    }

    int CreateConsole( lua_State* lua_state ) {
        auto Position = *( Vector2* ) luaL_checkudata( lua_state, 2, "vector2" );
        auto Size = *( Vector2* ) luaL_checkudata( lua_state, 3, "vector2" );

        HWND ConsoleHandle = Win32.CreateConsole(
            lua_tostring( lua_state, 1 ), Position, Size
        );

        if ( ConsoleHandle ) {
            int ConsoleRef = static_cast< int >( ConsoleHandles.size( ) + 1 );
            ConsoleHandles[ ConsoleRef ] = ConsoleHandle;

            lua_pushinteger( lua_state, ConsoleRef );
        }
        else {
            lua_pushnil( lua_state );
        }

        return 1;
    }

    int DestroyConsole( lua_State* lua_state ) {
        HWND ConsoleHandle = ConsoleHandles[ luaL_checkinteger( lua_state, 1 ) ];

        if ( !ConsoleHandle )
            return 1;

        Win32.DestroyConsole( ConsoleHandle );

        return 0;
    }

    int MessageBox_( lua_State* lua_state ) {
        int Reference = luaL_checkinteger( lua_state, 1 );

        HWND WindowHandle = WindowHandles[ Reference ];
        HWND ConsoleHandle = ConsoleHandles[ Reference ];
        HWND Handle = WindowHandle ? WindowHandle : ConsoleHandle;

        if ( Handle )
            Win32.MessageBox_( Handle, luaL_checkstring( lua_state, 2 ), luaL_checkstring( lua_state, 3 ), luaL_checkinteger( lua_state, 4 ) );

        return 0;
    }

    int GetScreenSize( lua_State* lua_state ) {
        Vector2 ScreenSize = Win32.GetScreenSize( );

        auto Vector = ( Vector2* ) lua_newuserdata( lua_state, sizeof( Vector2 ) );

        new ( Vector ) Vector2(
           ScreenSize.x,
           ScreenSize.y
        );

        luaL_getmetatable( lua_state, "vector2" );
        lua_setmetatable( lua_state, -2 );

        return 1;
    }
}