# learning--qt-file-explorer

## Development setup

- I was developing this project on macOS Sonoma 14.4.1, on a MacBook with Apple M1 Max CPU.
- I installed Qt6 with an [official installer of the open source version](https://www.qt.io/download-open-source)
    - during an installation process I picked `Qt` > `Qt 6.7.1` > `Desktop` and deselected everything else
    - in my case valid `CMAKE_PREFIX_PATH` (used below) was: `/Users/<username>/Qt6/6.7.1/macos/lib/cmake"`
- I was developing it in CLion 2024.1.1.
    - I had to add `-DCMAKE_PREFIX_PATH="<path_to_my_qt_cmake>"` in "CMake options" section of my CLion CMake settings
- I had CMake 3.29.3 installed with `brew install cmake`.

The set of commands to build and run this project in Debug mode (on macOS):

```sh
./cleanup.sh
CMAKE_PREFIX_PATH="<path_to_your_qt_cmake>" ./run_debug.sh
```

For Release mode please use `./run_release.sh`.

## Notes

- I took a look at [official Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and applied
  *some*
  of those on this codebase here.
