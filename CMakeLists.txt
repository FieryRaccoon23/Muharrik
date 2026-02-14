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
# RmlUi + FreeType (required by default font engine)
# ----------------------------
option(MUHARRIK_RMLUI "Enable RmlUi integration" ON)

if(MUHARRIK_RMLUI)
    # ---- FreeType (dependency of RmlUi default font engine) ----
    # Build FreeType from submodule: thirdparty/freetype
    # RmlUi expects a target named Freetype::Freetype.
    # The FreeType submodule often exports a target called 'freetype', so we create an ALIAS if needed.

    # Prefer static build to match your project
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

    add_subdirectory(thirdparty/freetype EXCLUDE_FROM_ALL)

    # Create the expected target name if the submodule only defines 'freetype'
    if(TARGET freetype AND NOT TARGET Freetype::Freetype)
        add_library(Freetype::Freetype ALIAS freetype)
    endif()

    # ---- RmlUi ----
    set(RMLUI_SAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

    add_subdirectory(thirdparty/rmlui EXCLUDE_FROM_ALL)
endif()

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

    # ---- Link RmlUi into engine (robust target selection) ----
    if(MUHARRIK_RMLUI)
        if(TARGET RmlUi::RmlUi)
            target_link_libraries(muharrik_engine PUBLIC RmlUi::RmlUi)
        elseif(TARGET RmlUi::Core)
            target_link_libraries(muharrik_engine PUBLIC RmlUi::Core)
        elseif(TARGET RmlUiCore)
            target_link_libraries(muharrik_engine PUBLIC RmlUiCore)
        else()
            message(FATAL_ERROR "RmlUi targets not found. Expected RmlUi::RmlUi or RmlUi::Core (or RmlUiCore).")
        endif()
    endif()

    # ---- Link llama.cpp into engine (app inherits it via game->engine) ----
    if(MUHARRIK_LLAMA)
        target_include_directories(muharrik_engine PUBLIC
            "${CMAKE_SOURCE_DIR}/thirdparty/llama/include"
        )
        target_link_libraries(muharrik_engine PUBLIC llama)
    endif()

    if (TARGET tracy_client)
        target_link_libraries(muharrik_engine PUBLIC tracy_client)
    endif()
endif()

# Create game library ONLY when you actually have game sources
if (GAME_SOURCES)
    add_library(muharrik_game STATIC ${GAME_SOURCES})

    target_include_directories(muharrik_game PUBLIC
        "${CMAKE_SOURCE_DIR}/src/Game"
    )

    if (TARGET muharrik_engine)
        target_link_libraries(muharrik_game PUBLIC muharrik_engine)
    else()
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

        if(MUHARRIK_LLAMA)
            target_include_directories(muharrik_game PUBLIC
                "${CMAKE_SOURCE_DIR}/thirdparty/llama/include"
            )
            target_link_libraries(muharrik_game PUBLIC llama)
        endif()

        # ---- Link RmlUi into game fallback (robust target selection) ----
        if(MUHARRIK_RMLUI)
            if(TARGET RmlUi::RmlUi)
                target_link_libraries(muharrik_game PUBLIC RmlUi::RmlUi)
            elseif(TARGET RmlUi::Core)
                target_link_libraries(muharrik_game PUBLIC RmlUi::Core)
            elseif(TARGET RmlUiCore)
                target_link_libraries(muharrik_game PUBLIC RmlUiCore)
            else()
                message(FATAL_ERROR "RmlUi targets not found. Expected RmlUi::RmlUi or RmlUi::Core (or RmlUiCore).")
            endif()
        endif()
    endif()

    if (TARGET tracy_client)
        target_link_libraries(muharrik_game PUBLIC tracy_client)
    endif()

    target_link_libraries(app PRIVATE muharrik_game)
else()
    if (TARGET muharrik_engine)
        target_link_libraries(app PRIVATE muharrik_engine)
    endif()
endif()

# For packaging
option(MUHARRIK_PACKAGE "Enable install + packaging rules" OFF)

if(MUHARRIK_PACKAGE)
  include("${CMAKE_SOURCE_DIR}/cmake/Packaging.cmake")
endif()
