#ifndef MEMORY_H
#define MEMORY_H

#include "../Common.hpp"

class Memory {
public:
    std::uintptr_t ScanPattern(const char* target, const std::string& signature);
};

#endif