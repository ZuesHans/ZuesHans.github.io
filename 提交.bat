@echo off
set /p msg=your message: 
if "%msg%"=="" set msg=post
git add .
git commit -m "%msg%"
git push origin source
echo.
echo sucssed!
pause