@echo off
setlocal

REM Check if folder name is provided
if "%1"=="" (
    echo Please provide the folder name as a parameter.
    exit /b 1
)

REM Set the folder name
set FOLDER=%1

REM Check if the folder exists
if not exist "%FOLDER%" (
    echo The folder "%FOLDER%" does not exist.
    exit /b 1
)

REM Compile the C++ file in the specified folder
g++ -std=c++23 -o "%FOLDER%\main.exe" "%FOLDER%\main.cpp"

REM Check if the compilation was successful
if errorlevel 1 (
    echo Compilation failed.
    exit /b 1
)

echo Compilation successful. The executable is "%FOLDER%\main.exe".
endlocal
