# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.IrrXML.Debug:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Debug/libIrrXMLd.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Debug/libIrrXMLd.a


PostBuild.assimp.Debug:
PostBuild.IrrXML.Debug: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/libassimpd.dylib
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/libassimpd.dylib:\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Debug/libIrrXMLd.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/libassimpd.dylib


PostBuild.assimp_cmd.Debug:
PostBuild.assimp.Debug: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/assimpd
PostBuild.IrrXML.Debug: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/assimpd
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/assimpd:\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/libassimpd.5.0.1.dylib\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Debug/libIrrXMLd.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/assimpd


PostBuild.create_window.Debug:
PostBuild.glad.Debug: /Users/matthew/Projects/LearnOpenGL/example/build/Debug/create_window
PostBuild.assimp.Debug: /Users/matthew/Projects/LearnOpenGL/example/build/Debug/create_window
PostBuild.IrrXML.Debug: /Users/matthew/Projects/LearnOpenGL/example/build/Debug/create_window
/Users/matthew/Projects/LearnOpenGL/example/build/Debug/create_window:\
	/Users/matthew/Projects/LearnOpenGL/example/build/Debug/libgladd.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/libassimpd.5.0.1.dylib\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libglfw.3.3.dylib\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Debug/libIrrXMLd.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/Debug/create_window


PostBuild.glad.Debug:
/Users/matthew/Projects/LearnOpenGL/example/build/Debug/libgladd.dylib:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/Debug/libgladd.dylib


PostBuild.IrrXML.Release:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Release/libIrrXML.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Release/libIrrXML.a


PostBuild.assimp.Release:
PostBuild.IrrXML.Release: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/libassimp.dylib
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/libassimp.dylib:\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Release/libIrrXML.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/libassimp.dylib


PostBuild.assimp_cmd.Release:
PostBuild.assimp.Release: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/assimp
PostBuild.IrrXML.Release: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/assimp
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/assimp:\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/libassimp.5.0.1.dylib\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Release/libIrrXML.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/assimp


PostBuild.create_window.Release:
PostBuild.glad.Release: /Users/matthew/Projects/LearnOpenGL/example/build/Release/create_window
PostBuild.assimp.Release: /Users/matthew/Projects/LearnOpenGL/example/build/Release/create_window
PostBuild.IrrXML.Release: /Users/matthew/Projects/LearnOpenGL/example/build/Release/create_window
/Users/matthew/Projects/LearnOpenGL/example/build/Release/create_window:\
	/Users/matthew/Projects/LearnOpenGL/example/build/Release/libglad.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/libassimp.5.0.1.dylib\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libglfw.3.3.dylib\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Release/libIrrXML.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/Release/create_window


PostBuild.glad.Release:
/Users/matthew/Projects/LearnOpenGL/example/build/Release/libglad.dylib:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/Release/libglad.dylib


PostBuild.IrrXML.MinSizeRel:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/MinSizeRel/libIrrXML.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/MinSizeRel/libIrrXML.a


PostBuild.assimp.MinSizeRel:
PostBuild.IrrXML.MinSizeRel: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/libassimp.dylib
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/libassimp.dylib:\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/MinSizeRel/libIrrXML.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/libassimp.dylib


PostBuild.assimp_cmd.MinSizeRel:
PostBuild.assimp.MinSizeRel: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/assimp
PostBuild.IrrXML.MinSizeRel: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/assimp
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/assimp:\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/libassimp.5.0.1.dylib\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/MinSizeRel/libIrrXML.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/assimp


PostBuild.create_window.MinSizeRel:
PostBuild.glad.MinSizeRel: /Users/matthew/Projects/LearnOpenGL/example/build/MinSizeRel/create_window
PostBuild.assimp.MinSizeRel: /Users/matthew/Projects/LearnOpenGL/example/build/MinSizeRel/create_window
PostBuild.IrrXML.MinSizeRel: /Users/matthew/Projects/LearnOpenGL/example/build/MinSizeRel/create_window
/Users/matthew/Projects/LearnOpenGL/example/build/MinSizeRel/create_window:\
	/Users/matthew/Projects/LearnOpenGL/example/build/MinSizeRel/libglad.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/libassimp.5.0.1.dylib\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libglfw.3.3.dylib\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/MinSizeRel/libIrrXML.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/MinSizeRel/create_window


PostBuild.glad.MinSizeRel:
/Users/matthew/Projects/LearnOpenGL/example/build/MinSizeRel/libglad.dylib:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/MinSizeRel/libglad.dylib


PostBuild.IrrXML.RelWithDebInfo:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/RelWithDebInfo/libIrrXML.a:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/RelWithDebInfo/libIrrXML.a


PostBuild.assimp.RelWithDebInfo:
PostBuild.IrrXML.RelWithDebInfo: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/libassimp.dylib
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/libassimp.dylib:\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/RelWithDebInfo/libIrrXML.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/libassimp.dylib


PostBuild.assimp_cmd.RelWithDebInfo:
PostBuild.assimp.RelWithDebInfo: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/assimp
PostBuild.IrrXML.RelWithDebInfo: /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/assimp
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/assimp:\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/libassimp.5.0.1.dylib\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/RelWithDebInfo/libIrrXML.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/assimp


PostBuild.create_window.RelWithDebInfo:
PostBuild.glad.RelWithDebInfo: /Users/matthew/Projects/LearnOpenGL/example/build/RelWithDebInfo/create_window
PostBuild.assimp.RelWithDebInfo: /Users/matthew/Projects/LearnOpenGL/example/build/RelWithDebInfo/create_window
PostBuild.IrrXML.RelWithDebInfo: /Users/matthew/Projects/LearnOpenGL/example/build/RelWithDebInfo/create_window
/Users/matthew/Projects/LearnOpenGL/example/build/RelWithDebInfo/create_window:\
	/Users/matthew/Projects/LearnOpenGL/example/build/RelWithDebInfo/libglad.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/libassimp.5.0.1.dylib\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libglfw.3.3.dylib\
	/usr/local/lib/libz.dylib\
	/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/RelWithDebInfo/libIrrXML.a
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/RelWithDebInfo/create_window


PostBuild.glad.RelWithDebInfo:
/Users/matthew/Projects/LearnOpenGL/example/build/RelWithDebInfo/libglad.dylib:
	/bin/rm -f /Users/matthew/Projects/LearnOpenGL/example/build/RelWithDebInfo/libglad.dylib




# For each target create a dummy ruleso the target does not have to exist
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd:
/Users/matthew/Projects/LearnOpenGL/example/build/Debug/libgladd.dylib:
/Users/matthew/Projects/LearnOpenGL/example/build/MinSizeRel/libglad.dylib:
/Users/matthew/Projects/LearnOpenGL/example/build/RelWithDebInfo/libglad.dylib:
/Users/matthew/Projects/LearnOpenGL/example/build/Release/libglad.dylib:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Debug/libassimpd.5.0.1.dylib:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/MinSizeRel/libassimp.5.0.1.dylib:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/RelWithDebInfo/libassimp.5.0.1.dylib:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/bin/Release/libassimp.5.0.1.dylib:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Debug/libIrrXMLd.a:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/MinSizeRel/libIrrXML.a:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/RelWithDebInfo/libIrrXML.a:
/Users/matthew/Projects/LearnOpenGL/example/build/assimp/lib/Release/libIrrXML.a:
/usr/local/lib/libglfw.3.3.dylib:
/usr/local/lib/libz.dylib:
