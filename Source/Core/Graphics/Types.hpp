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
    int x{}, y{}, z{};

    constexpr Vector3( ) noexcept = default;
    constexpr Vector3( int x, int y, int z ) noexcept 
        : x( x ), y( y ), z( z ) {}
};

class Vector4 {
public:
    int w{}, x{}, y{}, z{};

    constexpr Vector4( ) noexcept = default;
    constexpr Vector4( int w, int x, int y, int z ) noexcept 
        : w( w ), x( x ), y( y ), z( z ) {}
};

class Vertex {
public:
    float x{}, y{}, z{}, rhw{};
    float u{}, v{}; // NOTE: Texture coordinates
    unsigned long color{};

    constexpr Vertex( ) noexcept = default;
    constexpr Vertex( float x, float y, float z, float rhw, float u, float v, unsigned long color ) noexcept
        : x( x ), y( y ), z( z ), rhw( rhw ), u( u ), v( v ), color( color ) {}
};

class DrawCommand {
public:
    D3D_PRIMITIVE_TOPOLOGY primitive_type;
    std::vector<Vertex> vertices;
    std::vector<std::int32_t> indices;

    constexpr DrawCommand( ) noexcept = default;
    constexpr DrawCommand( D3D_PRIMITIVE_TOPOLOGY primitive_type ) :
        primitive_type( primitive_type ) {}
    constexpr DrawCommand( D3D_PRIMITIVE_TOPOLOGY primitive_type, std::vector<Vertex> vertices, std::vector<std::int32_t> indices ) :
        primitive_type( primitive_type ), vertices( vertices ), indices( indices ) {}
};

class Color {
public:
    uint8_t r{}, g{}, b{}, a{ 255 }; // NOTE: Default alpha to 255 (fully opaque)

    constexpr Color( ) noexcept = default;
    constexpr Color( uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255 ) noexcept
        : r( r ), g( g ), b( b ), a( a ) {}
};

#endif