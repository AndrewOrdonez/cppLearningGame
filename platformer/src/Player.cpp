#include "Player.h"
#include <algorithm>  // std::clamp, std::min, std::max

// ---- Constructor -------------------------------------------------------------
// The : pos{startX, startY}, vel{} syntax is an "initializer list".
// It initializes members BEFORE the constructor body runs — more efficient than
// assigning inside the body, and required for const members and references.
Player::Player(float startX, float startY)
    : pos{startX, startY}
    , vel{}
{}

// ---- Input -------------------------------------------------------------------
// SDL gives us a snapshot of every key on the keyboard as a byte array.
// keystate[SDL_SCANCODE_X] is 1 if that key is held, 0 if not.
// Scancodes refer to physical key positions; keycodes refer to the symbol.
void Player::handleInput(const Uint8* keystate) {
    float moveX = 0.0f;

    if (keystate[SDL_SCANCODE_LEFT]  || keystate[SDL_SCANCODE_A]) moveX -= 1.0f;
    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) moveX += 1.0f;

    vel.x = moveX * Constants::MOVE_SPEED;

    // Jump — only when standing on something
    if (onGround && (keystate[SDL_SCANCODE_SPACE] || keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])) {
        vel.y     = Constants::JUMP_SPEED;
        onGround  = false;
    }
}

// ---- Update (physics + collision) --------------------------------------------
// dt = delta time in seconds (e.g. 0.016 for 60fps).
// Multiplying by dt makes movement frame-rate-independent — same as in C# Unity.
void Player::update(float dt, const std::vector<Platform>& platforms) {
    // Apply gravity
    vel.y += Constants::GRAVITY * dt;

    // Clamp fall speed
    vel.y = std::min(vel.y, Constants::MAX_FALL);

    // Integrate velocity → position
    pos += vel * dt;

    // Resolve AABB collisions
    onGround = false;
    resolveCollisions(platforms);

    // Screen boundary (left/right only — falling off bottom just keeps falling)
    if (pos.x < 0.0f)                              pos.x = 0.0f;
    if (pos.x + width > Constants::SCREEN_W)       pos.x = Constants::SCREEN_W - width;
}

// ---- Collision resolution ----------------------------------------------------
// AABB = Axis-Aligned Bounding Box. Since nothing rotates, we can use the
// minimum-translation-vector (MTV) approach: find how much the player overlaps
// each platform, then push them apart along the shallowest axis.
void Player::resolveCollisions(const std::vector<Platform>& platforms) {
    // Range-for over a vector — identical in feel to C# foreach.
    // 'const auto&' — auto deduces Platform, & avoids copying, const for safety.
    for (const auto& plat : platforms) {
        // Player AABB edges
        float pLeft   = pos.x;
        float pRight  = pos.x + width;
        float pTop    = pos.y;
        float pBottom = pos.y + height;
        float pTopThird = pos.y + height / 3.0f;

        // Platform edges
        float platLeft   = plat.x;
        float platRight  = plat.x + plat.w;
        float platTop    = plat.y;
        float platBottom = plat.y + plat.h;

        // Check overlap on both axes
        bool overlapX = pRight > platLeft && pLeft < platRight;
        bool overlapY = pBottom > platTop && pTop < platBottom;

        if (!overlapX || !overlapY) continue;  // No collision — skip

        // Compute overlap depths on each axis
        float overlapLeft   = pRight  - platLeft;   // How far player's right is past platform's left
        float overlapRight  = platRight  - pLeft;   // How far platform's right is past player's left
        float overlapTop    = pBottom - platTop;     // How far player's bottom is past platform's top
        float overlapBottom = platBottom - pTop;     // How far platform's bottom is past player's top

        // Find the minimum penetration
        float minX = std::min(overlapLeft, overlapRight);
        float minY = std::min(overlapTop, overlapBottom);

        if (minY < minX) {
            // Resolve vertically (common case: landing on top, hitting ceiling)
            if (overlapTop < overlapBottom) {
                pos.y = platTop - height;   // Land on top
                vel.y = 0.0f;
                onGround = true;
                redAmount = 70;
            } else {
                pos.y = platBottom;         // Hit ceiling
                vel.y = 0.0f;
            }
        } else {
            if (pTopThird < platTop) {
                    vel.y = Constants::MANTLE_SPEED;; 
                    redAmount = 255;
            }
            // Resolve horizontally (hitting a wall)
            if (overlapLeft < overlapRight) {
                pos.x = platLeft - width;   // Pushed left
            } else {
                pos.x = platRight;          // Pushed right
            }
            vel.x = 0.0f;
        }
    }
}

// ---- Render ------------------------------------------------------------------
// SDL_RenderFillRectF draws a filled rectangle using float coordinates.
// We pass a pointer to a local SDL_FRect — the F stands for float.
void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, redAmount, 130, 220, 255);  // R, G, B, Alpha

    SDL_FRect rect{ pos.x, pos.y, width, height };
    SDL_RenderFillRectF(renderer, &rect);  // & takes the address — gives us a pointer to rect
}
