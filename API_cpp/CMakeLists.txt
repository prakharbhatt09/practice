cmake_minimum_required(VERSION 3.5.0)
project(APIClass)

find_package(Catch2 REQUIRED)

add_executable(apiClass_e main.cpp apiClass.hpp)

add_executable(apiClassTests_e apiClassTests.cpp apiClass.cpp) 

target_link_libraries(apiClassTests_e PRIVATE Catch2::Catch2WithMain)