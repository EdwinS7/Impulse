#ifndef LUAU_WRAPPER_H
#define LUAU_WRAPPER_H

#include "../Common.hpp"
#include "../Graphics/Types.hpp"

using Arg = std::variant<
    int, float, double,
    bool,
    const char*, std::string,

    Vector2, Vector3, Color,
    Vertex, DrawCommand
>;

using Args = std::vector<Arg>;

static inline void register_function( lua_State* state, lua_CFunction wrapper_function, const std::string& name, bool global = false ) {
    lua_pushcfunction( state, wrapper_function, nullptr );

    if ( global )
        lua_setglobal( state, name.c_str( ) );
    else
        lua_setfield( state, -2, name.c_str( ) );
}

static inline void register_usertype( lua_State* state, lua_CFunction new_function, lua_CFunction destroy_function, lua_CFunction index_function, lua_CFunction newindex_function, const char* name ) {
    luaL_newmetatable( state, name );

    register_function( state, index_function, "__index", false );
    register_function( state, newindex_function, "__newindex", false );

    register_function( state, destroy_function, "destroy", false );

    lua_createtable( state, 0, 1 );

    register_function( state, new_function, "new", false );

    lua_setglobal( state, name );
}

#endif