#pragma once

#include "Util.hpp"
#include "glfw/GlfwWindow.hpp"
#include "gl/GlRenderer.hpp"
#include "gl/GlMesh.hpp"
#include "gl/GlShader.hpp"
#include "gl/GlShaderParameter.hpp"

BEGIN_XE_NAMESPACE

#ifdef PLATFORM_GLFW
typedef GlfwWindow TWindow;
typedef GlRenderer TRenderer;
typedef GlMesh TMesh;
typedef GlShader TShader;
typedef GlShaderParameter TShaderParameter;
#endif

END_XE_NAMESPACE
