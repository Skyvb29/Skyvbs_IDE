@echo off
title Skyvb IDE Builder

echo ============================================
echo        Building SKYVB's IDE       
echo ============================================

REM -----------------------------------------------
REM AUTO-DETECT VS CODE’S MINGW (NEWER GCC)
REM -----------------------------------------------
for /f "delims=" %%i in ('where g++') do (
    echo Found compiler: %%i

    REM Pick the first (newest) MinGW found
    set "GPP=%%i"
    goto compilerFound
)

:compilerFound
echo Using compiler: %GPP%
echo.

REM -----------------------------------------------
REM Create user folder if missing
REM -----------------------------------------------
if not exist user (
    echo Creating user folder...
    mkdir user
)

REM -----------------------------------------------
REM Compile ALL source files from src/
REM -----------------------------------------------
echo Compiling Skyvb IDE...

"%GPP%" src\*.cpp -o Skyvb_IDE.exe

IF %ERRORLEVEL% NEQ 0 (
    echo.
    echo ❌ Compilation failed!
    echo Check errors above.
    echo ============================================
    pause
    exit /b
)

echo.
echo ✅ Compilation successful!
echo ============================================

REM -----------------------------------------------
REM ASK USER WHETHER TO RUN IDE NOW
REM -----------------------------------------------
set /p runChoice=Do you want to run Skyvb IDE now? (y/n): 

if /I "%runChoice%"=="y" (
    echo.
    echo Running Skyvb IDE...
    echo ============================================
    Skyvb_IDE.exe
) else (
    echo Not running. Build complete.
)

echo.
pause
