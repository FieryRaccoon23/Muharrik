cmake_minimum_required(VERSION 3.20)

if(APPLE)
  project(Muharrik LANGUAGES C CXX OBJC OBJCXX)
else()
  project(Muharrik LANGUAGES C CXX)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/sdl EXCLUDE_FROM_ALL)
set(SDL3_DIR "${CMAKE_BINARY_DIR}/thirdparty/sdl" CACHE PATH "" FORCE)

set(SDL3IMAGE_SHARED OFF CACHE BOOL "" FORCE)
set(SDL3IMAGE_STATIC ON  CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/sdl_image EXCLUDE_FROM_ALL)

find_package(Threads REQUIRED)

# ----------------------------
# Tracy (profiler)
# ----------------------------
option(MUHARRIK_TRACY "Enable Tracy profiling" OFF)

if(MUHARRIK_TRACY)
    add_library(tracy_client STATIC
        "${CMAKE_SOURCE_DIR}/extern/tracy/public/TracyClient.cpp"
    )
    target_include_directories(tracy_client PUBLIC
        "${CMAKE_SOURCE_DIR}/extern/tracy/public"
    )

    target_compile_definitions(tracy_client PUBLIC
        TRACY_ENABLE
        TRACY_CALLSTACK=1
    )

    target_link_libraries(tracy_client PUBLIC Threads::Threads)
endif()

add_library(taskflow INTERFACE)
target_include_directories(taskflow INTERFACE
    "${CMAKE_SOURCE_DIR}/thirdparty/taskflow"
)
target_link_libraries(taskflow INTERFACE Threads::Threads)

# EABase is headers-only
add_library(eabase INTERFACE)
target_include_directories(eabase INTERFACE
    "${CMAKE_SOURCE_DIR}/thirdparty/eabase/include/Common"
)

# Build EASTL from sources (works even if EASTL's own CMake isn't used)
file(GLOB EASTL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/thirdparty/eastl/source/*.cpp"
)

add_library(eastl STATIC ${EASTL_SOURCES})
target_include_directories(eastl PUBLIC
    "${CMAKE_SOURCE_DIR}/thirdparty/eastl/include"
    "${CMAKE_SOURCE_DIR}/thirdparty/eabase/include/Common"
)
target_link_libraries(eastl PUBLIC eabase)

# Ensure EASTL debug/aligned new/delete overloads are linked whenever EASTL is linked
target_sources(eastl PRIVATE
    "${CMAKE_SOURCE_DIR}/src/Engine/ThirdParty/eastl_new_delete.cpp"
)

# ----------------------------
# llama.cpp (local LLM)
# ----------------------------
option(MUHARRIK_LLAMA "Enable llama.cpp integration" ON)

if(MUHARRIK_LLAMA)
    # Disable llama.cpp extras (faster builds; keeps only libraries)
    set(LLAMA_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(LLAMA_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(LLAMA_BUILD_SERVER OFF CACHE BOOL "" FORCE)

    # ---- Optional GPU backends (pick one if you want) ----
    # macOS Apple Silicon:
    # set(GGML_METAL ON CACHE BOOL "" FORCE)

    # Cross-platform GPU (needs Vulkan SDK):
    # set(GGML_VULKAN ON CACHE BOOL "" FORCE)

    # Add llama.cpp from submodule folder: thirdparty/llama
    add_subdirectory(thirdparty/llama EXCLUDE_FROM_ALL)
endif()

# ---- Collect engine sources ----
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/Engine/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Engine/*.c"
)

# ---- Collect game sources ----
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/Game/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Game/*.c"
)

# App
add_executable(app src/main.cpp)
target_compile_definitions(app PRIVATE SDL_MAIN_HANDLED)

# Copy runtime content next to the executable: build/bin/content/...
# This will include: src/content/game/... automatically
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:app>/content"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/src/content"
            "$<TARGET_FILE_DIR:app>/content"
)

# Create engine library ONLY when you actually have engine sources
if (ENGINE_SOURCES)
    add_library(muharrik_engine STATIC ${ENGINE_SOURCES})

    # IMPORTANT:
    # - src/Engine is the include root so you can do: #include "ECS/ecs.h"
    target_include_directories(muharrik_engine PUBLIC
        "${CMAKE_SOURCE_DIR}/src/Engine"
        "${CMAKE_SOURCE_DIR}/thirdparty/glm"
        "${CMAKE_SOURCE_DIR}/thirdparty/entt/src"
    )

    target_link_libraries(muharrik_engine PUBLIC
        SDL3::SDL3-static
        SDL3_image::SDL3_image-static
        taskflow
        eastl
        eabase
    )

    # ---- Link llama.cpp into engine (app inherits it via game->engine) ----
    if(MUHARRIK_LLAMA)
        # llama.cpp exposes C API headers in: thirdparty/llama/include/llama.h
        target_include_directories(muharrik_engine PUBLIC
            "${CMAKE_SOURCE_DIR}/thirdparty/llama/include"
        )

        # Most current llama.cpp builds export a target named "llama"
        # If your revision differs, run:
        #   cmake --build build --target help | grep -i llama
        target_link_libraries(muharrik_engine PUBLIC llama)
    endif()

    if (TARGET tracy_client)
        target_link_libraries(muharrik_engine PUBLIC tracy_client)
    endif()

    # NOTE:
    # Do NOT link engine directly into app here.
    # If app links muharrik_game and muharrik_game links muharrik_engine,
    # linking engine again causes: ld: warning: ignoring duplicate libraries: 'libmuharrik_engine.a'
endif()

# Create game library ONLY when you actually have game sources
if (GAME_SOURCES)
    add_library(muharrik_game STATIC ${GAME_SOURCES})

    # Include root for game so you can do: #include "Player/player.h"
    # (if file is src/Game/Player/player.h)
    target_include_directories(muharrik_game PUBLIC
        "${CMAKE_SOURCE_DIR}/src/Game"
    )

    # Game should see engine headers (and inherit engine deps) if engine exists
    if (TARGET muharrik_engine)
        target_link_libraries(muharrik_game PUBLIC muharrik_engine)
    else()
        # If you ever build game without engine, it still needs core deps
        target_link_libraries(muharrik_game PUBLIC
            SDL3::SDL3-static
            SDL3_image::SDL3_image-static
            taskflow
            eastl
            eabase
        )
        target_include_directories(muharrik_game PUBLIC
            "${CMAKE_SOURCE_DIR}/thirdparty/glm"
            "${CMAKE_SOURCE_DIR}/thirdparty/entt/src"
        )

        # If you build game without engine but still want llama:
        if(MUHARRIK_LLAMA)
            target_include_directories(muharrik_game PUBLIC
                "${CMAKE_SOURCE_DIR}/thirdparty/llama/include"
            )
            target_link_libraries(muharrik_game PUBLIC llama)
        endif()
    endif()

    if (TARGET tracy_client)
        target_link_libraries(muharrik_game PUBLIC tracy_client)
    endif()

    # Link game into app
    target_link_libraries(app PRIVATE muharrik_game)
else()
    # Optional fallback: if there's no game target, but engine exists, link engine into app.
    if (TARGET muharrik_engine)
        target_link_libraries(app PRIVATE muharrik_engine)
    endif()
endif()

# ----------------------------
# Sanitizers (target-based)
# ----------------------------
# option(MUHARRIK_SANITIZE "Enable sanitizers (address/undefined)" ON)
# option(MUHARRIK_UBSAN "Also enable UBSan" ON)

# function(muharrik_enable_sanitizers target_name)
#   if(MSVC)
#     message(WARNING "MUHARRIK_SANITIZE: Use clang-cl or Visual Studio AddressSanitizer support.")
#     return()
#   endif()

#   # These should apply only to your code targets
#   target_compile_options(${target_name} PRIVATE
#     -fno-omit-frame-pointer
#     -g
#     -fsanitize=address
#   )
#   target_link_options(${target_name} PRIVATE
#     -fsanitize=address
#   )

#   if(MUHARRIK_UBSAN)
#     target_compile_options(${target_name} PRIVATE -fsanitize=undefined)
#     target_link_options(${target_name} PRIVATE -fsanitize=undefined)
#   endif()
# endfunction()

# if(MUHARRIK_SANITIZE)
#   # Enable on whatever targets exist
#   if(TARGET muharrik_engine)
#     muharrik_enable_sanitizers(muharrik_engine)
#   endif()

#   if(TARGET muharrik_game)
#     muharrik_enable_sanitizers(muharrik_game)
#   endif()

#   if(TARGET app)
#     muharrik_enable_sanitizers(app)
#   endif()
# endif()

# For packaging
option(MUHARRIK_PACKAGE "Enable install + packaging rules" OFF)

if(MUHARRIK_PACKAGE)
  include("${CMAKE_SOURCE_DIR}/cmake/Packaging.cmake")
endif()
