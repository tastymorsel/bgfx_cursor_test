@echo off
echo Setting VCPKG_ROOT Environment Variable
echo ======================================
echo.

echo This script will help you set VCPKG_ROOT for the current session.
echo.

echo Current VCPKG_ROOT: %VCPKG_ROOT%
echo.

echo Searching for vcpkg installations...
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
    if exist "%%~p\vcpkg.exe" (
        echo Found vcpkg at: %%~p
        set FOUND_VCPKG=1
        set VCPKG_PATH=%%~p
    )
)

if %FOUND_VCPKG%==0 (
    echo No vcpkg found in common locations.
    echo.
    echo Please enter the full path to your vcpkg installation:
    set /p VCPKG_PATH="vcpkg path: "
    
    if exist "%VCPKG_PATH%\vcpkg.exe" (
        set FOUND_VCPKG=1
    ) else (
        echo Invalid path or vcpkg.exe not found at: %VCPKG_PATH%
        pause
        exit /b 1
    )
)

echo.
echo Setting VCPKG_ROOT to: %VCPKG_PATH%
set VCPKG_ROOT=%VCPKG_PATH%

echo.
echo VCPKG_ROOT is now set to: %VCPKG_ROOT%
echo.
echo Note: This is only for the current command prompt session.
echo To make it permanent, add this to your system environment variables:
echo   VCPKG_ROOT=%VCPKG_PATH%
echo.
echo You can now run: build-vs-legacy.bat
echo.
pause