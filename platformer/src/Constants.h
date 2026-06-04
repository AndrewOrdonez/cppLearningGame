#pragma once   // Include guard — like #ifndef CONSTANTS_H / #define / #endif but shorter.
               // Prevents this header from being compiled twice in one translation unit.

// ---- Constants ---------------------------------------------------------------
// In C++, constexpr means "evaluate this at compile time".
// Prefer it over #define: it's typed, scoped, and debuggable.
namespace Constants {
    constexpr int   SCREEN_W     = 800;
    constexpr int   SCREEN_H     = 600;
    constexpr float GRAVITY      = 1800.0f; // pixels per second²
    constexpr float JUMP_SPEED   = -650.0f; // negative = upward (Y increases downward)
    constexpr float MANTLE_SPEED = -300.0f;
    constexpr float MOVE_SPEED   = 280.0f;
    constexpr float MAX_FALL     = 1200.0f; // terminal velocity
}

// ---- Vec2 --------------------------------------------------------------------
// A simple 2D float vector. In C# you'd reach for Vector2 — here we make our own.
// struct in C++ is identical to class except members are public by default.
struct Vec2 {
    float x = 0.0f;  // Member default initializers (C++11+) — like C# auto-props with defaults
    float y = 0.0f;

    // Operator overloading — C++ lets you define what +, +=, * mean for your type.
    Vec2 operator+(const Vec2& other) const { return {x + other.x, y + other.y}; }
    Vec2 operator-(const Vec2& other) const { return {x - other.x, y - other.y}; }
    Vec2 operator*(float s)           const { return {x * s, y * s}; }

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;  // Returning *this from compound-assignment is idiomatic C++
    }
};
