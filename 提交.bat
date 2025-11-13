@echo off
::============================================================
:: 一键发布 Hexo 博客（源码推到 source 分支）
:: 由 GitHub Actions 自动构建并部署到 main 分支
:: 任何错误立即终止，只有全部成功才显示 SUCCESS
::============================================================

cd /d "%~dp0"

echo.
echo ===== 步骤 1：清理旧文件 =====
call hexo clean
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] hexo clean 失败
    pause
    exit /b %errorlevel%
)

echo.
echo ===== 步骤 2：生成静态文件（预览用）=====
call hexo generate
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] hexo generate 失败
    pause
    exit /b %errorlevel%
)

echo.
echo ===== 步骤 3：提交源码改动 =====
git add .
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] git add 失败
    pause
    exit /b %errorlevel%
)

:: 检查是否有改动
git diff --cached --exit-code >nul 2>&1
if %errorlevel% equ 0 (
    echo.
    echo [INFO] 没有检测到改动，跳过提交和推送
    goto :success
)

:: 生成时间戳
for /f "tokens=2 delims==" %%a in ('"wmic OS Get localdatetime /value"') do set "dt=%%a"
set "timestamp=%dt:~0,4%-%dt:~4,2%-%dt:~6,2% %dt:~8,2%:%dt:~10,2%"

git commit -m "Site updated: %timestamp%"
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] git commit 失败
    pause
    exit /b %errorlevel%
)

echo.
echo ===== 步骤 4：推送源码到 origin/source =====
git push origin source
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] 推送失败！可能是网络超时或认证问题。
    echo        请检查网络、Git 配置或 GitHub 状态。
    pause
    exit /b %errorlevel%
)

:success
echo.
echo =========================================================
echo [SUCCESS] 源码已成功推送到 source 分支！
echo.
echo GitHub Actions 正在构建中……
echo 预计 1-2 分钟后网站更新：
echo https://ZuesHans.github.io
echo =========================================================
pause