cmake_minimum_required(VERSION 3.5.1)

# Locality Sensitive Hashing
project(LSH 
		VERSION 0.0.1 
		LANGUAGES C CXX)

# set(CMAKE_BUILD_TYPE Release)

# C11 Compliance
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.81.0)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Header location
message("Boost and Eigen libraries must be installed in /usr/local/include")
include_directories(include /usr/local/include )

# Source location
file(GLOB SOURCES "src/*.cpp")

# Executable target
add_executable(lsh ${SOURCES})

# Target link libraries
target_link_libraries(Eigen3::Eigen)

# Create a library that unit tests use
add_library(lsh_lib SHARED
			${SOURCES} )

enable_testing()

# Find boost test framework
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_definitions (-DBOOST_TEST_DYN_LINK)


# The location of the test codes sources
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)

# Find test codes
foreach(testSrc ${TEST_SRCS})
	#Extract the filename without an extension (NAME_WE)
	get_filename_component(testName ${testSrc} NAME_WE)

	# Add compile target
	add_executable(${testName} ${testSrc})

	# Add dependency
	add_dependencies(${testName} lsh)

	# link to Boost libraries AND your targets and dependencies
	target_link_libraries(${testName} ${Boost_LIBRARIES} Eigen3::Eigen lsh_lib)

	# Location of the test binaries 
	set_target_properties(${testName} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin)

	# Add the test to the collection of tests 
	# Notice the WORKING_DIRECTORY and COMMAND
	add_test(NAME ${testName} 
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin 
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin/${testName} )
endforeach(testSrc)
