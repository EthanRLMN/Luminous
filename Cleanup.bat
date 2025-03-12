@echo off
setlocal enabledelayedexpansion

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
call Build.bat