@echo off
echo Building Asteroids Game with Visual Studio (Legacy CMake)...
echo ========================================================

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

echo Creating build directory...
if not exist build-vs mkdir build-vs
cd build-vs

echo Backing up original CMakeLists.txt and replacing with Windows version...
cd ..
if exist "CMakeLists.txt" (
    echo Backing up original CMakeLists.txt...
    copy "CMakeLists.txt" "CMakeLists.txt.backup" >nul
)
copy "CMakeLists_Windows_NoPkgConfig.txt" "CMakeLists.txt" >nul
if errorlevel 1 (
    echo Error: Failed to copy CMakeLists file.
    pause
    exit /b 1
)

echo CMakeLists file replaced successfully.
echo.

echo Configuring with CMake...
cmake -G "Visual Studio 17 2022" -A x64 -B build-vs -S .
if errorlevel 1 (
    echo CMake configuration failed.
    echo Restoring original CMakeLists.txt...
    if exist "CMakeLists.txt.backup" (
        copy "CMakeLists.txt.backup" "CMakeLists.txt" >nul
    )
    pause
    exit /b 1
)

echo Building project...
cmake --build build-vs --config Release
if errorlevel 1 (
    echo Build failed.
    echo Restoring original CMakeLists.txt...
    if exist "CMakeLists.txt.backup" (
        copy "CMakeLists.txt.backup" "CMakeLists.txt" >nul
    )
    pause
    exit /b 1
)

echo Build successful!
echo Executable: build-vs\bin\Release\AsteroidsGame.exe

echo Restoring original CMakeLists.txt...
if exist "CMakeLists.txt.backup" (
    copy "CMakeLists.txt.backup" "CMakeLists.txt" >nul
    del "CMakeLists.txt.backup"
)

pause