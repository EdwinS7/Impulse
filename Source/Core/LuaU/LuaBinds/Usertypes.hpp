#pragma once
#include "../Wrapper.hpp"

namespace LuaBind::LuaUsertypes {
    namespace LuaVector2 {
        int New( lua_State* lua_state ) {
            auto* Userdata = static_cast< Vector2* >( lua_newuserdata( lua_state, sizeof( Vector2 ) ) );
            new ( Userdata ) Vector2(
                lua_tointeger( lua_state, 1 ),
                lua_tointeger( lua_state, 2 )
            );

            luaL_getmetatable( lua_state, "vector2" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int Destroy( lua_State* lua_state ) {
            auto** Userdata = static_cast< Vector2** >( luaL_checkudata( lua_state, 1, "vector2" ) );
            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
        }

        int __Index( lua_State* lua_state ) {
            auto* Userdata = static_cast< Vector2* >( luaL_checkudata( lua_state, 1, "vector2" ) );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "x" ) {
                lua_pushnumber( lua_state, static_cast< double >( Userdata->x ) );
            }
            else if ( Key == "y" ) {
                lua_pushnumber( lua_state, static_cast< double >( Userdata->y ) );
            }
            else {
                luaL_error( lua_state, "invalid property '%s' for vector2", Key.c_str( ) );
            }

            return 1;
        }
        int __NewIndex( lua_State* lua_state ) {
            auto* Userdata = static_cast< Vector2* >( luaL_checkudata( lua_state, 1, "vector2" ) );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "x" )
                Userdata->x = std::round( luaL_checknumber( lua_state, 3 ) );
            else if ( Key == "y" )
                Userdata->y = std::round( luaL_checknumber( lua_state, 3 ) );
            else {
                luaL_error( lua_state, "invalid property '%s' for vector2", Key );
            }

            return 0;
        }
        int __Add( lua_State* lua_state ) {
            auto* Vec1 = static_cast< Vector2* >( luaL_checkudata( lua_state, 1, "vector2" ) );
            auto* Vec2 = static_cast< Vector2* >( luaL_checkudata( lua_state, 2, "vector2" ) );

            auto* Userdata = static_cast< Vector2* >( lua_newuserdata( lua_state, sizeof( Vector2 ) ) );
            new ( Userdata ) Vector2(
                Vec1->x + Vec2->x,
                Vec1->y + Vec2->y
            );

            luaL_getmetatable( lua_state, "vector2" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int __Sub( lua_State* lua_state ) {
            auto* Vec1 = static_cast< Vector2* >( luaL_checkudata( lua_state, 1, "vector2" ) );
            auto* Vec2 = static_cast< Vector2* >( luaL_checkudata( lua_state, 2, "vector2" ) );

            auto* Userdata = static_cast< Vector2* >( lua_newuserdata( lua_state, sizeof( Vector2 ) ) );
            new ( Userdata ) Vector2(
                Vec1->x - Vec2->x,
                Vec1->y - Vec2->y
            );

            luaL_getmetatable( lua_state, "vector2" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int __Mul( lua_State* lua_state ) {
            Vector2* _Vector2 = nullptr;
            int Scalar = 0;

            if ( lua_isuserdata( lua_state, 1 ) && lua_isnumber( lua_state, 2 ) ) {
                _Vector2 = static_cast< Vector2* >( luaL_checkudata( lua_state, 1, "vector2" ) );
                Scalar = luaL_checknumber( lua_state, 2 );
            }
            else if ( lua_isnumber( lua_state, 1 ) && lua_isuserdata( lua_state, 2 ) ) {
                Scalar = luaL_checknumber( lua_state, 1 );
                _Vector2 = static_cast< Vector2* >( luaL_checkudata( lua_state, 2, "vector2" ) );
            }
            else
                return ThrowError( lua_state, "vector2.__mul: expected (vector2, number) or (number, vector2)" );

            auto* Userdata = static_cast< Vector2* >( lua_newuserdata( lua_state, sizeof( Vector2 ) ) );
            new ( Userdata ) Vector2(
                _Vector2->x * Scalar,
                _Vector2->y * Scalar
            );

            luaL_getmetatable( lua_state, "vector2" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int __Div( lua_State* lua_state ) {
            auto* _Vector2 = static_cast< Vector2* >( luaL_checkudata( lua_state, 1, "vector2" ) );
            float Scalar = static_cast< float >( lua_tonumber( lua_state, 2 ) );

            auto* Userdata = static_cast< Vector2* >( lua_newuserdata( lua_state, sizeof( Vector2 ) ) );
            new ( Userdata ) Vector2( _Vector2->x / Scalar, _Vector2->y / Scalar );

            luaL_getmetatable( lua_state, "vector2" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int __Unm( lua_State* lua_state ) {
            auto* _Vector2 = static_cast< Vector2* >( luaL_checkudata( lua_state, 1, "vector2" ) );

            auto* Userdata = static_cast< Vector2* >( lua_newuserdata( lua_state, sizeof( Vector2 ) ) );
            new ( Userdata ) Vector2(
                -_Vector2->x,
                -_Vector2->y
            );

            luaL_getmetatable( lua_state, "vector2" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
    }

    namespace LuaVector3 {
        int New( lua_State* lua_state ) {
            auto* Userdata = static_cast< Vector3* >( lua_newuserdata( lua_state, sizeof( Vector3 ) ) ); 
            new ( Userdata ) Vector3(
                static_cast< float >( lua_tonumber( lua_state, 1 ) ),
                static_cast< float >( lua_tonumber( lua_state, 2 ) ),
                static_cast< float >( lua_tonumber( lua_state, 3 ) )
            );

            luaL_getmetatable( lua_state, "vector3" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }

        int Destroy( lua_State* lua_state ) {
            auto** Userdata = static_cast< Vector3** >( luaL_checkudata( lua_state, 1, "vector3" ) );
            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
        }

        int __Index( lua_State* lua_state ) {
            auto* Userdata = static_cast< Vector3* >( luaL_checkudata( lua_state, 1, "vector3" ) );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "x" ) {
                lua_pushnumber( lua_state, Userdata->x );
            }
            else if ( Key == "y" ) {
                lua_pushnumber( lua_state, Userdata->y );
            }
            else if ( Key == "z" ) {
                lua_pushnumber( lua_state, Userdata->z );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for vector3", Key );
            }

            return 1;
        }

        int __NewIndex( lua_State* lua_state ) {
            auto* Userdata = static_cast< Vector3* >( luaL_checkudata( lua_state, 1, "vector3" ) );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "x" ) {
                Userdata->x = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( Key == "y" ) {
                Userdata->y = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( Key == "z" ) {
                Userdata->z = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for vector3", Key );
            }

            return 0;
        }

        int __Add( lua_State* lua_state ) {
            auto* Vec1 = static_cast< Vector3* >( luaL_checkudata( lua_state, 1, "vector3" ) );
            auto* Vec2 = static_cast< Vector3* >( luaL_checkudata( lua_state, 2, "vector3" ) );

            auto* Userdata = static_cast< Vector3* >( lua_newuserdata( lua_state, sizeof( Vector3 ) ) );
            new ( Userdata ) Vector3( Vec1->x + Vec2->x, Vec1->y + Vec2->y, Vec1->z + Vec2->z );

            luaL_getmetatable( lua_state, "vector3" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }

        int __Sub( lua_State* lua_state ) {
            auto* Vec1 = static_cast< Vector3* >( luaL_checkudata( lua_state, 1, "vector3" ) );
            auto* Vec2 = static_cast< Vector3* >( luaL_checkudata( lua_state, 2, "vector3" ) );

            auto* Userdata = static_cast< Vector3* >( lua_newuserdata( lua_state, sizeof( Vector3 ) ) );
            new ( Userdata ) Vector3( Vec1->x - Vec2->x, Vec1->y - Vec2->y, Vec1->z - Vec2->z );

            luaL_getmetatable( lua_state, "vector3" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }

        int __Mul( lua_State* lua_state ) {
            Vector3* _Vector2 = nullptr;
            float Scalar = 0;

            if ( lua_isuserdata( lua_state, 1 ) && lua_isnumber( lua_state, 2 ) ) {
                _Vector2 = static_cast< Vector3* >( luaL_checkudata( lua_state, 1, "vector3" ) );
                Scalar = static_cast< float >( lua_tonumber( lua_state, 2 ) );
            }
            else if ( lua_isnumber( lua_state, 1 ) && lua_isuserdata( lua_state, 2 ) ) {
                Scalar = static_cast< float >( lua_tonumber( lua_state, 1 ) );
                _Vector2 = static_cast< Vector3* >( luaL_checkudata( lua_state, 2, "vector3" ) );
            }
            else
                return ThrowError( lua_state, "vector3.__mul: expected (vector3, number) or (number, vector3)" );

            auto* Userdata = static_cast< Vector3* >( lua_newuserdata( lua_state, sizeof( Vector3 ) ) );
            new ( Userdata ) Vector3(
                _Vector2->x * Scalar, 
                _Vector2->y * Scalar, 
                _Vector2->z * Scalar
            );

            luaL_getmetatable( lua_state, "vector3" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }

        int __Div( lua_State* lua_state ) {
            auto* _Vector2 = static_cast< Vector3* >( luaL_checkudata( lua_state, 1, "vector3" ) );
            float Scalar = static_cast< float >( lua_tonumber( lua_state, 2 ) );

            auto* Userdata = static_cast< Vector3* >( lua_newuserdata( lua_state, sizeof( Vector3 ) ) );
            new ( Userdata ) Vector3( 
                _Vector2->x / Scalar, 
                _Vector2->y / Scalar, 
                _Vector2->z / Scalar
            );

            luaL_getmetatable( lua_state, "vector3" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }

        int __Unm( lua_State* lua_state ) {
            auto* _Vector2 = static_cast< Vector3* >( luaL_checkudata( lua_state, 1, "vector3" ) );

            auto* Userdata = static_cast< Vector3* >( lua_newuserdata( lua_state, sizeof( Vector3 ) ) );
            new ( Userdata ) Vector3( 
                -_Vector2->x, 
                -_Vector2->y, 
                -_Vector2->z
            );

            luaL_getmetatable( lua_state, "vector3" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
    }

    namespace LuaVertex {
        int New( lua_State* lua_state ) {
            auto* Userdata = ( Vertex* ) lua_newuserdata( lua_state, sizeof( Vertex ) );
            new ( Userdata ) Vertex(
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
        int Destroy( lua_State* lua_state ) {
            auto** Userdata = ( Vertex** ) luaL_checkudata( lua_state, 1, "vertex" );

            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
        }

        // Metatable functions
        int __Index( lua_State* lua_state ) {
            auto* Userdata = ( Vertex* ) luaL_checkudata( lua_state, 1, "vertex" );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "x" ) {
                lua_pushnumber( lua_state, Userdata->x );
            }
            else if ( Key == "y" ) {
                lua_pushnumber( lua_state, Userdata->y );
            }
            else if ( Key == "z" ) {
                lua_pushnumber( lua_state, Userdata->z );
            }
            else if ( Key == "rhw" ) {
                lua_pushnumber( lua_state, Userdata->rhw );
            }
            else if ( Key == "u" ) {
                lua_pushnumber( lua_state, Userdata->u );
            }
            else if ( Key == "v" ) {
                lua_pushnumber( lua_state, Userdata->v );
            }
            else if ( Key == "color" ) {
                lua_pushnumber( lua_state, static_cast< double >( Userdata->clr ) );
            }
            else
                ThrowError( lua_state, "invalid field '%s' for vertex", Key );

            return 1;
        }
        int __NewIndex( lua_State* lua_state ) {
            auto* Userdata = ( Vertex* ) luaL_checkudata( lua_state, 1, "vertex" );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "x" ) {
                Userdata->x = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( Key == "y" ) {
                Userdata->y = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( Key == "z" ) {
                Userdata->z = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( Key == "rhw" ) {
                Userdata->rhw = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( Key == "u" ) {
                Userdata->u = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( Key == "v" ) {
                Userdata->v = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( Key == "color" ) {
                Userdata->clr = static_cast< unsigned long >( lua_tonumber( lua_state, 3 ) );
            }
            else
                ThrowError( lua_state, "invalid field '%s' for vertex", Key );

            return 0;
        }
        int __Add( lua_State* lua_state ) {
            auto* Vertex1 = static_cast< Vertex* >( luaL_checkudata( lua_state, 1, "vertex" ) );
            auto* Vertex2 = static_cast< Vertex* >( luaL_checkudata( lua_state, 2, "vertex" ) );

            auto* Userdata = static_cast< Vertex* >( lua_newuserdata( lua_state, sizeof( Vertex ) ) );
            new ( Userdata ) Vertex(
                Vertex1->x + Vertex2->x,
                Vertex1->y + Vertex2->y,
                Vertex1->z + Vertex2->z,
                Vertex1->rhw + Vertex2->rhw,
                Vertex1->u + Vertex2->u,
                Vertex1->v + Vertex2->v,
                Vertex1->clr // TODO: should we blend colors?
            );

            luaL_getmetatable( lua_state, "vertex" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int __Sub( lua_State* lua_state ) {
            auto* Vertex1 = static_cast< Vertex* >( luaL_checkudata( lua_state, 1, "vertex" ) );
            auto* Vertex2 = static_cast< Vertex* >( luaL_checkudata( lua_state, 2, "vertex" ) );

            auto* Userdata = static_cast< Vertex* >( lua_newuserdata( lua_state, sizeof( Vertex ) ) );
            new ( Userdata ) Vertex(
                Vertex1->x - Vertex2->x,
                Vertex1->y - Vertex2->y,
                Vertex1->z - Vertex2->z,
                Vertex1->rhw - Vertex2->rhw,
                Vertex1->u - Vertex2->u,
                Vertex1->v - Vertex2->v,
                Vertex1->clr
            );

            luaL_getmetatable( lua_state, "vertex" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int __Mul( lua_State* lua_state ) {
            Vertex* _Vertex = nullptr;
            float Scalar = 0.0f;

            if ( lua_isuserdata( lua_state, 1 ) && lua_isnumber( lua_state, 2 ) ) {
                _Vertex = static_cast< Vertex* >( luaL_checkudata( lua_state, 1, "vertex" ) );
                Scalar = static_cast< float >( lua_tonumber( lua_state, 2 ) );
            }
            else if ( lua_isnumber( lua_state, 1 ) && lua_isuserdata( lua_state, 2 ) ) {
                Scalar = static_cast< float >( lua_tonumber( lua_state, 1 ) );
                _Vertex = static_cast< Vertex* >( luaL_checkudata( lua_state, 2, "vertex" ) );
            }
            else
                luaL_error( lua_state, "vertex.__mul: expected (vertex, number) or (number, vertex)" );

            auto* Userdata = static_cast< Vertex* >( lua_newuserdata( lua_state, sizeof( Vertex ) ) );
            new ( Userdata ) Vertex(
                _Vertex->x * Scalar,
                _Vertex->y * Scalar,
                _Vertex->z * Scalar,
                _Vertex->rhw * Scalar,
                _Vertex->u * Scalar,
                _Vertex->v * Scalar,
                _Vertex->clr // scalar * color is undefined—leaving it unchanged
            );

            luaL_getmetatable( lua_state, "vertex" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int __Div( lua_State* lua_state ) {
            auto* _Vertex = static_cast< Vertex* >( luaL_checkudata( lua_state, 1, "vertex" ) );
            float Scalar = static_cast< float >( luaL_checknumber( lua_state, 2 ) );

            auto* Userdata = static_cast< Vertex* >( lua_newuserdata( lua_state, sizeof( Vertex ) ) );
            new ( Userdata ) Vertex(
                _Vertex->x / Scalar,
                _Vertex->y / Scalar,
                _Vertex->z / Scalar,
                _Vertex->rhw / Scalar,
                _Vertex->u / Scalar,
                _Vertex->v / Scalar,
                _Vertex->clr
            );

            luaL_getmetatable( lua_state, "vertex" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int __Unm( lua_State* lua_state ) {
            auto* _Vertex = static_cast< Vertex* >( luaL_checkudata( lua_state, 1, "vertex" ) );

            auto* Userdata = static_cast< Vertex* >( lua_newuserdata( lua_state, sizeof( Vertex ) ) );
            new ( Userdata ) Vertex(
                -_Vertex->x,
                -_Vertex->y,
                -_Vertex->z,
                -_Vertex->rhw,
                -_Vertex->u,
                -_Vertex->v,
                _Vertex->clr
            );

            luaL_getmetatable( lua_state, "vertex" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
    }

    namespace LuaTexture {
        int New( lua_State* lua_state ) {
            luaL_error( lua_state, "Use 'graphics.create_texture' to create a texture instead." );
            return 0;
        }
        int Destroy( lua_State* lua_state ) {
            Texture** Userdata = ( Texture** ) luaL_checkudata( lua_state, 1, "texture" );

            if ( *Userdata ) {
                delete* Userdata;
                *Userdata = nullptr;
            }

            return 0;
        }

        // Metatable functions
        int __Index( lua_State* lua_state ) {
            Texture* _Texture = *( Texture** ) luaL_checkudata( lua_state, 1, "texture" );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "name" ) {
                lua_pushstring( lua_state, _Texture->Name.c_str( ) );
            }
            else if ( Key == "texture" ) {
                lua_pushlightuserdata( lua_state, _Texture->pTexture );
            }
            else if ( Key == "texture_srv" ) {
                lua_pushlightuserdata( lua_state, _Texture->pTextureSRV );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for texture", Key );
            }

            return 1;
        }
        int __NewIndex( lua_State* lua_state ) {
            luaL_error( lua_state, "Textures are read-only and cannot be modified." );
            return 0;
        }
    }

    namespace LuaGlyph {
        int New( lua_State* lua_state ) {
            luaL_error( lua_state, "Use 'graphics.create_font' to create a font. Fonts contain a table of glyphs." );
            return 0;
        }
        int Destroy( lua_State* lua_state ) {
            Glyph** Userdata = ( Glyph** ) luaL_checkudata( lua_state, 1, "glyph" );

            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
        }

        // Metatable functions
        int __Index( lua_State* lua_state ) {
            Glyph* Userdata = *( Glyph** ) luaL_checkudata( lua_state, 1, "glyph" );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "advance_x" ) {
                lua_pushnumber( lua_state, Userdata->AdvanceX );
            }
            else if ( Key == "offset_x" ) {
                lua_pushinteger( lua_state, Userdata->OffsetX );
            }
            else if ( Key == "offset_y" ) {
                lua_pushinteger( lua_state, Userdata->OffsetY );
            }
            else if ( Key == "width" ) {
                lua_pushinteger( lua_state, Userdata->Width );
            }
            else if ( Key == "height" ) {
                lua_pushinteger( lua_state, Userdata->Height );
            }
            else if ( Key == "u0" ) {
                lua_pushinteger( lua_state, Userdata->u0 );
            }
            else if ( Key == "v0" ) {
                lua_pushinteger( lua_state, Userdata->v0 );
            }
            else if ( Key == "u1" ) {
                lua_pushinteger( lua_state, Userdata->u1 );
            }
            else if ( Key == "v1" ) {
                lua_pushinteger( lua_state, Userdata->v1 );
            }
            else if ( Key == "texture" ) {
                auto** TextureUserdata = ( Texture** ) lua_newuserdata( lua_state, sizeof( Texture* ) );
                *TextureUserdata = Userdata->_Texture;

                luaL_getmetatable( lua_state, "texture" );
                lua_setmetatable( lua_state, -2 );
            }
            else {
                luaL_error( lua_state, "invalid property '%s' for glyph", Key );
            }

            return 1;
        }
        int __NewIndex( lua_State* lua_state ) {
            luaL_error( lua_state, "Glyphs are read-only and cannot be modified." );
            return 0;
        }     
    }

    namespace LuaFont {
        int New( lua_State* lua_state ) {
            luaL_error( lua_state, "Use 'graphics.create_font' to create a font instead." );
            return 0;
        }
        int Destroy( lua_State* lua_state ) {
            Font** Userdata = ( Font** ) luaL_checkudata( lua_state, 1, "font" );

            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
        }

        // Metatable functions
        int __Index( lua_State* lua_state ) {
            Font* Userdata = *( Font** ) luaL_checkudata( lua_state, 1, "font" );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "name" ) {
                lua_pushstring( lua_state, Userdata->Name.c_str( ) );
            }
            else if ( Key == "size" ) {
                lua_pushinteger( lua_state, Userdata->Size );
            }
            else if ( Key == "padding" ) {
                lua_pushinteger( lua_state, Userdata->Padding );
            }
            else if ( Key == "antialiasing" ) {
                lua_pushboolean( lua_state, Userdata->Antialiasing );
            }
            else if ( Key == "max_offset_y" ) {
                lua_pushnumber( lua_state, Userdata->MaxOffsetY );
            }
            else if ( Key == "glyphs" ) {
                lua_createtable( lua_state, 0, static_cast< int >( Userdata->Glyphs.size( ) ) );

                for ( const auto& [Char, GlyphRef] : Userdata->Glyphs ) {
                    char KeyStr[ 2 ] = { Char, '\0' };
                    lua_pushstring( lua_state, KeyStr );

                    auto** GlyphUserdata = ( Glyph** ) lua_newuserdata( lua_state, sizeof( Glyph* ) );
                    *GlyphUserdata = const_cast< Glyph* >( &GlyphRef );

                    luaL_getmetatable( lua_state, "glyph" );
                    lua_setmetatable( lua_state, -2 );

                    lua_settable( lua_state, -3 );
                }
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for font", Key );
            }

            return 1;
        }
        int __NewIndex( lua_State* lua_state ) {
            luaL_error( lua_state, "Fonts are read-only and cannot be modified." );
            return 0;
        }
    }

    namespace LuaColor {
        int New( lua_State* lua_state ) {
            auto* Userdata = ( Color* ) lua_newuserdata( lua_state, sizeof( Color ) );

            new ( Userdata ) Color(
                static_cast< uint8_t >( lua_tointeger( lua_state, 1 ) ),
                static_cast< uint8_t >( lua_tointeger( lua_state, 2 ) ),
                static_cast< uint8_t >( lua_tointeger( lua_state, 3 ) ),
                static_cast< uint8_t >( luaL_optinteger( lua_state, 4, 255 ) )
            );

            luaL_getmetatable( lua_state, "color" );
            lua_setmetatable( lua_state, -2 );

            return 1;
        }
        int Destroy( lua_State* lua_state ) {
            Color** Userdata = ( Color** ) luaL_checkudata( lua_state, 1, "color" );

            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
        }
        int ToGrayscale( lua_State* lua_state ) {
            auto* Userdata = ( Color* ) luaL_checkudata( lua_state, 1, "color" );

            uint8_t Gray = static_cast< uint8_t >(
                0.299f * Userdata->r + 0.587f * Userdata->g + 0.114f * Userdata->b
            );

            auto* GrayColor = ( Color* ) lua_newuserdata( lua_state, sizeof( Color ) );
            new ( GrayColor ) Color( Gray, Gray, Gray, Userdata->a );

            luaL_getmetatable( lua_state, "color" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int Invert( lua_State* lua_state ) {
            auto* Userdata = ( Color* ) luaL_checkudata( lua_state, 1, "color" );

            auto* InvertedColor = ( Color* ) lua_newuserdata( lua_state, sizeof( Color ) );
            new ( InvertedColor ) Color(
                255 - Userdata->r,
                255 - Userdata->g,
                255 - Userdata->b,
                Userdata->a
            );

            luaL_getmetatable( lua_state, "color" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }
        int Lerp( lua_State* lua_state ) {
            auto* Color1 = ( Color* ) luaL_checkudata( lua_state, 1, "color" );
            auto* Color2 = ( Color* ) luaL_checkudata( lua_state, 2, "color" );
            float Time = static_cast< float >( luaL_checknumber( lua_state, 3 ) );

            auto Lerp = [ ] ( uint8_t a, uint8_t b, float t ) -> uint8_t {
                return static_cast< uint8_t >( a + ( b - a ) * t );
            };

            auto* Userdata = ( Color* ) lua_newuserdata( lua_state, sizeof( Color ) );
            new ( Userdata ) Color(
                Lerp( Color1->r, Color2->r, Time ),
                Lerp( Color1->g, Color2->g, Time ),
                Lerp( Color1->b, Color2->b, Time ),
                Lerp( Color1->a, Color2->a, Time )
            );

            luaL_getmetatable( lua_state, "color" );
            lua_setmetatable( lua_state, -2 );
            return 1;
        }

        // Metatable functions
        int __Index( lua_State* lua_state ) {
            Color* Userdata = ( Color* ) luaL_checkudata( lua_state, 1, "color" );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "r" ) {
                lua_pushinteger( lua_state, static_cast< int >( Userdata->r ) );
            }
            else if ( Key == "g" ) {
                lua_pushinteger( lua_state, static_cast< int >( Userdata->g ) );
            }
            else if ( Key == "b" ) {
                lua_pushinteger( lua_state, static_cast< int >( Userdata->b ) );
            }
            else if ( Key == "a" ) {
                lua_pushinteger( lua_state, static_cast< int >( Userdata->a ) );
            }
            else if ( Key == "hex" ) {
                lua_pushnumber( lua_state, static_cast< double >(
                    RGBA_TO_DWORD( Userdata->r, Userdata->g, Userdata->b, Userdata->a )
                ) );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for color", Key );
            }

            return 1;
        }
        int __NewIndex( lua_State* lua_state ) {
            Color* Userdata = ( Color* ) luaL_checkudata( lua_state, 1, "color" );
            std::string Key = Utils.ToLowercase( lua_tostring( lua_state, 2 ) );

            if ( Key == "r" ) {
                Userdata->r = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
            }
            else if ( Key == "g" ) {
                Userdata->g = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
            }
            else if ( Key == "b" ) {
                Userdata->b = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
            }
            else if ( Key == "a" ) {
                Userdata->a = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for color", Key );
            }

            return 0;
        }
    }

    namespace LuaDrawCommand {
        int New( lua_State* lua_state ) {
            luaL_error( lua_state, "Use 'renderer.write_to_buffer' to create a draw_command instead." );
            return 0;
        }
        int Destroy( lua_State* lua_state ) {
            DrawCommand** Userdata = ( DrawCommand** ) luaL_checkudata( lua_state, 1, "draw_command" );

            if ( *Userdata ) {
                auto _DrawCommand = std::find_if( Graphics.DrawCommands.begin( ), Graphics.DrawCommands.end( ),
                    [ Userdata ] ( const std::unique_ptr<DrawCommand>& ptr ) {
                    return ptr.get( ) == *Userdata;
                } );

                if ( _DrawCommand != Graphics.DrawCommands.end( ) )
                    Graphics.DrawCommands.erase( _DrawCommand );

                *Userdata = nullptr;
            }

            return 0;
        }

        // Metatable functions
        int __Index( lua_State* lua_state ) {
            DrawCommand* Userdata = *( DrawCommand** ) luaL_checkudata( lua_state, 1, "draw_command" );

            auto Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "primitive_topology" ) == 0 ) {
                lua_pushinteger( lua_state, static_cast< int >( Userdata->PrimitiveTopology ) );
            }
            else if ( strcmp( Key, "vertices" ) == 0 ) {
                lua_createtable( lua_state, static_cast< int >( Userdata->Vertices.size( ) ), 0 );

                for ( size_t i = 0; i < Userdata->Vertices.size( ); i++ ) {
                    auto* _Vertex = ( Vertex* ) lua_newuserdata( lua_state, sizeof( Vertex ) );
                    *_Vertex = Userdata->Vertices[ i ];

                    luaL_getmetatable( lua_state, "vertex" );
                    lua_setmetatable( lua_state, -2 );

                    lua_rawseti( lua_state, -2, static_cast< int >( i + 1 ) );
                }
            }
            else if ( strcmp( Key, "indices" ) == 0 ) {
                lua_createtable( lua_state, static_cast< int >( Userdata->Indices.size( ) ), 0 );

                for ( size_t i = 0; i < Userdata->Indices.size( ); i++ ) {
                    lua_pushinteger( lua_state, static_cast< int >( Userdata->Indices[ i ] ) );
                    lua_rawseti( lua_state, -2, static_cast< int >( i + 1 ) );
                }
            }
            else if ( strcmp( Key, "z_index" ) == 0 ) {
                lua_pushinteger( lua_state, static_cast< int >( Userdata->ZIndex ) );
            }
            else if ( lua_getmetatable( lua_state, 1 ) ) {
                lua_pushvalue( lua_state, 2 );
                lua_rawget( lua_state, -2 );

                if ( !lua_isnil( lua_state, -1 ) ) {
                    return 1;
                }
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for draw_command", Key );
            }

            return 1;
        }
        int __NewIndex( lua_State* lua_state ) {
            DrawCommand* Userdata = *( DrawCommand** ) luaL_checkudata(
                lua_state, 1, "draw_command"
            );

            const char* Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "primitive_topology" ) == 0 ) {
                Userdata->PrimitiveTopology = static_cast< D3D_PRIMITIVE_TOPOLOGY >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "vertices" ) == 0 ) {
                size_t TableLength = static_cast< size_t >( lua_objlen( lua_state, 3 ) );

                Userdata->Vertices.resize( TableLength );

                for ( size_t i = 1; i <= TableLength; i++ ) {
                    lua_rawgeti( lua_state, 3, static_cast< int >( i ) );

                    auto* _Vertex = ( Vertex* ) luaL_checkudata( lua_state, -1, "vertex" );
                    Userdata->Vertices[ i - 1 ] = *_Vertex;

                    lua_pop( lua_state, 1 );
                }
            }
            else if ( strcmp( Key, "indices" ) == 0 ) {
                size_t TableLength = lua_objlen( lua_state, 3 );

                Userdata->Indices.resize( TableLength );

                for ( size_t i = 1; i <= TableLength; i++ ) {
                    lua_rawgeti( lua_state, 3, static_cast< int >( i ) );

                    Userdata->Indices[ i - 1 ] = lua_tointeger( lua_state, -1 );

                    lua_pop( lua_state, 1 );
                }
            }
            else if ( strcmp( Key, "z_index" ) == 0 ) {
                Userdata->ZIndex = static_cast< int >( lua_tonumber( lua_state, 3 ) );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for draw_command", Key );
            }

            return 0;
        }
    }
}