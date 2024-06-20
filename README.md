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
![Visual Studio Installer](images/visual_studio_installer.jpg)

> **Note:** Alternatively vcpkg can be cloned directly from the GitHub vcpkg repository using following steps.

    #### 1. Clone the repository
    ```bash
    git clone https://github.com/microsoft/vcpkg.git
    ```

    #### 2. Run the bootstrap script
    ```bash
    cd vcpkg && bootstrap-vcpkg.bat
    ```





