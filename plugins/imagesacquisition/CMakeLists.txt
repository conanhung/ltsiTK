cmake_minimum_required( VERSION 2.8 )

project( ImagesAcquisitionPlugin )
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

find_package(OpenCV REQUIRED)
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui)
include ( ${QT_USE_FILE} )

include_directories(/Users/longhung/dev/endotrack/src/include)

include_directories (
	${CMAKE_CURRENT_SOURCE_DIR}
	${OpenCV_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	)

file( GLOB_RECURSE imagesacquisition_source_files src/*.cpp )
file( GLOB_RECURSE imagesacquisition_include_files src/*.h )
file( GLOB_RECURSE imagesacquisition_UIS src/*.ui )

QT4_WRAP_UI(UIS ${imagesacquisition_UIS})

SET (CMAKE_AUTOMOC ON)

set(LIBRARY_OUTPUT_PATH /Users/longhung/dev/endotrack/build/bin/Debug/plugins)

add_library( imagesacquisition SHARED ${imagesacquisition_include_files} ${imagesacquisition_source_files} ${UIS} )

target_link_libraries(
imagesacquisition
/Users/longhung/dev/endotrack/build/lib/Debug/libEndoTrackCored.dylib
${OpenCV_LIBS}
${QT_LIBRARIES}
)