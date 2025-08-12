# Using Real bgfx Library on Windows

This project now supports using the real bgfx graphics library on Windows instead of the stub implementation. This will give you actual graphics rendering instead of a white screen.

## Prerequisites

1. **Visual Studio 2019/2022** with C++ development tools
2. **Windows SDK** (usually comes with Visual Studio)
3. **vcpkg** package manager

## Installation Steps

### 1. Install vcpkg

If you don't have vcpkg installed:

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```

### 2. Install bgfx

Run the provided script:
```bash
install-bgfx-windows.bat
```

Or manually:
```bash
vcpkg install bgfx:x64-windows
```

### 3. Set Environment Variable

Set the `VCPKG_ROOT` environment variable to point to your vcpkg installation:

```bash
set VCPKG_ROOT=C:\path\to\vcpkg
```

## Building with Real bgfx

### Option 1: Use the Legacy Build Script

```bash
build-vs-legacy.bat
```

### Option 2: Manual CMake

```bash
cmake -G "Visual Studio 17 2022" -A x64 -B build-vs -S .
cmake --build build-vs --config Release
```

## How It Works

The build system automatically detects whether the real bgfx library is available:

- **If found**: Uses the real bgfx library, links against it, and excludes stub sources
- **If not found**: Falls back to the stub implementation (white screen, but functional game logic)

## Verification

When building, you should see messages like:

```
Found real bgfx library: C:/vcpkg/installed/x64-windows/lib/bgfx.lib
Found bgfx include: C:/vcpkg/installed/x64-windows/include
Using real bgfx library - no stub sources needed
Linked with real bgfx library: C:/vcpkg/installed/x64-windows/lib/bgfx.lib
```

## Troubleshooting

### "bgfx not found" Error

1. Make sure vcpkg is installed and `VCPKG_ROOT` is set correctly
2. Verify bgfx was installed: `vcpkg list | findstr bgfx`
3. Check that the build is looking in the right directories

### Linker Errors

1. Ensure you're building for x64 (not x86)
2. Make sure Visual Studio has the C++ development tools installed
3. Verify the bgfx library file exists in the expected location

### Runtime Errors

1. If using dynamic linking, ensure `bgfx.dll` is in the same directory as the executable
2. Check that all required Visual C++ redistributables are installed

## Benefits of Real bgfx

- **Actual graphics rendering** instead of white screen
- **Hardware acceleration** via DirectX/OpenGL
- **Proper shader compilation** and execution
- **Real-time rendering** with proper frame timing
- **Professional graphics quality**

## Fallback Behavior

If the real bgfx library cannot be found, the build system automatically falls back to the stub implementation. This ensures the project always builds, even if bgfx is not available.

## Next Steps

Once you have real bgfx working:

1. The psychedelic background should render properly
2. Game sprites should be visible
3. You can enhance the graphics with real shaders
4. Performance should be much better than the stub