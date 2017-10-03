#include "MeshData.hpp"
#include <iostream>
#include <numeric>

BEGIN_XE_NAMESPACE

std::vector<float> interleave(std::vector<VertexData> data)
{
	if (data.size() == 0)
		return std::vector<float>();

	auto vertCount = data[0].data().size() / data[0].valuesPerVert();

	if (vertCount == 0)
	{
		std::cout << "ASSERTION FAILURE: vertCount is zero\n";
	}

	unsigned size = 0;
	for (unsigned i = 0; i < data.size(); i++)
	{
		size += data[i].data().size();
	}
	auto totalValuesPerVert = size / vertCount;
	std::vector<float> result(size);
	auto localOffset = 0;

	for (unsigned dataSetIndex = 0; dataSetIndex < data.size(); dataSetIndex++)
	{
		auto thisData = data[dataSetIndex];
		auto valuesPerVert = thisData.data().size() / vertCount;

		for (unsigned vertIndex = 0; vertIndex < vertCount; vertIndex++)
		{
			for (unsigned valIndex = 0; valIndex < valuesPerVert; valIndex++)
			{
				auto index = (vertIndex * totalValuesPerVert)
					+ valIndex + localOffset;
				result[index] =
					thisData.data()[(vertIndex * valuesPerVert) + valIndex];
			}
		}

		localOffset += valuesPerVert;
	}

	return result;
}

MeshData::MeshData(
	std::vector<VertexData> vertexData,
	std::vector<unsigned> indices) :
	_interleavedVertexData(interleave(vertexData)),
	_vertexData(vertexData),
	_indices(indices)
{ }

END_XE_NAMESPACE
