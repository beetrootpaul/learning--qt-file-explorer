set -e

cmake -D CMAKE_BUILD_TYPE=Debug -B ./build_debug
cmake --build ./build_debug

./build_debug/learning__qt_file_explorer
