cmake_minimum_required(VERSION 3.5.1)
project(xe)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include_directories(modules)
include_directories(modules/flatbuffers/include)
include_directories(modules/asio/asio/include)
include_directories(BEFORE modules/websocketpp)

set(SOURCES
	MeshData.cpp
	Keyboard.cpp
	InputController.cpp
	File.cpp
	AssetReaders.cpp
	WebSocketClient.cpp
	WebSocketServer.cpp)

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
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/glfw)

	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/glew)

	set(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(FLATBUFFERS_INSTALL OFF CACHE BOOL "" FORCE)
	set(FLATBUFFERS_BUILD_SHAREDLIB OFF CACHE BOOL "" FORCE)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/flatbuffers)

	add_library(xe ${SOURCES})
	target_link_libraries(xe glfw glew)
	target_compile_definitions(xe PUBLIC PLATFORM_LINUX PLATFORM_GLFW)

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
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -Wno-unused-local-typedefs -pedantic")
endif()
