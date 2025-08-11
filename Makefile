CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -Iinclude -Ithird_party/bgfx/include -Ithird_party/miniaudio -Ithird_party/glm
LIBS = -lglfw -lGL -ldl -lpthread -lm

# Source files
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
SOURCES += third_party/bgfx/src/bgfx.cpp
SOURCES += third_party/miniaudio/miniaudio.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Detect OS
ifeq ($(OS),Windows_NT)
    TARGET = asteroids.exe
    RM = del /Q
    CXXFLAGS += -DWIN32
    # Visual Studio toolchain
    ifeq ($(MSVC),1)
        CXX = cl
        CXXFLAGS = /std:c++17 /W4 /EHsc
        LIBS = glfw3.lib opengl32.lib gdi32.lib user32.lib kernel32.lib
    else
        # Fallback to MinGW if MSVC not specified
        LIBS += -lopengl32 -lgdi32 -luser32 -lkernel32
    endif
else
    TARGET = asteroids
    RM = rm -f
    LIBS += -ldl -lpthread -lm
endif

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	$(RM) $(OBJECTS) $(TARGET)

# Install dependencies (Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install -y build-essential cmake libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev

# Install dependencies (Arch Linux)
install-deps-arch:
	sudo pacman -S base-devel cmake glfw-x11 mesa glu

# Install dependencies (Fedora)
install-deps-fedora:
	sudo dnf install gcc-c++ cmake glfw-devel mesa-libGL-devel mesa-libGLU-devel

# Install dependencies (Windows)
install-deps-windows:
	@echo "Installing dependencies on Windows..."
	@echo "1. Install Visual Studio 2019/2022 Community (free)"
	@echo "2. In Visual Studio Installer, select:"
	@echo "   - Workloads > Desktop development with C++"
	@echo "   - Individual components > MSVC v143/v142 compiler"
	@echo "3. Download GLFW pre-built binaries from:"
	@echo "   https://www.glfw.org/download.html"
	@echo "4. Extract to third_party/glfw/"
	@echo "5. Or use vcpkg: vcpkg install glfw3:x64-windows"

.PHONY: all clean install-deps install-deps-arch install-deps-fedora install-deps-windows