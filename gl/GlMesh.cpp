#include "GlMesh.hpp"

BEGIN_XE_NAMESPACE

GlMesh::GlMesh(MeshData data) :
	_data(data),
	_indicesCount(data.indices().size()),
	_vertexBufferId(-1),
	_indexBufferId(-1),
	_bufferAttributesId(-1)
{
	auto interleavedVertexData = data.interleavedVertexData();
	auto vertexData = data.vertexData();
	auto indices = data.indices();

	// VAO
	glGenVertexArrays(1, &_bufferAttributesId);
	glBindVertexArray(_bufferAttributesId);

	// VBO
	glGenBuffers(1, &_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
	glBufferData(
		GL_ARRAY_BUFFER,
		interleavedVertexData.size() * sizeof(GLfloat),
		&interleavedVertexData[0],
		GL_STATIC_DRAW);

	unsigned short totalBytesPerVert = 0;
	for (unsigned i = 0; i < vertexData.size(); i++)
	{
		totalBytesPerVert += sizeof(GLfloat)
			* vertexData[i].valuesPerVert();
	}

	uintptr_t offset = 0;
	for (unsigned i = 0; i < vertexData.size(); i++)
	{
		auto data = vertexData[i];
		glVertexAttribPointer(
			data.location(),
			data.valuesPerVert(),
			GL_FLOAT,
			GL_FALSE,
			totalBytesPerVert,
			(void *)offset);
		glEnableVertexAttribArray(data.location());
		offset += sizeof(GLfloat) * data.valuesPerVert();
	}

	// EBO
	glGenBuffers(1, &_indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		_indicesCount * sizeof(unsigned int),
		&indices[0],
		GL_STATIC_DRAW);

	// opop: These might not be necessary
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GlMesh::~GlMesh()
{
	glDeleteBuffers(1, &_vertexBufferId);
	glDeleteBuffers(1, &_indexBufferId);
	glDeleteVertexArrays(1, &_bufferAttributesId);
}

void GlMesh::render()
{
	glBindVertexArray(_bufferAttributesId);
	glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT, 0);
}

END_XE_NAMESPACE
