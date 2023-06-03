cmake_minimum_required(VERSION 3.20)
project(binparse)
add_executable(test_binparse test_binparse.cpp)
set_target_properties(
  test_binparse
  PROPERTIES
  CXX_STANDARD 20 
)
