
cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( DisplayImageTransforms change_brightness_and_contrast_of_image.cpp)
target_link_libraries( DisplayImageTransforms ${OpenCV_LIBS} )
