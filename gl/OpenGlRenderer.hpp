#pragma once

#include <GL/gl.h>
#include "../Util.hpp"

BEGIN_XE_NAMESPACE

class OpenGlRenderer
{
public:
	void startFrame();
	void endFrame();
};

END_XE_NAMESPACE
