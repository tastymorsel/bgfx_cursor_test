#!/bin/bash

echo "Building Asteroids Game..."

# Check if we have the required tools
if ! command -v g++ &> /dev/null; then
    echo "Error: g++ compiler not found. Please install build tools."
    exit 1
fi

if ! command -v pkg-config &> /dev/null; then
    echo "Error: pkg-config not found. Please install pkg-config."
    exit 1
fi

# Check for required libraries
if ! pkg-config --exists glfw3; then
    echo "Error: GLFW3 not found. Please install libglfw3-dev"
    echo "On Ubuntu/Debian: sudo apt-get install libglfw3-dev"
    echo "On Arch: sudo pacman -S glfw-x11"
    echo "On Fedora: sudo dnf install glfw-devel"
    exit 1
fi

if ! pkg-config --exists gl; then
    echo "Error: OpenGL not found. Please install OpenGL development libraries"
    echo "On Ubuntu/Debian: sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev"
    echo "On Arch: sudo pacman -S mesa glu"
    echo "On Fedora: sudo dnf install mesa-libGL-devel mesa-libGLU-devel"
    exit 1
fi

echo "Dependencies found. Building..."

# Clean previous build
make clean

# Build the project
if make -j$(nproc); then
    echo "Build successful! Run './asteroids' to start the game."
else
    echo "Build failed. Please check the error messages above."
    exit 1
fi