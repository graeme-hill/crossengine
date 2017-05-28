#pragma once

#include "../Util.hpp"
#include "GlfwWindow.hpp"
#include "../gl/GlRenderer.hpp"
#include "../gl/GlMesh.hpp"
#include "../gl/GlShader.hpp"
#include "../gl/GlShaderParameter.hpp"

BEGIN_XE_NAMESPACE

class GlfwPlatform
{
public:
	using Window = GlfwWindow;
	using Renderer = GlRenderer;
	using Mesh = GlMesh;
	using Shader = GlShader;
	using ShaderParameter = GlShaderParameter;
};

END_XE_NAMESPACE
