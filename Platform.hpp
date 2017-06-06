#pragma once

#include "Util.hpp"

#ifdef PLATFORM_GLFW
#include "glfw/GlfwWindow.hpp"
#include "gl/GlRenderer.hpp"
#include "gl/GlMesh.hpp"
#include "gl/GlShader.hpp"
#include "gl/GlShaderParameter.hpp"

namespace xe
{
	typedef GlfwWindow TWindow;
	typedef GlRenderer TRenderer;
	typedef GlMesh TMesh;
	typedef GlShader TShader;
	typedef GlShaderParameter TShaderParameter;
}
#endif

#ifdef PLATFORM_WEB
#include "webgl/WebGlWindow.hpp"
#include "gles2/Gles2Renderer.hpp"
#include "gles2/Gles2Mesh.hpp"
#include "gles2/Gles2Shader.hpp"
#include "gles2/Gles2ShaderParameter.hpp"

namespace xe
{
	typedef WebGlWindow TWindow;
	typedef Gles2Renderer TRenderer;
	typedef Gles2Mesh TMesh;
	typedef Gles2Shader TShader;
	typedef Gles2ShaderParameter TShaderParameter;
}
#endif
