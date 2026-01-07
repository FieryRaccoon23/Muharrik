cmake_minimum_required(VERSION 3.20)
project(Muharrik LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/sdl EXCLUDE_FROM_ALL)

add_executable(app
    src/main.cpp
)

target_include_directories(app PRIVATE
    ${CMAKE_SOURCE_DIR}/thirdparty/glm
)

target_compile_definitions(app PRIVATE SDL_MAIN_HANDLED)

# Vulkan
target_link_libraries(app PRIVATE Vulkan::Vulkan)

# Similar to your Makefile rpath
if(APPLE)
  set_target_properties(app PROPERTIES
    BUILD_RPATH "$ENV{VULKAN_SDK}/lib"
  )
endif()

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
