#pragma once

#include "Gles2Headers.hpp"
#include "../Util.hpp"
#include "../MeshData.hpp"
#include <iostream>

BEGIN_XE_NAMESPACE

class Gles2Mesh
{
public:
	Gles2Mesh(MeshData data);
	~Gles2Mesh();
	void render();

private:
	MeshData _data;
	GLsizei _indicesCount;
	GLuint _vertexBufferId;
	GLuint _indexBufferId;
	GLuint _bufferAttributesId;
};

END_XE_NAMESPACE
