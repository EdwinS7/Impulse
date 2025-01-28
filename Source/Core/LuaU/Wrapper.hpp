#ifndef LUAU_RUNTIME_H
#define LUAU_RUNTIME_H

#include "../Common.hpp"
#include "../Memory/Memory.hpp"
#include "../FileSystem/FileSystem.hpp"
#include "../Utils/Utils.hpp"
#include "../Win32/Win32.hpp"
#include "../Http/Http.hpp"

int Copyable( lua_State* L ) {
    return 1;
}

namespace Wrapper {
    namespace Utils_ {
        int RandomString( lua_State* L ) {
            luaL_checktype( L, 1, LUA_TNUMBER );

            lua_pushstring( L, Utils::RandomString( luaL_checkinteger( L, 1 ) ) );

            return 1;
        }

        int SetClipboard( lua_State* L ) {
            Utils::SetClipboard( luaL_checkstring( L, 1 ) );

            return 1;
        }

        int GetClipboard( lua_State* L ) {
            lua_pushstring( L, Utils::GetClipboard( ) );

            return 1;
        }
    }

    namespace FileSystem_ {
        int ReadFile( lua_State* L ) {
            luaL_checktype( L, 1, LUA_TSTRING );
            lua_pushstring( L, FileSystem::ReadFile( luaL_checkstring( L, 1 ) ).c_str( ) );

            return 1;
        }

        int WriteFile( lua_State* L ) {
            luaL_checktype( L, 1, LUA_TSTRING );
            luaL_checktype( L, 2, LUA_TSTRING );

            FileSystem::WriteFile( luaL_checkstring( L, 1 ), luaL_checkstring( L, 2 ) );

            return 1;
        }
    }

    namespace Win32_ {
        std::unordered_map<int, HWND> WindowHandles;
        std::unordered_map<int, HWND> ConsoleHandles;

        int CreateWindow_( lua_State* L ) {
            HWND WindowHandle = Win32::CreateWindow_( lua_tostring( L, 1 ),
                lua_tointeger( L, 2 ), lua_tointeger( L, 3 ), lua_toboolean( L, 4 )
            );

            if ( WindowHandle ) {
                int WindowRef = WindowHandles.size( ) + 1;
                WindowHandles[ WindowRef ] = WindowHandle;

                lua_pushinteger( L, WindowRef );
            }
            else {
                lua_pushnil( L );
            }

            return 1;
        }

        int DestroyWindow( lua_State* L ) {
            HWND WindowHandle = WindowHandles[ luaL_checkinteger( L, 1 ) ];

            if ( !WindowHandle )
                return 0;

            Win32::DestroyWindow( &WindowHandle );

            return 1;
        }

        int CreateConsole( lua_State* L ) {
            HWND ConsoleHandle = Win32::CreateConsole(
                lua_tostring( L, 1 ), lua_tointeger( L, 2 ), lua_tointeger( L, 3 )
            );

            if ( ConsoleHandle ) {
                int ConsoleRef = ConsoleHandles.size( ) + 1;
                ConsoleHandles[ ConsoleRef ] = ConsoleHandle;

                lua_pushinteger( L, ConsoleRef );
            }
            else {
                lua_pushnil( L );
            }

            return 1;
        }

        int DestroyConsole( lua_State* L ) {
            HWND ConsoleHandle = ConsoleHandles[ luaL_checkinteger( L, 1 ) ];

            if ( !ConsoleHandle )
                return 0;

            Win32::DestroyConsole( &ConsoleHandle );

            return 1;
        }

        int MessageBox_( lua_State* L ) {
            int Reference = luaL_checkinteger( L, 1 );

            HWND WindowHandle = WindowHandles[ Reference ];
            HWND ConsoleHandle = ConsoleHandles[ Reference ];
            HWND Handle = WindowHandle ? WindowHandle : ConsoleHandle;

            Win32::MessageBox_( &Handle, luaL_checkstring( L, 2 ), luaL_checkstring( L, 3 ), luaL_checkinteger( L, 4 ) );

            return 1;
        }
    }

    namespace Http_ {
        int Get( lua_State* L ) {
            lua_pushstring( L, Http::Get( luaL_checkstring( L, 1 ) ).c_str() );

            return 1;
        }

        int Post( lua_State* L ) {
            lua_pushstring( L, Http::Post( luaL_checkstring( L, 1 ), luaL_checkstring( L, 2 ) ).c_str( ) );

            return 1;
        }

        int Put( lua_State* L ) {
            lua_pushstring( L, Http::Put( luaL_checkstring( L, 1 ), luaL_checkstring( L, 2 ) ).c_str( ) );

            return 1;
        }

        int Delete( lua_State* L ) {
            lua_pushstring( L, Http::Delete( luaL_checkstring( L, 1 ) ).c_str( ) );

            return 1;
        }
    }

    static std::unordered_map<const void*, const void*> HookedFunctions;

    int HookFunction( lua_State* L ) {
        luaL_checktype( L, 1, LUA_TFUNCTION );
        luaL_checktype( L, 2, LUA_TFUNCTION );

        if ( lua_iscfunction( L, 1 ) ) {
            // NOTE: This is only temporary!
            luaL_argerror( L, 1, "Cannot hook C functions" );
            return 0;
        }

        if ( lua_iscfunction( L, 2 ) ) {
            luaL_argerror( L, 2, "Lua function expected" );
            return 0;
        }

        // Do it do it, yh yh d-d-do it do it shake it shake it like sum jello feelin hella mello
        // I'm a poet

        return 1;
    }

    int RestoreFunction( lua_State* L ) {
        return 1;
    }
}

#endif