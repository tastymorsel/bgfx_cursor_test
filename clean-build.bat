@echo off
echo Cleaning Build Directory
echo ========================
echo.

echo This script will clean the build directory and remove CMake cache files.
echo.

if exist "build-vs" (
    echo Removing build-vs directory...
    rmdir /s /q "build-vs"
    echo Build directory removed.
) else (
    echo Build directory does not exist.
)

if exist "CMakeCache.txt" (
    echo Removing CMakeCache.txt...
    del "CMakeCache.txt"
    echo CMake cache removed.
)

if exist "CMakeFiles" (
    echo Removing CMakeFiles directory...
    rmdir /s /q "CMakeFiles"
    echo CMake files removed.
)

echo.
echo Cleanup complete!
echo You can now run: build-vs-legacy.bat
echo.
pause