cmake_minimum_required(VERSION 3.5.1)
project(xe)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(../glfw ../glfw)

set(SOURCES
	glfw/GlfwWindow.cpp
	gl/GlRenderer.cpp
	gl/GlMesh.cpp
	gl/GlShader.cpp
	gl/GlShaderParameter.cpp
	MeshData.cpp
	Keyboard.cpp
	InputController.cpp
	File.cpp)
add_library(xe ${SOURCES})

target_compile_definitions(xe PUBLIC PLATFORM_LINUX PLATFORM_GLFW)

# Require GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(xe ${GLEW_LIBRARIES})
if(NOT GLEW_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT GLEW_FOUND)

# Require OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(xe ${OPENGL_gl_LIBRARY})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

target_link_libraries(xe glfw)

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
