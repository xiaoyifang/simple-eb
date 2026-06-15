# simple-eb
Cross platform epwing library.  These files are extracted from libeb, a epwing library parser.

# how to build

## Linux / macOS

```sh
cmake .
cmake --build .
```

## Windows

### Prerequisites

- [CMake](https://cmake.org/download/) (≥ 3.22)
- [Visual Studio](https://visualstudio.microsoft.com/) (2019 or later, with "Desktop development with C++" workload)
- [vcpkg](https://github.com/microsoft/vcpkg) (for dependency management)

### Build with vcpkg

```sh
cmake -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake .
cmake --build .
```

Replace `[path-to-vcpkg]` with the actual path to your vcpkg installation.

### Build without vcpkg

If you prefer to manage dependencies manually, install [zlib](https://zlib.net/) first and make sure CMake can find it, then:

```sh
cmake .
cmake --build .
```

> **Note:** On Windows, you must run these commands from a **Visual Studio Developer Command Prompt** (e.g., "Developer Command Prompt for VS 2022") or use `-G` to specify the generator, such as:
> ```sh
> cmake -G "Visual Studio 17 2022" -A x64 .
> cmake --build .
> ```



