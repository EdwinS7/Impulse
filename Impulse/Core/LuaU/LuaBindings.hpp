#ifndef LUAU_BINDINGS_H
#define LUAU_BINDINGS_H

#include "../Common.hpp"
#include "Environment.hpp"
#include "../FileSystem/FileSystem.hpp"
#include "../Win32/Win32.hpp"
#include "../Graphics/Include.hpp"
#include "../Input/Input.hpp"
#include "../Http/Http.hpp"
#include "../Utils/Utils.hpp"

// NOTE: Just here so I can copy it for creating new stuff
int Dummy( lua_State* L ) {
    lua_pushboolean( L, true ); // Push our return value.

    return 1; // Indicates were returning 1 value ( true ).
}

namespace Wrapper {
    namespace Types {
        namespace Vector2_ {
            int New( lua_State* lua_state ) {
                Vector2* Vector = static_cast< Vector2* >( 
                    lua_newuserdata( lua_state, sizeof( Vector2 ) )
                );

                new ( Vector ) Vector2(
                    lua_tointeger( lua_state, 1 ),
                    lua_tointeger( lua_state, 2 )
                );

                luaL_getmetatable( lua_state, "vector2" );
                lua_setmetatable( lua_state, -2 );

                return 1;
            }

            int Index( lua_State* lua_state ) {
                Vector2* Vector = static_cast< Vector2* >( 
                    luaL_checkudata( lua_state, 1, "vector2" )
                );

                const char* Key = lua_tostring( lua_state, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    lua_pushinteger( lua_state, Vector->x );
                else if ( strcmp( Key, "y" ) == 0 )
                    lua_pushinteger( lua_state, Vector->y );
                else
                    luaL_error( lua_state, "invalid property '%s' for vector2", Key );

                return 1;
            }

            int NewIndex( lua_State* lua_state ) {
                Vector2* Vector = static_cast< Vector2* >( 
                    luaL_checkudata( lua_state, 1, "vector2" )
                );

                const char* Key = lua_tostring( lua_state, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    Vector->x = luaL_checkinteger( lua_state, 3 );
                else if ( strcmp( Key, "y" ) == 0 )
                    Vector->y = luaL_checkinteger( lua_state, 3 );
                else
                    luaL_error( lua_state, "invalid property '%s' for vector2", Key );

                return 0;
            }
        }

        namespace Vector3_ {
            int New( lua_State* lua_state ) {
                Vector3* Vector = static_cast< Vector3* >(
                    lua_newuserdata( lua_state, sizeof( Vector3 ) )
                );

                new ( Vector ) Vector3(
                    static_cast< float >( lua_tonumber( lua_state, 1 ) ),
                    static_cast< float >( lua_tonumber( lua_state, 2 ) ),
                    static_cast< float >( lua_tonumber( lua_state, 3 ) )
                );

                luaL_getmetatable( lua_state, "vector3" );
                lua_setmetatable( lua_state, -2 );

                return 1;
            }

            int Index( lua_State* lua_state ) {
                Vector3* Vector = ( Vector3* ) luaL_checkudata( 
                    lua_state, 1, "vector3"
                );
                
                const char* Key = lua_tostring( lua_state, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( Vector->x ) );
                else if ( strcmp( Key, "y" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( Vector->y ) );
                else if ( strcmp( Key, "z" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( Vector->z ) );
                else
                    luaL_error( lua_state, "invalid field '%s' for vector3", Key );

                return 1;
            }

            int NewIndex( lua_State* lua_state ) {
                Vector3* Vector = ( Vector3* ) luaL_checkudata( 
                    lua_state, 1, "vector3"
                );

                const char* Key = lua_tostring( lua_state, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    Vector->x = static_cast< float >( lua_tonumber( lua_state, 3 ) );
                else if ( strcmp( Key, "y" ) == 0 )
                    Vector->y = static_cast< float >( lua_tonumber( lua_state, 3 ) );
                else if ( strcmp( Key, "z" ) == 0 )
                    Vector->z = static_cast< float >( lua_tonumber( lua_state, 3 ) );
                else
                    luaL_error( lua_state, "invalid field '%s' for vector3", Key );

                return 0;
            }
        }

        namespace Vertex_ {
            int New( lua_State* lua_state ) {
                Vertex* Vertex_ = ( Vertex* ) lua_newuserdata( 
                    lua_state, sizeof( Vertex )
                );

                new ( Vertex_ ) Vertex(
                    static_cast< float >( lua_tonumber( lua_state, 1 ) ),
                    static_cast< float >( lua_tonumber( lua_state, 2 ) ),
                    static_cast< float >( lua_tonumber( lua_state, 3 ) ),
                    static_cast< float >( lua_tonumber( lua_state, 4 ) ),
                    static_cast< float >( lua_tonumber( lua_state, 5 ) ),
                    static_cast< float >( lua_tonumber( lua_state, 6 ) ),
                    static_cast< unsigned long >( lua_tonumber( lua_state, 7 ) )
                );

                luaL_getmetatable( lua_state, "vertex" );
                lua_setmetatable( lua_state, -2 );

                return 1;
            }

            int Index( lua_State* lua_state ) {
                Vertex* Vertex_ = ( Vertex* ) luaL_checkudata( 
                    lua_state, 1, "vertex"
                );

                const char* Key = lua_tostring( lua_state, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( Vertex_->x ) );
                else if ( strcmp( Key, "y" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( Vertex_->y ) );
                else if ( strcmp( Key, "z" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( Vertex_->z ) );
                else if ( strcmp( Key, "rhw" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( Vertex_->rhw ) );
                else if ( strcmp( Key, "u" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( Vertex_->u ) );
                else if ( strcmp( Key, "v" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( Vertex_->v ) );
                else if ( strcmp( Key, "color" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( Vertex_->color ) );
                else
                    luaL_error( lua_state, "invalid field '%s' for vertex", Key );

                return 1;
            }

            int NewIndex( lua_State* lua_state ) {
                Vertex* _Vertex = ( Vertex* ) luaL_checkudata( 
                    lua_state, 1, "vertex"
                );

                const char* Key = lua_tostring( lua_state, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    _Vertex->x = static_cast< float >( lua_tonumber( lua_state, 3 ) );
                else if ( strcmp( Key, "y" ) == 0 )
                    _Vertex->y = static_cast< float >( lua_tonumber( lua_state, 3 ) );
                else if ( strcmp( Key, "z" ) == 0 )
                    _Vertex->z = static_cast< float >( lua_tonumber( lua_state, 3 ) );
                else if ( strcmp( Key, "rhw" ) == 0 )
                    _Vertex->rhw = static_cast< float >( lua_tonumber( lua_state, 3 ) );
                else if ( strcmp( Key, "u" ) == 0 )
                    _Vertex->u = static_cast< float >( lua_tonumber( lua_state, 3 ) );
                else if ( strcmp( Key, "v" ) == 0 )
                    _Vertex->v = static_cast< float >( lua_tonumber( lua_state, 3 ) );
                else if ( strcmp( Key, "color" ) == 0 )
                    _Vertex->color = static_cast< unsigned long >( lua_tonumber( lua_state, 3 ) );
                else
                    luaL_error( lua_state, "invalid field '%s' for vertex", Key );

                return 0;
            }
        }

        namespace Color_ {
            int New( lua_State* lua_state ) {
                auto _Color = ( Color* ) lua_newuserdata( 
                    lua_state, sizeof( Color )
                );

                new ( _Color ) Color(
                    static_cast< uint8_t >( lua_tointeger( lua_state, 1 ) ), // r
                    static_cast< uint8_t >( lua_tointeger( lua_state, 2 ) ), // g
                    static_cast< uint8_t >( lua_tointeger( lua_state, 3 ) ), // b
                    static_cast< uint8_t >( luaL_optinteger( lua_state, 4, 255 ) ) // a: 255 (opt)
                );

                luaL_getmetatable( lua_state, "color" );
                lua_setmetatable( lua_state, -2 );

                return 1;
            }

            int Index( lua_State* lua_state ) {
                Color* _Color = ( Color* ) luaL_checkudata( lua_state, 1, "color" );
                
                const char* Key = lua_tostring( lua_state, 2 );

                if ( strcmp( Key, "r" ) == 0 )
                    lua_pushinteger( lua_state, static_cast< int >( _Color->r ) );
                else if ( strcmp( Key, "g" ) == 0 )
                    lua_pushinteger( lua_state, static_cast< int >( _Color->g ) );
                else if ( strcmp( Key, "b" ) == 0 )
                    lua_pushinteger( lua_state, static_cast< int >( _Color->b ) );
                else if ( strcmp( Key, "a" ) == 0 )
                    lua_pushinteger( lua_state, static_cast< int >( _Color->a ) );
                else if ( strcmp( Key, "hex" ) == 0 )
                    lua_pushnumber( lua_state, static_cast< double >( 
                        RGBA_TO_DWORD( _Color->r, _Color->g, _Color->b, _Color->a )
                    ) );
                else
                    luaL_error( lua_state, "invalid field '%s' for color", Key );

                return 1;
            }

            int NewIndex( lua_State* lua_state ) {
                Color* _Color = ( Color* ) luaL_checkudata( 
                    lua_state, 1, "color"
                );

                const char* Key = lua_tostring( lua_state, 2 );

                if ( strcmp( Key, "r" ) == 0 )
                    _Color->r = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
                else if ( strcmp( Key, "g" ) == 0 )
                    _Color->g = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
                else if ( strcmp( Key, "b" ) == 0 )
                    _Color->b = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
                else if ( strcmp( Key, "a" ) == 0 )
                    _Color->a = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
                else
                    luaL_error( lua_state, "invalid field '%s' for color", Key );

                return 0;
            }
        }

        namespace DrawCommand_ {
            int New( lua_State* lua_state ) {
                auto _DrawCommand = ( DrawCommand* ) lua_newuserdata( 
                    lua_state, sizeof( DrawCommand )
                );

                // TODO: add other args
                new ( _DrawCommand ) DrawCommand(
                    D3D_PRIMITIVE_TOPOLOGY( luaL_optinteger( lua_state, 1, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) )
                );

                luaL_getmetatable( lua_state, "draw_command" );
                lua_setmetatable( lua_state, -2 );

                return 1;
            }

            int Index( lua_State* lua_state ) {
                DrawCommand* _DrawCommand = *( DrawCommand** ) luaL_checkudata( 
                    lua_state, 1, "draw_command"
                );

                auto Key = lua_tostring( lua_state, 2 );

                if ( strcmp( Key, "primitive_topology" ) == 0 )
                    lua_pushinteger( lua_state, static_cast< int >( _DrawCommand->primitive_topology ) );
                else if ( strcmp( Key, "vertices" ) == 0 ) {
                    lua_createtable( lua_state, static_cast< int >( _DrawCommand->vertices.size( ) ), 0 );

                    for ( size_t i = 0; i < _DrawCommand->vertices.size( ); i++ ) {
                        auto _Vertex = ( Vertex* ) lua_newuserdata( 
                            lua_state, sizeof( Vertex )
                        );

                        *_Vertex = _DrawCommand->vertices[ i ];

                        luaL_getmetatable( lua_state, "vertex" );
                        lua_setmetatable( lua_state, -2 );

                        lua_rawseti( lua_state, -2, static_cast< int >( i + 1 ) );
                    }
                } else if ( strcmp( Key, "indices" ) == 0 ) {
                    lua_createtable( lua_state, static_cast< int >( _DrawCommand->indices.size( ) ), 0 );

                    for ( size_t i = 0; i < _DrawCommand->indices.size( ); i++ ) {
                        lua_pushinteger( lua_state, static_cast< int >( _DrawCommand->indices[ i ] ) );
                        lua_rawseti( lua_state, -2, static_cast< int >( i + 1 ) );
                    }
                } else if ( strcmp( Key, "z_index" ) == 0 )
                    lua_pushinteger( lua_state, static_cast< int >( _DrawCommand->z_index ) );
                else
                    luaL_error( lua_state, "invalid field '%s' for draw_command", Key );

                return 1;
            }

            int NewIndex( lua_State* lua_state ) {
                DrawCommand* _DrawCommand = *( DrawCommand** ) luaL_checkudata(
                    lua_state, 1, "draw_command"
                );

                auto Key = lua_tostring( lua_state, 2 );

                if ( strcmp( Key, "primitive_topology" ) == 0 ) {
                    _DrawCommand->primitive_topology = static_cast< D3D_PRIMITIVE_TOPOLOGY >(
                        lua_tonumber( lua_state, 3 )
                    );
                }
                else if ( strcmp( Key, "vertices" ) == 0 ) {
                    size_t TableLength = static_cast< size_t >( lua_objlen( lua_state, 3 ) );

                    _DrawCommand->vertices.resize( TableLength );

                    for ( size_t i = 1; i <= TableLength; i++ ) {
                        lua_rawgeti( lua_state, 3, static_cast< int >( i ) );

                        auto* _Vertex = static_cast< Vertex* >(
                            luaL_checkudata( lua_state, -1, "vertex" )
                        );

                        _DrawCommand->vertices[ i - 1 ] = *_Vertex;

                        lua_pop( lua_state, 1 );
                    }
                }
                else if ( strcmp( Key, "indices" ) == 0 ) {
                    size_t TableLength = lua_objlen( lua_state, 3 );

                    _DrawCommand->indices.resize( TableLength );

                    for ( size_t i = 1; i <= TableLength; i++ ) {
                        lua_rawgeti( lua_state, 3, static_cast< int >( i ) );
                        _DrawCommand->indices[ i - 1 ] = lua_tointeger( lua_state, -1 );
                        lua_pop( lua_state, 1 );
                    }
                } else if ( strcmp( Key, "primitive_topology" ) == 0 )
                    _DrawCommand->z_index = lua_tonumber( lua_state, 3 );
                else
                    luaL_error( lua_state, "invalid field '%s' for draw_command", Key );

                return 0;
            }
        }
    }

    namespace Utils_ {
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

    namespace FileSystem_ {
        int ListFiles( lua_State* lua_state ) {
            lua_newtable( lua_state );

            std::vector<std::string> Files = FileSystem.ListFiles( luaL_checkstring( lua_state, 1 ) );

            for ( size_t i = 0; i < Files.size( ); i++ ) {
                lua_pushinteger( lua_state, static_cast< int >( i + 1 ) );
                lua_pushstring( lua_state, Files[ i ].c_str( ) );
                lua_settable( lua_state, -3 );
            }

            return 1;
        }

        int FileExists( lua_State* lua_state ) {
            lua_pushboolean( lua_state, FileSystem.FileExists( luaL_checkstring( lua_state, 1 ) ) );

            return 1;
        }

        int ReadFile( lua_State* lua_state ) {
            lua_pushstring( lua_state, FileSystem.ReadFile( luaL_checkstring( lua_state, 1 ) ).c_str( ) );

            return 1;
        }

        int WriteFile( lua_State* lua_state ) {
            FileSystem.WriteFile( luaL_checkstring( lua_state, 1 ), luaL_checkstring( lua_state, 2 ) );

            return 0;
        }

        int RenameFile( lua_State* lua_state ) {
            FileSystem.RenameFile( luaL_checkstring( lua_state, 1 ), luaL_checkstring( lua_state, 2 ) );

            return 0;
        }

        int DeleteFile_( lua_State* lua_state ) {
            FileSystem.DeleteFile_( luaL_checkstring( lua_state, 1 ) );

            return 0;
        }

        int ListDirectories( lua_State* lua_state ) {
            lua_newtable( lua_state );

            std::vector<std::string> Directories = FileSystem.ListDirectories( luaL_checkstring( lua_state, 1 ) );

            for ( size_t i = 0; i < Directories.size( ); i++ ) {
                lua_pushinteger( lua_state, static_cast< int >( i + 1 ) );
                lua_pushstring( lua_state, Directories[ i ].c_str( ) );
                lua_settable( lua_state, -3 );
            }

            return 1;
        }

        int DirectoryExists( lua_State* lua_state ) {
            lua_pushboolean( lua_state, FileSystem.DirectoryExists( luaL_checkstring( lua_state, 1 ) ) );

            return 1;
        }

        int CreateDirectory_( lua_State* lua_state ) {
            FileSystem.CreateDirectory_( luaL_checkstring( lua_state, 1 ) );

            return 0;
        }

        int DeleteDirectory( lua_State* lua_state ) {
            FileSystem.DeleteDirectory( luaL_checkstring( lua_state, 1 ) );

            return 0;
        }

        int _LoadImage( lua_State* lua_state ) {
            unsigned char* Pixels = NULL;
            int Width = 0, Height = 0;

            if ( !FileSystem._LoadImage( luaL_checkstring( lua_state, 1 ), &Pixels, &Width, &Height ) ) {
                lua_pushnil( lua_state );
                lua_pushstring( lua_state, "Failed to load image" );
                return 2;
            }

            lua_pushlightuserdata( lua_state, Pixels );
            lua_pushinteger( lua_state, Width );
            lua_pushinteger( lua_state, Height );

            return 3; // Pixel data, width, height
        }
    }

    namespace Win32_ {
        std::unordered_map<int, HWND> WindowHandles;
        std::unordered_map<int, HWND> ConsoleHandles;

        int CreateWindow_( lua_State* lua_state ) {
            auto Position = *( Vector2* ) lua_touserdata( lua_state, 2 );
            auto Size = *( Vector2* ) lua_touserdata( lua_state, 3 );

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
            auto Position = *( Vector2* ) lua_touserdata( lua_state, 2 );
            auto Size = *( Vector2* ) lua_touserdata( lua_state, 3 );

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

    namespace Graphics_ {
        int Initiate( lua_State* lua_state ) {
            HWND WindowHandle = Win32_::WindowHandles[ luaL_checkinteger( lua_state, 1 ) ];

            DXGI_SWAP_CHAIN_DESC SwapChainDescription = {};

            if ( lua_istable( lua_state, 2 ) ) {
                { lua_getfield( lua_state, 2, "buffer_format" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        SwapChainDescription.BufferDesc.Format = static_cast< DXGI_FORMAT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 2, "buffer_usage" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        SwapChainDescription.BufferUsage = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 2, "output_window" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        SwapChainDescription.OutputWindow = Win32_::WindowHandles[ lua_tointeger( lua_state, -1 ) ];
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 2, "sample_count" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        SwapChainDescription.SampleDesc.Count = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 2, "windowed" );
                    if ( lua_isboolean( lua_state, -1 ) )
                        SwapChainDescription.Windowed = lua_toboolean( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 2, "buffer_count" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        SwapChainDescription.BufferCount = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 2, "buffer_width" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        SwapChainDescription.BufferDesc.Width = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 2, "buffer_height" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        SwapChainDescription.BufferDesc.Height = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 2, "swap_effect" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        SwapChainDescription.SwapEffect = static_cast< DXGI_SWAP_EFFECT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );
            }
            else {
                lua_pushstring( lua_state, "Error: Expected a table for SwapChainDescription." );
                lua_error( lua_state );
            }

            D3D11_BUFFER_DESC BufferDescription = {};

            if ( lua_istable( lua_state, 3 ) ) {
                { lua_getfield( lua_state, 3, "byte_width" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        BufferDescription.ByteWidth = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 3, "usage" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        BufferDescription.Usage = static_cast< D3D11_USAGE >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 3, "bind_flags" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        BufferDescription.BindFlags = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 3, "cpu_access_flags" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        BufferDescription.CPUAccessFlags = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 3, "misc_flags" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        BufferDescription.MiscFlags = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );
            }
            else {
                lua_pushstring( lua_state, "Error: Expected a table for BufferDescription." );
                lua_error( lua_state );
            }

            D3D11_RASTERIZER_DESC RasterizerDescription = {};

            if ( lua_istable( lua_state, 4 ) ) {
                { lua_getfield( lua_state, 4, "fill_mode" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        RasterizerDescription.FillMode = static_cast< D3D11_FILL_MODE >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 4, "cull_mode" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        RasterizerDescription.CullMode = static_cast< D3D11_CULL_MODE >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 4, "scissor_enable" );
                    if ( lua_isboolean( lua_state, -1 ) )
                        RasterizerDescription.ScissorEnable = lua_toboolean( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 4, "depth_clip_enable" );
                    if ( lua_isboolean( lua_state, -1 ) )
                        RasterizerDescription.DepthClipEnable = lua_toboolean( lua_state, -1 );
                } lua_pop( lua_state, 1 );
            }

            D3D11_DEPTH_STENCIL_DESC DepthStencilDescription = {};

            if ( lua_istable( lua_state, 5 ) ) {
                { lua_getfield( lua_state, 5, "depth_enable" );
                    if ( lua_isboolean( lua_state, -1 ) )
                        DepthStencilDescription.DepthEnable = lua_toboolean( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 5, "depth_write_mask" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        DepthStencilDescription.DepthWriteMask = static_cast< D3D11_DEPTH_WRITE_MASK >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 5, "depth_func" );
                    if ( lua_isnumber( lua_state, -1 ) )
                        DepthStencilDescription.DepthFunc = static_cast< D3D11_COMPARISON_FUNC >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 5, "stencil_enable" );
                    if ( lua_isboolean( lua_state, -1 ) )
                        DepthStencilDescription.StencilEnable = lua_toboolean( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 5, "front_face" );
                    if ( lua_istable( lua_state, -1 ) ) {
                        { lua_getfield( lua_state, -1, "stencil_fail_op" );
                            if ( lua_isnumber( lua_state, -1 ) )
                                DepthStencilDescription.FrontFace.StencilFailOp = static_cast< D3D11_STENCIL_OP >( lua_tointeger( lua_state, -1 ) );
                        } lua_pop( lua_state, 1 );

                        { lua_getfield( lua_state, -1, "stencil_depth_fail_op" );
                            if ( lua_isnumber( lua_state, -1 ) )
                                DepthStencilDescription.FrontFace.StencilDepthFailOp = static_cast< D3D11_STENCIL_OP >( lua_tointeger( lua_state, -1 ) );
                        } lua_pop( lua_state, 1 );

                        { lua_getfield( lua_state, -1, "stencil_pass_op" );
                            if ( lua_isnumber( lua_state, -1 ) )
                                DepthStencilDescription.FrontFace.StencilPassOp = static_cast< D3D11_STENCIL_OP >( lua_tointeger( lua_state, -1 ) );
                        } lua_pop( lua_state, 1 );

                        { lua_getfield( lua_state, -1, "stencil_func" );
                            if ( lua_isnumber( lua_state, -1 ) )
                                DepthStencilDescription.FrontFace.StencilFunc = static_cast< D3D11_COMPARISON_FUNC >( lua_tointeger( lua_state, -1 ) );
                        } lua_pop( lua_state, 1 );
                    }
                } lua_pop( lua_state, 1 );

                DepthStencilDescription.BackFace = DepthStencilDescription.FrontFace;
            }

            D3D11_SAMPLER_DESC SamplerDescription = {};

            if ( lua_istable( lua_state, 6 ) ) {
                lua_getfield( lua_state, 6, "filter" ); 
                if ( lua_isnumber( lua_state, -1 ) )
                    SamplerDescription.Filter = static_cast< D3D11_FILTER >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                // AddressU 
                lua_getfield( lua_state, 6, "address_u" );
                if ( lua_isnumber( lua_state, -1 ) )
                    SamplerDescription.AddressU = static_cast< D3D11_TEXTURE_ADDRESS_MODE >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                // AddressV
                lua_getfield( lua_state, 6, "address_v" );
                if ( lua_isnumber( lua_state, -1 ) )
                    SamplerDescription.AddressV = static_cast< D3D11_TEXTURE_ADDRESS_MODE >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                // AddressW
                lua_getfield( lua_state, 6, "address_w" );
                if ( lua_isnumber( lua_state, -1 ) )
                    SamplerDescription.AddressW = static_cast< D3D11_TEXTURE_ADDRESS_MODE >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                // MipLODBias
                lua_getfield( lua_state, 6, "mip_lod_bias" );
                if ( lua_isnumber( lua_state, -1 ) )
                    SamplerDescription.MipLODBias = static_cast< FLOAT >( lua_tonumber( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                // MaxAnisotropy
                lua_getfield( lua_state, 6, "max_anisotropy" );
                if ( lua_isnumber( lua_state, -1 ) )
                    SamplerDescription.MaxAnisotropy = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                // ComparisonFunc
                lua_getfield( lua_state, 6, "comparison_func" );
                if ( lua_isnumber( lua_state, -1 ) )
                    SamplerDescription.ComparisonFunc = static_cast< D3D11_COMPARISON_FUNC >( lua_tointeger( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                // BorderColor (table of 4 numbers)
                lua_getfield( lua_state, 6, "border_color" );
                if ( lua_istable( lua_state, -1 ) ) {
                    for ( int i = 0; i < 4; ++i ) {
                        lua_rawgeti( lua_state, -1, i + 1 );
                        if ( lua_isnumber( lua_state, -1 ) )
                            SamplerDescription.BorderColor[ i ] = static_cast< FLOAT >( lua_tonumber( lua_state, -1 ) );
                        else
                            SamplerDescription.BorderColor[ i ] = 0.0f;
                        lua_pop( lua_state, 1 );
                    }
                }
                lua_pop( lua_state, 1 );

                // MinLOD
                lua_getfield( lua_state, 6, "min_lod" );
                if ( lua_isnumber( lua_state, -1 ) )
                    SamplerDescription.MinLOD = static_cast< FLOAT >( lua_tonumber( lua_state, -1 ) );
                lua_pop( lua_state, 1 );

                // MaxLOD
                lua_getfield( lua_state, 6, "max_lod" );
                if ( lua_isnumber( lua_state, -1 ) )
                    SamplerDescription.MaxLOD = static_cast< FLOAT >( lua_tonumber( lua_state, -1 ) );
                lua_pop( lua_state, 1 );
            }

            D3D11_BLEND_DESC BlendDescription = {};

            if ( lua_istable( lua_state, 7 ) ) {
                { lua_getfield( lua_state, 7, "alpha_to_coverage_enable" );
                    if ( lua_isboolean( lua_state, -1 ) )
                        BlendDescription.AlphaToCoverageEnable = lua_toboolean( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_getfield( lua_state, 7, "render_target" );
                    if ( lua_istable( lua_state, -1 ) ) {
                        lua_getfield( lua_state, -1, "blend_enable" );
                        if ( lua_isboolean( lua_state, -1 ) )
                            BlendDescription.RenderTarget[ 0 ].BlendEnable = lua_toboolean( lua_state, -1 );
                        lua_pop( lua_state, 1 );
                    }
                } lua_pop( lua_state, 1 );
            }

            lua_pushboolean( lua_state, Graphics.Initiate(
                Win32_::WindowHandles[ luaL_checkinteger( lua_state, 1 ) ], SwapChainDescription, 
                BufferDescription, RasterizerDescription, DepthStencilDescription, SamplerDescription, 
                BlendDescription, lua_tostring( lua_state, 8 ), lua_tostring( lua_state, 9 )
            ) );

            return 1;
        }

        int SetProjectionMatrix( lua_State* lua_state ) {
            if ( !lua_istable( lua_state, 1 ) ) {
                lua_pushstring( lua_state, "Expected a table as the first argument" );
                lua_error( lua_state );
                return 0;
            }

            float Matrix[ 4 ][ 4 ];

            for ( int i = 0; i < 16; ++i ) {
                lua_rawgeti( lua_state, 1, i + 1 );

                if ( !lua_isnumber( lua_state, -1 ) ) {
                    lua_pushstring( lua_state, "All matrix elements must be numbers" );
                    lua_error( lua_state );
                    return 0;
                }

                Matrix[ i / 4 ][ i % 4 ] = static_cast< float >( lua_tonumber( lua_state, -1 ) );
                lua_pop( lua_state, 1 );
            }

            Graphics.SetProjectionMatrix( Matrix );
            return 0;
        }

        int SetViewport( lua_State* lua_state ) {
            Graphics.SetViewport(
                *( Vector2* ) luaL_checkudata( lua_state, 1, "vector2" ),
                * ( Vector2* ) luaL_checkudata( lua_state, 2, "vector2" ),
                luaL_optnumber( lua_state, 5, 0.0f ), 
                luaL_optnumber( lua_state, 6, 1.0f ) 
            );

            return 0;
        }

        int CreateTexture( lua_State* lua_state ) {
            D3D11_TEXTURE2D_DESC TextureDescription = {};

            if ( lua_istable( lua_state, 2 ) ) {
                lua_pushvalue( lua_state, 2 );

                { lua_pushstring( lua_state, "width" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) )
                        TextureDescription.Width = lua_tointeger( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "height" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) )
                        TextureDescription.Height = lua_tointeger( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "mip_levels" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) )
                        TextureDescription.MipLevels = lua_tointeger( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "array_size" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) )
                        TextureDescription.ArraySize = lua_tointeger( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "format" );
                    lua_gettable( lua_state, -2 );
                    if ( !lua_isnil( lua_state, -1 ) )
                        TextureDescription.Format = static_cast< DXGI_FORMAT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "sample_desc" );
                    lua_gettable( lua_state, -2 );

                    if ( lua_istable( lua_state, -1 ) ) {
                        { lua_pushstring( lua_state, "count" );
                            lua_gettable( lua_state, -2 );

                            if ( !lua_isnil( lua_state, -1 ) )
                                TextureDescription.SampleDesc.Count = lua_tointeger( lua_state, -1 );
                        } lua_pop( lua_state, 1 );

                        { lua_pushstring( lua_state, "quality" );
                            lua_gettable( lua_state, -2 );

                            if ( !lua_isnil( lua_state, -1 ) )
                                TextureDescription.SampleDesc.Quality = lua_tointeger( lua_state, -1 );
                        } lua_pop( lua_state, 1 );
                    }
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "usage" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) )
                        TextureDescription.Usage = static_cast< D3D11_USAGE >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "bind_flags" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) )
                        TextureDescription.BindFlags = lua_tointeger( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "cpu_access_flags" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) )
                        TextureDescription.CPUAccessFlags = lua_tointeger( lua_state, -1 );
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "misc_flags" );
                    lua_gettable( lua_state, -2 );
                    if ( !lua_isnil( lua_state, -1 ) ) {
                        TextureDescription.MiscFlags = lua_tointeger( lua_state, -1 );
                    }
                } lua_pop( lua_state, 1 );
            } lua_pop( lua_state, 1 );

            D3D11_SUBRESOURCE_DATA SubResourceData = {};

            if ( lua_istable( lua_state, 3 ) ) {
                lua_pushvalue( lua_state, 3 );

                { lua_pushstring( lua_state, "p_sys_mem" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) ) {
                        if ( lua_islightuserdata( lua_state, -1 ) )
                            SubResourceData.pSysMem = static_cast< unsigned char* >( lua_touserdata( lua_state, -1 ) );
                        else
                            luaL_error( lua_state, "p_sys_mem must be a userdata pointer" );
                    }
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "sys_mem_pitch" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) ) {
                        if ( lua_isnumber( lua_state, -1 ) )
                            SubResourceData.SysMemPitch = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                        else
                            luaL_error( lua_state, "sys_mem_pitch must be a number" );
                    }
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "sys_mem_slice_pitch" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) ) {
                        if ( lua_isnumber( lua_state, -1 ) )
                            SubResourceData.SysMemSlicePitch = static_cast< UINT >( lua_tointeger( lua_state, -1 ) );
                        else
                            luaL_error( lua_state, "sys_mem_slice_pitch must be a number" );
                    }
                } lua_pop( lua_state, 1 );
            } lua_pop( lua_state, 1 );

            D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDescription = {};

            if ( lua_istable( lua_state, 4 ) ) {
                lua_pushvalue( lua_state, 4 );

                { lua_pushstring( lua_state, "format" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) )
                        ShaderResourceViewDescription.Format = static_cast< DXGI_FORMAT >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "view_dimension" );
                    lua_gettable( lua_state, -2 );

                    if ( !lua_isnil( lua_state, -1 ) )
                        ShaderResourceViewDescription.ViewDimension = static_cast< D3D11_SRV_DIMENSION >( lua_tointeger( lua_state, -1 ) );
                } lua_pop( lua_state, 1 );

                { lua_pushstring( lua_state, "union" );
                    lua_gettable( lua_state, -2 );

                    if ( lua_istable( lua_state, -1 ) ) {
                        {
                            lua_pushstring( lua_state, "texture2d" );
                            lua_gettable( lua_state, -2 );

                            if ( lua_istable( lua_state, -1 ) ) {
                                { lua_pushstring( lua_state, "most_detailed_mip" );
                                    lua_gettable( lua_state, -2 );

                                    if ( !lua_isnil( lua_state, -1 ) )
                                        ShaderResourceViewDescription.Texture2D.MostDetailedMip = lua_tointeger( lua_state, -1 );
                                } lua_pop( lua_state, 1 );

                                { lua_pushstring( lua_state, "mip_levels" );
                                    lua_gettable( lua_state, -2 );

                                    if ( !lua_isnil( lua_state, -1 ) )
                                        ShaderResourceViewDescription.Texture2D.MipLevels = lua_tointeger( lua_state, -1 );
                                } lua_pop( lua_state, 1 );
                            }
                        } lua_pop( lua_state, 1 );
                    }
                } lua_pop( lua_state, 1 );
            } lua_pop( lua_state, 1 );

            Texture* _Texture = Graphics.CreateTexture(
                lua_tostring( lua_state, 1 ),
                TextureDescription, SubResourceData,
                ShaderResourceViewDescription
            );

            lua_pushlightuserdata( lua_state, _Texture );

            return 1;
        }

        int DestroyResource( lua_State* lua_state ) {
            Graphics.DestroyTexture( lua_tostring( lua_state, 1 ) );

            return 0;
        }

        int Cleanup( lua_State* lua_state ) {
            Graphics.Cleanup( );

            return 0;
        }
    }

    namespace Renderer_ {
        int WriteToBuffer( lua_State* lua_state ) {
            if ( !lua_istable( lua_state, 2 ) || !lua_istable( lua_state, 3 ) ) {
                luaL_error( lua_state, "Expected tables at argument 2 (vertices) and 3 (indices)" );
                return 0;
            }

            std::vector<Vertex> Vertices;

            { // Get vertices
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
            }

            std::vector<std::int32_t> Indices;

            { // Get indices
                lua_pushnil( lua_state );

                while ( lua_next( lua_state, 3 ) != 0 ) {
                    if ( lua_isnumber( lua_state, -1 ) ) {
                        Indices.push_back( static_cast< std::int32_t >( 
                            lua_tointeger( lua_state, -1 ) 
                        ) );
                    }

                    lua_pop( lua_state, 1 );
                }
            }

            DrawCommand** _DrawCommand = static_cast< DrawCommand** >(
               lua_newuserdata( lua_state, sizeof( DrawCommand* ) )
            );

            Texture* _Texture = ( Texture* ) lua_touserdata( lua_state, 4 );

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

    namespace Input_ {
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

    namespace Http_ {
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

    namespace Crypt {
        int SHA256Encode( lua_State* lua_state ) {
            lua_pushstring( lua_state, Utils.SHA256Encode( luaL_checkstring( lua_state, 1 ) ).c_str( ) );

            return 1;
        }

        int Base64Encode( lua_State* lua_state ) {
            lua_pushstring( lua_state, Utils.Base64Encode( luaL_checkstring( lua_state, 1 ) ).c_str( ) );

            return 1;
        }

        int Base64Decode( lua_State* lua_state ) {
            lua_pushstring( lua_state, Utils.Base64Decode( luaL_checkstring( lua_state, 1 ) ).c_str( ) );

            return 1;
        }

        int JsonEncode( lua_State* lua_state ) {
            lua_pushstring( lua_state, Utils.JsonEncode( luaL_checkstring( lua_state, 1 ) ).c_str( ) );

            return 1;
        }

        int JsonDecode( lua_State* lua_state ) {
            try {
                nlohmann::json JsonObject = nlohmann::json::parse( luaL_checkstring( lua_state, 1 ) );

                lua_newtable( lua_state );

                for ( auto& [key, value] : JsonObject.items( ) ) {
                    lua_pushstring( lua_state, key.c_str( ) );

                    if ( value.is_string( ) )
                        lua_pushstring( lua_state, value.get<std::string>( ).c_str( ) );
                    else if ( value.is_number_integer( ) )
                        lua_pushinteger( lua_state, value.get<int>( ) );
                    else if ( value.is_number_float( ) )
                        lua_pushnumber( lua_state, value.get<double>( ) );
                    else if ( value.is_boolean( ) )
                        lua_pushboolean( lua_state, value.get<bool>( ) );
                    else
                        lua_pushnil( lua_state );

                    lua_settable( lua_state, -3 );
                }

                return 1;
            }
            catch ( const std::exception& e ) {
                lua_pushnil( lua_state );
                lua_pushstring( lua_state, e.what( ) );

                return 2;
            }

            return 1;
        }
    }

    namespace Debug {
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

    int Print( lua_State* lua_state ) {
        HWND ConsoleHandle = Win32_::ConsoleHandles[ luaL_checkinteger( lua_state, 1 ) ];

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
        lua_pushinteger( lua_state, Environment.AddConnection( 
            luaL_checkstring( lua_state, 1 ), 
            lua_ref( lua_state, 2 ) 
        ) );

        return 1;
    }

    int RemoveConnection( lua_State* lua_state ) {
        Environment.RemoveConnection( luaL_checkinteger( lua_state, 1 ) );

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
}

#endif