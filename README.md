# learning--qt-file-explorer

## Development setup

- I was developing this project on macOS Sonoma 14.4.1, on a MacBook with Apple M1 Max CPU.
- I installed Qt6 with `brew install qt`.
- I was developing it in CLion 2024.1.1.
- I had CMake 3.29.3 installed with `brew install cmake`.

The set of commands to build and run this project (on macOS):
```sh
./cleanup.sh
./build_and_run.sh
```

NOTE: The CLion runs the project in a different manner than the commands above and seems to have issues because of two ways of doing it (`Cannot generate into …/learning--qt-file-explorer It was created with incompatible generator 'Unix Makefiles'`). With a lack of my know-how in the area, I decided to use the command line approach only.
