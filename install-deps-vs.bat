@echo off
echo Installing Visual Studio Dependencies for Asteroids Game
echo ======================================================
echo.

echo This script will help you install the required dependencies for Visual Studio builds.
echo.

echo Step 1: Install Visual Studio
echo -----------------------------
echo 1. Download Visual Studio 2022 Community (free) from:
echo    https://visualstudio.microsoft.com/downloads/
echo 2. Run the installer
echo 3. Select the following workloads:
echo    - Desktop development with C++
echo 4. In Individual Components, ensure these are selected:
echo    - MSVC v143 - VS 2022 C++ x64/x86 compiler
echo    - Windows 10/11 SDK
echo 5. Click Install and wait for completion
echo.
pause

echo.
echo Step 2: Install CMake
echo ---------------------
echo 1. Download CMake from https://cmake.org/download/
echo 2. Run the installer
echo 3. Choose "Add CMake to the system PATH for all users"
echo 4. Complete the installation
echo.
pause

echo.
echo Step 3: Install GLFW
echo --------------------
echo Choose one of these options:
echo.
echo Option A: Download pre-built binaries
echo 1. Go to https://www.glfw.org/download.html
echo 2. Download Windows pre-compiled binaries
echo 3. Extract to: third_party\glfw\
echo 4. Ensure the structure is: third_party\glfw\include\GLFW\glfw3.h
echo.
echo Option B: Use vcpkg (recommended)
echo 1. Open Visual Studio Developer Command Prompt as Administrator
echo 2. Run: git clone https://github.com/Microsoft/vcpkg.git
echo 3. Run: cd vcpkg
echo 4. Run: .\bootstrap-vcpkg.bat
echo 5. Run: .\vcpkg install glfw3:x64-windows
echo 6. Run: .\vcpkg integrate install
echo.
pause

echo.
echo Step 4: Verify Installation
echo ---------------------------
echo 1. Open "Developer Command Prompt for VS 2022" from Start Menu
echo 2. Navigate to this project directory
echo 3. Run: cl
echo 4. Run: cmake --version
echo.
echo If both commands work, you're ready to build!
echo.
echo You can now run: build-vs.bat
echo.
pause