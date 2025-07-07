#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "../Common.hpp"

class CFileSystem {
public:
    std::vector<std::string> ListFiles( const char* dir_path );

    bool FileExists( const char* file_path );
    std::string ReadFile( const char* file_path);
    void WriteFile( const char* file_path, const char* content);
    void RenameFile( const char* old_path, const char* new_path );
    void DeleteFile_( const char* file_path );

    std::vector<std::string> ListDirectories( const char* dir_path );

    bool DirectoryExists( const char* dir_path );
    void CreateDirectory_( const char* dir_path );
    void DeleteDirectory( const char* dir_path );

    bool _LoadImageData( const char* file_path, unsigned char** pixels, int* width, int* height );
} extern FileSystem;

#endif