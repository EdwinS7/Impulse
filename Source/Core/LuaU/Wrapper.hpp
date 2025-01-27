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

    // NOTE: Temp removed cuz it no work
    // NOTE: Pasted from Synapse X / https://github.com/Acrillis/SynapseX/blob/master/Synapse/Src/Exploit/Execution/RbxApi.cpp#L1591
    int HookFunction(lua_State* L /*, const char* file_path, const char* content*/) {
        return 1;
    }

    int RestoreFunction(lua_State* L) {
        return 1;
    }
}

#endif