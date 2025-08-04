# Generate CMake files
printf "\n[36m----Generate CMake Files----[0m\n"
if [ ! -d "build" ]; then
    mkdir "build"
fi
if [ ! -d "build/linux" ]; then
    mkdir "build/linux"
fi
cmake -S "." -B "build/linux"

# Use CMake to build
printf "\n[36m------------Build-----------[0m\n"
cmake --build "build/linux"

if [ ! $? -eq 0 ]; then
    printf "\nCMake exited with error code $?. Build process stopped.\n"
    exit $?
fi

# Rename and copy to root directory for convinience
cp build/linux/divisor build/linux/divisor-tests build/linux/libfile-divisor.so ./

# Run the project
"./divisor-tests"