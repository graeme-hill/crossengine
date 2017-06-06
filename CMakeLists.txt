cmake_minimum_required(VERSION 3.5.1)
project(xe)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include_directories(..)

set(SOURCES
	MeshData.cpp
	Keyboard.cpp
	InputController.cpp
	File.cpp
	AssetReaders.cpp)

option(JS "JS" OFF)

if(JS)
	list(APPEND SOURCES
		webgl/WebGlWindow.cpp
		gles2/Gles2Renderer.cpp
		gles2/Gles2Mesh.cpp
		gles2/Gles2Shader.cpp
		gles2/Gles2ShaderParameter.cpp)

	add_library(xe ${SOURCES})
	target_link_libraries(xe "-s USE_GLFW=3")
	target_compile_definitions(xe PUBLIC PLATFORM_WEB GLM_FORCE_PURE)
	target_compile_options(xe PUBLIC -std=c++14 -lglfw -lglfw3)
else()
	list(APPEND SOURCES
		glfw/GlfwWindow.cpp
		gl/GlRenderer.cpp
		gl/GlMesh.cpp
		gl/GlShader.cpp
		gl/GlShaderParameter.cpp)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	add_subdirectory(../glfw ../glfw)

	add_library(xe ${SOURCES})
	target_link_libraries(xe glfw)
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
endif()

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
