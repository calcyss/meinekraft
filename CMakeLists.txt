cmake_minimum_required(VERSION 3.7)
project(meinekraft)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE src_files src/*.cpp)
include_directories(include)

find_package(OpenGL REQUIRED)

set(corelibs ${OPENGL_LIBRARY})
set(coreincludes ${OPENGL_INCLUDE_DIR})


add_executable(meinekraft ${src_files})
target_link_libraries(meinekraft ${corelibs})
target_include_directories(meinekraft PUBLIC ${coreincludes})
