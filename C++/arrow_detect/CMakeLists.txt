CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(arrow_detect)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 OLD)
	cmake_policy(SET CMP0015 OLD)
endif(COMMAND cmake_policy)

SET(EXECUTABLE_OUTPUT_PATH ".")
SET(OpenCV_DIR /usr/local/lib/cmake/opencv4)

find_package(OpenCV REQUIRED) 
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

SET(SRC_FOLDER src)
FILE(GLOB_RECURSE SRC_FILES "${SRC_FOLDER}/*.cpp")  

ADD_EXECUTABLE(arrow_detect arrow_detect_cv.cpp)
add_definitions(-std=c++0x -g -O3)

TARGET_LINK_LIBRARIES(arrow_detect ${OpenCV_LIBS})

