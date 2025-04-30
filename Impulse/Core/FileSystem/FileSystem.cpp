#include "FileSystem.hpp"

std::vector<std::string> CFileSystem::ListFiles( const char* dir_path ) {
    std::vector<std::string> Files;

    for ( const auto& file : std::filesystem::directory_iterator( dir_path ) ) {
        if ( file.is_regular_file( ) )
            Files.push_back( file.path( ).filename( ).string( ) );
    }

    return Files;
}

bool CFileSystem::FileExists( const char* file_path ) {
    return std::filesystem::exists( file_path ) && std::filesystem::is_regular_file( file_path );
}

std::string CFileSystem::ReadFile( const char* file_path ) {
    std::ifstream File( file_path, std::ios::in | std::ios::binary );
    if ( !File ) {
        std::cerr << "Failed to open file: " << file_path << std::endl;

        return std::string( );
    }

    return std::string(
        std::istreambuf_iterator<char>( File ),
        std::istreambuf_iterator<char>( )
    );
}

void CFileSystem::WriteFile( const char* file_path, const char* content ) {
    std::ofstream File( file_path, std::ios::out | std::ios::binary );

    if ( !File )
        return;

    File << content;
}

void CFileSystem::RenameFile( const char* old_path, const char* new_path ) {
    if ( std::filesystem::exists( old_path ) ) {
        std::filesystem::rename( old_path, new_path );
    }
}

void CFileSystem::DeleteFile_( const char* file_path ) {
    if ( std::filesystem::exists( file_path ) ) {
        std::filesystem::remove( file_path );
    }
}

std::vector<std::string> CFileSystem::ListDirectories( const char* dir_path ) {
    std::vector<std::string> directories;

    for ( const auto& file : std::filesystem::directory_iterator( dir_path ) ) {
        if ( file.is_directory( ) )
            directories.push_back( file.path( ).filename( ).string( ) );
    }

    return directories;
}

bool CFileSystem::DirectoryExists( const char* dir_path ) {
    return std::filesystem::is_directory( dir_path );
}

void CFileSystem::CreateDirectory_( const char* dir_path ) {
    std::filesystem::create_directory( dir_path );
}

void CFileSystem::DeleteDirectory( const char* dir_path ) {
    if ( DirectoryExists( dir_path ) ) {
        std::filesystem::remove( dir_path );
    }
}

CFileSystem FileSystem;