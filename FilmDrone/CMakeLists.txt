cmake_minimum_required(VERSION 3.13)
project(FilmDrone)

#set(CMAKE_CXX_STANDARD 14)

#add_executable(FilmDrone main.cpp)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)
add_executable(filmDrone ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(filmDrone ${OpenCV_LIBS})