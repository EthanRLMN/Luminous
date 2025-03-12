@echo off

echo What do you want to do? :
echo 1 - Build Project (Will execute cleanup first)
echo 2 - Update Submodules
echo 3 - Cleanup Project (Without rebuilding)
echo 4 - Exit

set /p choice="Please chose a number between 1 & 3 : "

if "%choice%"=="1" (
    echo Building project...
    ping 127.0.0.1 -n 1 > nul
    call Build.bat
    pause
) else if "%choice%"=="2" (
    echo Updating submodules...
    ping 127.0.0.1 -n 1 > nul
    call Submodules.bat
    pause
) else if "%choice%"=="3" (
    echo Cleaning up project...
    ping 127.0.0.1 -n 1 > nul
    call Cleanup.bat
    pause
) else if "%choice%"=="4" (
    echo Exiting project in 3 seconds...
    ping 127.0.0.1 -n 3 > nul
    exit
) else (
    echo Wrong choice, try again!
    pause
)