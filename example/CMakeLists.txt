cmake_minimum_required(VERSION 3.8)
project(LearnOpenGL LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(assimp)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_library(dl REQUIRED)
find_package(GLFW3 REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)


include_directories(${GLFW_INCLUDE_DIRS})
include_directories(include/glm)
include_directories(include)

message("GLFW3:" ${GLFW_LIBRARIES})

add_library(glad include/glad/glad.c)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)

add_executable(create_window
    creating-window.cpp
    Shader.cpp Shader.hpp
    Mesh.hpp Mesh.cpp
    colours.vs colours.fs
    Camera.cpp Camera.hpp
    stb_image.cpp stb_image.h)
target_include_directories(create_window PUBLIC include)
target_link_libraries(create_window dl glad assimp OpenGL::GL Threads::Threads ${GLFW_LIBRARIES})
