@echo off
set /p title=your title: 
set filename=%date:~0,4%-%date:~5,2%-%date:~8,2%-%title%.md
hexo new post "%title%"
echo. >> "source\_posts\%filename%"
start notepad "source\_posts\%filename%"
echo.
echo created：source\_posts\%filename%
echo done?：git add . ^& git commit -m "post: %title%" ^& git push
pause