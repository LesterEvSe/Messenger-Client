# Messenger-Client
Description

# Linux build
## Requirements
To run the project you need to install the Qt5 and GMP
##### Qt install
###### Note: Replace 'name' with the name of your executable
1. Install Qt https://www.qt.io/download-qt-installer
2. Go to the download where our *.run* file is installed. Before we run it,
we need to give permission to run it, using the command ***chmod +x 'name'***
3. Запускаем наш файл ***./'name'***
4. During the installation you can not install CMake, Ninja, Qt Creatr components.
However, it is **necessary** to select *Desktop gcc 64* or *gcc 32* for Qt5,
otherwise the project will not build.

## Easy build and run via .sh files for Debian-type distributions
Skip this part now

## Build and run
###### Note: Most of the examples for Debian distributions
1. Need to install the GMP library: https://gmplib.org/  
or with commands in the console:  
Ubuntu/Debian/Linux Mint ***sudo apt-get install libgmp-dev***  
Fedora ***sudo dnf install gmp-devel***  
CentOS и RHEL ***sudo yum install gmp-devel***  
Arch Linux ***sudo pacman -S gmp***  
2. Install compiler for C++ with the command ***sudo apt install g++***
3. Install build system ***sudo apt install cmake***
4. To build a project, you need to make a "build" directory 
in the project folder with the command ***mkdir build***
5. Then move into it with the command ***cd build*** 
6. Next, you need to run ***cmake ..*** command inside "build" directory. 
7. Finally, use the ***make*** command to compile, link the project, and create an executable. 
8. Now you can run the application with the ***./Client*** command.


# Windows build
