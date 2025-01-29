#ifndef TYPES_H
#define TYPES_H

class Vector2 {
public:
    int x{}, y{};

    constexpr Vector2( ) noexcept = default;
    constexpr Vector2( int x, int y ) noexcept : x( x ), y( y ) {}
};

class Vector3 {
public:
    int x{}, y{}, z{};

    constexpr Vector3( ) noexcept = default;
    constexpr Vector3( int x, int y, int z ) noexcept : x( x ), y( y ), z( z ) {}
};

class Vector4 {
public:
    int w{}, x{}, y{}, z{};

    constexpr Vector4( ) noexcept = default;
    constexpr Vector4( int w, int x, int y, int z ) noexcept : w( w ), x( x ), y( y ), z( z ) {}
};

class Vertex {
public:
    float x{}, y{}, z{};
    float u{}, v{}; // NOTE: Texture coordinates
    unsigned long color{};

    constexpr Vertex( ) noexcept = default;

    constexpr Vertex( float x, float y, float z, float u, float v, unsigned long color ) noexcept
        : x( x ), y( y ), z( z ), u( u ), v( v ), color( color ) {}
};

class Color {
public:
    float r{}, g{}, b{}, a{ 1.0f }; // NOTE: Default alpha to 1 (fully opaque)

    constexpr Color( ) noexcept = default;

    constexpr Color( float r, float g, float b, float a = 1.0f ) noexcept
        : r( r ), g( g ), b( b ), a( a ) {}
};

#endif