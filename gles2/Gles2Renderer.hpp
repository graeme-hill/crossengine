#pragma once

#include "Gles2Headers.hpp"
#include "../Util.hpp"
#include "Gles2Shader.hpp"

BEGIN_XE_NAMESPACE

class Gles2Renderer
{
public:
	Gles2Renderer();
	void startFrame();
	void endFrame();
	void setActiveShader(const Gles2Shader &shader);
};

END_XE_NAMESPACE
