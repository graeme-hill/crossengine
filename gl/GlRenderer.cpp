#include "GlRenderer.hpp"

BEGIN_XE_NAMESPACE

GlRenderer::GlRenderer()
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
}

void GlRenderer::startFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GlRenderer::endFrame()
{ }

void GlRenderer::setActiveShader(const GlShader &shader)
{
	glUseProgram(shader.programId());
}

END_XE_NAMESPACE
