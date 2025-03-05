@echo off
REM Chemin du dossier de génération
set BUILD_DIR=Solution

REM Supprime l'ancien dossier de build s'il existe
if exist %BUILD_DIR% (
    rmdir /s /q %BUILD_DIR%
)

REM Crée un nouveau dossier de build
mkdir %BUILD_DIR%
cd %BUILD_DIR%

REM Génération de la solution Visual Studio 2022
cmake -G "VS_2022 Release" ..

echo Visual Studio 2022 solution generated
pause