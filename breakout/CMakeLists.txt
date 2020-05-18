cmake_minimum_required(VERSION 3.11)
project(breakout LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENABLE_MUSIC ON)
set(ENABLE_AUDIO ON)

#set(ASSIMP_BUILD_TESTS OFF)
#add_subdirectory(assimp)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(cmake/FindEmbed.cmake)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)

# find_library(dl REQUIRED)
find_package(GLFW3 QUIET)
if (NOT GLFW3_FOUND)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
endif()
message("GLFW3:" ${GLFW3_LIBRARY})

include_directories(${GLFW3_INCLUDE_DIR})

add_subdirectory(engine)

# find_package(Embed REQUIRED)
set(EMBED_SHADER_OUTPUTS "")
EMBED_TARGET(sprite_vert src/sprite.vert)
list(APPEND EMBED_SHADER_OUTPUTS ${EMBED_sprite_vert_OUTPUTS})
EMBED_TARGET(sprite_frag src/sprite.frag)
list(APPEND EMBED_SHADER_OUTPUTS ${EMBED_sprite_frag_OUTPUTS})

message("Shaders: " ${EMBED_SHADER_OUTPUTS})

add_library(shaders include/shaders.h ${EMBED_SHADER_OUTPUTS})

add_executable(breakout
    src/main.cpp
    src/breakout.cpp include/breakout.hpp
    src/ball_object.cpp include/ball_object.hpp
    src/sprite.vert src/sprite.frag
    src/particle.vert src/particle.frag
    src/post_processing.vert src/post_processing.frag
    src/breakout_effects.cpp include/breakout_effects.hpp
    src/power_up.cpp include/power_up.hpp
)

target_compile_definitions(breakout PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")
target_include_directories(breakout PUBLIC include)
target_include_directories(breakout PUBLIC engine/include)

# SDL2-static or SDL2
target_link_libraries(breakout PUBLIC engine Threads::Threads ${GLFW3_LIBRARY})
run_tidy(breakout)