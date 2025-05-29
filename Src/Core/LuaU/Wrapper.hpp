#ifndef LUAU_WRAPPER_H
#define LUAU_WRAPPER_H

#include "../Common.hpp"

static inline void register_function( lua_State* L, lua_CFunction wrapper_function, const std::string& name, bool global = false ) {
    lua_pushcfunction( L, wrapper_function, nullptr );

    if ( global )
        lua_setglobal( L, name.c_str( ) );
    else
        lua_setfield( L, -2, name.c_str( ) );
}

template<typename... Funcs>
void register_table( lua_State* L, const char* name, Funcs... funcs ) {
    std::vector<std::pair<const char*, lua_CFunction>> Entries = { funcs... };

    lua_createtable( L, 0, static_cast< int >( Entries.size( ) ) );
    for ( const auto& [name, fn] : Entries ) {
        register_function( L, fn, name, false );
    }

    lua_setglobal( L, name );
}

template<typename... Pairs>
void extend_table( lua_State* L, const char* tableName, Pairs&&... pairs ) {
    lua_getglobal( L, tableName );

    if ( !lua_istable( L, -1 ) ) {
        lua_pop( L, 1 );
        luaL_error( L, "Global '%s' is not a table", tableName );
        return;
    }

    ( [ & ] {
        register_function( L, pairs.second, pairs.first );
    }( ), ... );

    lua_pop( L, 1 );
}

static inline void register_usertype( lua_State* L, lua_CFunction new_function, lua_CFunction destroy_function, lua_CFunction index_function, lua_CFunction newindex_function, const char* name ) {
    luaL_newmetatable( L, name );

    register_function( L, index_function, "__index", false );
    register_function( L, newindex_function, "__newindex", false );
    register_function( L, destroy_function, "destroy", false );

    lua_createtable( L, 0, 1 );

    register_function( L, new_function, "new", false );

    lua_setglobal( L, name );
}

#endif