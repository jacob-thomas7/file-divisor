@echo off
:: If CMake files have not been generated, generate them 
if not exist "build"\ (
    mkdir "build"
    cmake -S "." -B "build"
)

:: Use CMake to build
cmake --build "build"
:: Copy to root directory for convinience
cd "build/Debug"
copy "FileDivisor.exe" "../../FileDivisor.exe" /Y
cd "../../"
:: Run the project
"FileDivisor.exe"