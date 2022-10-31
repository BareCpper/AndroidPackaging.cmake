# AndroidPackaging.cmake
Android APK Cmake build for NDK Activity and eventual native Services support.

## Prerequisites

1. Use [CMake](https://cmake.org/) to build your project.
2. Structure your project. See [Here](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html).
4. Use _modern_ CMake features like targets and properties. See [here](https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/) and [here](https://rix0r.nl/blog/2015/08/13/cmake-guide/).

# Using AndroidPackaging.cmake

We recommend using [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake) so you stay upto-date with the latest fixes and features.

Alternative, you may directly include `AndroidPackaging.cmake` in your project but we don't encourage this.

### Basic Usage

After [adding CPM.cmake](https://github.com/cpm-cmake/CPM.cmake#adding-cpm), add the following line to the `CMakeLists.txt`.

```cmake
include(CPM)
CPMAddPackage("gh:BareCpper/AndroidPackaging.cmake")
```


To use AndroidPackaging.cmake to package a Native NDK Activity into an `Android APK`:

```cmake  
apk_add_executable( MyActivity )
                       
target_sources( MyActivity
    PRIVATE
        main.cpp
)
```


# Advantages
- **Small and reusable** so can be added to any CMake build
- **Automatic update of buil-time variables** so code always has up-to date `Version.h` with no developer interaction.
- **Short Git-SHA available** so multiple-developers can generate unique build versions.
- **No re-configuring of CMake project necessary** as the build-time step will udpate version information for your build transparently.
- ...lots more to think about & list

# Limitations
- **CMake variables** are cached and do not reflect the current development version.
  <br/> :exclamation: This can affect version-name when using CPack Installers. See [Issue #1](https://github.com/BareCpper/Version.cmake/issues/1)
- **Only Git support is currently maintained** but we would love you to [raise an issue](https://github.com/BareCpper/Version.cmake/issues)