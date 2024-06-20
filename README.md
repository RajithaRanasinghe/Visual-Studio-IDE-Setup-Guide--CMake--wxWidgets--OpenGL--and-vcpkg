# Visual Studio IDE Setup Guide: CMake, wxWidgets, OpenGL, and vcpkg
 This repository provides instructions on how to set up the Visual Studio IDE for C++ development using CMake, wxWidgets, OpenGL, and the Visual C++ Package Manager (vcpkg).

## Setting up Prerequisites

Before you start, ensure you have the following installed:

###  Download and Install Git

#### Windows

1. Download the Git installer from the [official Git website](https://git-scm.com/downloads).
2. Run the installer and follow the setup instructions. Use the default settings unless you have specific requirements.

#### macOS

1. Install Git using Homebrew. If you don't have Homebrew installed, first install it by running:

   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

### Visual Studio, C++ with vcpkg

- Visual Studio 2022 (or later) with the "Desktop development with C++" workload [official website](https://visualstudio.microsoft.com/downloads/).
    In the installation details make sure following are selected,
    - C++ CMake tools for Windows
    - vcpkg package manager (Visual Studio 2022 comes with built-in support for vcpkg, simplifying the process of installing and managing C++ libraries.)

vcpkg is an open-source C++ library manager that helps you manage library dependencies across different platforms. It simplifies the process of finding, installing, and integrating libraries into your C++ projects. Developed by Microsoft, vcpkg is designed to work seamlessly with CMake.

![Visual Studio Installer](images/visual_studio_installer.jpg)

**Note:** Alternatively vcpkg can be cloned directly from the GitHub vcpkg repository using following steps.

1. Clone the repository

    ```bash
    git clone https://github.com/microsoft/vcpkg.git
    ```

2. Run the bootstrap script

    ```bash
    cd vcpkg && bootstrap-vcpkg.bat
    ```

###  Download and Install CMake

CMake is an open-source, cross-platform family of tools designed to build, test, and package software. It controls the software compilation process using simple platform and compiler-independent configuration files, and generates native makefiles and workspaces that can be used in the compiler environment of your choice.

Download the CMake installer from the [official CMake website](https://cmake.org/download/).


## Set Up Visual Studio Project

### Create a New Project

1. **Create a New CMake Project**:
   - Go to `File` > `New` > `Project`.
   - Select `Create a new project`.
   - Select `CMake Project` and click `Next`.
   - Name your project ("CMake_wxWidgets_openGL") and click `Create`.

This will create a project with following project files.

    - CMakeLists.txt
    - CMakePresets.json
    - CMake_wxWidgets_openGL.cpp
    - CMake_wxWidgets_openGL.h

![Visual Studio IDE with fresh CMake project](images/vs_ide_1.jpg)





