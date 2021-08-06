
cmake_minimum_required(VERSION 2.8)
project( DocumentScanner )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( DocumentScanner document_scanner.cpp)
target_link_libraries( DocumentScanner ${OpenCV_LIBS} )

