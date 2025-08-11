@echo off
echo CMake Diagnostic Tool
echo =====================
echo.

echo 1. Checking CMake version...
cmake --version
if errorlevel 1 (
    echo ERROR: cmake --version failed
    goto :end
)

echo.
echo 2. Checking CMake location...
where cmake
if errorlevel 1 (
    echo ERROR: cmake not found in PATH
    goto :end
)

echo.
echo 3. Checking CMake help for -f flag...
cmake --help | findstr /i "-f"
if errorlevel 1 (
    echo WARNING: -f flag not found in help output
) else (
    echo SUCCESS: -f flag found in help
)

echo.
echo 4. Testing basic CMake functionality...
cmake --help >nul 2>&1
if errorlevel 1 (
    echo ERROR: Basic CMake functionality failed
    goto :end
)

echo.
echo 5. Testing CMake with simple command...
cmake -P CMakeLists.txt >nul 2>&1
if errorlevel 1 (
    echo WARNING: CMake -P test failed (this is normal if no CMakeLists.txt exists)
) else (
    echo SUCCESS: CMake -P test passed
)

echo.
echo 6. Checking environment variables...
echo PATH: %PATH%
echo.

echo 7. Testing CMake with verbose output...
cmake --help | findstr /i "generator"
if errorlevel 1 (
    echo WARNING: Generator help not found
) else (
    echo SUCCESS: Generator help found
)

echo.
echo 8. Testing specific CMake command...
echo Testing: cmake -G "Visual Studio 17 2022" --help
cmake -G "Visual Studio 17 2022" --help >nul 2>&1
if errorlevel 1 (
    echo ERROR: Visual Studio generator test failed
) else (
    echo SUCCESS: Visual Studio generator test passed
)

:end
echo.
echo Diagnostic complete.
pause