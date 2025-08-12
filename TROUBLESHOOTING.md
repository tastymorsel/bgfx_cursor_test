# Troubleshooting Guide

## Windows Batch File Issues

### "not was unexpected at this time" Error

This error typically occurs when there are syntax issues in Windows batch files. Here are the most common causes and solutions:

#### **Cause 1: Hidden Characters or Encoding Issues**
- **Problem**: The batch file contains hidden Unicode characters or wrong line endings
- **Solution**: 
  1. Open the batch file in Notepad++
  2. Go to Encoding → Convert to ANSI
  3. Go to Edit → EOL Conversion → Windows (CR LF)
  4. Save the file

#### **Cause 2: Path Issues**
- **Problem**: Paths contain spaces or special characters
- **Solution**: 
  1. Use quotes around all paths: `"C:\Program Files\My Folder"`
  2. Avoid spaces in project directory names
  3. Use short path names if available

#### **Cause 3: Environment Variable Problems**
- **Problem**: Environment variables contain unexpected characters
- **Solution**:
  1. Check if `%CD%`, `%PATH%`, or other variables contain special characters
  2. Use `echo %CD%` to see current directory
  3. Avoid using `%` in echo statements

#### **Cause 4: Command Syntax Issues**
- **Problem**: Incorrect batch file syntax
- **Solution**:
  1. Use `if errorlevel 1` instead of `if %errorlevel% neq 0`
  2. Use `if not exist "folder"` instead of `if not exist folder`
  3. Quote all file paths

### **Quick Fixes**

#### **Option 1: Use the Simple Build Script**
```cmd
build-vs-simple.bat
```

#### **Option 2: Manual Commands**
```cmd
mkdir build-vs
cd build-vs
cmake -G "Visual Studio 17 2022" -A x64 -f ..\CMakeLists_VisualStudio.txt ..
cmake --build . --config Release
```

#### **Option 3: PowerShell Alternative**
```powershell
.\build-vs.ps1
```

### **Prevention Tips**

1. **Always use quotes** around paths: `"C:\My Path\file.txt"`
2. **Use simple syntax**: `if errorlevel 1` instead of complex expressions
3. **Avoid special characters** in directory names
4. **Test with simple commands** first
5. **Use PowerShell** for complex scripts (more robust)

### **Testing Your Environment**

Run this simple test to verify your setup:
```cmd
test-simple.bat
```

If this works, the issue is in the main build script. If it fails, there's a system-level problem.

### **Common Workarounds**

1. **Run from Developer Command Prompt**: Always use Visual Studio's Developer Command Prompt
2. **Use absolute paths**: Avoid relative paths that might cause issues
3. **Check file encoding**: Ensure files are saved as ANSI or UTF-8 without BOM
4. **Use CMake GUI**: Alternative to command-line builds
5. **Open in Visual Studio**: Use the generated .sln file directly

### **Still Having Issues?**

If none of the above solutions work:

1. **Check Windows version**: Ensure you're on Windows 10/11
2. **Verify Visual Studio**: Make sure C++ workload is installed
3. **Check antivirus**: Some antivirus software blocks batch files
4. **Run as Administrator**: Try running Command Prompt as Administrator
5. **Use PowerShell**: PowerShell is more robust than batch files