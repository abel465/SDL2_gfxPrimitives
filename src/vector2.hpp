#ifndef SDL2_GFXPRIMITIVES_VECTOR2_HPP
#define SDL2_GFXPRIMITIVES_VECTOR2_HPP

#include <cmath>

template <typename T>
struct Vector2 {
    constexpr Vector2(T p_x, T p_y) noexcept : x{p_x}, y{p_y} {}
    constexpr Vector2(const T* vx, const T* vy, int i) noexcept : x{vx[i]}, y{vy[i]} {}

    [[nodiscard]] constexpr Vector2 operator+() const noexcept {
        return *this;
    }

    [[nodiscard]] constexpr Vector2 operator-() const noexcept {
        return {-x, -y};
    }

    [[nodiscard]] constexpr Vector2 operator+(Vector2 other) const noexcept {
        return {x + other.x, y + other.y};
    }

    [[nodiscard]] constexpr Vector2 operator-(Vector2 other) const noexcept {
        return {x - other.x, y - other.y};
    }

    constexpr Vector2& operator+=(Vector2 other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr Vector2& operator-=(Vector2 other) noexcept {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    [[nodiscard]] constexpr Vector2 operator*(T scalar) const noexcept {
        return {x * scalar, y * scalar};
    }

    [[nodiscard]] constexpr Vector2 operator/(T scalar) const noexcept {
        return {x / scalar, y / scalar};
    }

    constexpr Vector2& operator*=(T scalar) noexcept {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr Vector2& operator/=(T scalar) noexcept {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    [[nodiscard]] constexpr T dot_product(Vector2 other) const noexcept {
        return x * other.x + y * other.y;
    }

    [[nodiscard]] constexpr T magnitude() const noexcept {
        return std::sqrt(dot_product(*this));
    }

    [[nodiscard]] constexpr Vector2 normal() const noexcept {
        return {-y, x};
    }

    [[nodiscard]] constexpr Vector2 unit_vector() const noexcept {
        return *this / magnitude();
    }

    [[nodiscard]] constexpr Vector2 unit_normal() const noexcept {
        return normal().unit_vector();
    }

    [[nodiscard]] constexpr T atan2() const noexcept {
        return std::atan2(y, x);
    }

    [[nodiscard]] friend constexpr Vector2 operator*(T scalar, Vector2 vec) noexcept {
        return {scalar * vec.x, scalar * vec.y};
    }

    T x;
    T y;
};

template <typename T>
Vector2(T* vx, T* vy, int i) -> Vector2<T>;

#endif //SDL2_GFXPRIMITIVES_VECTOR2_HPP
