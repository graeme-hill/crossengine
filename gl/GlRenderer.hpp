#pragma once

#include "GlHeaders.hpp"
#include "../Util.hpp"
#include "GlShader.hpp"

BEGIN_XE_NAMESPACE

class GlRenderer
{
public:
	void startFrame();
	void endFrame();
	void setActiveShader(const GlShader &shader);
};

END_XE_NAMESPACE
