@echo off
setlocal enabledelayedexpansion

:: === CONFIGURATION ===
:: On se place à la racine du projet (un dossier au-dessus du script)
cd /d "%~dp0\.."

set "PROJECT_DIR=%cd%"
set "BACKUP_DIR=%PROJECT_DIR%\[#]BACKUP"
set "EXCLUDE1=[#]BACKUP"
set "EXCLUDE2=[#]LC_S"
set "EXCLUDE3=[#]LCG_I"
set "TMP_DIR=%PROJECT_DIR%\_TMP_ENDSTONE_"
set "REPO_URL=https://github.com/EndstoneMC/endstone"

:: === DATE + HEURE FORMATÉES ===
for /f "tokens=2 delims==" %%I in ('"wmic os get localdatetime /value"') do set datetime=%%I
set "YYYY=%datetime:~0,4%"
set "MM=%datetime:~4,2%"
set "DD=%datetime:~6,2%"
set "HH=%datetime:~8,2%"
set "MN=%datetime:~10,2%"
set "SS=%datetime:~12,2%"
set "TIMESTAMP=%YYYY%-%MM%-%DD%_%HH%-%MN%-%SS%"

echo === SAUVEGARDE DU PROJET ===
set "BACKUP_DEST=%BACKUP_DIR%\%TIMESTAMP%"
mkdir "%BACKUP_DEST%" >nul 2>&1

echo Copie des fichiers vers "%BACKUP_DEST%"...
:: Exclut les dossiers spécifiques + tous les fichiers/dossiers commençant par [#]
robocopy "%PROJECT_DIR%" "%BACKUP_DEST%" /E /XD "%EXCLUDE1%" "%EXCLUDE2%" "%EXCLUDE3%" /XF "[#]*" /XD "[#]*" >nul

:: === TÉLÉCHARGEMENT DU DÉPÔT GITHUB (branche main) ===
echo === Téléchargement du dépôt Endstone (branche main) ===
if exist "%TMP_DIR%" rd /s /q "%TMP_DIR%"
mkdir "%TMP_DIR%"

curl -L -o "%TMP_DIR%\main.zip" "%REPO_URL%/archive/refs/heads/main.zip" >nul 2>&1
tar -xf "%TMP_DIR%\main.zip" -C "%TMP_DIR%" >nul 2>&1

echo Mise à jour des fichiers du projet...
for /d %%D in ("%TMP_DIR%\endstone-main*") do (
    robocopy "%%~fD" "%PROJECT_DIR%" /E >nul
)

:: Nettoyage du dossier temporaire
rd /s /q "%TMP_DIR%" >nul 2>&1

:: === TÉLÉCHARGEMENT DU SOURCECODE.ZIP DE LA DERNIÈRE RELEASE ===
echo === Téléchargement du source code de la dernière release ===
set "SC_DIR=%BACKUP_DIR%\SC"
mkdir "%SC_DIR%" >nul 2>&1

curl -L -o "%SC_DIR%\endstone_latest_source.zip" "https://api.github.com/repos/EndstoneMC/endstone/zipball" >nul 2>&1

echo.
echo === ✅ MISE À JOUR TERMINÉE AVEC SUCCÈS ===
echo Sauvegarde: %BACKUP_DEST%
echo SourceCode: %SC_DIR%\endstone_latest_source.zip
echo.
pause
