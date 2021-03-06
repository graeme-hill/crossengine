cmake_minimum_required(VERSION 3.5.1)
project(xe)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include_directories(modules)
include_directories(modules/flatbuffers/include)

set(SOURCES
	MeshData.cpp
	Keyboard.cpp
	InputController.cpp
	File.cpp
	AssetReaders.cpp
	Blob.cpp
	SmallGroupConnectionManager.cpp
	SmallGroupServerDispatcher.cpp)

option(JS "JS" OFF)

if(JS)
	list(APPEND SOURCES
		webgl/WebGlWindow.cpp
		gles2/Gles2Renderer.cpp
		gles2/Gles2Mesh.cpp
		gles2/Gles2Shader.cpp
		gles2/Gles2ShaderParameter.cpp
		jsws/EmscriptenWebSocketClient.cpp)

	add_library(xe ${SOURCES})
	target_link_libraries(xe "-s USE_GLFW=3" "--js-library ${CMAKE_CURRENT_SOURCE_DIR}/jsws/library_xews.js")
	target_compile_definitions(xe PUBLIC PLATFORM_WEB GLM_FORCE_PURE)
	target_compile_options(xe PUBLIC -std=c++14 -lglfw -lglfw3)
	add_dependencies(xe ${CMAKE_CURRENT_SOURCE_DIR}/jsws/library_xews.js)
else()
	include_directories(modules/asio/asio/include)
	include_directories(BEFORE modules/websocketpp)

	list(APPEND SOURCES
		glfw/GlfwWindow.cpp
		gl/GlRenderer.cpp
		gl/GlMesh.cpp
		gl/GlShader.cpp
		gl/GlShaderParameter.cpp
		wspp/WebSocketClient.cpp
		wspp/WebSocketServer.cpp)

	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/glfw)

	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/glew)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/xg)

	set(XT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/xt)

	set(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(FLATBUFFERS_INSTALL OFF CACHE BOOL "" FORCE)
	set(FLATBUFFERS_BUILD_SHAREDLIB OFF CACHE BOOL "" FORCE)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/flatbuffers)

	add_library(xe ${SOURCES})
	target_link_libraries(xe glfw glew xg xt)
	target_compile_definitions(xe PUBLIC
		PLATFORM_LINUX PLATFORM_GLFW PLATFORM_WEBSOCKETPP)

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
