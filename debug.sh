# this file is used to create a debuggable executable, not for debug itself
# you run this, and use it with gdb
g++ -g -I ./Source/ -I ./Source/Console -I ./Source/Console/Log -I ./Source/Compiler -I ./Source/Compiler/Analyser ./Source/*.cpp ./Source/Console/*.cpp ./Source/Console/Log/*.cpp ./Source/Compiler/*.cpp ./Source/Compiler/Analyser/*.cpp -std=c++11 -o exec.out