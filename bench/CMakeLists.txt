cmake_minimum_required(VERSION 3.10)
project(taglog_bench CXX)

add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE taglog)
set_target_properties(bench PROPERTIES LINK_FLAGS "/PROFILE")

add_executable(stdcout_vs_win32writeconsole stdcout_vs_win32writeconsole.cpp)
target_link_libraries(stdcout_vs_win32writeconsole PRIVATE taglog)
set_target_properties(stdcout_vs_win32writeconsole PROPERTIES LINK_FLAGS "/PROFILE")