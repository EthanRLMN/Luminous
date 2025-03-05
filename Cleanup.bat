@echo off
setlocal enabledelayedexpansion

REM Folders to delete
set folders=Builds Editor\Builds Editor\Libs\imgui Engine\Builds Engine\Libs\assimp Libs\glfw

for %%d in (%folders%) do (
    if exist "%%d" (
        echo Deleting %%d...
        rmdir /s /q "%%d"
    ) else (
        echo Folder %%d does not exist.
    )
)

echo Cleanup Done.
pause
