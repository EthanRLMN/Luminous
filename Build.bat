@echo off
setlocal enabledelayedexpansion

rem Display welcome message
:welcome
echo.
echo What do you want to do? :
echo 1 - Build Project (Will execute cleanup first)
echo 2 - Update Submodules
echo 3 - Cleanup Project (Without rebuilding)
echo 4 - Exit
echo.

set /p choice="Please chose a number between 1 & 4 : "

if "%choice%"=="1" (
    echo.
    echo Building project...
    goto :build
    exit
) else if "%choice%"=="2" (
    echo.
    echo Updating submodules...
    ping 127.0.0.1 -n 1 > nul
    goto :submodules
    pause
) else if "%choice%"=="3" (
    echo.
    echo Cleaning up project...
    ping 127.0.0.1 -n 1 > nul
    goto :cleanup
    pause
) else if "%choice%"=="4" (
    echo.
    echo Exiting project...
    ping 127.0.0.1 -n 1 > nul
    exit
) else (
    echo.
    echo Wrong choice, try again!
    pause
)


rem Function to cleanup files
:cleanup
set folders=Builds Editor\Builds Engine\Builds Engine\Libs\assimp Engine\Libs\glfw Engine\Libs\logger Engine\Libs\luminousmaths

for %%d in (%folders%) do (
    if exist "%%d" (
        echo.
        echo Deleting %%d...
        rmdir /s /q "%%d"
    ) else (
        echo.
        echo Folder %%d does not exist.
    )
)
echo.
echo Cleanup Done!
ping 127.0.0.1 -n 1 > nul
exit



:build
echo.
echo Initializing and Updating Submodules!
git submodule update --init --recursive
echo.
echo Submodules Initialized!
ping 127.0.0.1 -n 1 > nul

echo.
echo Generating Files!
cmake --preset "VS_2022"
echo.
echo File Generation Complete!
ping 127.0.0.1 -n 1 > nul
echo.
echo Testing Executable!
ctest --preset "VS_2022 Release"
echo.
echo Test successful!
ping 127.0.0.1 -n 1 > nul

echo.
echo Project Built successfully! Starting .sln!
ping 127.0.0.1 -n 2 > nul
start TEMP\VS_2022\Luminous.sln
exit


rem Function update submodules
:submodules
echo.
echo Initializing Submodules...
git submodule init
echo.
echo Submodules initialization done!

echo.
echo Updating Submodules...
git submodule update --recursive --remote --merge
echo.
echo Submodules update done!

echo.
echo All submodules were updated...
ping 127.0.0.1 -n 1 > nul
goto :welcome