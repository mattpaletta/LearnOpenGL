cmake_minimum_required(VERSION 3.8)
project(breakout LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(ASSIMP_BUILD_TESTS OFF)
#add_subdirectory(assimp)
include(cmake/FindEmbed.cmake)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_library(dl REQUIRED)
find_package(GLFW3 REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
message("GLFW3:" ${GLFW_LIBRARIES})

include_directories(${GLFW_INCLUDE_DIRS})
add_subdirectory(engine)

# find_package(Embed REQUIRED)
set(EMBED_SHADER_OUTPUTS "")
EMBED_TARGET(sprite_vert src/sprite.vert)
list(APPEND EMBED_SHADER_OUTPUTS ${EMBED_sprite_vert_OUTPUTS})
EMBED_TARGET(sprite_frag src/sprite.frag)
list(APPEND EMBED_SHADER_OUTPUTS ${EMBED_sprite_frag_OUTPUTS})

message("Shaders: " ${EMBED_SHADER_OUTPUTS})

add_library(shaders include/shaders.h ${EMBED_SHADER_OUTPUTS})

# Include the engine as part of the game
get_property(ENGINE_SRC GLOBAL PROPERTY ENGINE_SRC)
get_property(ENGINE_DEPS GLOBAL PROPERTY ENGINE_DEPS)

add_executable(breakout
    src/main.cpp
    src/breakout.cpp
    include/breakout.hpp
    src/sprite.vert
    src/sprite.frag
	${ENGINE_SRC}
)

target_compile_definitions(breakout PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")
target_include_directories(breakout PUBLIC include)
target_include_directories(breakout PUBLIC engine/include)

target_link_libraries(breakout ${ENGINE_DEPS} dl Threads::Threads ${GLFW_LIBRARIES})
