@echo off
setlocal

set BUILD_DIR=Builds

if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

cmake -S . -B %BUILD_DIR% -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo [ERROR] CMake generation failed.
    exit /b %errorlevel%
)

cmake --build %BUILD_DIR% --config Release
if %errorlevel% neq 0 (
    echo [ERROR] Compilation failed.
    exit /b %errorlevel%
)

set EXE_PATH=%BUILD_DIR%\Debug\L_RUNTIME.exe
if exist %EXE_PATH% (
    echo.
    echo [INFO] Executing %EXE_PATH%
    echo --------------------------------------------------
    %EXE_PATH%
) else (
    echo [ERROR] Could not find %EXE_PATH%.
    exit /b 1
)

endlocal