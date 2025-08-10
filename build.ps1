# PowerShell build script for Asteroids Game on Windows

Write-Host "Building Asteroids Game for Windows..." -ForegroundColor Green

# Check if we have the required tools
try {
    $gpp = Get-Command g++ -ErrorAction Stop
    Write-Host "Found g++ at: $($gpp.Source)" -ForegroundColor Green
} catch {
    Write-Host "Error: g++ compiler not found." -ForegroundColor Red
    Write-Host "Please install MSYS2 and add mingw64/bin to your PATH" -ForegroundColor Yellow
    Write-Host "See install-deps-windows in Makefile for instructions" -ForegroundColor Yellow
    Read-Host "Press Enter to continue"
    exit 1
}

# Check for pkg-config
try {
    $pkgconfig = Get-Command pkg-config -ErrorAction Stop
    Write-Host "Found pkg-config at: $($pkgconfig.Source)" -ForegroundColor Green
} catch {
    Write-Host "Error: pkg-config not found." -ForegroundColor Red
    Write-Host "Please install MSYS2 and add mingw64/bin to your PATH" -ForegroundColor Yellow
    Read-Host "Press Enter to continue"
    exit 1
}

# Check for required libraries
try {
    $glfw = pkg-config --exists glfw3 2>$null
    if ($LASTEXITCODE -eq 0) {
        Write-Host "GLFW3 found" -ForegroundColor Green
    } else {
        throw "GLFW3 not found"
    }
} catch {
    Write-Host "Error: GLFW3 not found." -ForegroundColor Red
    Write-Host "Please install mingw-w64-x86_64-glfw via MSYS2" -ForegroundColor Yellow
    Read-Host "Press Enter to continue"
    exit 1
}

Write-Host "Dependencies found. Building..." -ForegroundColor Green

# Clean previous build
Write-Host "Cleaning previous build..." -ForegroundColor Yellow
make clean

# Build the project
Write-Host "Building project..." -ForegroundColor Yellow
$cpuCount = (Get-WmiObject -Class Win32_Processor).NumberOfLogicalProcessors
if ($cpuCount -eq $null) { $cpuCount = 4 }

if (make -j$cpuCount) {
    Write-Host "Build successful! Run 'asteroids.exe' to start the game." -ForegroundColor Green
} else {
    Write-Host "Build failed. Please check the error messages above." -ForegroundColor Red
    Read-Host "Press Enter to continue"
    exit 1
}

Write-Host "Build completed successfully!" -ForegroundColor Green
Read-Host "Press Enter to continue"