#pragma once

#include "../../Utils/Utils.hpp"

namespace LuaBind::LuaCrypt {
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