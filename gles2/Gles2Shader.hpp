#pragma once

#include "Gles2Headers.hpp"
#include "../Util.hpp"
#include <string>
#include <iostream>
#include <vector>

BEGIN_XE_NAMESPACE

class Gles2Shader
{
public:
	const std::string FRAG_SUFFIX = "-frag.glsl";
	const std::string VERT_SUFFIX = "-vert.glsl";

	Gles2Shader(std::string vert, std::string frag);
	Gles2Shader(const Gles2Shader &) = delete;
	Gles2Shader(Gles2Shader &&other);
	Gles2Shader &operator=(const Gles2Shader &) = delete;
	~Gles2Shader();
	GLuint programId() const { return _programId; }

private:
	bool _hydrated;
	GLuint _programId;
};

END_XE_NAMESPACE
