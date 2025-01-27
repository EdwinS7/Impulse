#ifndef LUAU_ENVIORNMENT_H
#define LUAU_ENVIORNMENT_H

#include "../Common.hpp"

class Enviornment {
public:
    Enviornment();
    ~Enviornment();

    bool LoadScript(const std::string& script);

    lua_State* GetState() const;

private:
    void HandleError(int error_code);

    lua_State* m_State;
};

#endif