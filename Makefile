CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -Iinclude -Ithird_party/bgfx/include -Ithird_party/miniaudio
LIBS = -lglfw -lGL -lGLU -ldl -lpthread -lm

# Source files
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Target executable
TARGET = asteroids

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
	rm -f $(OBJECTS) $(TARGET)

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

.PHONY: all clean install-deps install-deps-arch install-deps-fedora