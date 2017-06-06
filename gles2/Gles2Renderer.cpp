#include "Gles2Renderer.hpp"

BEGIN_XE_NAMESPACE

Gles2Renderer::Gles2Renderer()
{
	glClearColor(0.0, 0.1, 0.5, 0.1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void Gles2Renderer::startFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Gles2Renderer::endFrame()
{ }

void Gles2Renderer::setActiveShader(const Gles2Shader &shader)
{
	glUseProgram(shader.programId());
}

END_XE_NAMESPACE
