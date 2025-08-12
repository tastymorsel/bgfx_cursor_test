@echo off
echo Installing Windows Dependencies for Asteroids Game
echo ================================================
echo.

echo This script will help you install the required dependencies using MSYS2.
echo.

echo Step 1: Download and Install MSYS2
echo ----------------------------------
echo 1. Go to https://www.msys2.org/
echo 2. Download the installer for Windows
echo 3. Run the installer and follow the setup wizard
echo 4. Make sure to add MSYS2 to your PATH during installation
echo.
pause

echo.
echo Step 2: Install Required Packages
echo --------------------------------
echo 1. Open MSYS2 MinGW 64-bit terminal (from Start Menu)
echo 2. Run the following commands:
echo.
echo    pacman -S mingw-w64-x86_64-toolchain
echo    pacman -S mingw-w64-x86_64-glfw
echo    pacman -S mingw-w64-x86_64-opengl-headers
echo    pacman -S mingw-w64-x86_64-pkg-config
echo.
echo 3. When prompted, type 'Y' and press Enter
echo.
pause

echo.
echo Step 3: Add to PATH
echo -------------------
echo 1. Open System Properties (Win + Pause/Break)
echo 2. Click "Environment Variables"
echo 3. Under "System Variables", find "Path" and click "Edit"
echo 4. Click "New" and add: C:\msys64\mingw64\bin
echo 5. Click "OK" on all dialogs
echo 6. Restart your terminal/IDE
echo.
pause

echo.
echo Step 4: Verify Installation
echo ---------------------------
echo After restarting your terminal, run:
echo   g++ --version
echo   pkg-config --version
echo.
echo If both commands work, you're ready to build!
echo.
echo You can now run: build.bat
echo.
pause