@echo off
setlocal enabledelayedexpansion

echo Building Asteroids Game with Visual Studio...
echo ===========================================

REM Check if we're in a Visual Studio Developer Command Prompt
cl >nul 2>&1
if errorlevel 1 (
    echo Error: Visual Studio C++ compiler (cl.exe) not found.
    echo.
    echo Please run this script from a Visual Studio Developer Command Prompt:
    echo 1. Open Start Menu
    echo 2. Search for "Developer Command Prompt for VS 2022" (or 2019)
    echo 3. Run as Administrator
    echo 4. Navigate to this directory and run build-vs.bat
    echo.
    echo Or install Visual Studio 2019/2022 Community (free) with C++ workload.
    echo.
    pause
    exit /b 1
)

echo Found Visual Studio C++ compiler.
echo.

REM Check for CMake
cmake --version >nul 2>&1
if errorlevel 1 (
    echo Error: CMake not found.
    echo Please install CMake from https://cmake.org/download/
    pause
    exit /b 1
)

echo Found CMake.
echo.

REM Create build directory
if not exist "build-vs" (
    mkdir "build-vs"
)
cd "build-vs"

REM Configure with CMake
echo Configuring project with CMake...
cmake -G "Visual Studio 17 2022" -A x64 -f "..\CMakeLists_VisualStudio.txt" ".."
if errorlevel 1 (
    echo CMake configuration failed.
    pause
    exit /b 1
)

REM Build the project
echo.
echo Building project...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

echo.
echo Build successful! 
echo Executable is located at: build-vs\bin\Release\AsteroidsGame.exe
echo.
echo You can also open AsteroidsGame.sln in Visual Studio to build and debug.
echo.

cd ".."
pause