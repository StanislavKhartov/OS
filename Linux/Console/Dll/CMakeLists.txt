cmake_minimum_required(VERSION 3.23)
project(Dll)

set(CMAKE_CXX_STANDARD 14)

add_library(Dll SHARED library.cpp)

find_library(LIBNUMLIB libNumLib lib)
target_link_libraries(Dll LINK_PUBLIC ${LIBNUMLIB})
