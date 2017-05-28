#pragma once

#include "GlHeaders.hpp"
#include "../Util.hpp"
#include "../MeshData.hpp"
#include <iostream>

BEGIN_XE_NAMESPACE

class GlMesh
{
public:
	GlMesh(MeshData data);
	~GlMesh();
	void render();

private:
	MeshData _data;
	GLsizei _indicesCount;
	GLuint _vertexBufferId;
	GLuint _indexBufferId;
	GLuint _bufferAttributesId;
};

END_XE_NAMESPACE
