#pragma once

#include "GlHeaders.hpp"
#include "../Util.hpp"
#include <string>
#include <iostream>
#include <vector>

BEGIN_XE_NAMESPACE

class GlShader
{
public:
	const std::string FRAG_SUFFIX = "-frag.glsl";
	const std::string VERT_SUFFIX = "-vert.glsl";

	GlShader(std::string vert, std::string frag);
	GlShader(const GlShader &) = delete;
	GlShader(GlShader &&other);
	GlShader &operator=(const GlShader &) = delete;
	~GlShader();
	GLuint programId() const { return _programId; }

private:
	bool _hydrated;
	GLuint _programId;
};

END_XE_NAMESPACE
