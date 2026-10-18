@echo off
chcp 65001 >nul
setlocal
REM 走 Clash Verge 代理（仅本脚本进程内生效，不改全局 git 配置）
set "HTTP_PROXY=http://127.0.0.1:7897"
set "HTTPS_PROXY=http://127.0.0.1:7897"
set "REPO_URL=https://github.com/wwWWW56600/nucscc-cpp.git"

if "%REPO_URL%"=="https://github.com/USER/REPO.git" (
  echo ERROR: edit REPO_URL at the top of this file to your repo URL first.
  pause
  exit /b 1
)

echo ============================================
echo  NCUSCC cpp code upload
echo ============================================
git init
git add .
git commit -m "NCUSCC cpp L1-L5 source + upload guide" || echo (nothing new to commit)
git branch -M main
git remote remove origin >nul 2>&1
git remote add origin %REPO_URL%
git push -u origin main
echo.
echo If prompted for password, use GitHub Personal Access Token (PAT), not account password.
pause
