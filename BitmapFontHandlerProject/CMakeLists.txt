# CMakeList.txt : CMake project for BitmapFontHandlerProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
include_directories (
	#"C:/Program Files/ImageMagick-7.1.1-Q16-HDRI/include/"
	"C:/opencv/opencv/build/include/"
)
LINK_DIRECTORIES("C:/opencv/opencv/build/x64/vc14/lib")
# Add source to this project's executable.
add_library(FontHandler "FontHandler/FontHandler.cpp" "FontHandler/FontHandler.h")
add_executable (BitmapFontHandlerProject "BitmapFontHandlerProject.cpp" "BitmapFontHandlerProject.h")
 

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("debug mode")
	TARGET_LINK_LIBRARIES(BitmapFontHandlerProject opencv_world430d.lib)
	ELSE()
	message("release mode")
	TARGET_LINK_LIBRARIES(BitmapFontHandlerProject opencv_world430.lib)
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BitmapFontHandlerProject PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
 
