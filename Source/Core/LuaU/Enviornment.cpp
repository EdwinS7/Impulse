#include "Enviornment.hpp"
#include "Wrapper.hpp"

#define lua_pushfunction(L, fn) lua_pushcfunction(L, fn, nullptr)

Enviornment::Enviornment() {
    m_State = luaL_newstate();
    
    if (!m_State) {
        throw std::runtime_error("Failed to initialize Lua state.");
    }

    luaL_openlibs(m_State);

    lua_pushfunction(m_State, Wrapper::RandomString);
    lua_setglobal(m_State, "random_string");

    lua_pushfunction(m_State, Wrapper::ReadFile);
    lua_setglobal(m_State, "read_file");

    lua_pushfunction(m_State, Wrapper::WriteFile);
    lua_setglobal(m_State, "write_file");

    lua_pushfunction(m_State, Wrapper::HookFunction);
    lua_setglobal(m_State, "hook_function");
    
    lua_pushfunction(m_State, Wrapper::RestoreFunction);
    lua_setglobal(m_State, "restore_function");
}

Enviornment::~Enviornment() {
    if (m_State) {
        lua_close(m_State);
    }
}

bool Enviornment::LoadScript(const std::string& script) {
    size_t BytecodeSize = 0;
    char* Bytecode = luau_compile(script.c_str(), script.size(), nullptr, &BytecodeSize);

    int Result = luau_load(m_State, "main chunk", Bytecode, BytecodeSize, 0);

    free(Bytecode);

    if (Result != LUA_OK) {
        HandleError(Result);
        return false;
    }

    Result = lua_pcall(m_State, 0, LUA_MULTRET, 0);

    if (Result != LUA_OK) {
        HandleError(Result);
        return false;
    }

    return true;
}

lua_State* Enviornment::GetState() const {
    return m_State;
}

// PRIVATE

void Enviornment::HandleError(int error_code) {
    const char* Error = lua_tostring(m_State, -1);
    std::cerr << "[" << error_code << "] " << Error << std::endl;

    // Clear the error message from the stack
    lua_pop(m_State, 1);
}