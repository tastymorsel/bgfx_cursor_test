@echo off
echo Testing CMake Functionality
echo ===========================
echo.

echo 1. CMake version:
cmake --version
echo.

echo 2. CMake location:
where cmake
echo.

echo 3. Testing basic cmake command:
cmake --help | findstr /i "usage"
echo.

echo 4. Testing cmake -f flag:
cmake -f CMakeLists.txt --help >nul 2>&1
if errorlevel 1 (
    echo ERROR: cmake -f flag not working
    echo.
    echo 5. Testing alternative approach:
    echo Copying CMakeLists file...
    copy "CMakeLists_VisualStudio.txt" "CMakeLists.txt" >nul 2>&1
    echo Testing cmake without -f flag...
    cmake --help | findstr /i "usage"
) else (
    echo SUCCESS: cmake -f flag working
)

echo.
echo 6. Testing Visual Studio generator:
cmake -G "Visual Studio 17 2022" --help >nul 2>&1
if errorlevel 1 (
    echo ERROR: Visual Studio generator not working
) else (
    echo SUCCESS: Visual Studio generator working
)

echo.
echo Test complete.
pause