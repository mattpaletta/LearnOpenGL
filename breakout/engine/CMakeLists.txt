cmake_minimum_required(VERSION 3.8)
project(breakout LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(glad include/glad/glad.c)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)

include(FetchContent)

function(fetch_extern name repo tag)
	FetchContent_Declare(
		${name}
		GIT_REPOSITORY ${repo}
		GIT_TAG ${tag}
	)
	FetchContent_GetProperties(${name})
	if (NOT ${name}_POPULATED)
		FetchContent_Populate(${name})
	endif()
	set(source_dir ${${name}_SOURCE_DIR})
	set(binary_dir ${${name}_BINARY_DIR})
	add_subdirectory(${source_dir} ${binary_dir} EXCLUDE_FROM_ALL)
	
	# Store source & binary dir as global variables
	set_property(GLOBAL PROPERTY ${name}_SOURCE_DIR ${source_dir})
	set_property(GLOBAL PROPERTY ${name}_BINARY_DIR ${binary_dir})
endfunction(fetch_extern)

function(fetch_extern_url name url)
	FetchContent_Declare(
		${name}
		URL ${url}
	)
	FetchContent_GetProperties(${name})
	if (NOT ${name}_POPULATED)
		FetchContent_Populate(${name})
	endif()
	set(source_dir ${${name}_SOURCE_DIR})
	set(binary_dir ${${name}_BINARY_DIR})
#	add_subdirectory(${source_dir} ${binary_dir} EXCLUDE_FROM_ALL)
	
	# Store source & binary dir as global variables
	set_property(GLOBAL PROPERTY ${name}_SOURCE_DIR ${source_dir})
	set_property(GLOBAL PROPERTY ${name}_BINARY_DIR ${binary_dir})
endfunction(fetch_extern_url)

#<LANG>_CLANG_TIDY  can be set with cache variable CMAKE_<LANG>_CLANG_TIDY
#<LANG>_CPPCHECK can be set with cache variable CMAKE_<LANG>_CPPCHECK
#<LANG>_CPPLINT can be set with cache variable CMAKE_<LANG>_CPPLINT
#<LANG>_INCLUDE_WHAT_YOU_USE  can be set with cache variable CMAKE_<LANG>_INCLUDE_WHAT_YOU_USE
#LINK_WHAT_YOU_USE can be set with cache variable CMAKE_LINK_WHAT_YOU_USE

set(ENABLE_CLANG_TIDY ON)

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
    list(
        APPEND CMAKE_CXX_CPPCHECK 
            "--enable=warning"
            "--inconclusive"
            "--force" 
            "--inline-suppr"
            "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
    )
endif()

if (ENABLE_CLANG_TIDY)
	find_program(CLANG_TIDY_EXE NAMES "clang-tidy" DOC "Path to clang-tidy executable" ) 
	if(NOT CLANG_TIDY_EXE) 
		message(STATUS "clang-tidy not found.") 
	else() 
		message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}") 
		set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*")
	endif()
endif()

function (run_tidy target_name)
	if(CLANG_TIDY_EXE) 
		set_target_properties( target_name PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}" ) 
	endif()
endfunction()

set(ENABLE_SDL OFF)

# Add audio library
if (ENABLE_SDL)
	fetch_extern(sdl https://github.com/SDL-mirror/SDL release-2.0.12)
	set(SDL_STATIC ON)
	set(SDL_SHARED ON)
	add_definitions("-DSDL_MAIN_HANDLED")
	get_property(sdl_SOURCE_DIR GLOBAL PROPERTY sdl_SOURCE_DIR)
	set(SDL2_LIBRARY SDL2-static)
	set(SDL2_INCLUDE_DIR ${sdl_SOURCE_DIR}/include)
endif()

if (ENABLE_AUDIO)
	# Requires SNDFile
	set(BUILD_PROGRAMS OFF)
	set(BUILD_EXAMPLES OFF)
	set(ENABLE_CPACK OFF)
	set(BUILD_TESTING OFF)
	set(BUILD_REGTEST OFF)
	set(ENABLE_PACKAGE_CONFIG OFF)
	fetch_extern(sndfile https://github.com/erikd/libsndfile 06ebde50e362966184790c1b53512438a4385d47)

	set(ALSOFT_EXAMPLES OFF)
	set(ALSOFT_UTILS ON)
	set(ALSOFT_INSTALL OFF)
	set(ALSOFT_BUILD_ROUTER ON)

	fetch_extern(openal https://github.com/kcat/openal-soft openal-soft-1.20.1)
	get_property(openal_SOURCE_DIR GLOBAL PROPERTY openal_SOURCE_DIR)
	set(OpenAl_INCLUDE_DIRECTORIES ${openal_SOURCE_DIR}/include)
	# SndFile::sndfile
	set(OpenAl_DEPS OpenAL sndfile)
endif()

fetch_extern(freetype2 https://github.com/aseprite/freetype2 VER-2-10-0)

add_library(stb_image include/stb_image/stb_image.cpp include/stb_image/stb_image.h)

file(GLOB SRC_FILES src/*.cpp)
file(GLOB INC_FILES include/engine/*.hpp include/engine/*.h)

set(ENGINE_SRC ${SRC_FILES} ${INC_FILES})
set(ENGINE_DEPS glad OpenGL::GL stb_image freetype)

add_library(engine ${ENGINE_SRC})
target_compile_definitions(engine PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")

if (ENABLE_AUDIO)
	target_compile_definitions(engine PUBLIC "-DENABLE_AUDIO=1")
	message("Including OpenAl: " ${OpenAl_INCLUDE_DIRECTORIES})
	target_include_directories(engine PUBLIC ${OpenAl_INCLUDE_DIRECTORIES})

	list(APPEND ENGINE_DEPS ${OpenAl_DEPS})
else()
	# target_compile_definitions(engine PUBLIC "-DENABLE_AUDIO=0")
endif()


message("Engine Deps: " ${ENGINE_DEPS})

target_include_directories(engine PUBLIC include)
target_link_libraries(engine ${ENGINE_DEPS})
run_tidy(engine)