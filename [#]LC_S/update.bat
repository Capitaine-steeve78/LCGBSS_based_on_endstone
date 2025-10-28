@echo off
setlocal enabledelayedexpansion

:: === CONFIGURATION ===
cd /d "%~dp0\.."

set "PROJECT_DIR=%cd%"
set "BACKUP_DIR=%PROJECT_DIR%\[#]BACKUP"
set "EXCLUDE1=[#]BACKUP"
set "EXCLUDE2=[#]LC_S"
set "EXCLUDE3=[#]LCG_I"
set "TMP_DIR=%PROJECT_DIR%\_TMP_ENDSTONE_"
set "REPO_API=https://api.github.com/repos/EndstoneMC/endstone/releases/latest"

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
robocopy "%PROJECT_DIR%" "%BACKUP_DEST%" /E /XD "%EXCLUDE1%" "%EXCLUDE2%" "%EXCLUDE3%" /XF "[#]*" /XD "[#]*" >nul

:: === TÉLÉCHARGEMENT DE LA DERNIÈRE RELEASE ===
echo === Téléchargement de la dernière release Endstone ===
if exist "%TMP_DIR%" rd /s /q "%TMP_DIR%"
mkdir "%TMP_DIR%"

:: Récupère l'URL du zip de la dernière release
for /f "tokens=*" %%u in ('curl -s %REPO_API% ^| findstr /i "zipball_url"') do (
    set "ZIP_URL=%%u"
)

:: Nettoyage de l'URL (extraire l'URL entre guillemets)
set "ZIP_URL=!ZIP_URL:*\"=!"
set "ZIP_URL=!ZIP_URL:~0,-2!"

echo Téléchargement depuis !ZIP_URL! ...
curl -L -o "%TMP_DIR%\latest_release.zip" "!ZIP_URL!" >nul 2>&1

:: Extraction
tar -xf "%TMP_DIR%\latest_release.zip" -C "%TMP_DIR%" >nul 2>&1

echo Mise à jour des fichiers du projet...
for /d %%D in ("%TMP_DIR%\*") do (
    robocopy "%%~fD" "%PROJECT_DIR%" /E >nul
)

:: Nettoyage du dossier temporaire
rd /s /q "%TMP_DIR%" >nul 2>&1

echo.
echo === ✅ MISE À JOUR TERMINÉE AVEC SUCCÈS ===
echo Sauvegarde: %BACKUP_DEST%
echo SourceCode: %TMP_DIR%\latest_release.zip
echo.
pause
