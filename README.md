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

### Create a New CMake Project

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

## Configure vcpkg

1. Check vcpkg environment variable

    - Go to `Tools` > `Command Line` > `Developer Command Prompt`.
    - In Command Prompt, type:
    ```bash
    echo %VCPKG_ROOT%
    ```
    - You should get "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\vcpkg" path as response if vcpkg is installed successfully.

**Note:** The `VCPKG_ROOT` environment variable will only be visible in the Visual Studio Environment Command prompt.
![Visual Studio Command Prompt](images/vcpkg_path.jpg)

**Note:** If you have vcpkg cloned from github use following command to set the environment variable. if Visual Studio vcpkg is already installed it will have `VCPKG_ROOT` environment variable name by default Therefor we need to use a different environment variable name.
    ```bash
    set USER_VCPKG_ROOT="C:\path\to\vcpkg"
    set PATH=%VCPKG_ROOT%;%PATH%
    ```

2. Generate a manifest file and add dependencies

    - In Command Prompt, type the following command to create a vcpkg manifest file (`vcpkg.json`) This will add `vcpkg.json` file and a `vcpkg-configuration.json` file in the project's directory:
    ```bash
    vcpkg new --application
    ```
    - Add the `wxwidgets` `opengl` packages as a dependencies by typing following in the Command Prompt:
    ```bash
    vcpkg add port wxwidgets opengl
    ```
    Now the manifest file `vcpkg.json` should look like this:
    ```bash
    {
    "dependencies": [
        "fmt",
        "opengl",
        "wxwidgets"
        ]
    }
    ```

## Configure CMake files.

1. Configure the `CMakePresets.json` file for letting vcpkg to provide packages to CMake when configuring and building the project:

    - Edit `CMakePresets.json` as follows,
    in the json, under the "cacheVariables", add following line, If you are using the vcpkg that comes with Visual Studio.
    ```bash
    "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    ```
    or usimng custom vcpkg Replace `<VCPKG_Path>` with the path to your vcpkg directory
    ```bash
    "CMAKE_TOOLCHAIN_FILE": "<VCPKG_Path>/scripts/buildsystems/vcpkg.cmake"
    ```

    - The edited `CMakePresets.json` file should look lke this:
    ```bash
    {
    "version": 3,
    "configurePresets": [
        {
        "name": "windows-base",
        "hidden": true,
        "generator": "Ninja",
        "binaryDir": "${sourceDir}/out/build/${presetName}",
        "installDir": "${sourceDir}/out/install/${presetName}",
        "cacheVariables": {
            "CMAKE_C_COMPILER": "cl.exe",
            "CMAKE_CXX_COMPILER": "cl.exe",
            "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        },
        "condition": {
            "type": "equals",
            "lhs": "${hostSystemName}",
            "rhs": "Windows"
        }
        },
        {
        "name": "x64-debug",
        "displayName": "x64 Debug",
        "inherits": "windows-base",
        "architecture": {
            "value": "x64",
            "strategy": "external"
        },
        "cacheVariables": {
            "CMAKE_BUILD_TYPE": "Debug"
        }
        },
        {
        "name": "x64-release",
        "displayName": "x64 Release",
        "inherits": "x64-debug",
        "cacheVariables": {
            "CMAKE_BUILD_TYPE": "Release"
        }
        },
        {
        "name": "x86-debug",
        "displayName": "x86 Debug",
        "inherits": "windows-base",
        "architecture": {
            "value": "x86",
            "strategy": "external"
        },
        "cacheVariables": {
            "CMAKE_BUILD_TYPE": "Debug"
        }
        },
        {
        "name": "x86-release",
        "displayName": "x86 Release",
        "inherits": "x86-debug",
        "cacheVariables": {
            "CMAKE_BUILD_TYPE": "Release"
        }
        },
        {
        "name": "linux-debug",
        "displayName": "Linux Debug",
        "generator": "Ninja",
        "binaryDir": "${sourceDir}/out/build/${presetName}",
        "installDir": "${sourceDir}/out/install/${presetName}",
        "cacheVariables": {
            "CMAKE_BUILD_TYPE": "Debug",
            "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        },
        "condition": {
            "type": "equals",
            "lhs": "${hostSystemName}",
            "rhs": "Linux"
        },
        "vendor": {
            "microsoft.com/VisualStudioRemoteSettings/CMake/1.0": {
            "sourceDir": "$env{HOME}/.vs/$ms{projectDirName}"
            }
        }
        },
        {
        "name": "macos-debug",
        "displayName": "macOS Debug",
        "generator": "Ninja",
        "binaryDir": "${sourceDir}/out/build/${presetName}",
        "installDir": "${sourceDir}/out/install/${presetName}",
        "cacheVariables": {
            "CMAKE_BUILD_TYPE": "Debug",
            "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        },
        "condition": {
            "type": "equals",
            "lhs": "${hostSystemName}",
            "rhs": "Darwin"
        },
        "vendor": {
            "microsoft.com/VisualStudioRemoteSettings/CMake/1.0": {
            "sourceDir": "$env{HOME}/.vs/$ms{projectDirName}"
            }
        }
        }
    ]
    }
    ```












