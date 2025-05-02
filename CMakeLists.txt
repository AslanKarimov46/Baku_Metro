cmake_minimum_required(VERSION 3.29)
project(BMetro)


option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
add_library(metro_lib violetLine.cpp redGreenLines.cpp)
target_include_directories(metro_lib PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(BMetro main.cpp)

target_link_libraries(BMetro PRIVATE metro_lib)

#set(CMAKE_CXX_STANDARD 17)

#add_executable(BMetro main.cpp
#        metro.h
#        violetLine.cpp
#        redGreenLines.cpp)
