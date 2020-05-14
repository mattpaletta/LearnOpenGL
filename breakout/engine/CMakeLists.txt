cmake_minimum_required(VERSION 3.8)
project(breakout LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(glad include/glad/glad.c)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)

add_library(stb_image include/stb_image/stb_image.cpp include/stb_image/stb_image.h)

file(GLOB SRC_FILES src/*.cpp)
file(GLOB INC_FILES include/engine/*.hpp include/engine/*.h)

set(ENGINE_SRC ${SRC_FILES} ${INC_FILES})
set(ENGINE_DEPS glad OpenGL::GL stb_image)

add_library(engine ${ENGINE_SRC})
target_include_directories(engine PUBLIC include)
target_link_libraries(engine ${ENGINE_DEPS})
