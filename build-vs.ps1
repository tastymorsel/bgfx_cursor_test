# PowerShell build script for Asteroids Game with Visual Studio

Write-Host "Building Asteroids Game with Visual Studio..." -ForegroundColor Green
Write-Host "===========================================" -ForegroundColor Green
Write-Host ""

# Check if we're in a Visual Studio Developer Command Prompt
try {
    $cl = Get-Command cl -ErrorAction Stop
    Write-Host "Found Visual Studio C++ compiler at: $($cl.Source)" -ForegroundColor Green
} catch {
    Write-Host "Error: Visual Studio C++ compiler (cl.exe) not found." -ForegroundColor Red
    Write-Host ""
    Write-Host "Please run this script from a Visual Studio Developer Command Prompt:" -ForegroundColor Yellow
    Write-Host "1. Open Start Menu" -ForegroundColor Yellow
    Write-Host "2. Search for 'Developer Command Prompt for VS 2022' (or 2019)" -ForegroundColor Yellow
    Write-Host "3. Run as Administrator" -ForegroundColor Yellow
    Write-Host "4. Navigate to this directory and run build-vs.ps1" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Or install Visual Studio 2019/2022 Community (free) with C++ workload." -ForegroundColor Yellow
    Write-Host ""
    Read-Host "Press Enter to continue"
    exit 1
}

Write-Host "Found Visual Studio C++ compiler." -ForegroundColor Green
Write-Host ""

# Check for CMake
try {
    $cmake = Get-Command cmake -ErrorAction Stop
    Write-Host "Found CMake at: $($cmake.Source)" -ForegroundColor Green
} catch {
    Write-Host "Error: CMake not found." -ForegroundColor Red
    Write-Host "Please install CMake from https://cmake.org/download/" -ForegroundColor Yellow
    Read-Host "Press Enter to continue"
    exit 1
}

Write-Host "Found CMake." -ForegroundColor Green
Write-Host ""

# Create build directory
if (!(Test-Path "build-vs")) {
    New-Item -ItemType Directory -Name "build-vs" | Out-Null
}
Set-Location "build-vs"

# Copy CMakeLists file for older CMake versions
Write-Host "Copying CMakeLists file..." -ForegroundColor Yellow
Copy-Item "..\CMakeLists_VisualStudio.txt" "CMakeLists.txt" -Force

# Configure with CMake
Write-Host "Configuring project with CMake..." -ForegroundColor Yellow
try {
    cmake -G "Visual Studio 17 2022" -A x64 ".."
    if ($LASTEXITCODE -ne 0) {
        throw "CMake configuration failed with exit code $LASTEXITCODE"
    }
} catch {
    Write-Host "CMake configuration failed: $($_.Exception.Message)" -ForegroundColor Red
    Read-Host "Press Enter to continue"
    exit 1
}

# Build the project
Write-Host ""
Write-Host "Building project..." -ForegroundColor Yellow
try {
    cmake --build . --config Release
    if ($LASTEXITCODE -ne 0) {
        throw "Build failed with exit code $LASTEXITCODE"
    }
} catch {
    Write-Host "Build failed: $($_.Exception.Message)" -ForegroundColor Red
    Read-Host "Press Enter to continue"
    exit 1
}

Write-Host ""
Write-Host "Build successful!" -ForegroundColor Green
Write-Host "Executable is located at: build-vs\bin\Release\AsteroidsGame.exe" -ForegroundColor Green
Write-Host ""
Write-Host "You can also open AsteroidsGame.sln in Visual Studio to build and debug." -ForegroundColor Green
Write-Host ""

Set-Location ".."
Read-Host "Press Enter to continue"