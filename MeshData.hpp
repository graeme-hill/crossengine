#pragma once

#include <vector>
#include "Util.hpp"

BEGIN_XE_NAMESPACE

class VertexData
{
public:
	VertexData(
		unsigned short location,
		unsigned short valuesPerVert,
		std::vector<float> data) :
		_location(location), _valuesPerVert(valuesPerVert), _data(data)
	{ }

	std::vector<float> data() const { return _data; }
	unsigned short location() const { return _location; }
	unsigned short valuesPerVert() const { return _valuesPerVert; }

private:
	unsigned short _location;
	unsigned short _valuesPerVert;
	std::vector<float> _data;
};

class MeshData
{
public:
	MeshData(
		std::vector<VertexData> vertexData,
		std::vector<unsigned> indices);

	const std::vector<float> &interleavedVertexData() const
	{
		return _interleavedVertexData;
	}

	const std::vector<VertexData> &vertexData() const
	{
		return _vertexData;
	}

	const std::vector<unsigned> &indices() const
	{
		return _indices;
	}
private:
	std::vector<float> _interleavedVertexData;
	std::vector<VertexData> _vertexData;
	std::vector<unsigned> _indices;
};

END_XE_NAMESPACE
