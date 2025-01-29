#ifndef TYPES_H
#define TYPES_H

class Vector2 {
public:
    int x{}, y{};

    constexpr Vector2( ) noexcept = default;
    constexpr Vector2( int x, int y ) noexcept : x( x ), y( y ) {}

    constexpr Vector2 operator+( const Vector2& v ) const noexcept { return { x + v.x, y + v.y }; }
    constexpr Vector2 operator-( const Vector2& v ) const noexcept { return { x - v.x, y - v.y }; }
    constexpr Vector2 operator*( const Vector2& v ) const noexcept { return { x * v.x, y * v.y }; }
    constexpr Vector2 operator/( const Vector2& v ) const noexcept { return { x / v.x, y / v.y }; }

    constexpr Vector2& operator+=( const Vector2& v ) noexcept { x += v.x; y += v.y; return *this; }
    constexpr Vector2& operator-=( const Vector2& v ) noexcept { x -= v.x; y -= v.y; return *this; }
    constexpr Vector2& operator*=( const Vector2& v ) noexcept { x *= v.x; y *= v.y; return *this; }
    constexpr Vector2& operator/=( const Vector2& v ) noexcept { x /= v.x; y /= v.y; return *this; }

    constexpr bool operator==( const Vector2& v ) const noexcept { return x == v.x && y == v.y; }
    constexpr bool operator<( const Vector2& v ) const noexcept { return x < v.x && y < v.y; }
    constexpr bool operator>( const Vector2& v ) const noexcept { return x > v.x && y > v.y; }
    constexpr bool operator<=( const Vector2& v ) const noexcept { return !( *this > v ); }
    constexpr bool operator>=( const Vector2& v ) const noexcept { return !( *this < v ); }
};

class Vector3 {
public:
    int x{}, y{}, z{};

    constexpr Vector3( ) noexcept = default;
    constexpr Vector3( int x, int y, int z ) noexcept : x( x ), y( y ), z( z ) {}

    constexpr Vector3 operator+( const Vector3& v ) const noexcept { return { x + v.x, y + v.y, z + v.z }; }
    constexpr Vector3 operator-( const Vector3& v ) const noexcept { return { x - v.x, y - v.y, z - v.z }; }
    constexpr Vector3 operator*( const Vector3& v ) const noexcept { return { x * v.x, y * v.y, z * v.z }; }
    constexpr Vector3 operator/( const Vector3& v ) const noexcept { return { x / v.x, y / v.y, z / v.z }; }

    constexpr Vector3& operator+=( const Vector3& v ) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
    constexpr Vector3& operator-=( const Vector3& v ) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
    constexpr Vector3& operator*=( const Vector3& v ) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
    constexpr Vector3& operator/=( const Vector3& v ) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }

    constexpr bool operator==( const Vector3& v ) const noexcept { return x == v.x && y == v.y && z == v.z; }
    constexpr bool operator<( const Vector3& v ) const noexcept { return x < v.x && y < v.y && z < v.z; }
    constexpr bool operator>( const Vector3& v ) const noexcept { return x > v.x && y > v.y && z > v.z; }
    constexpr bool operator<=( const Vector3& v ) const noexcept { return !( *this > v ); }
    constexpr bool operator>=( const Vector3& v ) const noexcept { return !( *this < v ); }
};

#endif