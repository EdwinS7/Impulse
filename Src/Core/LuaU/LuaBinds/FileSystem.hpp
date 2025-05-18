#pragma once

#include "../../FileSystem/FileSystem.hpp"

namespace LuaBind::LuaFileSystem {
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