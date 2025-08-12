@echo off
echo Verifying CMakeLists File
echo =========================
echo.

if not exist "CMakeLists.txt" (
    echo Error: CMakeLists.txt not found in current directory.
    pause
    exit /b 1
)

echo Checking CMakeLists.txt for pkg-config usage...
echo.

echo File contents:
echo --------------
type CMakeLists.txt
echo.

echo Checking for pkg-config usage (excluding comments)...
echo.

REM Create a temporary file without comment lines
findstr /v "^#" CMakeLists.txt > temp_check.txt 2>nul

if exist "temp_check.txt" (
    echo Non-comment lines:
    echo -----------------
    type temp_check.txt
    echo.
    
    REM Check for pkg-config usage
    findstr /i "pkg-config" temp_check.txt >nul 2>&1
    if not errorlevel 1 (
        echo WARNING: Found pkg-config usage in non-comment lines!
        echo This may cause build issues on Windows.
    ) else (
        echo ✓ No pkg-config usage found in non-comment lines.
    )
    
    del temp_check.txt
) else (
    echo Warning: Could not create temporary file for verification.
    echo Checking entire file for pkg-config...
    
    findstr /i "pkg-config" CMakeLists.txt >nul 2>&1
    if not errorlevel 1 (
        echo WARNING: Found pkg-config in file (may be in comments).
        echo Check if this is actual usage or just comments.
    ) else (
        echo ✓ No pkg-config found in file.
    )
)

echo.
echo Verification complete.
pause