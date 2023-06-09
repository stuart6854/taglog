cmake_minimum_required(VERSION 3.25)
project(LogLib)

set(CMAKE_CXX_STANDARD 23)

add_library(taglog INTERFACE)
TARGET_COMPILE_FEATURES(taglog INTERFACE cxx_std_23)
target_include_directories(taglog INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(TestApp main.cpp)
target_link_libraries(TestApp PRIVATE taglog)

add_subdirectory(bench)