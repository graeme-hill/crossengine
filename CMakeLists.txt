cmake_minimum_required(VERSION 3.5.1)
project(xe)

set(CMAKE_CXX_STANDARD 14)

include_directories(..)
add_subdirectory(../xr ../xr)
set(SOURCES File.cpp)
add_library(xe ${SOURCES})
target_link_libraries(xe xr)

# Require GLM
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})
if(NOT GLM_FOUND)
    message(ERROR " GLM not found!")
endif(NOT GLM_FOUND)

# Enable warnings
if(MSVC)
	# Force to always compile with W4
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
else()
	# Update if necessary
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()
