cmake_minimum_required(VERSION 3.0)
project(meinekraft)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE src_files src/*.cpp)
include_directories(include)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)

add_executable(meinekraft ${src_files})
target_link_libraries(meinekraft ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW3_LIBRARIES})
add_custom_command(TARGET meinekraft POST_BUILD COMMAND yes | cp -rf ${CMAKE_SOURCE_DIR}/content/. ${CMAKE_CURRENT_BINARY_DIR}/)