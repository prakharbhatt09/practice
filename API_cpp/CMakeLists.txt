cmake_minimum_required(VERSION 3.5.0)
project(APIClass)

find_package(Catch2 REQUIRED)

#add_library(Catch2 INTERFACE)
#target_include_directories(Catch2 INTERFACE C:\Users\PraBha\Documents\Practice\src\CheckPrime)

add_executable(apiClass main.cpp apiClass.hpp)

add_executable(apiClassTests apiClassTests.cpp apiClass.cpp) 

target_link_libraries(apiClassTests Catch2::Catch2WithMain)