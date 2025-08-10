CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -Iinclude -Ithird_party/bgfx/include -Ithird_party/miniaudio
LIBS = -lglfw -lGL -lGLU -ldl -lpthread -lm

# Source files
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Detect OS
ifeq ($(OS),Windows_NT)
    TARGET = asteroids.exe
    RM = del /Q
    CXXFLAGS += -DWIN32
    LIBS += -lopengl32 -lgdi32 -luser32 -lkernel32
else
    TARGET = asteroids
    RM = rm -f
    LIBS += -lGL -lGLU -ldl -lpthread -lm
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
	@echo "1. Install MSYS2 from https://www.msys2.org/"
	@echo "2. Open MSYS2 terminal and run:"
	@echo "   pacman -S mingw-w64-x86_64-toolchain"
	@echo "   pacman -S mingw-w64-x86_64-glfw"
	@echo "   pacman -S mingw-w64-x86_64-opengl-headers"
	@echo "3. Add MSYS2 mingw64/bin to your PATH"

.PHONY: all clean install-deps install-deps-arch install-deps-fedora install-deps-windows