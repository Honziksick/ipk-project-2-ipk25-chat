################################################################################
#                                                                              #
# Project:      IPK25 Chat Client                                              #
# University:   Faculty of Information Technology, BUT                         #
# Subject:      IPK: Computer Communications and Networks                      #
#                                                                              #
# File:         CMakeLists.txt                                                 #
# Author:       Jan Kalina <xkalinj00>                                         #
#                                                                              #
# Created:      02.04.2025                                                     #
# Last edit:    20.04.2025                                                     #
#                                                                              #
# Description:  This file contains the CMake configuration for the IPK25 Chat  #
#               Client project. It sets up the project, specifies the C++20    #
#               standard, collects source files, creates a static library,     #
#               defines the main executable, and configures testing with       #
#               Google Test. This CMakeLists.txt is inspired by CMakeLists.txt #
#               I created for previous projects at BUT FIT (e.g., IPK course). #
#                                                                              #
################################################################################

################################################################################
#                                                                              #
#                        BASIC CMakeLists.txt SETTINGS                         #
#                                                                              #
################################################################################

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

# Set the project name (source location) and version
project(src LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compile options based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Test")
    add_compile_options(-g -fsanitize=address -Wall -Werror -Wextra -pedantic)
    add_link_options(-fsanitize=address)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -DNDEBUG)
endif()


################################################################################
#                                                                              #
#                             BUILD CONFIGURATION                              #
#                                                                              #
################################################################################

# Ensure the existence of the build directory
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Set the output directory for the app release binary (ipk25chat-client)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/..")

# Include necessary directories (e.g., src)
include_directories(src)

# Collect all source files in the 'src' directory
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS
     src/*.cpp
     src/*.hpp
     )

# Remove main.cpp to avoid including it in the library
list(REMOVE_ITEM ALL_SOURCES
     "${CMAKE_CURRENT_SOURCE_DIR}/src/App/main.cpp"
     )

###                                                                          ###
#  Build library from project files (ipk25chat-client-lib) (except 'main.cpp') #
###                                                                          ###

# Create a static library from the source files
add_library(ipk25chat-client-lib STATIC ${ALL_SOURCES})
target_include_directories(ipk25chat-client-lib PUBLIC src)


###                                       ###
#  Build main executabe (ipk25chat-client)  #
###                                       ###

add_executable(ipk25chat-client src/App/main.cpp)
target_link_libraries(ipk25chat-client
                      PRIVATE
                      ipk25chat-client-lib
                      )

target_include_directories(ipk25chat-client PRIVATE ipk25chat-client-lib)

### end of file CMakeLists.txt ###
