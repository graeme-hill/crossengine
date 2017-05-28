#pragma once

#include "GlHeaders.hpp"
#include "GlShader.hpp"
#include "../Util.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

BEGIN_XE_NAMESPACE

class GlShaderParameter
{
public:
	GlShaderParameter(GlShader &shader, std::string name);

	void set(glm::mat4 matrix);

private:
	GLuint _location;
};

END_XE_NAMESPACE
