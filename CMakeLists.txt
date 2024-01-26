cmake_minimum_required(VERSION 3.5.0)

find_package(Catch2 REQUIRED)

project(Circle_Area)

add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/C:/Users/PraBha/Documents/Practice/Circle_Area)

add_executable(circle_area_ex main.cpp areaOfCircle.hpp)

add_executable(circle_area_tests addNumTest.cpp addNum.cpp) 

target_link_libraries(circle_area_tests PRIVATE Catch2::Catch2WithMain)