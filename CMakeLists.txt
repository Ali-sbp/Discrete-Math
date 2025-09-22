cmake_minimum_required(VERSION 3.12)
project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type defaults to Release if not set
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Common warnings and optimizations (mirrors Makefile intent)
add_compile_options(-Wall -Wextra)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_compile_options(-O2)
endif()

# Sources
set(SHARED_SRCS
  funcs.cpp
)

# Header (for IDEs; not strictly required by the compiler listing)
set(SHARED_HDRS
  funcs.h
)

# Main program target
add_executable(lab1
  main.cpp
  ${SHARED_SRCS}
  ${SHARED_HDRS}
)

# Test program target
add_executable(test_program
  test.cpp
  ${SHARED_SRCS}
  ${SHARED_HDRS}
)


