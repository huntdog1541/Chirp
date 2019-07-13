set(chirplib_SOURCES 
  ./Build.cpp
  ./Compiler/Function.cpp
  ./Compiler/Object.cpp
  ./Compiler/Output.cpp
  ./Compiler/Scope.cpp
  ./Compiler/Variable.cpp
  ./Console/Commands.cpp
  ./Console/Debug.cpp
  ./Console/Keyboard.cpp
  ./Console/Menu.cpp
  ./Compiler/Analyser/Lexer.cpp
  ./Compiler/Analyser/Parser.cpp
  ./Compiler/Analyser/Syntax.cpp
  ./Compiler/Analyser/Tree.cpp
  ./Console/Log/Color.cpp
  ./Console/Log/Error.cpp
  ./Console/Log/Log.cpp)

set(chirp_SOURCES
    ./Chirp.cpp)

set(chirplib_INCLUDE_DIRS
    ./
    ./Compiler
    ./Compiler/Analyser
    ./Console
    ./Console/Log)

# Split the program into a library and an executable for testing purposes
add_library(chirplib SHARED ${chirplib_SOURCES})
target_compile_features(chirplib PUBLIC cxx_auto_type)
target_include_directories(chirplib PUBLIC ${chirplib_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_link_libraries(chirplib PUBLIC ${Boost_LIBRARIES})

add_executable(chirp ${chirp_SOURCES})
target_link_libraries(chirp PUBLIC chirplib)
