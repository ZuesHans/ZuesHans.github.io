@echo off
::============================================================
:: One-click publish script for Hexo blog (NO WMIC)
:: Uses PowerShell to get timestamp – works everywhere
::============================================================

cd /d "%~dp0"

echo.
echo ===== Step 1: Clean old files =====
call hexo clean
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] hexo clean failed
    pause
    exit /b %errorlevel%
)

echo.
echo ===== Step 2: Generate static files =====
call hexo generate
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] hexo generate failed
    pause
    exit /b %errorlevel%
)

echo.
echo ===== Step 3: Stage source changes =====
git add .
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] git add failed
    pause
    exit /b %errorlevel%
)

:: Check for changes
git diff --cached --quiet
if %errorlevel% equ 0 (
    echo.
    echo [INFO] No changes to commit
    goto :success
)

:: Get timestamp using PowerShell (works even if wmic is disabled)
for /f %%a in ('powershell -command "Get-Date -Format \"yyyy-MM-dd HH:mm\""') do set "timestamp=%%a"

git commit -m "Site updated: %timestamp%" >nul 2>&1
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] git commit failed
    pause
    exit /b %errorlevel%
)

echo.
echo ===== Step 4: Push to origin/source =====
git push origin source
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Push failed (network/auth issue)
    pause
    exit /b %errorlevel%
)

:success
echo.
echo =========================================================
echo [SUCCESS] Source pushed to 'source' branch!
echo GitHub Actions is building... (~1-2 min)
echo Live at: https://ZuesHans.github.io
echo =========================================================
pause