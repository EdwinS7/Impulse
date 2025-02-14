#ifndef LUAU_ENVIORNMENT_H
#define LUAU_ENVIORNMENT_H

#include "../Common.hpp"

class CEnvironment {
public:
    CEnvironment();
    ~CEnvironment();

    lua_State* GetState( );

    bool RunScript( std::string script, std::string& error );
    
    void RunConnection( const char* connection_name );
    int AddConnection( const char* connection_name, int function_reference );
    void RemoveConnection( int connection_id );

private:
    lua_State* m_State = nullptr;
    const char* m_ChunkName = "chunk";

    // TODO: Make a connection class, store the id, function, and function arguments.
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> m_Connections = {
       {"new_frame", std::vector<std::pair<int, int>>( ) },
       {"shutdown", std::vector<std::pair<int, int>>( ) },
    };

    std::string CompileScript( std::string script, std::string& error );
} extern Environment;

#endif