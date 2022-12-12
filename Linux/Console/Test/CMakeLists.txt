cmake_minimum_required(VERSION 3.23)
project(Test)

set(CMAKE_CXX_STANDARD 14)

add_executable(Test main.cpp)

add_library(Dll SHARED IMPORTED)
set_target_properties(Dll PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../Dll)
set_target_properties(Dll PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../Dll/cmake-build-debug/libDll.so)
target_link_libraries(Test Dll)

