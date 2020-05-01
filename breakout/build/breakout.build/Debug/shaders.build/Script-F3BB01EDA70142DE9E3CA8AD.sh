#!/bin/sh
make -C /Users/matthew/Projects/LearnOpenGL/breakout/build -f /Users/matthew/Projects/LearnOpenGL/breakout/build/CMakeScripts/shaders_cmakeRulesBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
