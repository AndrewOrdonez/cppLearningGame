#pragma once
#include <vector>      // std::vector — like C# List<T>
#include <string>      // std::vector — like C# List<T>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Constants.h"
#include "Platform.h"

// ---- Player class ------------------------------------------------------------
// In C++, the class definition (declaration of members) goes in the .h file.
// The method bodies (definitions) go in the .cpp file.
// This separation keeps compile times manageable — only files that #include
// Player.h get recompiled when the header changes, not all of them.

class Player {
public:
    // Constructor — called when you create a Player object.
    // C++ constructors can use an initializer list (the : pos{...} part).
    // Prefer initializer lists over assignment in the body — they're more efficient.
    Player(float startX, float startY);

    // Pass platforms by const reference — no copy, no ownership transfer.
    // In C#, reference types (classes) are always passed by reference implicitly.
    // In C++, you must be explicit: & means reference, const means read-only.
    void update(float dt, const std::vector<Platform>& platforms);

// ---- Vec2 --------------------------------------------------------------------

    void handleInput(const Uint8* keystate);  // Uint8 is SDL's typedef for unsigned char

    void render(SDL_Renderer* renderer, Vec2 windowScale);      // Raw pointer — SDL owns this, we just borrow it

    // Accessor — read-only view of position
    Vec2 getPosition() const { return pos; }

    void loadTexture(std::string path, SDL_Renderer* renderer);

private:
    // Private members: only Player's own methods can touch these.
    // This is the same access control as C#, just with the colon syntax.
    Vec2  pos;
    Vec2  vel;
    float width  = 32.0f;
    float height = 48.0f;
    int redAmount = 70;
    bool  onGround = false;
    bool flipped = false;

    SDL_Surface *playerSprite = NULL;
    SDL_Texture *playerTexture = NULL;

    // Helper declared here, defined in .cpp — keeps the header clean
    void resolveCollisions(const std::vector<Platform>& platforms);
};
