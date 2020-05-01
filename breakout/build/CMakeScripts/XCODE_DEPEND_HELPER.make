# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.breakout.Debug:
PostBuild.glad.Debug: /Users/matthew/Projects/LearnOpenGL/breakout/build/Debug/breakout
PostBuild.stb_image.Debug: /Users/matthew/Projects/LearnOpenGL/breakout/build/Debug/breakout
/Users/matthew/Projects/LearnOpenGL/breakout/build/Debug/breakout:\
	/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Debug/libglad.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Debug/libstb_image.a\
	/usr/local/lib/libglfw.3.3.dylib
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/Debug/breakout


PostBuild.engine.Debug:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Debug/libengine.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Debug/libengine.a


PostBuild.glad.Debug:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Debug/libglad.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Debug/libglad.a


PostBuild.shaders.Debug:
/Users/matthew/Projects/LearnOpenGL/breakout/build/Debug/libshaders.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/Debug/libshaders.a


PostBuild.stb_image.Debug:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Debug/libstb_image.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Debug/libstb_image.a


PostBuild.breakout.Release:
PostBuild.glad.Release: /Users/matthew/Projects/LearnOpenGL/breakout/build/Release/breakout
PostBuild.stb_image.Release: /Users/matthew/Projects/LearnOpenGL/breakout/build/Release/breakout
/Users/matthew/Projects/LearnOpenGL/breakout/build/Release/breakout:\
	/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Release/libglad.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Release/libstb_image.a\
	/usr/local/lib/libglfw.3.3.dylib
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/Release/breakout


PostBuild.engine.Release:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Release/libengine.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Release/libengine.a


PostBuild.glad.Release:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Release/libglad.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Release/libglad.a


PostBuild.shaders.Release:
/Users/matthew/Projects/LearnOpenGL/breakout/build/Release/libshaders.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/Release/libshaders.a


PostBuild.stb_image.Release:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Release/libstb_image.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Release/libstb_image.a


PostBuild.breakout.MinSizeRel:
PostBuild.glad.MinSizeRel: /Users/matthew/Projects/LearnOpenGL/breakout/build/MinSizeRel/breakout
PostBuild.stb_image.MinSizeRel: /Users/matthew/Projects/LearnOpenGL/breakout/build/MinSizeRel/breakout
/Users/matthew/Projects/LearnOpenGL/breakout/build/MinSizeRel/breakout:\
	/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/MinSizeRel/libglad.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/MinSizeRel/libstb_image.a\
	/usr/local/lib/libglfw.3.3.dylib
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/MinSizeRel/breakout


PostBuild.engine.MinSizeRel:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/MinSizeRel/libengine.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/MinSizeRel/libengine.a


PostBuild.glad.MinSizeRel:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/MinSizeRel/libglad.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/MinSizeRel/libglad.a


PostBuild.shaders.MinSizeRel:
/Users/matthew/Projects/LearnOpenGL/breakout/build/MinSizeRel/libshaders.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/MinSizeRel/libshaders.a


PostBuild.stb_image.MinSizeRel:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/MinSizeRel/libstb_image.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/MinSizeRel/libstb_image.a


PostBuild.breakout.RelWithDebInfo:
PostBuild.glad.RelWithDebInfo: /Users/matthew/Projects/LearnOpenGL/breakout/build/RelWithDebInfo/breakout
PostBuild.stb_image.RelWithDebInfo: /Users/matthew/Projects/LearnOpenGL/breakout/build/RelWithDebInfo/breakout
/Users/matthew/Projects/LearnOpenGL/breakout/build/RelWithDebInfo/breakout:\
	/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/RelWithDebInfo/libglad.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/RelWithDebInfo/libstb_image.a\
	/usr/local/lib/libglfw.3.3.dylib
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/RelWithDebInfo/breakout


PostBuild.engine.RelWithDebInfo:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/RelWithDebInfo/libengine.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/RelWithDebInfo/libengine.a


PostBuild.glad.RelWithDebInfo:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/RelWithDebInfo/libglad.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/RelWithDebInfo/libglad.a


PostBuild.shaders.RelWithDebInfo:
/Users/matthew/Projects/LearnOpenGL/breakout/build/RelWithDebInfo/libshaders.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/RelWithDebInfo/libshaders.a


PostBuild.stb_image.RelWithDebInfo:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/RelWithDebInfo/libstb_image.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/breakout/build/engine/RelWithDebInfo/libstb_image.a




# For each target create a dummy ruleso the target does not have to exist
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Debug/libglad.a:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Debug/libstb_image.a:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/MinSizeRel/libglad.a:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/MinSizeRel/libstb_image.a:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/RelWithDebInfo/libglad.a:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/RelWithDebInfo/libstb_image.a:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Release/libglad.a:
/Users/matthew/Projects/LearnOpenGL/breakout/build/engine/Release/libstb_image.a:
/usr/local/lib/libglfw.3.3.dylib:
