cmake_minimum_required (VERSION 3.0.0)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "-std=c++17 -std=gnu++17")

project (course)

include_directories(.)

add_executable(	course
                main.cpp
		        query.cpp
                responses.cpp
                bus_manager.cpp)
