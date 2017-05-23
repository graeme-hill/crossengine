#include "MeshData.hpp"

#include <numeric>

BEGIN_XR_NAMESPACE

std::vector<float> interleave(std::vector<VertexData> data)
{
	if (data.size() == 0)
		return std::vector<float>();

	auto vertCount = data[0].data().size() / data[0].valuesPerVert();
	unsigned int size = 0;
	for (auto i = 0; i < data.size(); i++)
	{
		size += data[i].data().size();
	}
	auto totalValuesPerVert = size / vertCount;
	std::vector<float> result(size);
	auto localOffset = 0;

	for (auto dataSetIndex = 0; dataSetIndex < data.size(); dataSetIndex++)
	{
		auto thisData = data[dataSetIndex];
		auto valuesPerVert = thisData.data().size() / vertCount;

		for (auto vertIndex = 0; vertIndex < vertCount; vertIndex++)
		{
			for (auto valueIndex = 0; valueIndex < valuesPerVert; valueIndex++)
			{
				auto index = (vertIndex * totalValuesPerVert)
					+ valueIndex + localOffset;
				result[index] =
					thisData.data()[(vertIndex * valuesPerVert) + valueIndex];
			}
		}

		localOffset += valuesPerVert;
	}

	return result;
}

MeshData::MeshData(
	std::vector<VertexData> vertexData,
	std::vector<unsigned int> indices) :
	_interleavedVertexData(interleave(vertexData)), _indices(indices)
{ }

END_XR_NAMESPACE
