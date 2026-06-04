# C++ Platformer — Learning Project

A minimal SDL2 platformer designed to introduce C++ concepts to developers
already experienced in C#, JavaScript, or similar languages.

## What you'll learn from this code

| C++ concept              | Where it appears                              |
|--------------------------|-----------------------------------------------|
| Stack vs heap allocation | `Player player(...)` vs `SDL_CreateWindow`    |
| Header / .cpp split      | Player.h declaration, Player.cpp definition   |
| Pointers & references    | `SDL_Renderer*`, `const std::vector<...>&`    |
| unique_ptr / RAII        | WindowPtr / RendererPtr in main.cpp           |
| Operator overloading     | Vec2 +, -, * in Constants.h                   |
| Aggregate initialization | Platform{x, y, w, h} in buildLevel()          |
| Range-for                | `for (const auto& plat : platforms)`          |
| Delta-time game loop     | `dt` calculation in main loop                 |
| AABB collision           | Player::resolveCollisions()                   |
| constexpr                | Constants namespace in Constants.h            |

---

## Prerequisites

Install SDL2 for your platform:

### macOS (Homebrew)
```
brew install sdl2
```

### Ubuntu / Debian
```
sudo apt install libsdl2-dev
```

### Windows (vcpkg)
```
vcpkg install sdl2
```

---

## Build & Run

```bash
# From the project root:
mkdir build && cd build
cmake ..
cmake --build .
./Platformer        # macOS/Linux
Platformer.exe      # Windows
```

### Windows: alternative manual compile (MinGW)
```
g++ -std=c++17 src/*.cpp -Iinclude -lSDL2 -o Platformer.exe
```

---

## Controls

| Key              | Action     |
|------------------|------------|
| A / Left arrow   | Move left  |
| D / Right arrow  | Move right |
| W / Up / Space   | Jump       |
| Escape           | Quit       |

---

## Suggested next steps (each teaches something new)

1. **Sprite sheet rendering** — SDL_RenderCopyEx, textures, SDL_image  
   *Teaches: resource loading, SDL_Texture lifetime, SDL_image linkage*

2. **Animated tiles** — load a tilemap from a 2D array  
   *Teaches: 2D vectors, enum class for tile types, bitwise flags*

3. **Camera / scrolling** — offset all draw calls by a camera position  
   *Teaches: coordinate systems, passing state through render()*

4. **Collectibles / enemies** — add a base `Entity` class  
   *Teaches: inheritance, virtual functions, vtables*

5. **Sound effects** — SDL_mixer for jump/land sounds  
   *Teaches: linking a second SDL extension library*

6. **Save/load** — write player position to a binary file with fstream  
   *Teaches: file I/O, binary vs text streams, endianness*
