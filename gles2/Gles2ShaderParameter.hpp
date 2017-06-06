#pragma once

#include "Gles2Headers.hpp"
#include "Gles2Shader.hpp"
#include "../Util.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

BEGIN_XE_NAMESPACE

class Gles2ShaderParameter
{
public:
	Gles2ShaderParameter(Gles2Shader &shader, std::string name);

	void set(glm::mat4 matrix);

private:
	GLuint _location;
};

END_XE_NAMESPACE
