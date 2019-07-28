

set(chirplib_SOURCES
    ./cli/cli.cpp
    ./cli/log.cpp
    ./parser/lexer.cpp
    ./parser/parser.cpp
    ./parser/syntax.cpp
    ./parser/token.cpp
    ./parser/tree.cpp
    ./gen/gen_asm.cpp
    ./gen/gen_ir.cpp
    ./gen/ir.cpp
    ./gen/asm.cpp
    ./build.cpp
    ./chirp.cpp
    ./error.cpp
    ./preprocessor.cpp)

set(chirp_SOURCES
    ./chirp.cpp)

set(chirplib_INCLUDE_DIRS
    ./
    ./drawing
    ./cli
    ./gen
    ./parser)

# Split the program into a library and an executable for testing purposes
add_library(chirplib SHARED ${chirplib_SOURCES})
target_compile_features(chirplib PUBLIC cxx_auto_type cxx_std_14) 
target_include_directories(chirplib PUBLIC ${chirplib_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_link_libraries(chirplib PUBLIC ${Boost_LIBRARIES})

add_executable(chirp ${chirp_SOURCES})
target_link_libraries(chirp PUBLIC chirplib)
