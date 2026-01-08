cmake_minimum_required(VERSION 3.20)
project(Muharrik LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(Vulkan REQUIRED)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/sdl EXCLUDE_FROM_ALL)

# ---- Collect engine sources (optional for now) ----
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/engine/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/engine/*.c"
)

# App
add_executable(app src/main.cpp)
target_compile_definitions(app PRIVATE SDL_MAIN_HANDLED)

# glm include (header-only)
target_include_directories(app PRIVATE
    "${CMAKE_SOURCE_DIR}/thirdparty/glm"
    "${CMAKE_SOURCE_DIR}/src"
)

# Vulkan
#target_link_libraries(app PRIVATE Vulkan::Vulkan)

# SDL link
if (TARGET SDL3::SDL3-static)
    target_link_libraries(app PRIVATE SDL3::SDL3-static)
elseif (TARGET SDL2::SDL2-static)
    target_link_libraries(app PRIVATE SDL2::SDL2-static)
elseif (TARGET SDL2::SDL2)
    target_link_libraries(app PRIVATE SDL2::SDL2)
else()
    message(FATAL_ERROR "Could not find SDL CMake target.")
endif()

# Create engine library ONLY when you actually have engine sources
if (ENGINE_SOURCES)
    add_library(muharrik_engine STATIC ${ENGINE_SOURCES})
    target_include_directories(muharrik_engine PUBLIC
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/thirdparty/glm"
    )
    #target_link_libraries(muharrik_engine PUBLIC Vulkan::Vulkan)

    # Link engine into app
    target_link_libraries(app PRIVATE muharrik_engine)
endif()

# rpath for Vulkan loader (macOS)
# if(APPLE)
#   set_target_properties(app PROPERTIES
#     BUILD_RPATH "$ENV{VULKAN_SDK}/lib"
#   )
# endif()
