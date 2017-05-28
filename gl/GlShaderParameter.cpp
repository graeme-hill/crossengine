#include "GlShaderParameter.hpp"

BEGIN_XE_NAMESPACE

GlShaderParameter::GlShaderParameter(GlShader &shader, std::string name) :
	_location(glGetUniformLocation(shader.programId(), name.c_str()))
{ }

void GlShaderParameter::set(glm::mat4 matrix)
{
	glUniformMatrix4fv(_location, 1, false, glm::value_ptr(matrix));
}

END_XE_NAMESPACE
