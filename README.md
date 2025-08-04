# File Divisor 
![C++ Badge](https://img.shields.io/badge/Language-C++-F34B7D)
![CMake Badge](https://img.shields.io/badge/Build-CMake-darkblue)
![Crossplatform Badge](https://img.shields.io/badge/OS-Cross&#8211;Platform-888888)
![Doxygen Badge](https://img.shields.io/badge/Documentation-Doxygen-green")
![MIT Badge](https://img.shields.io/badge/License-MIT-yellow.svg)

A C++ library and a File Explorer alternative which support organizing and accessing files by
categories beyond regular system directories.

## Description
File Divisor is based on the idea that users do not always want their files organized the same
way all the time. It could be frustrating if, for example, they originally decided to sort their
photographs into subdirectories based on their subject, but one day they decide they want to
see all photographs taken in a certain timeframe. In a traditional file system, they would have
to manually go through each subdirectory and check the date of each file.

With File Divisor, this process is taken care of automatically, quickly retrieving all the files
that match the specified categories, or "divisors." Multiple divisors, sorting orders, and filters
may be applied simultaneously, allowing users to efficiently find the files they need.

## Getting Started
### Library

### Program
This project can be built with
[<img alt="CMake Logo" src="https://upload.wikimedia.org/wikipedia/commons/e/ef/CMake_logo.svg" height="15px"/> CMake](https://cmake.org/) 
version 3.12 or greater.

#### Windows
Simply run the provided <code>build.cmd</code> file to compile the code. The resulting executables
can now be found in the root directory. They depend on <code>file-divisor.dll</code>.

#### Mac and Linux
Run <code>chmod +x ./build.sh</code> then <code>./build.sh</code> to compile the code. The resulting
executables can now be found in the root directory.

## System Requirements
![Windows Supported](https://custom-icon-badges.demolab.com/badge/Windows-Supported-42BA2D?logo=windows11&logoColor=white&labelColor=0078D6)
![Linux Supported](https://img.shields.io/badge/Linux-Supported-42BA2D?logo=linux&logoColor=black&labelColor=FCC624)
![macOS Untested](https://img.shields.io/badge/macOS-Untested-F5D902?logo=apple&logoColor=F0F0F0&labelColor=000000)

## Program Usage
File Divisor's core library is available here for use within C++ programs. This repository also
provides a command-line utility—similar to <code>ls</code>—and a GUI program—much like File
Explorer—but with the sorting and filtering capabilities of File Divisor.

### Library
See [Documentation](#documentation).

### Command Line

### Graphical Interface

## Documentation
File Divisor's core library is fully documented by [Doxygen](https://www.doxygen.nl/). Install
Doxygen, then run it in the repository's root directory. It will automatically create documentation
based on the provided <code>doxyfile</code>

Alternatively, the header files found in <code>source/library/include</code> provide documentation
comments in the form of <code>//! Documentation Comment</code>.

## License
Copyright © 2025 [Jacob Thomas](https://github.com/jacob-thomas7).

This repository is released under the [MIT License](https://opensource.org/licenses/MIT).