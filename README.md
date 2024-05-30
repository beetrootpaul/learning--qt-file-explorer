# learning--qt-file-explorer

## Development setup

### macOS

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

### Windows

I do not have any Windows machine right know which I could use for setting up Qt development env.

To build this project on Windows, please take a look at macOS section above and try to replicate those steps since the steps should be similar (e.g. to have Qt 6 installed, to have `cmake` available, etc.)

## Notes

- I took a look at [official Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and applied
  *some* of those on this codebase here.
- Code formatting was performed by CLion IDE (with some configuration modifications applied by me to match aforementioned Google's guide a bit). It might result with some strange indentation, especially for long constructor signatures.
- I was thinking about adding a language switcher between English and Polish. This is why I prepared the GUI labels with wrapping `tr(…)` calls. In the end, I decided setting up the whole Qt Linguist workflow for such simple project would be a big time expense and reward would be non-satisfactory.
