# Asteroids Game

A modern C++ implementation of the classic Asteroids arcade game with psychedelic graphics and procedural audio.

## Features

### Graphics
- **bgfx Rendering**: High-performance cross-platform graphics API
- **Procedural Background**: Dynamic psychedelic space effects using fragment shaders
- **Pixel-Perfect Graphics**: Lit sprites with custom fragment shaders
- **Resolution**: 1024x512 (approximately 512 lines as requested)

### Audio
- **miniaudio Integration**: Cross-platform audio library
- **Procedural Sound Effects**: Musically-based tones for all game events
- **Dynamic Audio**: Shoot, explosion, hit, and player death sounds
- **Background Music**: Procedurally generated space ambiance

### Gameplay
- **Classic Asteroids Mechanics**: Break large rocks into smaller pieces
- **Three-Tier Destruction**: Large → Medium → Small → Explosion
- **Mouse Control**: Ship rotation follows mouse movement
- **Left-Click Shooting**: Fire bullets with left mouse button
- **Wave-Based Spawning**: Rocks spawn in progressive waves
- **Scoring System**: Points for each asteroid destroyed

### Controls
- **Mouse Movement**: Rotate ship towards cursor
- **Left Mouse Button**: Fire bullets
- **Escape**: Close game
- **R**: Reset game

## Technical Architecture

### Core Classes
- **Game**: Main game loop and state management
- **Renderer**: bgfx-based rendering system
- **Audio**: miniaudio sound management
- **Entity**: Base class for all game objects
- **Player**: Player ship with mouse control
- **Asteroid**: Destructible rocks with size variants
- **Bullet**: Projectile system
- **ParticleSystem**: Visual effects

### Dependencies
- **bgfx**: Cross-platform graphics API
- **miniaudio**: Audio library
- **GLFW**: Window management and input
- **GLM**: Mathematics library
- **OpenGL**: Graphics driver

## Building

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+)
- CMake 3.10+
- OpenGL development libraries
- GLFW3 development libraries

### Quick Build

#### Linux/macOS
```bash
# Make the build script executable
chmod +x build.sh

# Run the build script
./build.sh
```

#### Windows
```cmd
# Using Visual Studio (Recommended)
build-vs.bat

# Using PowerShell with Visual Studio
.\build-vs.ps1

# Using Command Prompt with MinGW (Alternative)
build.bat

# Using PowerShell with MinGW (Alternative)
.\build.ps1

# Using MSYS2/MinGW directly
make
```

### Manual Build
```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install build-essential cmake libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev

# Install dependencies (Arch Linux)
sudo pacman -S base-devel cmake glfw-x11 mesa glu

# Install dependencies (Fedora)
sudo dnf install gcc-c++ cmake glfw-devel mesa-libGL-devel mesa-libGLU-devel

# Install dependencies (Windows)
# Option A: Visual Studio (Recommended)
# 1. Install Visual Studio 2022 Community (free) with C++ workload
# 2. Install CMake from https://cmake.org/download/
# 3. Install GLFW via vcpkg or download pre-built binaries
#    Run: install-deps-vs.bat for detailed instructions

# Option B: MSYS2/MinGW (Alternative)
# 1. Install MSYS2 from https://www.msys2.org/
# 2. Open MSYS2 terminal and run:
#    pacman -S mingw-w64-x86_64-toolchain
#    pacman -S mingw-w64-x86_64-glfw
#    pacman -S mingw-w64-x86_64-opengl-headers
# 3. Add MSYS2 mingw64/bin to your PATH

# Build the project
make clean
make -j$(nproc)
```

### Running

#### Linux/macOS
```bash
./asteroids
```

#### Windows
```cmd
asteroids.exe
```

## Project Structure

```
.
├── include/                 # Header files
│   ├── game.hpp            # Main game class
│   ├── renderer.hpp        # bgfx rendering system
│   ├── audio.hpp           # miniaudio sound system
│   ├── entity.hpp          # Base entity class
│   ├── player.hpp          # Player ship
│   ├── asteroid.hpp        # Asteroid objects
│   ├── bullet.hpp          # Bullet projectiles
│   ├── particle_system.hpp # Visual effects
│   └── shader_utils.hpp    # Shader management
├── src/                    # Source files
│   ├── main.cpp            # Application entry point
│   ├── game.cpp            # Game logic implementation
│   ├── renderer.cpp        # Rendering implementation
│   ├── audio.cpp           # Audio implementation
│   ├── entity.cpp          # Entity base implementation
│   ├── player.cpp          # Player implementation
│   ├── asteroid.cpp        # Asteroid implementation
│   ├── bullet.cpp          # Bullet implementation
│   ├── particle_system.cpp # Particle system implementation
│   └── shader_utils.cpp    # Shader utilities implementation
├── assets/                 # Game assets
│   └── shaders/            # GLSL shaders
│       ├── background.vert # Background vertex shader
│       ├── background.frag # Psychedelic background fragment shader
│       ├── sprite.vert     # Sprite vertex shader
│       └── sprite.frag     # Lit sprite fragment shader
├── third_party/            # Third-party libraries
│   ├── bgfx/               # bgfx headers
│   └── miniaudio/          # miniaudio headers
├── CMakeLists.txt          # CMake build configuration
├── CMakeLists_Windows.txt  # Windows-specific CMake configuration
├── CMakeLists_VisualStudio.txt # Visual Studio CMake configuration
├── Makefile                # Make-based build system
├── build.sh                # Linux/macOS build script
├── build.bat               # Windows MinGW build script
├── build.ps1               # Windows MinGW PowerShell build script
├── build-vs.bat            # Windows Visual Studio build script
├── build-vs.ps1            # Windows Visual Studio PowerShell build script
├── install-deps-windows.bat # Windows MinGW dependency installer
├── install-deps-vs.bat     # Windows Visual Studio dependency installer
└── README.md               # This file
```

## Shader Features

### Background Shader
- **Procedural Noise**: Multiple layers of fractal noise
- **Psychedelic Colors**: Dynamic color mixing and animation
- **Star Field**: Procedurally generated stars
- **Nebula Effects**: Swirling space gas patterns
- **Time-Based Animation**: Continuously evolving visuals

### Sprite Shader
- **Per-Pixel Lighting**: Distance-based attenuation
- **Glow Effects**: Screen-space glow calculations
- **Rim Lighting**: Edge highlighting for depth
- **Pulsing Animation**: Subtle breathing effects

## Audio Features

### Procedural Generation
- **Sine Wave Synthesis**: Pure tone generation
- **Harmonic Content**: Rich, musical sound design
- **ADSR Envelopes**: Attack, decay, sustain, release
- **Noise Generation**: Explosion and impact sounds
- **Tone Variations**: Different musical notes for events

### Sound Events
- **Shoot**: High-pitched laser sound
- **Hit**: Musical impact tone
- **Explosion**: Low-frequency explosion with harmonics
- **Player Death**: Extended explosion sequence

## Development Notes

### Performance Considerations
- **Delta Time Capping**: Prevents physics issues during frame drops
- **Efficient Collision**: Circle-based collision detection
- **Particle Management**: Automatic cleanup of expired particles
- **Memory Management**: Smart pointers for automatic cleanup

### Cross-Platform Support
- **bgfx**: Multiple graphics APIs (OpenGL, Vulkan, DirectX)
- **miniaudio**: Windows, macOS, Linux audio support
- **GLFW**: Cross-platform window management
- **Modern C++**: Standard library features for portability

## Troubleshooting

### Windows Build Issues

#### Visual Studio Build Issues
1. **"cl.exe not found" error:**
   - Install Visual Studio 2019/2022 Community with C++ workload
   - Run from "Developer Command Prompt for VS 2022"
   - Or run `install-deps-vs.bat` for detailed instructions

2. **"CMake not found" error:**
   - Install CMake from https://cmake.org/download/
   - Choose "Add CMake to system PATH for all users"

3. **"GLFW not found" error:**
   - Use vcpkg: `vcpkg install glfw3:x64-windows`
   - Or download pre-built binaries to `third_party/glfw/`
   - Run `install-deps-vs.bat` for detailed instructions

4. **Build fails with linking errors:**
   - Use `build-vs.bat` or `build-vs.ps1`
   - Ensure you're using the Visual Studio toolchain, not MinGW

#### MinGW Build Issues (Alternative)
1. **"g++ not found" error:**
   - Install MSYS2 from https://www.msys2.org/
   - Add `C:\msys64\mingw64\bin` to your PATH environment variable
   - Restart your terminal/IDE

2. **"GLFW3 not found" error:**
   - In MSYS2 terminal: `pacman -S mingw-w64-x86_64-glfw`
   - Ensure MSYS2 mingw64/bin is in your PATH

3. **"OpenGL not found" error:**
   - In MSYS2 terminal: `pacman -S mingw-w64-x86_64-opengl-headers`
   - Windows includes OpenGL drivers by default

4. **Build fails with linking errors:**
   - Use the Windows-specific CMakeLists.txt: `cmake -f CMakeLists_Windows.txt`
   - Ensure you're using MinGW-w64, not MSVC

### Linux Build Issues

1. **Missing GLFW3:**
   ```bash
   sudo apt-get install libglfw3-dev  # Ubuntu/Debian
   sudo pacman -S glfw-x11           # Arch
   sudo dnf install glfw-devel       # Fedora
   ```

2. **Missing OpenGL:**
   ```bash
   sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev  # Ubuntu/Debian
   sudo pacman -S mesa glu                                # Arch
   sudo dnf install mesa-libGL-devel mesa-libGLU-devel    # Fedora
   ```

## Future Enhancements

- [ ] Power-ups and special weapons
- [ ] Multiple player ships
- [ ] High score persistence
- [ ] Sound effect customization
- [ ] Additional visual effects
- [ ] Multiplayer support
- [ ] Level progression system

## License

This project is open source. Feel free to modify and distribute according to your needs.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.