#include "GlRenderer.hpp"

BEGIN_XE_NAMESPACE

void GlRenderer::startFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void GlRenderer::endFrame()
{ }

void GlRenderer::setActiveShader(const GlShader &shader)
{
	glUseProgram(shader.programId());
}

END_XE_NAMESPACE
