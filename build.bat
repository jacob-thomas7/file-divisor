@echo off
:: If CMake files have not been generated, generate them 
if not exist "build"\ (
    echo:
    echo [36m----Generate CMake Files----[0m
    mkdir "build"
    cmake -S "." -B "build"
)

:: Use CMake to build
echo:
echo [36m------------Build-----------[0m
cmake --build "build"

:: Rename and copy to root directory for convinience
cd "build/Debug"
copy "FileDivisor.exe" "../../File Divisor.exe" /Y
copy "FileDivisor_GUI.exe" "../../File Divisor GUI.exe" /Y
cd "../../"

:: Run the project
echo:
echo [36m-------------Run------------[0m
"File Divisor.exe"