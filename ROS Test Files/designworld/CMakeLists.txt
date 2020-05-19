cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_INCLUDE_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(welcomemessage SHARED script/welcomemessage.cpp)
target_link_libraries(welcomemessage ${GAZEBO_LIBRARIES})
