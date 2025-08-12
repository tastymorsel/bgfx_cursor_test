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
echo.

echo 1. Checking third_party\glfw\...
if exist "third_party\glfw\include\GLFW\glfw3.h" (
    echo   ✓ Found GLFW in third_party\glfw\
    echo   Include: third_party\glfw\include\GLFW\glfw3.h
) else (
    echo   ✗ GLFW not found in third_party\glfw\
)

echo.
echo 2. Checking for vcpkg installations...
set FOUND_VCPKG=0

REM Check common vcpkg locations
for %%p in (
    "C:\vcpkg"
    "C:\dev\vcpkg"
    "C:\tools\vcpkg"
    "C:\Users\%USERNAME%\vcpkg"
    "C:\Users\%USERNAME%\dev\vcpkg"
    "C:\Users\%USERNAME%\tools\vcpkg"
    "%~dp0..\vcpkg"
    "%~dp0..\..\vcpkg"
    "%~dp0..\..\..\vcpkg"
) do (
    if exist "%%~p\installed\x64-windows\include\GLFW\glfw3.h" (
        echo   ✓ Found GLFW in vcpkg: %%~p\installed\x64-windows\
        set FOUND_VCPKG=1
        set VCPKG_PATH=%%~p
    )
)

if %FOUND_VCPKG%==0 (
    echo   ✗ GLFW not found in common vcpkg locations
    echo.
    echo 3. Searching for vcpkg in current directory tree...
    
    REM Search for vcpkg in current directory and parent directories
    for /f "delims=" %%i in ('dir /s /b /ad "vcpkg" 2^>nul') do (
        if exist "%%i\installed\x64-windows\include\GLFW\glfw3.h" (
            echo   ✓ Found GLFW in vcpkg: %%i\installed\x64-windows\
            set FOUND_VCPKG=1
            set VCPKG_PATH=%%i
            goto :found_vcpkg
        )
    )
    
    if %FOUND_VCPKG%==0 (
        echo   ✗ No vcpkg with GLFW found in current directory tree
    )
)

:found_vcpkg
echo.
echo 4. Checking system PATH for vcpkg...
where vcpkg >nul 2>&1
if errorlevel 1 (
    echo   ✗ vcpkg not found in system PATH
) else (
    echo   ✓ vcpkg found in system PATH
    for /f "delims=" %%i in ('where vcpkg') do (
        echo     Location: %%i
    )
)

echo.
echo 5. Checking for Visual Studio vcpkg integration...
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" (
    echo   ✓ Visual Studio 2022 Community found
) else if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Professional\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" (
    echo   ✓ Visual Studio 2022 Professional found
) else if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" (
    echo   ✓ Visual Studio 2022 Enterprise found
) else (
    echo   ✗ Visual Studio 2022 not found in Program Files
)

echo.
if %FOUND_VCPKG%==1 (
    echo GLFW found! You can now run: build-vs-legacy.bat
    echo.
    echo To use this vcpkg installation, you may need to set:
    echo set CMAKE_PREFIX_PATH=%VCPKG_PATH%
) else (
    echo GLFW not found. Please install it using one of the options above.
)

echo.
pause