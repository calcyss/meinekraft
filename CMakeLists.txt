cmake_minimum_required(VERSION 3.7)
project(meinekraft)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE src_files src/*.cpp)
include_directories(include)

add_executable(meinekraft ${src_files})