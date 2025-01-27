#ifndef LUAU_RUNTIME_H
#define LUAU_RUNTIME_H

#include "../Common.hpp"
#include "../Memory/Memory.hpp"
#include "../FileSystem/FileSystem.hpp"
#include "../Utils/Utils.hpp"

namespace Wrapper {
    int RandomString(lua_State* L /*, int length*/) {
        luaL_checktype(L, 1, LUA_TNUMBER);

        lua_pushstring(L, Utils::RandomString(luaL_checkinteger(L, 1)).c_str());

        return 1;
    }

    int ReadFile(lua_State* L /*, const char* file_path*/) {
        luaL_checktype(L, 1, LUA_TSTRING);
        lua_pushstring(L, FileSystem::ReadFile(luaL_checkstring(L, 1)).c_str());

        return 1;
    }

    int WriteFile(lua_State* L /*, const char* file_path, const char* content*/) {
        luaL_checktype(L, 1, LUA_TSTRING);
        luaL_checktype(L, 2, LUA_TSTRING);

        FileSystem::WriteFile(luaL_checkstring(L, 1), luaL_checkstring(L, 2));

        return 1;
    }

    static std::unordered_map<int, int> OriginalFunctions;

    // NOTE: Pasted from Synapse X / https://github.com/Acrillis/SynapseX/blob/master/Synapse/Src/Exploit/Execution/RbxApi.cpp#L1591
    int HookFunction(lua_State* L /*, const char* file_path, const char* content*/) {
        luaL_checktype(L, 1, LUA_TFUNCTION);
        luaL_checktype(L, 2, LUA_TFUNCTION);

        if (lua_iscfunction(L, 1)) {
            if (!lua_iscfunction(L, 2)) {
                luaL_argerror(L, 2, "C function expected");
                return 0;
            }

            // Backup original C function
            lua_pushvalue(L, 1);
            int OriginalRef = lua_ref(L, LUA_REGISTRYINDEX);

            // Hook the function by replacing its implementation
            lua_pushvalue(L, 2);
            lua_rawseti(L, LUA_REGISTRYINDEX, OriginalRef);

            // Return the original reference for potential restoration
            lua_pushinteger(L, OriginalRef);

            return 1;
        }

        if (lua_iscfunction(L, 2)) {
            luaL_argerror(L, 2, "Lua function expected");
            return 0;
        }

        lua_pushvalue(L, 1);
        int OriginalRef = lua_ref(L, LUA_REGISTRYINDEX);

        int HookUpvalues = lua_getupvalue(L, 2, 1) ? lua_gettop(L) : 0;
        int OriginalUpvalues = lua_getupvalue(L, 1, 1) ? lua_gettop(L) : 0;

        if (HookUpvalues > OriginalUpvalues) {
            luaL_argerror(L, 2, "hook function has too many upvalues");
            return 0;
        }

        // Replace the original function with the hook
        lua_pushvalue(L, 2);
        lua_rawseti(L, LUA_REGISTRYINDEX, OriginalRef);

        // Update upvalues
        for (int i = 1; i <= HookUpvalues; i++) {
            const char* name = lua_getupvalue(L, 2, i);
            if (name) lua_setupvalue(L, 1, i);
        }

        // Return the original reference for potential restoration
        lua_pushinteger(L, OriginalRef);

        return 1;
    }

    int RestoreFunction(lua_State* L) {
        intptr_t funcRef = reinterpret_cast<intptr_t>(lua_touserdata(L, 1));

        auto it = OriginalFunctions.find(funcRef);

        if (it != OriginalFunctions.end()) {
            OriginalFunctions.erase(it);
            lua_pushboolean(L, true);

            return 1;
        }

        lua_pushboolean(L, false);

        return 1;
    }
}

#endif