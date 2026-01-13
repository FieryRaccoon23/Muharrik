cmake_minimum_required(VERSION 3.20)
project(Muharrik LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/sdl EXCLUDE_FROM_ALL)
set(SDL3_DIR "${CMAKE_BINARY_DIR}/thirdparty/sdl" CACHE PATH "" FORCE)

set(SDL3IMAGE_SHARED OFF CACHE BOOL "" FORCE)
set(SDL3IMAGE_STATIC ON  CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/sdl_image EXCLUDE_FROM_ALL)

# ---- Collect engine sources (optional for now) ----
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/engine/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/engine/*.c"
)

# App
add_executable(app src/main.cpp)
target_compile_definitions(app PRIVATE SDL_MAIN_HANDLED)

# Copy runtime content next to the executable: build/bin/content/...
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:app>/content"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/src/content"
            "$<TARGET_FILE_DIR:app>/content"
)


# Create engine library ONLY when you actually have engine sources
if (ENGINE_SOURCES)
    add_library(muharrik_engine STATIC ${ENGINE_SOURCES})
    target_include_directories(muharrik_engine PUBLIC
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/thirdparty/glm"
        "${CMAKE_SOURCE_DIR}/thirdparty/entt/src"
    )

    target_link_libraries(muharrik_engine PUBLIC 
        SDL3::SDL3-static
        SDL3_image::SDL3_image-static
    )

    # Link engine into app
    target_link_libraries(app PRIVATE muharrik_engine)
endif()

