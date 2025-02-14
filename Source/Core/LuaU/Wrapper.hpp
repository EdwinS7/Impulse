#ifndef LUAU_RUNTIME_H
#define LUAU_RUNTIME_H

#include "../Common.hpp"
#include "Environment.hpp"
#include "../FileSystem/FileSystem.hpp"
#include "../Win32/Win32.hpp"
#include "../Graphics/Include.hpp"
#include "../Input/Input.hpp"
#include "../Memory/Memory.hpp"
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
            int New( lua_State* L ) {
                Vector2* Vector = ( Vector2* ) lua_newuserdata( L, sizeof( Vector2 ) );

                new ( Vector ) Vector2(
                    luaL_optnumber( L, 1, 0.0 ),
                    luaL_optnumber( L, 2, 0.0 )
                );

                luaL_getmetatable( L, "vector2" );
                lua_setmetatable( L, -2 );

                return 1;
            }

            int Index( lua_State* L ) {
                Vector2* Vector = ( Vector2* ) luaL_checkudata( L, 1, "vector2" );
                const char* Key = luaL_checkstring( L, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    lua_pushnumber( L, Vector->x );
                else if ( strcmp( Key, "y" ) == 0 )
                    lua_pushnumber( L, Vector->y );
                else
                    luaL_error( L, "invalid field '%s' for vector2", Key );

                return 1;
            }

            int NewIndex( lua_State* L ) {
                Vector2* Vector = ( Vector2* ) luaL_checkudata( L, 1, "vector2" );
                const char* Key = luaL_checkstring( L, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    Vector->x = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "y" ) == 0 )
                    Vector->y = luaL_checknumber( L, 3 );
                else
                    luaL_error( L, "invalid field '%s' for vector2", Key );

                return 0;
            }
        }

        namespace Vector3_ {
            int New( lua_State* L ) {
                Vector3* Vector = ( Vector3* ) lua_newuserdata( L, sizeof( Vector3 ) );

                new ( Vector ) Vector3(
                    luaL_optnumber( L, 1, 0.0 ),
                    luaL_optnumber( L, 2, 0.0 ),
                    luaL_optnumber( L, 3, 0.0 )
                );

                luaL_getmetatable( L, "vector3" );
                lua_setmetatable( L, -2 );

                return 1;
            }

            int Index( lua_State* L ) {
                Vector3* Vector = ( Vector3* ) luaL_checkudata( L, 1, "vector3" );
                
                const char* Key = luaL_checkstring( L, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    lua_pushnumber( L, Vector->x );
                else if ( strcmp( Key, "y" ) == 0 )
                    lua_pushnumber( L, Vector->y );
                else if ( strcmp( Key, "z" ) == 0 )
                    lua_pushnumber( L, Vector->z );
                else
                    luaL_error( L, "invalid field '%s' for vector3", Key );

                return 1;
            }

            int NewIndex( lua_State* L ) {
                Vector3* Vector = ( Vector3* ) luaL_checkudata( L, 1, "vector3" );

                const char* Key = luaL_checkstring( L, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    Vector->x = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "y" ) == 0 )
                    Vector->y = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "z" ) == 0 )
                    Vector->z = luaL_checknumber( L, 3 );
                else
                    luaL_error( L, "invalid field '%s' for vector3", Key );

                return 0;
            }
        }

        namespace Vertex_ {
            int New( lua_State* L ) {
                Vertex* Vertex_ = ( Vertex* ) lua_newuserdata( L, sizeof( Vertex ) );

                new ( Vertex_ ) Vertex(
                    luaL_optnumber( L, 1, 0.0 ), // x: 0
                    luaL_optnumber( L, 2, 0.0 ), // y: 0
                    luaL_optnumber( L, 3, 0.0 ), // z: 0
                    luaL_optnumber( L, 4, 1.0 ), // rhw: 1 (2D)
                    luaL_optnumber( L, 5, 0.0 ), // u: 0
                    luaL_optnumber( L, 6, 0.0 ), // v: 0
                    luaL_optnumber( L, 7, ( double ) 0xFFFFFF ) // color: white
                );

                luaL_getmetatable( L, "vertex" );
                lua_setmetatable( L, -2 );

                return 1;
            }

            int Index( lua_State* L ) {
                Vertex* Vertex_ = ( Vertex* ) luaL_checkudata( L, 1, "vertex" );
                const char* Key = luaL_checkstring( L, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    lua_pushnumber( L, Vertex_->x );
                else if ( strcmp( Key, "y" ) == 0 )
                    lua_pushnumber( L, Vertex_->y );
                else if ( strcmp( Key, "z" ) == 0 )
                    lua_pushnumber( L, Vertex_->z );
                else if ( strcmp( Key, "rhw" ) == 0 )
                    lua_pushnumber( L, Vertex_->rhw );
                else if ( strcmp( Key, "u" ) == 0 )
                    lua_pushnumber( L, Vertex_->u );
                else if ( strcmp( Key, "v" ) == 0 )
                    lua_pushnumber( L, Vertex_->v );
                else if ( strcmp( Key, "color" ) == 0 )
                    lua_pushnumber( L, Vertex_->color );
                else
                    luaL_error( L, "invalid field '%s' for vertex", Key );

                return 1;
            }

            int NewIndex( lua_State* L ) {
                Vertex* _Vertex = ( Vertex* ) luaL_checkudata( L, 1, "vertex" );

                const char* Key = luaL_checkstring( L, 2 );

                if ( strcmp( Key, "x" ) == 0 )
                    _Vertex->x = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "y" ) == 0 )
                    _Vertex->y = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "z" ) == 0 )
                    _Vertex->z = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "rhw" ) == 0 )
                    _Vertex->rhw = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "u" ) == 0 )
                    _Vertex->u = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "v" ) == 0 )
                    _Vertex->v = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "color" ) == 0 )
                    _Vertex->color = luaL_checknumber( L, 3 );
                else
                    luaL_error( L, "invalid field '%s' for vertex", Key );

                return 0;
            }
        }

        namespace Color_ {
            int New( lua_State* L ) {
                auto _Color = ( Color* ) lua_newuserdata( L, sizeof( Color ) );

                new ( _Color ) Color(
                    luaL_optnumber( L, 1, 0.0 ),
                    luaL_optnumber( L, 2, 0.0 ),
                    luaL_optnumber( L, 3, 0.0 ),
                    luaL_optnumber( L, 4, 255.0 ) // Default alpha to 255
                );

                luaL_getmetatable( L, "color" );
                lua_setmetatable( L, -2 );

                return 1;
            }

            #define RGBA_TO_DWORD(r, g, b, a) ((DWORD)((((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff)))

            int Index( lua_State* L ) {
                Color* _Color = ( Color* ) luaL_checkudata( L, 1, "color" );
                
                const char* Key = luaL_checkstring( L, 2 );

                if ( strcmp( Key, "r" ) == 0 )
                    lua_pushnumber( L, _Color->r );
                else if ( strcmp( Key, "g" ) == 0 )
                    lua_pushnumber( L, _Color->g );
                else if ( strcmp( Key, "b" ) == 0 )
                    lua_pushnumber( L, _Color->b );
                else if ( strcmp( Key, "a" ) == 0 )
                    lua_pushnumber( L, _Color->a );
                else if ( strcmp( Key, "hex" ) == 0 )
                    lua_pushnumber( L, RGBA_TO_DWORD( _Color->r, _Color->g, _Color->b, _Color->a ) );
                else
                    luaL_error( L, "invalid field '%s' for color", Key );

                return 1;
            }

            int NewIndex( lua_State* L ) {
                Color* _Color = ( Color* ) luaL_checkudata( L, 1, "color" );

                const char* Key = luaL_checkstring( L, 2 );

                if ( strcmp( Key, "r" ) == 0 )
                    _Color->r = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "g" ) == 0 )
                    _Color->g = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "b" ) == 0 )
                    _Color->b = luaL_checknumber( L, 3 );
                else if ( strcmp( Key, "a" ) == 0 )
                    _Color->a = luaL_checknumber( L, 3 ); else
                    luaL_error( L, "invalid field '%s' for color", Key );

                return 0;
            }
        }

        namespace DrawCommand_ {
            int New( lua_State* L ) {
                auto _DrawCommand = ( DrawCommand* ) lua_newuserdata( L, sizeof( DrawCommand ) );

                new ( _DrawCommand ) DrawCommand(
                    D3D_PRIMITIVE_TOPOLOGY( luaL_optnumber( L, 1, ( double ) D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) )
                );

                luaL_getmetatable( L, "draw_command" );
                lua_setmetatable( L, -2 );

                return 1;
            }

            int Index( lua_State* L ) {
                DrawCommand* _DrawCommand = *( DrawCommand** ) luaL_checkudata( L, 1, "draw_command" );

                auto Key = luaL_checkstring( L, 2 );

                if ( strcmp( Key, "primitive_topology" ) == 0 )
                    lua_pushnumber( L, _DrawCommand->primitive_type );
                else if ( strcmp( Key, "vertices" ) == 0 ) {
                    lua_createtable( L, _DrawCommand->vertices.size( ), 0 );

                    for ( size_t i = 0; i < _DrawCommand->vertices.size( ); i++ ) {
                        auto _Vertex = ( Vertex* ) lua_newuserdata( L, sizeof( Vertex ) );
                        *_Vertex = _DrawCommand->vertices[ i ];

                        luaL_getmetatable( L, "vertex" );
                        lua_setmetatable( L, -2 );
                        lua_rawseti( L, -2, i + 1 );
                    }
                } else if ( strcmp( Key, "indices" ) == 0 ) {
                    lua_createtable( L, _DrawCommand->indices.size( ), 0 );

                    for ( size_t i = 0; i < _DrawCommand->indices.size( ); i++ ) {
                        lua_pushinteger( L, _DrawCommand->indices[ i ] );
                        lua_rawseti( L, -2, i + 1 );
                    }
                }
                else
                    luaL_error( L, "invalid field '%s' for draw_command", Key );

                return 1;
            }

            int NewIndex( lua_State* L ) {
                DrawCommand* _DrawCommand = *( DrawCommand** ) luaL_checkudata( L, 1, "draw_command" );

                auto Key = luaL_checkstring( L, 2 );

                if ( strcmp( Key, "primitive_topology" ) == 0 ) {
                    _DrawCommand->primitive_type = static_cast< D3D_PRIMITIVE_TOPOLOGY >(
                        luaL_checknumber( L, 3 )
                    );
                }
                else if ( strcmp( Key, "vertices" ) == 0 ) {
                    size_t TableLength = lua_objlen( L, 3 );

                    _DrawCommand->vertices.resize( TableLength );

                    for ( size_t i = 1; i <= TableLength; i++ ) {
                        lua_rawgeti( L, 3, i );
                        auto* vertex = static_cast< Vertex* >(
                            luaL_checkudata( L, -1, "vertex" )
                        );

                        _DrawCommand->vertices[ i - 1 ] = *vertex;

                        lua_pop( L, 1 );
                    }
                }
                else if ( strcmp( Key, "indices" ) == 0 ) {
                    size_t TableLength = lua_objlen( L, 3 );

                    _DrawCommand->indices.resize( TableLength );

                    for ( size_t i = 1; i <= TableLength; i++ ) {
                        lua_rawgeti( L, 3, i );
                        _DrawCommand->indices[ i - 1 ] = luaL_checkinteger( L, -1 );
                        lua_pop( L, 1 );
                    }
                }
                else
                    luaL_error( L, "invalid field '%s' for draw_command", Key );

                return 0;
            }
        }
    }

    namespace Utils_ {
        int RandomString( lua_State* L ) {
            lua_pushstring( L, Utils.RandomString( luaL_checkinteger( L, 1 ) ) );

            return 0;
        }

        int SetClipboard( lua_State* L ) {
            Utils.SetClipboard( luaL_checkstring( L, 1 ) );

            return 0;
        }

        int GetClipboard( lua_State* L ) {
            lua_pushstring( L, Utils.GetClipboard( ) );

            return 0;
        }

        int SHA256Encode( lua_State* L ) {
            lua_pushstring( L, Utils.SHA256Encode( luaL_checkstring( L, 1 ) ).c_str( ) );

            return 1;
        }

        int Base64Encode( lua_State* L ) {
            lua_pushstring( L, Utils.Base64Encode( luaL_checkstring( L, 1 ) ).c_str( ) );

            return 1;
        }

        int Base64Decode( lua_State* L ) {
            lua_pushstring( L, Utils.Base64Decode( luaL_checkstring( L, 1 ) ).c_str( ) );

            return 1;
        }

        int IsInternetConnected( lua_State* L ) {
            lua_pushboolean( L, Utils.IsInternetConnected( ) );

            return 1;
        }
    }

    namespace FileSystem_ {
        int ListFiles( lua_State* L ) {
            lua_newtable( L );

            std::vector<std::string> Files = FileSystem.ListFiles( luaL_checkstring( L, 1 ) );

            for ( size_t i = 0; i < Files.size( ); i++ ) {
                lua_pushinteger( L, i + 1 );
                lua_pushstring( L, Files[ i ].c_str( ) );
                lua_settable( L, -3 );
            }

            return 1;
        }

        int FileExists( lua_State* L ) {
            lua_pushboolean( L, FileSystem.FileExists( luaL_checkstring( L, 1 ) ) );

            return 1;
        }

        int ReadFile( lua_State* L ) {
            lua_pushstring( L, FileSystem.ReadFile( luaL_checkstring( L, 1 ) ).c_str( ) );

            return 0;
        }

        int WriteFile( lua_State* L ) {
            FileSystem.WriteFile( luaL_checkstring( L, 1 ), luaL_checkstring( L, 2 ) );

            return 0;
        }

        int RenameFile( lua_State* L ) {
            FileSystem.RenameFile( luaL_checkstring( L, 1 ), luaL_checkstring( L, 2 ) );

            return 0;
        }

        int DeleteFile_( lua_State* L ) {
            FileSystem.DeleteFile_( luaL_checkstring( L, 1 ) );

            return 0;
        }

        int ListDirectories( lua_State* L ) {
            lua_newtable( L );

            std::vector<std::string> Directories = FileSystem.ListDirectories( luaL_checkstring( L, 1 ) );

            for ( size_t i = 0; i < Directories.size( ); i++ ) {
                lua_pushinteger( L, i + 1 );
                lua_pushstring( L, Directories[ i ].c_str( ) );
                lua_settable( L, -3 );
            }

            return 1;
        }

        int DirectoryExists( lua_State* L ) {
            lua_pushboolean( L, FileSystem.DirectoryExists( luaL_checkstring( L, 1 ) ) );

            return 1;
        }

        int CreateDirectory_( lua_State* L ) {
            FileSystem.CreateDirectory_( luaL_checkstring( L, 1 ) );

            return 0;
        }

        int DeleteDirectory( lua_State* L ) {
            FileSystem.DeleteDirectory( luaL_checkstring( L, 1 ) );

            return 0;
        }
    }

    namespace Win32_ {
        std::unordered_map<int, HWND> WindowHandles;
        std::unordered_map<int, HWND> ConsoleHandles;

        int CreateWindow_( lua_State* L ) {
            HWND WindowHandle = Win32.CreateWindow_( lua_tostring( L, 1 ),
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
                return 1;

            Win32.DestroyWindow( WindowHandle );

            return 0;
        }

        int CreateConsole( lua_State* L ) {
            HWND ConsoleHandle = Win32.CreateConsole( lua_tostring( L, 1 ),
                lua_tointeger( L, 2 ), lua_tointeger( L, 3 ),
                lua_tointeger( L, 4 ), lua_tointeger( L, 5 )
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
                return 1;

            Win32.DestroyConsole( ConsoleHandle );

            return 0;
        }

        int MessageBox_( lua_State* L ) {
            int Reference = luaL_checkinteger( L, 1 );

            HWND WindowHandle = WindowHandles[ Reference ];
            HWND ConsoleHandle = ConsoleHandles[ Reference ];
            HWND Handle = WindowHandle ? WindowHandle : ConsoleHandle;

            if ( Handle )
                Win32.MessageBox_( Handle, luaL_checkstring( L, 2 ), luaL_checkstring( L, 3 ), luaL_checkinteger( L, 4 ) );

            return 0;
        }

        int GetScreenSize( lua_State* L ) {
            Vector2 ScreenSize = Win32.GetScreenSize( );

            auto Vector = ( Vector2* ) lua_newuserdata( L, sizeof( Vector2 ) );

            new ( Vector ) Vector2(
                static_cast< double >( ScreenSize.x ),
                static_cast< double >( ScreenSize.y )
            );

            luaL_getmetatable( L, "vector2" );
            lua_setmetatable( L, -2 );

            return 1;
        }
    }

    namespace Graphics_ {
        int Initiate( lua_State* L ) {
            lua_pushboolean( L, Graphics.Initiate( Win32_::WindowHandles[ luaL_checkinteger( L, 1 ) ] ) );

            return 1;
        }

        int Cleanup( lua_State* L ) {
            Graphics.Cleanup( );

            return 0;
        }
    }

    namespace Renderer_ {
        int WriteToBuffer( lua_State* L ) {
            std::vector<Vertex> Vertices;

            { // Get vertices
                lua_pushnil( L );

                while ( lua_next( L, 2 ) != 0 ) {
                    if ( lua_isuserdata( L, -1 ) ) {
                        Vertices.push_back( *( Vertex* ) luaL_checkudata( L, -1, "vertex" ) );
                        lua_pop( L, 1 );
                    }
                }
            }

            std::vector<std::int32_t> Indices;

            { // Get indices
                lua_pushnil( L );

                while ( lua_next( L, 3 ) != 0 ) {
                    if ( lua_isnumber( L, -1 ) ) {
                        Indices.push_back( ( int ) lua_tonumber( L, -1 ) );
                        lua_pop( L, 1 );
                    }
                }
            }

            DrawCommand** _DrawCommand = ( DrawCommand** ) lua_newuserdata( L, sizeof( DrawCommand* ) );
            *_DrawCommand = Renderer.WriteToBuffer( D3D_PRIMITIVE_TOPOLOGY( luaL_checkinteger( L, 1 ) ), &Vertices, &Indices );

            luaL_getmetatable( L, "draw_command" );
            lua_setmetatable( L, -2 );

            return 1;
        }

        int Line( lua_State* L ) {
            Renderer.Line(
                *( Vector2* ) luaL_checkudata( L, 1, "vector2" ),
                *( Vector2* ) luaL_checkudata( L, 2, "vector2" ),
                *( Color* ) luaL_checkudata( L, 3, "color" )
            );

            return 0;
        }

        int Polyline( lua_State* L ) {
            std::vector<Vector2> PointList = {};

            lua_pushnil( L );
            while ( lua_next( L, 1 ) != 0 ) {
                PointList.push_back( *( Vector2* ) luaL_checkudata( L, -1, "vector2" ) );

                lua_pop( L, 1 );
            }

            Renderer.Polyline( PointList, *( Color* ) luaL_checkudata( L, 3, "color" ) );

            return 0;
        }

        int Polygon( lua_State* L ) {
            std::vector<Vector2> PointList = {};

            lua_pushnil( L );
            while ( lua_next( L, 1 ) != 0 ) {
                PointList.push_back( *( Vector2* ) luaL_checkudata( L, -1, "vector2" ) );

                lua_pop( L, 1 );
            }

            Renderer.Polygon( PointList, *( Color* ) luaL_checkudata( L, 3, "color" ) );

            return 0;
        }

        int Rectangle( lua_State* L ) {
            Renderer.Rectangle(
                *( Vector2* ) luaL_checkudata( L, 1, "vector2" ),
                *( Vector2* ) luaL_checkudata( L, 2, "vector2" ),
                *( Color* ) luaL_checkudata( L, 3, "color" )
            );

            return 0;
        }

        int FilledRectangle( lua_State* L ) {
            Renderer.FilledRectangle(
                *( Vector2* ) luaL_checkudata( L, 1, "vector2" ),
                *( Vector2* ) luaL_checkudata( L, 2, "vector2" ),
                *( Color* ) luaL_checkudata( L, 3, "color" )
            );

            return 0;
        }
    }

    namespace Input_ {
        int IsKeyPressed( lua_State* L ) {
            lua_pushboolean( L, Input.IsKeyPressed( luaL_checkinteger( L, 1 ) ) );

            return 1;
        }

        int IsKeyHeld( lua_State* L ) {
            lua_pushboolean( L, Input.IsKeyHeld( luaL_checkinteger( L, 1 ) ) );

            return 1;
        }

        int SetCursorPosition( lua_State* L ) {
            Input.SetCursorPosition( *( Vector2* ) luaL_checkudata( L, 1, "vector2" ), true );

            return 1;
        }

        int GetCursorPosition( lua_State* L ) {
            Vector2 MousePosition = Input.GetCursorPosition( );

            auto Vector = ( Vector2* ) lua_newuserdata( L, sizeof( Vector2 ) );

            new ( Vector ) Vector2(
                static_cast< double >( MousePosition.x ),
                static_cast< double >( MousePosition.y )
            );

            luaL_getmetatable( L, "vector2" );
            lua_setmetatable( L, -2 );

            return 1;
        }

        int SetCursorStyle( lua_State* L ) {
            Input.SetCursorStyle( ( PointerStyle ) luaL_checknumber( L, 1 ) );

            return 0;
        }

        int GetCursorStyle( lua_State* L ) {
            lua_pushnumber( L, ( double ) Input.GetCursorStyle( ) );

            return 1;
        }
    }

    namespace Memory_ {
        int SetTarget( lua_State* L ) {
            Memory.SetTarget( luaL_checkstring( L, 1 ) );

            return 0;
        }

        int Read( lua_State* L ) {

            return 1;
        }

        int Write( lua_State* L ) {

            return 0;
        }
        int ScanPattern( lua_State* L ) {
            lua_pushnumber( L, ( double ) Memory.ScanPattern( luaL_checkstring( L, 1 ) ) );

            return 1;
        }

    }

    namespace Http_ {
        int Get( lua_State* L ) {
            lua_pushstring( L, Http::Get( luaL_checkstring( L, 1 ) ).c_str( ) );

            return 0;
        }

        int Post( lua_State* L ) {
           lua_pushstring( L, Http::Post( luaL_checkstring( L, 1 ), luaL_checkstring( L, 2 ) ).c_str( ) );

            return 0;
        }

        int Put( lua_State* L ) {
            lua_pushstring( L, Http::Put( luaL_checkstring( L, 1 ), luaL_checkstring( L, 2 ) ).c_str( ) );

            return 0;
        }

        int Delete( lua_State* L ) {
            lua_pushstring( L, Http::Delete( luaL_checkstring( L, 1 ) ).c_str( ) );

            return 0;
        }
    }

    namespace Debug {
        int GetUpvalue_( lua_State* L ) {
            if ( lua_iscfunction( L, 1 ) )
                luaL_argerror( L, 1, "function must cannot be a c function" );

            int Index = luaL_checkinteger( L, 2 );

            if ( Index <= 0 )
                luaL_argerror( L, 2, "index must be positive" );

            // Sum wrong here
            const char* Upvalue = lua_getupvalue( L, 1, Index );

            if ( Upvalue )
                lua_pushstring( L, "test" );
            else
                lua_pushnil( L );

            return 1;
        }
    }
    
    int AddConnection( lua_State* L ) {
        lua_pushinteger( L, Environment.AddConnection( luaL_checkstring( L, 1 ), lua_ref( L, 2 ) ) );

        return 1;
    }

    int RemoveConnection( lua_State* L ) {
        Environment.RemoveConnection( luaL_checkinteger( L, 1 ) );

        return 0; 
    }

    int LoadString_( lua_State* L ) {
        const char* Source = luaL_checkstring( L, 1 );

        size_t BytecodeSize;
        char* Bytecode = luau_compile( Source, strlen( Source ), nullptr, &BytecodeSize );

        if ( !Bytecode ) {
            lua_pushnil( L );
            lua_pushstring( L, "failed to compile" );
            return 2;
        }

        int Status = luau_load( L, luaL_optstring( L, 2, "chunk" ), Bytecode, BytecodeSize, 0 );
        free( Bytecode );

        if ( Status != LUA_OK ) {
            lua_pushnil( L );
            lua_insert( L, -2 );
            return 2;
        }

        lua_pushvalue( L, LUA_GLOBALSINDEX );
        lua_setfenv( L, -2 );

        return 1;
    }

    int NewCClosure( lua_State* L ) {
        lua_pushvalue( L, 1 );

        lua_pushcclosure( L, [ ] ( lua_State* L ) -> int {
            lua_getupvalue( L, lua_upvalueindex( 1 ), 1 );
            lua_insert( L, 1 );

            lua_call( L, lua_gettop( L ) - 1, LUA_MULTRET );

            return lua_gettop( L );
        }, Utils.RandomString( 16 ), 1 );

        return 1;
    }

    int IsLuaClosure( lua_State* L ) {
        lua_pushboolean( L, lua_isLfunction( L, 1 ) );

        return 1;
    }

    int IsCClosure( lua_State* L ) {
        lua_pushboolean( L, lua_iscfunction( L, 1 ) );

        return 1;
    }

    int GetWrappedOriginal( lua_State* L ) {
       lua_getupvalue( L, 1, 1 );

        if ( !lua_isfunction( L, -1 ) ) {
            lua_pop( L, 1 );
            lua_pushnil( L );
        }

        return 1;
    }

    int SetReadOnly( lua_State* L ) {
        lua_setreadonly( L, 1, luaL_checkboolean( L, 1 ) );

        return 1;
    }

    int GetReadOnly( lua_State* L ) {
        lua_pushboolean( L, lua_getreadonly( L, 1 ) );

        return 1;
    }
}

#endif