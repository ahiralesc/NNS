cmake_minimum_required(VERSION 3.5.1)

# Locality Sensitive Hashing
project(LSH)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For use of gdb to analyze segmentation faults
# set(GCC_DEBUG_COMPILE_FLAGS "-g")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_DEBUG_COMPILE_FLAGS}")

# Header location
include_directories( include )

# Source location
file(GLOB SOURCES "src/*.cpp")

# Executable target
add_executable(lsh ${SOURCES})
