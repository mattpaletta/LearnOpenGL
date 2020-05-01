#!/bin/sh
make -C /Users/matthew/Projects/LearnOpenGL/example/build -f /Users/matthew/Projects/LearnOpenGL/example/build/CMakeScripts/glad_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
