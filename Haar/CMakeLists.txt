cmake_minimum_required(VERSION 2.8.3)

project(face)

find_package(OpenCV 3 REQUIRED)
message(STATUS "${OpenCV_INCLUDE_DIRS}")
message(STATUS "${OpenCV_LIBS}")

add_executable(main haar.cpp)
target_link_libraries(main ${OpenCV_LIBS})