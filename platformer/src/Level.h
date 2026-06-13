#pragma once
#include <SDL2/SDL.h>
#include "Constants.h"
#include "Platform.h"
#include <vector>

class Level
{
private:
    std::vector<Platform> platforms;
public:
    Level(int levelNumber);
    static std::vector<Platform> buildLevel(int levelNumber);
    static int getLevelWidth(int levelNumber);
};

Level::Level(int levelNumber)
{
}

std::vector<Platform> Level::buildLevel(int levelNumber) {
    return {
        // Ground platform spanning the whole screen
        {   0.0f, 540.0f, 2000.0f,  60.0f },

        // Floating platforms
        {  80.0f, 430.0f, 140.0f,  18.0f },
        { 280.0f, 350.0f, 160.0f,  18.0f },
        { 500.0f, 280.0f, 120.0f,  18.0f },
        { 650.0f, 380.0f, 130.0f,  18.0f },
        { 160.0f, 220.0f, 100.0f,  18.0f },
        { 380.0f, 160.0f, 180.0f,  18.0f },
        { 1300.0f, 430.0f, 300.0f,  18.0f },
        { 1400.0f, 370.0f, 100.0f,  50.0f },
    };
}

int Level::getLevelWidth(int levelNumber) {
    return 2000;
}