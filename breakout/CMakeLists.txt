cmake_minimum_required(VERSION 3.11)
project(breakout LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(BUILD_STATIC_EXECUTABLES)
	set(CMAKE_EXE_LINKER_FLAGS -static)
	set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
	set(CMAKE_EXE_LINK_DYNAMIC_C_FLAGS)       # remove -Wl,-Bdynamic
	set(CMAKE_EXE_LINK_DYNAMIC_CXX_FLAGS)
	set(CMAKE_SHARED_LIBRARY_C_FLAGS)         # remove -fPIC
	set(CMAKE_SHARED_LIBRARY_CXX_FLAGS)
	set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)    # remove -rdynamic
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
	# Maybe this works as well, haven't tried yet.
	# set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)
elseif(BUILD_SHARED_EXECUTABLES)
	# Set RPATH to use for installed targets; append linker search path
	set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LOFAR_LIBDIR}")
	set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif(BUILD_STATIC_EXECUTABLES)

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

set(ENABLE_AUDIO ON)
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