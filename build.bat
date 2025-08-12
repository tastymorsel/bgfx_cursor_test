@echo off
echo Building Asteroids Game for Windows...

REM Check if we have the required tools
where g++ >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: g++ compiler not found.
    echo Please install MSYS2 and add mingw64/bin to your PATH
    echo See install-deps-windows in Makefile for instructions
    pause
    exit /b 1
)

REM Check for required libraries
pkg-config --exists glfw3 >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: GLFW3 not found.
    echo Please install mingw-w64-x86_64-glfw via MSYS2
    pause
    exit /b 1
)

echo Dependencies found. Building...

REM Clean previous build
make clean

REM Build the project
if make -j%NUMBER_OF_PROCESSORS% (
    echo Build successful! Run 'asteroids.exe' to start the game.
) else (
    echo Build failed. Please check the error messages above.
    pause
    exit /b 1
)

pause