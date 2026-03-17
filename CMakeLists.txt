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
# RmlUi + FreeType
# ----------------------------
option(MUHARRIK_RMLUI "Enable RmlUi integration" ON)

if(MUHARRIK_RMLUI)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    add_subdirectory(thirdparty/freetype EXCLUDE_FROM_ALL)

    if(TARGET freetype AND NOT TARGET Freetype::Freetype)
        add_library(Freetype::Freetype ALIAS freetype)
    endif()

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

# ----------------------------
# Taskflow
# ----------------------------
add_library(taskflow INTERFACE)
target_include_directories(taskflow INTERFACE
    "${CMAKE_SOURCE_DIR}/thirdparty/taskflow"
)
target_link_libraries(taskflow INTERFACE Threads::Threads)

# ----------------------------
# EABase + EASTL
# ----------------------------
add_library(eabase INTERFACE)
target_include_directories(eabase INTERFACE
    "${CMAKE_SOURCE_DIR}/thirdparty/eabase/include/Common"
)

file(GLOB EASTL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/thirdparty/eastl/source/*.cpp"
)
add_library(eastl STATIC ${EASTL_SOURCES})
target_include_directories(eastl PUBLIC
    "${CMAKE_SOURCE_DIR}/thirdparty/eastl/include"
    "${CMAKE_SOURCE_DIR}/thirdparty/eabase/include/Common"
)
target_link_libraries(eastl PUBLIC eabase)
target_sources(eastl PRIVATE
    "${CMAKE_SOURCE_DIR}/src/Engine/ThirdParty/eastl_new_delete.cpp"
)

# ----------------------------
# llama.cpp (local LLM)
# ----------------------------
option(MUHARRIK_LLAMA "Enable llama.cpp integration" ON)

if(MUHARRIK_LLAMA)
    set(LLAMA_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
    set(LLAMA_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(LLAMA_BUILD_SERVER   OFF CACHE BOOL "" FORCE)
    add_subdirectory(thirdparty/llama EXCLUDE_FROM_ALL)
endif()

# ----------------------------
# MuJoCo (physics engine)
# ----------------------------
option(MUHARRIK_MUJOCO "Enable MuJoCo physics" ON)

if(MUHARRIK_MUJOCO)
    # Turn off everything we don't need
    set(MUJOCO_BUILD_EXAMPLES  OFF CACHE BOOL "" FORCE)
    set(MUJOCO_BUILD_TESTS     OFF CACHE BOOL "" FORCE)
    set(MUJOCO_BUILD_SIMULATE  OFF CACHE BOOL "" FORCE)
    set(MUJOCO_PYTHON_BINDINGS OFF CACHE BOOL "" FORCE)
    set(MUJOCO_SAMPLES         OFF CACHE BOOL "" FORCE)

    # MuJoCo uses FetchContent internally for some deps.
    # This tells it to look locally first before going online.
    set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "" FORCE)

    add_subdirectory(thirdparty/mujoco EXCLUDE_FROM_ALL)
endif()

# ----------------------------
# Engine sources
# ----------------------------
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/Engine/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Engine/*.c"
)

# ----------------------------
# Game sources
# ----------------------------
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/Game/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Game/*.c"
)

# ----------------------------
# App executable
# ----------------------------
add_executable(app src/main.cpp)
target_compile_definitions(app PRIVATE SDL_MAIN_HANDLED)

add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:app>/content"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/src/content"
            "$<TARGET_FILE_DIR:app>/content"
)

# ----------------------------
# Engine library
# ----------------------------
if(ENGINE_SOURCES)
    add_library(muharrik_engine STATIC ${ENGINE_SOURCES})

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

    # ---- RmlUi ----
    if(MUHARRIK_RMLUI)
        target_sources(muharrik_engine PRIVATE
            "${CMAKE_SOURCE_DIR}/src/Engine/ThirdParty/rmlui/Backends/RmlUi_Renderer_SDL.cpp"
            "${CMAKE_SOURCE_DIR}/src/Engine/ThirdParty/rmlui/Backends/RmlUi_Platform_SDL.cpp"
        )
        target_compile_definitions(muharrik_engine PUBLIC
            RMLUI_SDL_VERSION_MAJOR=3
        )
        target_include_directories(muharrik_engine PUBLIC
            "${CMAKE_SOURCE_DIR}/src/Engine/ThirdParty/rmlui"
        )
        if(TARGET RmlUi::RmlUi)
            target_link_libraries(muharrik_engine PUBLIC RmlUi::RmlUi)
        elseif(TARGET RmlUi::Core)
            target_link_libraries(muharrik_engine PUBLIC RmlUi::Core)
        elseif(TARGET RmlUiCore)
            target_link_libraries(muharrik_engine PUBLIC RmlUiCore)
        else()
            message(FATAL_ERROR "RmlUi target not found.")
        endif()
    endif()

    # ---- llama.cpp ----
    if(MUHARRIK_LLAMA)
        target_include_directories(muharrik_engine PUBLIC
            "${CMAKE_SOURCE_DIR}/thirdparty/llama/include"
        )
        target_link_libraries(muharrik_engine PUBLIC llama)
    endif()

    # ---- MuJoCo ----
    if(MUHARRIK_MUJOCO)
        target_link_libraries(muharrik_engine PUBLIC mujoco)

        # MuJoCo headers are exposed through its own target
        # but add include explicitly for IDE support
        target_include_directories(muharrik_engine PUBLIC
            "${CMAKE_SOURCE_DIR}/thirdparty/mujoco/include"
        )

        target_compile_definitions(muharrik_engine PUBLIC
            MUHARRIK_PHYSICS_MUJOCO
        )
    endif()

    # ---- Tracy ----
    if(TARGET tracy_client)
        target_link_libraries(muharrik_engine PUBLIC tracy_client)
    endif()
endif()

# ----------------------------
# Game library
# ----------------------------
if(GAME_SOURCES)
    add_library(muharrik_game STATIC ${GAME_SOURCES})

    target_include_directories(muharrik_game PUBLIC
        "${CMAKE_SOURCE_DIR}/src/Game"
    )

    if(TARGET muharrik_engine)
        target_link_libraries(muharrik_game PUBLIC muharrik_engine)
    else()
        # Fallback — no engine lib yet, link everything directly
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

        if(MUHARRIK_RMLUI)
            if(TARGET RmlUi::RmlUi)
                target_link_libraries(muharrik_game PUBLIC RmlUi::RmlUi)
            elseif(TARGET RmlUi::Core)
                target_link_libraries(muharrik_game PUBLIC RmlUi::Core)
            elseif(TARGET RmlUiCore)
                target_link_libraries(muharrik_game PUBLIC RmlUiCore)
            else()
                message(FATAL_ERROR "RmlUi target not found.")
            endif()
        endif()

        # MuJoCo fallback — game links directly if no engine lib
        if(MUHARRIK_MUJOCO)
            target_link_libraries(muharrik_game PUBLIC mujoco)
            target_include_directories(muharrik_game PUBLIC
                "${CMAKE_SOURCE_DIR}/thirdparty/mujoco/include"
            )
            target_compile_definitions(muharrik_game PUBLIC
                MUHARRIK_PHYSICS_MUJOCO
            )
        endif()
    endif()

    if(TARGET tracy_client)
        target_link_libraries(muharrik_game PUBLIC tracy_client)
    endif()

    target_link_libraries(app PRIVATE muharrik_game)
else()
    if(TARGET muharrik_engine)
        target_link_libraries(app PRIVATE muharrik_engine)
    endif()
endif()

# ----------------------------
# Packaging
# ----------------------------
option(MUHARRIK_PACKAGE "Enable install + packaging rules" OFF)

if(MUHARRIK_PACKAGE)
    include("${CMAKE_SOURCE_DIR}/cmake/Packaging.cmake")
endif()