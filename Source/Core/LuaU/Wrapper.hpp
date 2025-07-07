#ifndef LUAU_WRAPPER_H
#define LUAU_WRAPPER_H

#include "../Common.hpp"

static inline void RegisterFunction( lua_State* L, lua_CFunction wrapper_function, const std::string& name, bool global = false ) {
    lua_pushcfunction( L, wrapper_function, nullptr );

    if ( global )
        lua_setglobal( L, name.c_str( ) );
    else
        lua_setfield( L, -2, name.c_str( ) );
}

template<typename... Funcs>
inline void RegisterTable( lua_State* L, const char* name, Funcs... funcs ) {
    std::vector<std::pair<const char*, lua_CFunction>> Entries = { funcs... };

    lua_createtable( L, 0, static_cast< int >( Entries.size( ) ) );
    for ( const auto& [name, fn] : Entries ) {
        RegisterFunction( L, fn, name, false );
    }

    lua_setglobal( L, name );
}

template<typename... Pairs>
inline void ExtendTable( lua_State* L, const char* tableName, Pairs&&... pairs ) {
    lua_getglobal( L, tableName );

    if ( !lua_istable( L, -1 ) ) {
        lua_pop( L, 1 );
        luaL_error( L, "Global '%s' is not a table", tableName );
        return;
    }

    ( [ & ] {
        RegisterFunction( L, pairs.second, pairs.first );
    }( ), ... );

    lua_pop( L, 1 );
}

static inline void RegisterUsertype( lua_State* L, const char* name,
    const std::unordered_map<std::string, lua_CFunction>& methods,
    lua_CFunction new_function, lua_CFunction destroy_function
) {
    luaL_newmetatable( L, name );

    RegisterFunction( L, destroy_function, "destroy", false );
    for ( const auto& [key, func] : methods ) {
        if ( key.compare( 0, 2, "__" ) == 0 )
            RegisterFunction( L, func, key.c_str( ), false );
    }

    lua_createtable( L, 0, 1 );

    RegisterFunction( L, new_function, "new", false );
    for ( const auto& [key, func] : methods ) {
        if ( key.compare( 0, 2, "__" ) != 0 )
            RegisterFunction( L, func, key.c_str( ), false );
    }

    lua_setglobal( L, name );
}

inline int ThrowError( lua_State* L, const char* fmt, ... ) {
    va_list args;
    va_start( args, fmt );
    luaL_error( L, fmt, args );
    va_end( args );
    return 0;
}

inline int ThrowArgError( lua_State* L, int arg, const char* fmt, ... ) {
    va_list args;
    va_start( args, fmt );
    luaL_argerror( L, arg, fmt, args );
    va_end( args );
    return 0;
}

#endif