@echo off
echo ========================================
echo   KuGouConverter Deploy Script
echo ========================================
echo.

set RELEASE_DIR=%~dp0release

cd /d "%RELEASE_DIR%"

if exist "KuGouConverter.exe" (
    "C:\Qt\6.10.2\msvc2022_64\bin\windeployqt.exe" --release KuGouConverter.exe
) else (
    echo Error: KuGouConverter.exe not found
    echo Please build Release version first
    pause
    exit /b 1
)

echo.
echo Deploy completed!
pause
