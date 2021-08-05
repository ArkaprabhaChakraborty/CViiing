cmake_minimum_required(VERSION 2.8)
project( WarpPerspective )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( WarpPerspective warp_perspective.cpp )
target_link_libraries( WarpPerspective ${OpenCV_LIBS} )

