#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "../Common.hpp"

namespace FileSystem {
    std::string ReadFile(const std::string& file_path);
    void WriteFile(const std::string& file_path, const std::string& content);
};

#endif