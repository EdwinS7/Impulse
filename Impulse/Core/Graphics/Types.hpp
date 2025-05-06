#ifndef TYPES_H
#define TYPES_H

class Vector2 {
public:
    int x{}, y{};

    constexpr Vector2( ) noexcept = default;
    constexpr Vector2( int x, int y ) noexcept 
        : x( x ), y( y ) {}
};

class Vector3 {
public:
    float x{}, y{}, z{};

    constexpr Vector3( ) noexcept = default;
    constexpr Vector3( float x, float y, float z ) noexcept
        : x( x ), y( y ), z( z ) {}
};

class Color {
public:
    uint8_t r{}, g{}, b{}, a{ 255 }; // NOTE: Default alpha to 255 (fully opaque)

    constexpr Color( ) noexcept = default;
    constexpr Color( uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255 ) noexcept
        : r( r ), g( g ), b( b ), a( a ) {}
};

class Texture {
public:
	const char* Name = nullptr;
	ID3D11Texture2D* pTexture = nullptr;
	ID3D11ShaderResourceView* pTextureSRV = nullptr;

	constexpr Texture( ) noexcept = default;
	constexpr Texture( const char* name = nullptr, ID3D11Texture2D* texture = nullptr, ID3D11ShaderResourceView* texture_srv = nullptr ) noexcept
		: Name( name ), pTexture( texture ), pTextureSRV( texture_srv ) {}
};

#define RGBA_TO_DWORD(r, g, b, a) \
    ((DWORD)((((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff)))

class Vertex {
public:
    float x{}, y{}, z{}, rhw{};
    float u{}, v{}; // NOTE: Texture coordinates
    unsigned long color{};

    constexpr Vertex( ) noexcept = default;
    constexpr Vertex( float x, float y, float z, float rhw, float u, float v, unsigned long color ) noexcept
        : x( x ), y( y ), z( z ), rhw( rhw ), u( u ), v( v ), color( color ) {}
    constexpr Vertex( float x, float y, float z, float rhw, float u, float v, Color color ) noexcept
        : x( x ), y( y ), z( z ), rhw( rhw ), u( u ), v( v ), color( RGBA_TO_DWORD(color.r, color.g, color.b, color.a ) ) {}
};

class DrawCommand {
public:
    D3D_PRIMITIVE_TOPOLOGY primitive_topology;
    std::vector<Vertex> vertices;
    std::vector<std::int32_t> indices;
    Texture* texture;
    uint8_t z_index;

    constexpr DrawCommand( ) noexcept :
        primitive_topology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) {}
    constexpr DrawCommand( D3D_PRIMITIVE_TOPOLOGY primitive_topology ) :
        primitive_topology( primitive_topology ) {}
    constexpr DrawCommand( D3D_PRIMITIVE_TOPOLOGY primitive_topology, std::vector<Vertex> vertices, std::vector<std::int32_t> indices, Texture* texture, uint8_t z_index ) :
        primitive_topology( primitive_topology ), vertices( vertices ), indices( indices ), texture( texture ), z_index( z_index ) {}
};

#endif