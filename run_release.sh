set -e

cmake -D CMAKE_BUILD_TYPE=Release -B ./build_release
cmake --build ./build_release

./build_release/learning__qt_file_explorer
