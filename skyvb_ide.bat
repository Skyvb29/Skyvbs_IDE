@echo off
title Skyvb IDE Builder

echo ===============================
echo    Building SKYVB's IDE
echo ===============================

REM Make sure user folder exists
if not exist user (
    mkdir user
)

REM Compile all cpp files from src/
echo Compiling Skyvb IDE...
g++ src\*.cpp -o Skyvb_IDE.exe

IF %ERRORLEVEL% NEQ 0 (
    echo.
    echo ❌ Compilation failed!
    pause
    exit /b
)

echo.
echo ✅ Build successful!

REM Ask user if they want to run the IDE
set /p runChoice=Run IDE now? (y/n): 

if /I "%runChoice%"=="y" (
    echo.
    echo ===============================
    echo Running Skyvb IDE...
    echo ===============================
    Skyvb_IDE.exe
)

echo.
pause
