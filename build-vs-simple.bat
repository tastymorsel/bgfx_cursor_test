@echo off
echo Building Asteroids Game with Visual Studio...
echo ===========================================

echo Checking Visual Studio compiler...
cl >nul 2>&1
if errorlevel 1 (
    echo Error: Visual Studio C++ compiler not found.
    echo Please run from Developer Command Prompt for VS 2022.
    pause
    exit /b 1
)

echo Checking CMake...
cmake --version >nul 2>&1
if errorlevel 1 (
    echo Error: CMake not found.
    echo Please install CMake from https://cmake.org/download/
    pause
    exit /b 1
)

REM Get CMake version for compatibility check
for /f "tokens=3" %%i in ('cmake --version 2^>nul ^| findstr /r "cmake version"') do set CMAKE_VERSION=%%i
echo Found CMake version: %CMAKE_VERSION%

echo Creating build directory...
if not exist build-vs mkdir build-vs
cd build-vs

REM Check if CMake supports -f flag (CMake 3.13+)
echo Checking CMake compatibility...
cmake -f "..\CMakeLists_VisualStudio.txt" -G "Visual Studio 17 2022" -A x64 ".." >nul 2>&1
if errorlevel 1 (
    echo Using compatibility mode for older CMake version...
    echo Copying CMakeLists file...
    copy "..\CMakeLists_VisualStudio.txt" "CMakeLists.txt" >nul
    echo Configuring with CMake...
    cmake -G "Visual Studio 17 2022" -A x64 ..
) else (
    echo Using modern CMake with -f flag...
    echo Configuring with CMake...
    cmake -f "..\CMakeLists_VisualStudio.txt" -G "Visual Studio 17 2022" -A x64 ..
)

if errorlevel 1 (
    echo CMake configuration failed.
    pause
    exit /b 1
)

echo Building project...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

echo Build successful!
echo Executable: build-vs\bin\Release\AsteroidsGame.exe

cd ..
pause