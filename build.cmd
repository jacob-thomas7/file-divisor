@echo off
:: Generate CMake files
if not exist "build"\ (
    mkdir "build"
)
if not exist "build/windows"\ (
    mkdir "build/windows"
)
echo:
echo [36m----Generate CMake Files----[0m
cmake -S "." -B "build/windows"

:: Use CMake to build
echo:
echo [36m------------Build-----------[0m
cmake --build "build/windows"

if not %errorlevel% == 0 (
    echo CMake exited with error code %errorlevel%. Build process stopped.
    exit /b %errorlevel%
)

:: Rename and copy to root directory for convinience
cd "build/windows/Debug"
copy "divisor.exe" "../../../divisor.exe" /Y
copy "divisor-gui.exe" "../../../divisor-gui.exe" /Y
copy "divisor-tests.exe" "../../../divisor-tests.exe" /Y
copy "file-divisor.dll" "../../../file-divisor.dll" /Y
cd "../../../"

:: Run the project
echo:
echo [36m-------------Run------------[0m
"divisor-tests"