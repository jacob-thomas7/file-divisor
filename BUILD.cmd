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

if not %errorlevel% == 0 (
    echo CMake exited with error code %errorlevel%. Build process stopped.
    exit /b %errorlevel%
)

:: Rename and copy to root directory for convinience
cd "build/Debug"
copy "divisor.exe" "../../divisor.exe" /Y
copy "divisor-gui.exe" "../../divisor-gui.exe" /Y
copy "divisor-tests.exe" "../../divisor-tests.exe" /Y
copy "file-divisor.dll" "../../file-divisor.dll" /Y
cd "../../"

:: Run the project
echo:
echo [36m-------------Run------------[0m
"divisor-tests"