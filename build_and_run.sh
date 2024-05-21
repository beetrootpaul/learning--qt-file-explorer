set -e
set -x

cmake .
cmake --build .
./learning__qt_file_explorer
