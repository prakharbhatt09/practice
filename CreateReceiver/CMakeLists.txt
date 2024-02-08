cmake_minimum_required(VERSION 3.5.0)
project(CreateReceiver)

find_package(Catch2 REQUIRED)

add_executable(CR_e main.cpp CreateReceiver.hpp)

add_executable(CRTests_e CreateReceiverTests.cpp CreateReceiver.cpp) 

target_link_libraries(CRTests_e PRIVATE Catch2::Catch2WithMain)