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
    D3D_PRIMITIVE_TOPOLOGY primitive_topology;
    std::vector<Vertex> vertices;
    std::vector<std::int32_t> indices;
    uint8_t z_index;

    constexpr DrawCommand( ) noexcept :
        primitive_topology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) {}
    constexpr DrawCommand( D3D_PRIMITIVE_TOPOLOGY primitive_topology ) :
        primitive_topology( primitive_topology ) {}
    constexpr DrawCommand( D3D_PRIMITIVE_TOPOLOGY primitive_topology, std::vector<Vertex> vertices, std::vector<std::int32_t> indices, uint8_t z_index ) :
        primitive_topology( primitive_topology ), vertices( vertices ), indices( indices ), z_index( z_index ) {}
};

class Color {
public:
    uint8_t r{}, g{}, b{}, a{ 255 }; // NOTE: Default alpha to 255 (fully opaque)

    constexpr Color( ) noexcept = default;
    constexpr Color( uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255 ) noexcept
        : r( r ), g( g ), b( b ), a( a ) {}
};

#endif