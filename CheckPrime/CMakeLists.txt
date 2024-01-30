cmake_minimum_required(VERSION 3.5.0)
project(CheckPrime)

find_package(Catch2 REQUIRED)

#add_library(Catch2 INTERFACE)
#target_include_directories(Catch2 INTERFACE C:\Users\PraBha\Documents\Practice\src\CheckPrime)

add_executable(CheckPrime main.cpp CheckPrime.hpp)

add_executable(CheckPrimeTests CheckPrimeTests.cpp CheckPrime.cpp) 

target_link_libraries(CheckPrimeTests Catch2::Catch2WithMain)