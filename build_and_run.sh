set -e
set -x

cmake -B ./build
cmake --build ./build

./build/learning__qt_file_explorer
