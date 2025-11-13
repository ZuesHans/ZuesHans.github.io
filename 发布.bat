@echo off
::============================================================
:: One-click create new Hexo post (English date + fixed cover)
:: Path: C:\Users\31802\Documents\ZuesHans.github.io\source\_posts
::============================================================

cd /d "C:\Users\31802\Documents\ZuesHans.github.io\source\_posts"

echo.
echo ===== Create New Blog Post =====
echo.

:: Input title
set "title="
set /p "title=Enter post title (e.g. wp_11_2): "
if not defined title (
    echo.
    echo [ERROR] Title cannot be empty!
    pause
    exit /b 1
)

:: Generate English timestamp: 2025-11-07 14:30
for /f %%a in ('powershell -command "Get-Date -Format \"yyyy-MM-dd HH:mm\""') do set "postdate=%%a"

:: Fixed default cover
set "cover_line=cover: /img/cover/default.png"

:: Create markdown file
set "filename=%title%.md"
(
echo ---
echo title: %title%
echo date: %postdate%
echo tags:
echo     - 杂谈
echo     - 算法
echo     %cover_line%
echo ---
echo.
echo.
) > "%filename%"

echo.
echo [SUCCESS] New post created: %filename%
echo     Date: %postdate%
echo     Cover: /img/cover/default.png
echo.
echo Ready to edit: %filename%
pause