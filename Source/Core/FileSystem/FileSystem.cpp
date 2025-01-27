#include "FileSystem.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>

std::string FileSystem::ReadFile(const std::string & file_path) {
    std::ifstream File(file_path, std::ios::in | std::ios::binary);

    if (!File)
        throw std::runtime_error("Unable to open file: " + file_path);

    File.seekg(0, std::ios::end);
    std::streampos file_size = File.tellg();
    File.seekg(0, std::ios::beg);

    std::string content;
    content.resize(file_size);

    if (!File.read(content.data(), file_size))
        throw std::runtime_error("Error reading file: " + file_path);

    return content;
}

void FileSystem::WriteFile(const std::string& file_path, const std::string& content) {
    std::ofstream file(file_path, std::ios::out | std::ios::binary);

    if (!file)
        throw std::runtime_error("Unable to open file for writing: " + file_path);

    file.write(content.data(), content.size());

    if (!file)
        throw std::runtime_error("Error writing to file: " + file_path);
}