CMAKE_MINIMUM_REQUIRED ( VERSION 2.4 )
PROJECT ( Assignment )
set(CMAKE_CXX_FLAGS "-std=c++11 -larmadillo")

#set(CMAKE_BUILD_TYPE Debug)

set(SOURCES_src
    src/assignment.cpp
    src/MedianFilter/MedianFilter.cpp

 )
include_directories(
         src/MedianFilter/MedianFilter.h
         )

#LIBS +=  -larmadillo
#set(LIBS "-llapack -lblas -larmadillo")
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
add_executable(Assignment ${SOURCES_src})
target_link_libraries(Assignment ${ARMADILLO_LIBRARIES})
