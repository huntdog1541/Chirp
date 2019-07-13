# this file is used to create a debuggable executable, not for debug itself
# you run this, and use it with gdb
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make all
