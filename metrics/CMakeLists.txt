cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_BUILD_TYPE Release)

# Defines the project properties
project( 
	"Hash metrics" 
	VERSION 1.0.0
	DESCRIPTION "A header-only c++ library that provides metrics for evaluation of hash operators"
	HOMEPAGE_URL "https://github.com/ahiralesc/Hash"
	LANGUAGES CXX)

# GNU directory structure. 
# See https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)


# Tells cmake to set up the target with logical name hash "operators"
# They keyword INTERFACE makes the target a header only library, thus 
# it is not compiled
add_library(hmtrics INTERFACE)



# The keyword INTERFACE means that files in the library are public and  visible when 
# using the library.  
# $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> indicates that the include 
# path, in other cmake projects, will be ${PROJECT_SOURCE_DIR}/include}.
# $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> defines the project install path
target_include_directories(
	hmetrics
	INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)


# If the library code uses a feature that is tied to a particular c++ version i. e.
# C++ 11/14/17/20/23 or newer. It must be specified in the following line i.e. 
# cxx_std_11, cxx_std_14, cxx_std_17 etc. 
target_compile_features(hmetrics INTERFACE cxx_std_11)



# Enables creation of test cases
enable_testing()


# Find boost test framework
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_definitions (-DBOOST_TEST_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})


# The location of the test codes sources
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)


# Find test codes
foreach(testSrc ${TEST_SRCS})
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)

    # Add compile target
    add_executable(${testName} ${testSrc})

    # Add dependency
    add_dependencies(${testName} hmetrics)

    # link to Boost libraries AND your targets and dependencies
    target_link_libraries(${testName} ${Boost_LIBRARIES} hmetrics )

    # Location of the test binaries 
    set_target_properties(${testName} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin)

    # Add the test to the collection of tests 
    # Notice the WORKING_DIRECTORY and COMMAND
    add_test(NAME ${testName} 
             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin 
             COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin/${testName} )
endforeach(testSrc)
