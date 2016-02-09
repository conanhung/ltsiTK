cmake_minimum_required(VERSION 2.8)

project(endotrack)

set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_MACOSX_RPATH 0)

####### DEPENDENCIES #######

find_package(OpenCV REQUIRED)
find_package(Qt4)

include ( ${QT_USE_FILE} )

include_directories (
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${OpenCV_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	)

add_definitions(-DCOMPILE_CAPTUREMANAGER_API)

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

file( GLOB_RECURSE endotrack_SRCS *.cpp )
file( GLOB_RECURSE endotrack_HDRS include/*.h )
file( GLOB_RECURSE endotrack_UIS *.ui )

QT4_WRAP_UI(UIS ${endotrack_UIS})

set (CMAKE_AUTOMOC ON)

add_library(EndoTrackCore SHARED 
	CaptureManager.cpp ImagePlus.cpp PaintArea.cpp ParametersToolbox.cpp ImageConversion.cpp Settings.cpp Util.cpp interfaces.cpp
	include/CaptureManager.h include/ImagePlus.h include/PaintArea.h include/ImageConversion.h include/ParametersToolbox.h include/Settings.h include/Util.h include/interfaces.h
)

target_link_libraries(
	EndoTrackCore
	${OpenCV_LIBS}
	${QT_LIBRARIES}
)

add_executable ( endotrack MainWindow.cpp main.cpp include/MainWindow.h ${UIS} )
target_link_libraries ( endotrack EndoTrackCore ${OpenCV_LIBS} ${QT_LIBRARIES} )
