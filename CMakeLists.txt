cmake_minimum_required(VERSION 3.12)

project(IMG_CONCAT)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
#set(CMAKE_EXE_LINKER_FLAGS "-static")
set(OpenCV_DIR "<opencv_dir>/lib64/cmake/opencv4") 
file(GLOB SOURCE_FILE
	"*.cpp"
	"*.h"
)

find_package( OpenCV REQUIRED )

message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

include_directories( ${OpenCV_INCLUDE_DIRS} "includes/")
add_executable( IMG_CONCAT ${SOURCE_FILE} )
add_library( imgconcat STATIC ${SOURCE_FILE} )
target_link_libraries( IMG_CONCAT ${OpenCV_LIBS} )
