@echo off
setlocal
set SCRIPT_DIR=%~dp0
set ROOT_DIR=%SCRIPT_DIR%..
set BUILD_DIR=%ROOT_DIR%\build

echo === Configuring CMake for Visual Studio ===
rmdir /s /q "%BUILD_DIR%" 2>nul
mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

:: Generate Visual Studio solution
cmake -G "Visual Studio 17 2022" "%ROOT_DIR%"
if errorlevel 1 (
    echo CMake configuration failed
    exit /b 1
)

:: Build solution in Debug
cmake --build . --config Debug -- /m
if errorlevel 1 (
    echo Build failed
    exit /b 1
)

echo === Project build complete ===
endlocal
