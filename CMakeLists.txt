cmake_minimum_required(VERSION 3.0)
project(chirp)

set(chirp_SOURCES
  "${chirp_SOURCE_DIR}/Source/Build.cpp"
  "${chirp_SOURCE_DIR}/Source/Chirp.cpp"
  "${chirp_SOURCE_DIR}/Source/Compiler/Function.cpp"
  "${chirp_SOURCE_DIR}/Source/Compiler/Object.cpp"
  "${chirp_SOURCE_DIR}/Source/Compiler/Output.cpp"
  "${chirp_SOURCE_DIR}/Source/Compiler/Scope.cpp"
  "${chirp_SOURCE_DIR}/Source/Compiler/Variable.cpp"
  "${chirp_SOURCE_DIR}/Source/Console/Commands.cpp"
  "${chirp_SOURCE_DIR}/Source/Console/Debug.cpp"
  "${chirp_SOURCE_DIR}/Source/Console/Keyboard.cpp"
  "${chirp_SOURCE_DIR}/Source/Console/Menu.cpp"
  "${chirp_SOURCE_DIR}/Source/Compiler/Analyser/Lexer.cpp"
  "${chirp_SOURCE_DIR}/Source/Compiler/Analyser/Parser.cpp"
  "${chirp_SOURCE_DIR}/Source/Compiler/Analyser/Syntax.cpp"
  "${chirp_SOURCE_DIR}/Source/Compiler/Analyser/Tree.cpp"
  "${chirp_SOURCE_DIR}/Source/Console/Log/Color.cpp"
  "${chirp_SOURCE_DIR}/Source/Console/Log/Error.cpp"
  "${chirp_SOURCE_DIR}/Source/Console/Log/Log.cpp")
set(chirp_INCLUDE_DIRS
  "${chirp_SOURCE_DIR}/Source"
  "${chirp_SOURCE_DIR}/Source/Compiler"
  "${chirp_SOURCE_DIR}/Source/Compiler/Analyser"
  "${chirp_SOURCE_DIR}/Source/Console"
  "${chirp_SOURCE_DIR}/Source/Console/Log")

add_executable(chirp ${chirp_SOURCES})
target_include_directories(chirp PUBLIC ${chirp_INCLUDE_DIRS})
