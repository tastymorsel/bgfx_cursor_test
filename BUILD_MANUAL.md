# Manual Build Guide

## Visual Studio Build (Windows)

### Prerequisites
1. **Visual Studio 2019/2022** with C++ workload installed
2. **CMake** 3.10+ installed
3. **GLFW** installed (via vcpkg or pre-built binaries)

### Step-by-Step Build

#### 1. Open Developer Command Prompt
- Start Menu → Search for "Developer Command Prompt for VS 2022"
- Run as Administrator
- Navigate to your project directory

#### 2. Create Build Directory
```cmd
mkdir build-vs
cd build-vs
```

#### 3. Configure with CMake
```cmd
cmake -f "..\CMakeLists_VisualStudio.txt" -G "Visual Studio 17 2022" -A x64 ".."
```

**Note**: The `-f` flag must come BEFORE the generator specification.

#### 4. Build the Project
```cmd
cmake --build . --config Release
```

#### 5. Run the Game
```cmd
cd bin\Release
AsteroidsGame.exe
```

### Alternative: Debug Build
```cmd
cmake --build . --config Debug
```

### Alternative: Open in Visual Studio
After step 3, you can:
1. Open `AsteroidsGame.sln` in Visual Studio
2. Set `AsteroidsGame` as startup project
3. Press F5 to build and debug

## Common Issues & Solutions

### CMake Error: "Unknown argument -f"
- **Problem**: Wrong order of CMake flags
- **Solution**: Use `-f` before `-G` flag
- **Correct**: `cmake -f file.txt -G "Generator" ..`
- **Wrong**: `cmake -G "Generator" -f file.txt ..`

### CMake Error: "Could not find GLFW"
- **Solution 1**: Use vcpkg
  ```cmd
  vcpkg install glfw3:x64-windows
  ```
- **Solution 2**: Download pre-built binaries to `third_party/glfw/`

### Build Error: "cl.exe not found"
- **Solution**: Run from Visual Studio Developer Command Prompt
- **Alternative**: Add Visual Studio tools to PATH

### Path Issues
- **Problem**: Spaces or special characters in paths
- **Solution**: Use quotes around all paths
- **Example**: `"C:\Program Files\My Project"`

## Quick Commands Reference

```cmd
# Full build sequence
mkdir build-vs
cd build-vs
cmake -f "..\CMakeLists_VisualStudio.txt" -G "Visual Studio 17 2022" -A x64 ".."
cmake --build . --config Release

# Clean and rebuild
cmake --build . --target clean
cmake --build . --config Release

# Install dependencies (if using vcpkg)
vcpkg install glfw3:x64-windows
vcpkg integrate install
```

## Troubleshooting

If you encounter issues:

1. **Check Visual Studio**: Ensure C++ workload is installed
2. **Check CMake**: Run `cmake --version`
3. **Check GLFW**: Verify GLFW is accessible
4. **Use quotes**: Always quote paths with spaces
5. **Check order**: `-f` flag must come before `-G` flag
6. **Use PowerShell**: More robust than Command Prompt
7. **Run as Admin**: Some operations require administrator privileges