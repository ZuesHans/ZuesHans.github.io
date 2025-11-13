@echo off
::============================================================
:: One-click publish script for Hexo blog
:: - Source code lives in branch: source
:: - GitHub Actions builds and pushes to: main
:: - Any error stops immediately
:: - SUCCESS shown only when everything finishes
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
echo ===== Step 2: Generate static files (for preview) =====
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

:: Check if there are any changes to commit
git diff --cached --exit-code >nul 2>&1
if %errorlevel% equ 0 (
    echo.
    echo [INFO] No changes detected – skipping commit & push
    goto :success
)

:: Generate timestamp for commit message
for /f "tokens=2 delims==" %%a in ('"wmic OS Get localdatetime /value"') do set "dt=%%a"
set "timestamp=%dt:~0,4%-%dt:~4,2%-%dt:~6,2% %dt:~8,2%:%dt:~10,2%"

git commit -m "Site updated: %timestamp%"
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] git commit failed
    pause
    exit /b %errorlevel%
)

echo.
echo ===== Step 4: Push source to origin/source =====
git push origin source
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Push failed! (network timeout, auth, etc.)
    echo        Check your connection, Git config, or GitHub status.
    pause
    exit /b %errorlevel%
)

:success
echo.
echo =========================================================
echo [SUCCESS] Source code pushed to branch 'source'!
echo.
echo GitHub Actions is now building...
echo Site will be live in ~1-2 minutes:
echo https://ZuesHans.github.io
echo =========================================================
pause