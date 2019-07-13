cmake_minimum_required(VERSION 3.0)
project(chirp)

find_package(Boost COMPONENTS program_options REQUIRED)
message(STATUS "Boost included from ${Boost_INCLUDE_DIR}")

add_subdirectory(Source)
#add_subdirectory(Test)
