cmake_minimum_required(VERSION 3.5.0)
project(CreateReceiver_repl)

find_package(Catch2 REQUIRED)

add_executable(CRrepl_e main.cpp CreateReceiver_repl.hpp)

add_executable(CRreplTests_e CreateReceiver_repl_Tests.cpp CreateReceiver_repl.cpp) 

target_link_libraries(CRreplTests_e PRIVATE Catch2::Catch2WithMain)