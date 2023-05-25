# Messenger-Client
Client application messenger using library Qt5 and GMP library.
Designed for network communication with other users.
Messages are encrypted using a 2048-bit RSA key, as well as stored on the server.  
Read **Linux build** for build on Linux OS.

# Linux build
## Requirements
To run the project you need to install the Qt5 and GMP
### Qt install. Install Qt in the /home directory, otherwise the paths to the Qt files will not be found
###### Note: Replace 'name' with the name of your executable
1. Install Qt https://www.qt.io/download-qt-installer
2. Go to the download where our *.run* file is installed. Before we run it,
we need to give permission to run it, using the command ***chmod +x 'name'***
3. Run our file ***./'name'***
4. During the installation you can not install CMake, Ninja, Qt Creator components.
However, it is **necessary** to select *Desktop gcc 64* or *gcc 32* for Qt5,
otherwise the project will not build.
###### Note: The gmp library is installed through the .sh files in the next section or through a link in **Build and run** section

## Easy build and run via .sh files
1. Run the console from the **tools** directory.
2. Install the necessary programs and build the project, using the ***bash build.sh*** command.
3. You can run the messenger with the ***bash messenger.sh*** command.

## Build and run
1. Need to install the GMP library: https://gmplib.org/ or with commands in the console:  
* Ubuntu, Debian and Linux Mint ***sudo apt-get install libgmp-dev***  
* Fedora ***sudo dnf install gmp-devel***  
* CentOS and RHEL ***sudo yum install gmp-devel***  
* Arch Linux ***sudo pacman -S gmp***  
2. Install compiler for C++ and build system with the commands
* Ubuntu, Debian and Linux Mint  
  ***sudo apt-get update  
  sudo apt-get install g++ cmake***  
* Fedora  
  ***sudo dnf install gcc-c++ cmake***  
* CentOS and RHEL  
  ***sudo yum install gcc-c++ cmake***  
* Arch Linux  
  ***sudo pacman -S gcc cmake***  
3. To build a project, you need to make a "build" directory 
in the project folder with the command ***mkdir build***
4. Then move into it with the command ***cd build*** 
5. Next, you need to run ***cmake ..*** command inside "build" directory. 
6. Finally, use the ***make*** command to compile, link the project, and create an executable. 
7. Now you can run the application with the ***./Client*** command.
