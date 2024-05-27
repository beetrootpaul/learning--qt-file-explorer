# learning--qt-file-explorer

## Development setup

- I was developing this project on macOS Sonoma 14.4.1, on a MacBook with Apple M1 Max CPU.
- I installed Qt6 with `brew install qt`.
- I was developing it in CLion 2024.1.1.
- I had CMake 3.29.3 installed with `brew install cmake`.

The set of commands to build and run this project in Debug mode (on macOS):

```sh
./cleanup.sh
./run_debug.sh
```

For Release mode please use `./run_release.sh`.

## Notes

- I took a look at [official Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and applied
  *some*
  of those on this codebase here.