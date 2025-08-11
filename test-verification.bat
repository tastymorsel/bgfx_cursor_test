@echo off
echo Testing pkg-config Verification Logic
echo ====================================
echo.

echo Creating test CMakeLists file with comments...
echo # This is a comment about pkg-config > test_cmake.txt
echo find_package(PkgConfig REQUIRED) >> test_cmake.txt
echo # Another comment >> test_cmake.txt

echo Test file contents:
type test_cmake.txt
echo.

echo Testing verification logic...
REM Create a temporary file without comment lines
findstr /v "^#" test_cmake.txt > temp_check.txt
echo Non-comment lines:
type temp_check.txt
echo.

REM Check for pkg-config usage in non-comment lines
findstr /i "pkg-config" temp_check.txt >nul 2>&1
if not errorlevel 1 (
    echo ✓ Found pkg-config usage in non-comment lines
) else (
    echo ✗ No pkg-config usage found
)

echo.
echo Cleaning up test files...
del test_cmake.txt
del temp_check.txt
echo Test complete.
pause