
cmake_minimum_required(VERSION 2.8)
project( ImageProcessing )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ImageProcessing basic_image_processing.cpp)
target_link_libraries( ImageProcessing ${OpenCV_LIBS} )

