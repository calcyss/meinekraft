cmake_minimum_required(VERSION 3.7)
project(meinekraft)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE src_files src/*.cpp)
include_directories(include)

FIND_PACKAGE(OpenGL)
FIND_PACKAGE(GLEW)

add_executable(meinekraft ${src_files})
target_link_libraries(meinekraft ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})