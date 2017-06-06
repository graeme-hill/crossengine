#include "Gles2Shader.hpp"

BEGIN_XE_NAMESPACE

Gles2Shader::Gles2Shader(std::string vert, std::string frag) :
	_hydrated(true),
	_programId(0)
{
	auto vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	auto fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	auto vertShaderCode = vert.c_str();
	auto fragShaderCode = frag.c_str();

	GLint result = GL_FALSE;
	int logLength;

	glShaderSource(vertexShaderId, 1, &vertShaderCode, NULL);
	glCompileShader(vertexShaderId);
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		std::cout << "Error compiling vertex shader:\n";
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
		glGetShaderInfoLog(vertexShaderId, logLength, NULL, &vertShaderError[0]);
		std::cout << &vertShaderError[0] << std::endl;
	}

	glShaderSource(fragmentShaderId, 1, &fragShaderCode, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		std::cout << "Error compiling fragment shader:\n";
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> fragShaderError((logLength > 1) ? logLength : 1);
		glGetShaderInfoLog(fragmentShaderId, logLength, NULL, &fragShaderError[0]);
		std::cout << &fragShaderError[0] << std::endl;
	}

	_programId = glCreateProgram();
	glAttachShader(_programId, vertexShaderId);
	glAttachShader(_programId, fragmentShaderId);
	glLinkProgram(_programId);

	glGetProgramiv(_programId, GL_LINK_STATUS, &result);
	if (!result)
	{
		std::cout << "Error linking program:\n";
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> programError((logLength > 1) ? logLength : 1);
		glGetProgramInfoLog(_programId, logLength, NULL, &programError[0]);
		std::cout << &programError[0] << std::endl;
	}

	// Textures
	glUseProgram(_programId);
	// for (auto i = 0; i < samplers.size(); i++)
	// {
	// 	auto s = samplers[i];
	// 	glUniform1i(s.uniformLocation(), s.textureUnit());
	// }

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

Gles2Shader::Gles2Shader(Gles2Shader &&other) :
	_hydrated(true),
	_programId(other._programId)
{
	other._hydrated = false;
	other._programId = 0;
}

Gles2Shader::~Gles2Shader()
{
	if (_hydrated)
	{
		glDeleteProgram(_programId);
		_hydrated = false;
	}
}

END_XE_NAMESPACE
