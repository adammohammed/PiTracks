cmake_minimum_required(VERSION 3.6)
project(faceDetectionNTracking)

set(CMAKE_CXX_STANDARD 14)

file(COPY haarcascade_frontalface_default.xml DESTINATION ${PROJECT_BINARY_DIR})

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES driver.cpp robot.cpp robot.h VideoFaceDetector.cpp VideoFaceDetector.h SerialInterface.c SerialInterface.h)
add_executable(driver ${SOURCE_FILES})

target_link_libraries(driver ${OpenCV_LIBS})
