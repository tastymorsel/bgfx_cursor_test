@echo off
echo Installing bgfx via vcpkg...

REM Try to find vcpkg in common locations
set VCPKG_FOUND=0

REM Check environment variable first
if defined VCPKG_ROOT (
    echo Found VCPKG_ROOT: %VCPKG_ROOT%
    if exist "%VCPKG_ROOT%\vcpkg.exe" (
        echo Using VCPKG_ROOT: %VCPKG_ROOT%
        set VCPKG_FOUND=1
        goto :install
    )
)

REM Check common vcpkg locations
for %%p in (
    "C:\vcpkg"
    "C:\dev\vcpkg"
    "C:\tools\vcpkg"
    "%USERPROFILE%\vcpkg"
    "%USERPROFILE%\dev\vcpkg"
    "%USERPROFILE%\tools\vcpkg"
) do (
    if exist "%%~p\vcpkg.exe" (
        echo Found vcpkg in: %%~p
        set VCPKG_ROOT=%%~p
        set VCPKG_FOUND=1
        goto :install
    )
)

REM Check relative paths from current directory
for %%p in (
    "..\vcpkg"
    "..\..\vcpkg"
    "..\..\..\vcpkg"
) do (
    if exist "%%~p\vcpkg.exe" (
        echo Found vcpkg in: %%~p
        set VCPKG_ROOT=%%~p
        set VCPKG_FOUND=1
        goto :install
    )
)

if %VCPKG_FOUND%==0 (
    echo.
    echo ERROR: vcpkg not found!
    echo.
    echo Please install vcpkg first:
    echo 1. Clone vcpkg: git clone https://github.com/Microsoft/vcpkg.git
    echo 2. Run: cd vcpkg
    echo 3. Run: .\bootstrap-vcpkg.bat
    echo 4. Set VCPKG_ROOT environment variable to point to vcpkg directory
    echo.
    echo Or run this script from a directory near your vcpkg installation.
    echo.
    pause
    exit /b 1
)

:install
echo.
echo Installing bgfx for x64-windows...
"%VCPKG_ROOT%\vcpkg.exe" install bgfx:x64-windows

if errorlevel 1 (
    echo.
    echo ERROR: Failed to install bgfx!
    echo.
    echo This might be because:
    echo - Visual Studio is not installed
    echo - Windows SDK is not installed
    echo - Insufficient disk space
    echo.
    pause
    exit /b 1
)

echo.
echo SUCCESS: bgfx installed successfully!
echo.
echo You can now build the project with:
echo   cmake -G "Visual Studio 17 2022" -A x64 -B build-vs -S .
echo   cmake --build build-vs --config Release
echo.
echo The build system will automatically detect and use the real bgfx library.
echo.
pause