@echo off
chcp 65001 >nul
setlocal
set "REPO_URL=https://github.com/USER/REPO.git"

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
