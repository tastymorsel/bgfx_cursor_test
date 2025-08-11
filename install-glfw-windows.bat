@echo off
echo Installing GLFW for Windows
echo ===========================
echo.

echo This script will help you install GLFW for Windows builds.
echo.

echo Option 1: Install via vcpkg (Recommended)
echo -----------------------------------------
echo 1. Open Visual Studio Developer Command Prompt as Administrator
echo 2. Run these commands:
echo    git clone https://github.com/Microsoft/vcpkg.git
echo    cd vcpkg
echo    .\bootstrap-vcpkg.bat
echo    .\vcpkg install glfw3:x64-windows
echo    .\vcpkg integrate install
echo.
echo Option 2: Download pre-built binaries
echo ------------------------------------
echo 1. Go to https://www.glfw.org/download.html
echo 2. Download "Windows pre-compiled binaries"
echo 3. Extract to: third_party\glfw\
echo 4. Ensure structure is: third_party\glfw\include\GLFW\glfw3.h
echo.

echo Checking current GLFW installation...
if exist "third_party\glfw\include\GLFW\glfw3.h" (
    echo Found GLFW in third_party\glfw\
    echo Include: third_party\glfw\include\GLFW\glfw3.h
) else (
    echo GLFW not found in third_party\glfw\
)

if exist "C:\vcpkg\installed\x64-windows\include\GLFW\glfw3.h" (
    echo Found GLFW in vcpkg: C:\vcpkg\installed\x64-windows\
) else (
    echo GLFW not found in vcpkg
)

echo.
echo After installing GLFW, run: build-vs-legacy.bat
echo.
pause