#pragma once
#include <SDL2/SDL.h>
#include "Constants.h"

// Platform is pure data — no physics logic lives here.
// Keeping data and behavior separate is good practice; it also makes Platform
// trivially copyable (the compiler-generated copy/move constructors are sufficient).
struct Platform {
    float x, y, w, h;

    // SDL_FRect is SDL's float rectangle: {x, y, w, h}
    // Returning by value is cheap — SDL_FRect is 16 bytes (4 floats).
    SDL_FRect rect() const {
        return {x, y, w, h};
    }
};
