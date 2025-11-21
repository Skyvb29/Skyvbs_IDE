@echo off
cls
echo Compiling Skyvb IDE...
echo starting_id.....
g++ *.cpp -o Skyvb_IDE

if %errorlevel% neq 0 (
    echo ? Compilation failed!
    pause
    exit /b
)

echo ? Compilation successful!
echo ------------------------------
Skyvb_IDE.exe
pause
