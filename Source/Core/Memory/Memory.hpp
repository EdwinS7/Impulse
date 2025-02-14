#ifndef MEMORY_H
#define MEMORY_H

#include "../Common.hpp"

class CMemory {
public:
    void SetTarget( const char* target_name );
    template <typename T>
    static void Write( std::uintptr_t address, T* value );

    template <typename T>
    static T Read( std::uintptr_t address );

    std::uintptr_t ScanPattern( const std::string& signature );

private:
    HMODULE m_Target;
} extern Memory;

#endif