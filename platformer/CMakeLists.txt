cmake_minimum_required(VERSION 3.16)
project(Platformer VERSION 1.0 LANGUAGES CXX)

# Require C++17 — this project uses structured bindings and std::optional
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 — CMake will search your system paths.
# On macOS with Homebrew: brew install sdl2
# On Ubuntu/Debian:       sudo apt install libsdl2-dev
# On Windows with vcpkg:  vcpkg install sdl2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Collect all .cpp files in src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL2 and SDL2_image using CMake imported targets.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)

# On some Linux setups SDL2 doesn't export include dirs through the target —
# this line makes sure the compiler can find SDL2/SDL.h.
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
