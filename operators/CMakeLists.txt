cmake_minimum_required(VERSION 3.12)

# Defines the project properties
project( 
	"Hash operators" 
	VERSION 1.0.0
	DESCRIPTION "A header-only c++ library that provides hash operators"
	HOMEPAGE_URL "https://github.com/ahiralesc/Hash")

# GNU directory structure. 
# See https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)


# Tells cmake to set up the target with logical name hash "operators"
# They keyword INTERFACE makes the target a header only library, thus 
# it is not compiled
add_library(operators INTERFACE)


# The keyword INTERFACE means that files in the library are public and  visible when 
# using the library.  
# $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> indicates that the include 
# path, in other cmake projects, will be ${PROJECT_SOURCE_DIR}/include}.
# $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> defines the project install path
target_include_directories(
	operators
	INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)


# If the library code uses a feature that is tied to a particular c++ version i. e.
# C++ 11/14/17/20/23 or newer. It must be specified in the following line i.e. 
# cxx_std_11, cxx_std_14, cxx_std_17 etc. 
target_compile_features(operators INTERFACE cxx_std_11)


# Enables creation of test cases
enable_testing()


# Tests are to be stored in the subdirectory test
add_subdirectory(test)


# locations are provided by GNUInstallDirs
install(
	TARGETS operators
	EXPORT operators_Targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


include(CMakePackageConfigHelpers)


write_basic_package_version_file(
	"operatorsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)


configure_package_config_file(
	"${PROJECT_SOURCE_DIR}/cmake/operatorsConfig.cmake.in"
  	"${PROJECT_BINARY_DIR}/operatorsConfig.cmake"
  	INSTALL_DESTINATION
  	${CMAKE_INSTALL_DATAROOTDIR}/operators/cmake)


install(EXPORT operators_Targets
        FILE operatorsTargets.cmake
        NAMESPACE operators::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/operators/cmake)

install(FILES "${PROJECT_BINARY_DIR}/operatorsConfig.cmake"
              "${PROJECT_BINARY_DIR}/operatorsConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/operators/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/operators DESTINATION include)
