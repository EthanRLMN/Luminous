@echo off
setlocal enabledelayedexpansion

rem Display welcome message
:welcome
echo What do you want to do? :
echo 1 - Build Project (Will execute cleanup first)
echo 2 - Update Submodules
echo 3 - Cleanup Project (Without rebuilding)
echo 4 - Exit

set /p choice="Please chose a number between 1 & 4 : "

if "%choice%"=="1" (
    echo Building project...
    echo NOT WORKING YET...
    ping 127.0.0.1 -n 1 > nul
    exit
) else if "%choice%"=="2" (
    echo Updating submodules...
    ping 127.0.0.1 -n 1 > nul
    goto :submodules
    pause
) else if "%choice%"=="3" (
    echo Cleaning up project...
    ping 127.0.0.1 -n 1 > nul
    goto :cleanup
    pause
) else if "%choice%"=="4" (
    echo Exiting project in 3 seconds...
    ping 127.0.0.1 -n 3 > nul
    exit
) else (
    echo Wrong choice, try again!
    pause
)


rem Function to cleanup files
:cleanup
set folders=Builds Editor\Builds Editor\Libs\imgui Engine\Builds Engine\Libs\assimp Engine\Libs\glfw Libs\logger Libs\luminousmaths

for %%d in (%folders%) do (
    if exist "%%d" (
        echo Deleting %%d...
        rmdir /s /q "%%d"
    ) else (
        echo Folder %%d does not exist.
    )
)
echo Cleanup Done!
ping 127.0.0.1 -n 3 > nul
goto :welcome


rem Function update submodules
:submodules
echo Initializing Submodules...
git submodule init
echo Submodules initialization done!

echo Updating Submodules...
git submodule update
echo Submodules update done!

echo All submodules were updated...
ping 127.0.0.1 -n 3 > nul
goto :welcome