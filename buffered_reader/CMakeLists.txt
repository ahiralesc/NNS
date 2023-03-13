cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(
	"Text buffered reader"
	VERSION 1.0.0
	DESCRIPTION "A simple text buffered reader"
	HOMEPAGE_URL "https://github.com/ahiralesc/Hash"
	LANGUAGES CXX)

include(GNUInstallDirs)


#Include the headers *.h from the include dir.
include_directories(include)


#Wildcard addition for sources
file(GLOB SOURCES "src/*.cpp")


#Generate the shared library from the sources
add_library(csv SHARED ${SOURCES})


#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
# install(TARGETS csv DESTINATION /home/ahiralesc/mysrc/cpp/cutu/guttaccept/lib)
