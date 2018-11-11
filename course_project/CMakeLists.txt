cmake_minimum_required (VERSION 3.0.0)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "-std=c++17 -std=gnu++17")

include_directories(.)
include_directories(../test_runner)

project (course)
add_executable(	course
		        main.cpp
                condition_parser.cpp
                #condition_parser_test.cpp
                token.cpp
                database.cpp
                date.cpp
                node.cpp
                )