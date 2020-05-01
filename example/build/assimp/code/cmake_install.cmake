# Install script for directory: /Users/matthew/Projects/LearnOpenGL/example/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
      "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/libassimpd.5.0.1.dylib"
      "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/libassimpd.5.dylib"
      )
    foreach(file
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.5.0.1.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.5.dylib"
        )
      if(EXISTS "${file}" AND
         NOT IS_SYMLINK "${file}")
        if(CMAKE_INSTALL_DO_STRIP)
          execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
        endif()
      endif()
    endforeach()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
      "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/libassimp.5.0.1.dylib"
      "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/libassimp.5.dylib"
      )
    foreach(file
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.0.1.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.dylib"
        )
      if(EXISTS "${file}" AND
         NOT IS_SYMLINK "${file}")
        if(CMAKE_INSTALL_DO_STRIP)
          execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
        endif()
      endif()
    endforeach()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
      "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/libassimp.5.0.1.dylib"
      "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/libassimp.5.dylib"
      )
    foreach(file
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.0.1.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.dylib"
        )
      if(EXISTS "${file}" AND
         NOT IS_SYMLINK "${file}")
        if(CMAKE_INSTALL_DO_STRIP)
          execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
        endif()
      endif()
    endforeach()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
      "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/libassimp.5.0.1.dylib"
      "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/libassimp.5.dylib"
      )
    foreach(file
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.0.1.dylib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.dylib"
        )
      if(EXISTS "${file}" AND
         NOT IS_SYMLINK "${file}")
        if(CMAKE_INSTALL_DO_STRIP)
          execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
        endif()
      endif()
    endforeach()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/libassimpd.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/libassimp.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/libassimp.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/libassimp.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
      endif()
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/anim.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/aabb.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/ai_assert.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/camera.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/color4.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/color4.inl"
    "/Users/matthew/Projects/LearnOpenGL/example/build/assimp/code/../include/assimp/config.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/commonMetaData.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/defs.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Defines.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/cfileio.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/light.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/material.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/material.inl"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/matrix3x3.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/matrix3x3.inl"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/matrix4x4.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/matrix4x4.inl"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/mesh.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/pbrmaterial.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/postprocess.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/quaternion.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/quaternion.inl"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/scene.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/metadata.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/texture.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/types.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/vector2.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/vector2.inl"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/vector3.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/vector3.inl"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/version.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/cimport.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/importerdesc.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Importer.hpp"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/IOStream.hpp"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/IOSystem.hpp"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Logger.hpp"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/LogStream.hpp"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/NullLogger.hpp"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/cexport.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Exporter.hpp"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/DefaultIOStream.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/DefaultIOSystem.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/SceneCombiner.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/fast_atof.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/qnan.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/BaseImporter.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Hash.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/ParsingUtils.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/StreamReader.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/StreamWriter.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/StringComparison.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/StringUtils.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/SGSpatialSort.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/GenericProperty.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/SpatialSort.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/SmallVector.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/SmoothingGroups.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/SmoothingGroups.inl"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/StandardShapes.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/RemoveComments.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Subdivision.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Vertex.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/LineSplitter.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/TinyFormatter.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Profiler.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/LogAux.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Bitmap.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/XMLTools.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/IOStreamBuffer.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/CreateAnimMesh.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/irrXMLWrapper.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/BlobIOSystem.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/MathFunctions.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Exceptional.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/Users/matthew/Projects/LearnOpenGL/example/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

