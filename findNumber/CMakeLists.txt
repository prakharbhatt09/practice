cmake_minimum_required(VERSION 3.5.0)
project(findNumber)

find_package(Catch2 REQUIRED)

add_executable(findNumber_e main.cpp findNumber.hpp)

add_executable(findNumberTests_e findNumberTests.cpp findNumber.cpp) 

target_link_libraries(findNumberTests_e Catch2::Catch2WithMain)