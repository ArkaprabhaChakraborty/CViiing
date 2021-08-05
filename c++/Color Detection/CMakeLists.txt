
cmake_minimum_required(VERSION 2.8)
project( ColorDetection )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ColorDetection color_detection.cpp)
target_link_libraries( ColorDetection ${OpenCV_LIBS} )
