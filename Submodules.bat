@echo off

echo Initializing Submodules...
git submodule init
echo Submodules initialization done!

echo Updating Submodules...
git submodule update
echo Submodules update done!

echo All submodules were updated...
echo Press Enter to close this window!
exit /b