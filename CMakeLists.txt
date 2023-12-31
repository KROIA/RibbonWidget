﻿cmake_minimum_required(VERSION 3.20)

project(RibbonWidget)
set(PARALLEL_BUILD ON)
#
# -----------------------------------------
#
# Check if variable is set, otherwise set to default
if(NOT RELATIVE_BUILD_FOLDER)
	set(RELATIVE_BUILD_FOLDER build)
endif()
if(NOT CMAKE_INSTALL_PREFIX)
	set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
endif()
if(NOT RELATIVE_INSTALL_FOLDER)
	set(RELATIVE_INSTALL_FOLDER lib)
endif()

if(CMAKE_GENERATOR STREQUAL "Ninja")
    message("CMake was configured using Ninja")
else()
    set(PARALLEL_BUILD OFF) # Multithreading does mostly not work if not configured using ninja
    message("CMake was not configured using Ninja")
endif()
 
# Set output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${RELATIVE_BUILD_FOLDER}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${RELATIVE_BUILD_FOLDER}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${RELATIVE_BUILD_FOLDER}")

set(INSTALL_LIB_PATH "${CMAKE_INSTALL_PREFIX}/${RELATIVE_INSTALL_FOLDER}")
set(INSTALL_BIN_PATH "${CMAKE_INSTALL_PREFIX}/bin")
# create bin folder
file(MAKE_DIRECTORY ${INSTALL_BIN_PATH})


set(QT_LOCATOR_CMAKE "${CMAKE_CURRENT_SOURCE_DIR}/QtLocator.cmake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

if(PARALLEL_BUILD)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
endif()


include(utility.cmake)
include(dependencies.cmake)

add_subdirectory(core)
add_subdirectory(Examples)

