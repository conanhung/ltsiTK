cmake_minimum_required( VERSION 2.8 )

project( drawingtools )
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

find_package(OpenCV REQUIRED)
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui)
include ( ${QT_USE_FILE} )

#path to the endotrack include directory
include_directories(/Users/longhung/dev/endotrack/src/include)

include_directories (
	${CMAKE_CURRENT_SOURCE_DIR}
	${OpenCV_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	)

file( GLOB_RECURSE drawingtools_source_files src/* )
file( GLOB_RECURSE drawingtools_include_files include/*.h )

SET (CMAKE_AUTOMOC ON)

set(LIBRARY_OUTPUT_PATH /Users/longhung/dev/endotrack/build/bin/Debug/plugins)

add_library( drawingtools SHARED ${drawingtools_include_files} ${drawingtools_source_files} )

target_link_libraries(
    drawingtools
    /Users/longhung/dev/endotrack/build/lib/Debug/libEndoTrackCored.dylib
    ${OpenCV_LIBS}
    ${QT_LIBRARIES}
)