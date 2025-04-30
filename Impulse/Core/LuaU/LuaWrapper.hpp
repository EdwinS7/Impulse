#ifndef LUAU_WRAPPER_H
#define LUAU_WRAPPER_H

#include "../Common.hpp"
#include "../Graphics/Types.hpp"

// NOTE: List of possible lua types.
using Arg = std::variant<
    int, float, double,
    bool,
    const char*, std::string,

    Vector2, Vector3, Color,
    Vertex, DrawCommand
>;

using Args = std::vector<Arg>;

static inline void register_table( lua_State* state, const std::string& name, bool global ) {
    if ( global )
        lua_setglobal( state, name.c_str( ) );
    else
        lua_setfield( state, -2, name.c_str( ) );
}

static inline void register_usertype( lua_State* state, lua_CFunction wrapper_function, const std::string& name, bool global ) {
    lua_createtable( state, 0, 1 );

    lua_pushcfunction( state, wrapper_function, nullptr );
    lua_setfield( state, -2, "new" );

    lua_setglobal( state, name.c_str( ) );
}

static inline void register_function( lua_State* state, lua_CFunction wrapper_function, const std::string& name, bool global ) {
    lua_pushcfunction( state, wrapper_function, nullptr );

    if ( global )
        lua_setglobal( state, name.c_str( ) );
    else
        lua_setfield( state, -2, name.c_str( ) );
}

#endif