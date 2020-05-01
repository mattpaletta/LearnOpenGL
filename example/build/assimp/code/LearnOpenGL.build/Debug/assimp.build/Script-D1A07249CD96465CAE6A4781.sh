#!/bin/sh
make -C /Users/matthew/Projects/LearnOpenGL/example/build/assimp/code -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/code/CMakeScripts/assimp_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
