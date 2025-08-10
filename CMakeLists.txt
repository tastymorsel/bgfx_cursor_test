cmake_minimum_required(VERSION 3.16)
project(AsteroidsGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(OPENGL REQUIRED gl)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/bgfx/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/miniaudio)

# Source files
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/renderer.cpp
    src/audio.cpp
    src/entity.cpp
    src/player.cpp
    src/asteroid.cpp
    src/bullet.cpp
    src/particle_system.cpp
    src/shader_utils.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    bgfx
    miniaudio
    m
    dl
    pthread
)

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
    ${GLFW_CFLAGS_OTHER}
    ${OPENGL_CFLAGS_OTHER}
    -Wall -Wextra -O2
)

# Set working directory for runtime
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)