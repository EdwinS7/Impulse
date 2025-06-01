#pragma once

namespace LuaBind::LuaUsertypes {
    // TODO: Finish the 'New' function for every user type.

    namespace LuaVector2 {
        int New( lua_State* lua_state ) {
            auto* Userdata = ( Vector2* ) lua_newuserdata( lua_state, sizeof( Vector2 ) );

            new ( Userdata ) Vector2(
                lua_tointeger( lua_state, 1 ),
                lua_tointeger( lua_state, 2 )
            );

            luaL_getmetatable( lua_state, "vector2" );
            lua_setmetatable( lua_state, -2 );

            return 1;
        }

        int Index( lua_State* lua_state ) {
            auto* Userdata = ( Vector2* ) luaL_checkudata( lua_state, 1, "vector2" );
            const char* Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "x" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->x );
            }
            else if ( strcmp( Key, "y" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->y );
            }
            else {
                luaL_error( lua_state, "invalid property '%s' for vector2", Key );
            }

            return 1;
        }

        int NewIndex( lua_State* lua_state ) {
            auto* Userdata = ( Vector2* ) luaL_checkudata( lua_state, 1, "vector2" );
            const char* Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "x" ) == 0 ) {
                Userdata->x = luaL_checkinteger( lua_state, 3 );
            }
            else if ( strcmp( Key, "y" ) == 0 ) {
                Userdata->y = luaL_checkinteger( lua_state, 3 );
            }
            else {
                luaL_error( lua_state, "invalid property '%s' for vector2", Key );
            }

            return 0;
        }

        int Destroy( lua_State* lua_state ) {
            auto** Userdata = ( Vector2** ) luaL_checkudata( lua_state, 1, "vector2" );

            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
        }
    }

    namespace LuaVector3 {
        int New( lua_State* lua_state ) {
            auto* Userdata = ( Vector3* ) lua_newuserdata( lua_state, sizeof( Vector3 ) );

            new ( Userdata ) Vector3(
                static_cast< float >( lua_tonumber( lua_state, 1 ) ),
                static_cast< float >( lua_tonumber( lua_state, 2 ) ),
                static_cast< float >( lua_tonumber( lua_state, 3 ) )
            );

            luaL_getmetatable( lua_state, "vector3" );
            lua_setmetatable( lua_state, -2 );

            return 1;
        }

        int Index( lua_State* lua_state ) {
            auto* Userdata = ( Vector3* ) luaL_checkudata( lua_state, 1, "vector3" );
            const char* Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "x" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->x );
            }
            else if ( strcmp( Key, "y" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->y );
            }
            else if ( strcmp( Key, "z" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->z );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for vector3", Key );
            }

            return 1;
        }

        int NewIndex( lua_State* lua_state ) {
            auto* Userdata = ( Vector3* ) luaL_checkudata( lua_state, 1, "vector3" );
            const char* Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "x" ) == 0 ) {
                Userdata->x = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "y" ) == 0 ) {
                Userdata->y = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "z" ) == 0 ) {
                Userdata->z = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for vector3", Key );
            }

            return 0;
        }

        int Destroy( lua_State* lua_state ) {
            auto** Userdata = ( Vector3** ) luaL_checkudata( lua_state, 1, "vector3" );

            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
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

        int Index( lua_State* lua_state ) {
            auto* Userdata = ( Vertex* ) luaL_checkudata( lua_state, 1, "vertex" );
            const char* Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "x" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->x );
            }
            else if ( strcmp( Key, "y" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->y );
            }
            else if ( strcmp( Key, "z" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->z );
            }
            else if ( strcmp( Key, "rhw" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->rhw );
            }
            else if ( strcmp( Key, "u" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->u );
            }
            else if ( strcmp( Key, "v" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->v );
            }
            else if ( strcmp( Key, "color" ) == 0 ) {
                lua_pushnumber( lua_state, static_cast< double >( Userdata->clr ) );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for vertex", Key );
            }

            return 1;
        }

        int NewIndex( lua_State* lua_state ) {
            auto* Userdata = ( Vertex* ) luaL_checkudata( lua_state, 1, "vertex" );
            const char* Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "x" ) == 0 ) {
                Userdata->x = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "y" ) == 0 ) {
                Userdata->y = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "z" ) == 0 ) {
                Userdata->z = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "rhw" ) == 0 ) {
                Userdata->rhw = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "u" ) == 0 ) {
                Userdata->u = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "v" ) == 0 ) {
                Userdata->v = static_cast< float >( lua_tonumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "color" ) == 0 ) {
                Userdata->clr = static_cast< unsigned long >( lua_tonumber( lua_state, 3 ) );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for vertex", Key );
            }

            return 0;
        }

        int Destroy( lua_State* lua_state ) {
            auto** Userdata = ( Vertex** ) luaL_checkudata( lua_state, 1, "vertex" );

            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
        }
    }

    namespace LuaTexture {
        int New( lua_State* lua_state ) {
            luaL_error( lua_state, "Use 'graphics.create_texture' to create a texture instead." );
            return 0;
        }

        int Index( lua_State* lua_state ) {
            Texture* _Texture = *( Texture** ) luaL_checkudata( lua_state, 1, "texture" );
            const char* Key = luaL_checkstring( lua_state, 2 );

            if ( strcmp( Key, "name" ) == 0 ) {
                lua_pushstring( lua_state, _Texture->Name.c_str( ) );
            }
            else if ( strcmp( Key, "texture" ) == 0 ) {
                lua_pushlightuserdata( lua_state, _Texture->pTexture );
            }
            else if ( strcmp( Key, "texture_srv" ) == 0 ) {
                lua_pushlightuserdata( lua_state, _Texture->pTextureSRV );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for texture", Key );
            }

            return 1;
        }

        int NewIndex( lua_State* lua_state ) {
            luaL_error( lua_state, "Textures are read-only and cannot be modified." );
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
    }

    namespace LuaGlyph {
        int New( lua_State* lua_state ) {
            luaL_error( lua_state, "Use 'graphics.create_font' to create a font. Fonts contain a table of glyphs." );
            return 0;
        }

        int Index( lua_State* lua_state ) {
            Glyph* Userdata = *( Glyph** ) luaL_checkudata( lua_state, 1, "glyph" );
            const char* Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "advance_x" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->AdvanceX );
            }
            else if ( strcmp( Key, "offset_x" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->OffsetX );
            }
            else if ( strcmp( Key, "offset_y" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->OffsetY );
            }
            else if ( strcmp( Key, "width" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->Width );
            }
            else if ( strcmp( Key, "height" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->Height );
            }
            else if ( strcmp( Key, "u0" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->u0 );
            }
            else if ( strcmp( Key, "v0" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->v0 );
            }
            else if ( strcmp( Key, "u1" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->u1 );
            }
            else if ( strcmp( Key, "v1" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->v1 );
            }
            else if ( strcmp( Key, "texture" ) == 0 ) {
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

        int NewIndex( lua_State* lua_state ) {
            luaL_error( lua_state, "Glyphs are read-only and cannot be modified." );
            return 0;
        }

        int Destroy( lua_State* lua_state ) {
            Glyph** Userdata = ( Glyph** ) luaL_checkudata( lua_state, 1, "glyph" );

            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
        }
    }

    namespace LuaFont {
        int New( lua_State* lua_state ) {
            luaL_error( lua_state, "Use 'graphics.create_font' to create a font instead." );
            return 0;
        }

        int Index( lua_State* lua_state ) {
            Font* Userdata = *( Font** ) luaL_checkudata( lua_state, 1, "font" );
            const char* Key = luaL_checkstring( lua_state, 2 );

            if ( strcmp( Key, "name" ) == 0 ) {
                lua_pushstring( lua_state, Userdata->Name.c_str( ) );
            }
            else if ( strcmp( Key, "size" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->Size );
            }
            else if ( strcmp( Key, "padding" ) == 0 ) {
                lua_pushinteger( lua_state, Userdata->Padding );
            }
            else if ( strcmp( Key, "antialiasing" ) == 0 ) {
                lua_pushboolean( lua_state, Userdata->Antialiasing );
            }
            else if ( strcmp( Key, "max_offset_y" ) == 0 ) {
                lua_pushnumber( lua_state, Userdata->MaxOffsetY );
            }
            else if ( strcmp( Key, "glyphs" ) == 0 ) {
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

        int NewIndex( lua_State* lua_state ) {
            luaL_error( lua_state, "Fonts are read-only and cannot be modified." );
            return 0;
        }

        int Destroy( lua_State* lua_state ) {
            Font** Userdata = ( Font** ) luaL_checkudata( lua_state, 1, "font" );

            if ( *Userdata ) {
                *Userdata = nullptr;
            }

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

        int Index( lua_State* lua_state ) {
            Color* Userdata = ( Color* ) luaL_checkudata( lua_state, 1, "color" );
            const char* Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "r" ) == 0 ) {
                lua_pushinteger( lua_state, static_cast< int >( Userdata->r ) );
            }
            else if ( strcmp( Key, "g" ) == 0 ) {
                lua_pushinteger( lua_state, static_cast< int >( Userdata->g ) );
            }
            else if ( strcmp( Key, "b" ) == 0 ) {
                lua_pushinteger( lua_state, static_cast< int >( Userdata->b ) );
            }
            else if ( strcmp( Key, "a" ) == 0 ) {
                lua_pushinteger( lua_state, static_cast< int >( Userdata->a ) );
            }
            else if ( strcmp( Key, "hex" ) == 0 ) {
                lua_pushnumber( lua_state, static_cast< double >(
                    RGBA_TO_DWORD( Userdata->r, Userdata->g, Userdata->b, Userdata->a )
                ) );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for color", Key );
            }

            return 1;
        }

        int NewIndex( lua_State* lua_state ) {
            Color* Userdata = ( Color* ) luaL_checkudata( lua_state, 1, "color" );
            const char* Key = lua_tostring( lua_state, 2 );

            if ( strcmp( Key, "r" ) == 0 ) {
                Userdata->r = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "g" ) == 0 ) {
                Userdata->g = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "b" ) == 0 ) {
                Userdata->b = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
            }
            else if ( strcmp( Key, "a" ) == 0 ) {
                Userdata->a = static_cast< uint8_t >( luaL_checknumber( lua_state, 3 ) );
            }
            else {
                luaL_error( lua_state, "invalid field '%s' for color", Key );
            }

            return 0;
        }

        int Destroy( lua_State* lua_state ) {
            Color** Userdata = ( Color** ) luaL_checkudata( lua_state, 1, "color" );

            if ( *Userdata ) {
                *Userdata = nullptr;
            }

            return 0;
        }
    }

    namespace LuaDrawCommand {
        int New( lua_State* lua_state ) {
            luaL_error( lua_state, "Use 'renderer.write_to_buffer' to create a draw_command instead." );
            return 0;
        }

        int Index( lua_State* lua_state ) {
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

        int NewIndex( lua_State* lua_state ) {
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
    }
}