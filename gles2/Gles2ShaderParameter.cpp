#include "Gles2ShaderParameter.hpp"

BEGIN_XE_NAMESPACE

Gles2ShaderParameter::Gles2ShaderParameter(Gles2Shader &shader, std::string name) :
	_location(glGetUniformLocation(shader.programId(), name.c_str()))
{ }

void Gles2ShaderParameter::set(glm::mat4 matrix)
{
	glUniformMatrix4fv(_location, 1, false, glm::value_ptr(matrix));
}

END_XE_NAMESPACE
