cmake_minimum_required(VERSION 3.20)
project(Muharrik LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- SDL build options (must be set BEFORE add_subdirectory) ----
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)

# Build SDL from the submodule
add_subdirectory(thirdparty/sdl EXCLUDE_FROM_ALL)

# Your test app
add_executable(app
    src/main.cpp
)

# glm is header-only
target_include_directories(app PRIVATE
    ${CMAKE_SOURCE_DIR}/thirdparty/glm
)

# SDL sometimes provides its own main() on some platforms.
# This avoids surprises and is a good habit.
target_compile_definitions(app PRIVATE SDL_MAIN_HANDLED)

# Link SDL (handle SDL3 vs SDL2 automatically)
if (TARGET SDL3::SDL3-static)
    target_link_libraries(app PRIVATE SDL3::SDL3-static)
elseif (TARGET SDL2::SDL2-static)
    target_link_libraries(app PRIVATE SDL2::SDL2-static)
elseif (TARGET SDL2::SDL2)
    target_link_libraries(app PRIVATE SDL2::SDL2)
else()
    message(FATAL_ERROR "Could not find SDL CMake target. Check whether you checked out SDL2 or SDL3 and that it builds.")
endif()
