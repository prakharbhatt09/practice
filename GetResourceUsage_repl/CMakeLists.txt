cmake_minimum_required(VERSION 3.5.0)
project(GetResourceUsage_repl)

find_package(Catch2 REQUIRED)

add_executable(Usage_e main.cpp GetResourceUsage_repl.hpp)

add_executable(Tests_e GetResourceUsage_replTests.cpp GetResourceUsage_repl.cpp) 

target_link_libraries(Tests_e PRIVATE Catch2::Catch2WithMain)