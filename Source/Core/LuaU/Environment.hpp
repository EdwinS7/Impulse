#ifndef LUAU_ENVIORNMENT_H
#define LUAU_ENVIORNMENT_H

#include "../Common.hpp"

class CEnvironment {
private:
    lua_State* m_State = nullptr;
    const char* m_ChunkName = "chunk";

public:
    bool Initiate( );
    bool Cleanup( );

    bool LoadScript( const char* name, std::string source_code );
    bool LoadFile( const char* file_path );

    lua_State* GetState( );
} extern Environment;

#include "Callbacks.hpp"

#endif