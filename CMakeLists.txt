cmake_minimum_required(VERSION 3.5)
project(FindIsomorphy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CSVFile.cpp Tree.cpp VAF_CSVTree_struct.h)
add_executable(FindIsomorphy ${SOURCE_FILES})