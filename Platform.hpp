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
