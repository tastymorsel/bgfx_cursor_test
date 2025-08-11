# CMake Diagnostic Tool (PowerShell)

Write-Host "CMake Diagnostic Tool" -ForegroundColor Green
Write-Host "=====================" -ForegroundColor Green
Write-Host ""

# 1. Check CMake version
Write-Host "1. Checking CMake version..." -ForegroundColor Yellow
try {
    $version = cmake --version
    Write-Host $version -ForegroundColor Green
} catch {
    Write-Host "ERROR: cmake --version failed" -ForegroundColor Red
    exit 1
}

Write-Host ""

# 2. Check CMake location
Write-Host "2. Checking CMake location..." -ForegroundColor Yellow
try {
    $cmakePath = Get-Command cmake -ErrorAction Stop
    Write-Host "Found at: $($cmakePath.Source)" -ForegroundColor Green
} catch {
    Write-Host "ERROR: cmake not found in PATH" -ForegroundColor Red
    exit 1
}

Write-Host ""

# 3. Check CMake help for -f flag
Write-Host "3. Checking CMake help for -f flag..." -ForegroundColor Yellow
try {
    $help = cmake --help
    if ($help -match "-f") {
        Write-Host "SUCCESS: -f flag found in help" -ForegroundColor Green
    } else {
        Write-Host "WARNING: -f flag not found in help output" -ForegroundColor Yellow
    }
} catch {
    Write-Host "ERROR: Failed to get CMake help" -ForegroundColor Red
}

Write-Host ""

# 4. Test basic CMake functionality
Write-Host "4. Testing basic CMake functionality..." -ForegroundColor Yellow
try {
    cmake --help | Out-Null
    Write-Host "SUCCESS: Basic CMake functionality works" -ForegroundColor Green
} catch {
    Write-Host "ERROR: Basic CMake functionality failed" -ForegroundColor Red
    exit 1
}

Write-Host ""

# 5. Test CMake with simple command
Write-Host "5. Testing CMake with simple command..." -ForegroundColor Yellow
try {
    cmake -P CMakeLists.txt 2>$null
    Write-Host "SUCCESS: CMake -P test passed" -ForegroundColor Green
} catch {
    Write-Host "WARNING: CMake -P test failed (this is normal if no CMakeLists.txt exists)" -ForegroundColor Yellow
}

Write-Host ""

# 6. Check environment variables
Write-Host "6. Checking environment variables..." -ForegroundColor Yellow
Write-Host "PATH: $env:PATH" -ForegroundColor Cyan

Write-Host ""

# 7. Test CMake with verbose output
Write-Host "7. Testing CMake with verbose output..." -ForegroundColor Yellow
try {
    $help = cmake --help
    if ($help -match "generator") {
        Write-Host "SUCCESS: Generator help found" -ForegroundColor Green
    } else {
        Write-Host "WARNING: Generator help not found" -ForegroundColor Yellow
    }
} catch {
    Write-Host "ERROR: Failed to get generator help" -ForegroundColor Red
}

Write-Host ""

# 8. Test specific CMake command
Write-Host "8. Testing specific CMake command..." -ForegroundColor Yellow
Write-Host "Testing: cmake -G 'Visual Studio 17 2022' --help" -ForegroundColor Cyan
try {
    cmake -G "Visual Studio 17 2022" --help | Out-Null
    Write-Host "SUCCESS: Visual Studio generator test passed" -ForegroundColor Green
} catch {
    Write-Host "ERROR: Visual Studio generator test failed" -ForegroundColor Red
}

Write-Host ""
Write-Host "Diagnostic complete." -ForegroundColor Green
Read-Host "Press Enter to continue"