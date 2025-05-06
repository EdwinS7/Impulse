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

static IWICImagingFactory* GetWICFactory( ) {
    static IWICImagingFactory* Factory = NULL;

    if ( !Factory ) {
        CoInitialize( NULL );

        CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IWICImagingFactory,
            ( void** ) &Factory
        );
    }

    return Factory;
}

bool CFileSystem::_LoadImage( const char* file_path, unsigned char** pixels, int* width, int* height ) {
    if ( !file_path || !pixels || !width || !height )
        return false;

    wchar_t WFilePath[ MAX_PATH ];

    int Length = MultiByteToWideChar( CP_UTF8, 0, file_path, -1, NULL, 0 );

    if ( Length == 0 || Length > MAX_PATH )
        return false;

    MultiByteToWideChar( CP_UTF8, 0, file_path, -1, WFilePath, Length );

    IWICImagingFactory* Factory = GetWICFactory( );
    IWICBitmapDecoder* Decoder = NULL;

    if ( FAILED( Factory->CreateDecoderFromFilename( WFilePath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &Decoder ) ) ) {
        return false;
    }

    IWICBitmapFrameDecode* Frame = NULL;
    if ( FAILED( Decoder->GetFrame( 0, &Frame ) ) ) {
        Decoder->Release( );
        return false;
    }
    Decoder->Release( );

    UINT ImageWidth = 0, ImageHeight = 0;
    if ( FAILED( Frame->GetSize( &ImageWidth, &ImageHeight ) ) ) {
        Frame->Release( );
        return false;
    }

    IWICFormatConverter* Converter = NULL;
    if ( FAILED( Factory->CreateFormatConverter( &Converter ) ) ) {
        Frame->Release( );
        return false;
    }

    if ( FAILED( Converter->Initialize( Frame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom ) ) ) {
        Converter->Release( );
        Frame->Release( );
        return false;
    }

    Frame->Release( );

    size_t row_pitch = ImageWidth * 4;
    size_t data_size = row_pitch * ImageHeight;
    unsigned char* pixel_buffer = ( unsigned char* ) malloc( data_size );

    if ( !pixel_buffer ) {
        Converter->Release( );
        return false;
    }

    if ( FAILED( Converter->CopyPixels( NULL, ( UINT ) row_pitch, ( UINT ) data_size, pixel_buffer ) ) ) {
        free( pixel_buffer );
        Converter->Release( );
        return false;
    }

    Converter->Release( );

    *pixels = pixel_buffer;
    *width = ( int ) ImageWidth;
    *height = ( int ) ImageHeight;

    return true;
}

CFileSystem FileSystem;