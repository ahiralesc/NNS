cmake_minimum_required(VERSION 3.5.1)

# Locality Sensitive Hashing
project(LSH)

# set(CMAKE_BUILD_TYPE Release)

# C11 Compliance
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.81.0)

# Header location
include_directories( include )

# Source location
file(GLOB SOURCES "src/*.cpp")

# Executable target
add_executable(lsh ${SOURCES})
