#ifndef TYPES_H
#define TYPES_H

class Vector2 {
public:
    int x{}, y{};

    Vector2( ) noexcept = default;
    Vector2( int x, int y ) noexcept 
        : x( x ), y( y ) {}
};

class Vector3 {
public:
    float x{}, y{}, z{};

    Vector3( ) noexcept = default;
    Vector3( float x, float y, float z ) noexcept
        : x( x ), y( y ), z( z ) {}
};

class Color {
public:
    uint8_t r{}, g{}, b{}, a{ 255 }; // NOTE: Default alpha to 255 (fully opaque)

    Color( ) noexcept = default;
    Color( uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255 ) noexcept
        : r( r ), g( g ), b( b ), a( a ) {}
};

class Texture {
public:
	std::string Name;
	ID3D11Texture2D* pTexture = nullptr;
	ID3D11ShaderResourceView* pTextureSRV = nullptr;

	Texture( ) noexcept = default;
	Texture( std::string name, ID3D11Texture2D* texture, ID3D11ShaderResourceView* texture_srv ) noexcept
		: Name( std::move( name ) ), pTexture( texture ), pTextureSRV( texture_srv ) {}
};

struct Glyph {
    float AdvanceX;
    float OffsetX, OffsetY;
    float Width, Height;
    float u0, v0, u1, v1;

    Texture* _Texture;

    Glyph( ) noexcept = default;
    Glyph( float advance_x, float offset_x, float offset_y, float width, float height, float u0, float v0, float u1, float v1, Texture* texture )
        : AdvanceX( advance_x ), OffsetX( offset_x ), OffsetY( offset_y ), Width( width ), Height( height ), u0( u0 ), v0( v0 ), u1( u1 ), v1( v1 ), _Texture( texture ) {}
};

class Font {
public:
    std::string Name;
    int Size;

    std::map<char, Glyph> Glyphs;

    Font( ) noexcept = default;

    Font( const std::string& name, int size )
        : Name( name ), Size( size ) {}

    /*const Glyph* GetGlyph( char character ) const {
        auto It = Glyphs.find( character );

        if ( It != Glyphs.end( ) ) {
            return It->second;
        }
        
        return nullptr;
    }*/
};

#define RGBA_TO_DWORD(r, g, b, a) \
    ((DWORD)((((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff)))

class Vertex {
public:
    float x{}, y{}, z{}, rhw{};
    float u{}, v{}; // NOTE: Texture coordinates
    unsigned long color{};

    Vertex( ) noexcept = default;
    Vertex( float x, float y, float z, float rhw, float u, float v, unsigned long color ) noexcept
        : x( x ), y( y ), z( z ), rhw( rhw ), u( u ), v( v ), color( color ) {}
    Vertex( float x, float y, float z, float rhw, float u, float v, Color color ) noexcept
        : x( x ), y( y ), z( z ), rhw( rhw ), u( u ), v( v ), color( RGBA_TO_DWORD(color.r, color.g, color.b, color.a ) ) {}
};

class DrawCommand {
public:
    D3D_PRIMITIVE_TOPOLOGY primitive_topology;
    std::vector<Vertex> vertices;
    std::vector<std::int32_t> indices;
    Texture* texture;
    uint8_t z_index;

    DrawCommand( ) noexcept :
        primitive_topology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) {}
    DrawCommand( D3D_PRIMITIVE_TOPOLOGY primitive_topology ) :
        primitive_topology( primitive_topology ) {}
    DrawCommand( D3D_PRIMITIVE_TOPOLOGY primitive_topology, std::vector<Vertex> vertices, std::vector<std::int32_t> indices, Texture* texture, uint8_t z_index ) :
        primitive_topology( primitive_topology ), vertices( vertices ), indices( indices ), texture( texture ), z_index( z_index ) {}
};

#endif