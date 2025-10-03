@echo off
setlocal
set SCRIPT_DIR=%~dp0
set VENDOR_DIR=%SCRIPT_DIR%..\vendor

echo === Building vendor libraries in %VENDOR_DIR% ===
cd /d %VENDOR_DIR%

:: Run premake5 for Visual Studio
premake5 vs2022
if errorlevel 1 (
    echo Failed to run premake5
    exit /b 1
)

:: Build the generated Visual Studio solution in Debug
MSBuild vendor.sln /p:Configuration=Debug /m
if errorlevel 1 (
    echo Vendor build failed
    exit /b 1
)

echo === Vendor build complete ===
endlocal
