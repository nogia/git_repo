CMAKE_MINIMUM_REQUIRED ( VERSION 2.4 )
PROJECT ( Assignment )
set(CMAKE_CXX_FLAGS "-std=c++11")
#set(CMAKE_BUILD_TYPE Debug)

set(SOURCES_src
    src/assignment.cpp
    src/MedianFilter/MedianFilter.cpp

 )
include_directories(
         src/MedianFilter/MedianFilter.h
         )
add_executable(Assignment ${SOURCES_src})
#target_link_libraries(Assignment  MedianFilter_LIB)
