#pragma once

#include <vector>
#include <string>
#include "Util.hpp"

BEGIN_XE_NAMESPACE

struct ModelData
{
	std::vector<float> positions;
	std::vector<float> normals;
	std::vector<float> uvs;
	std::vector<unsigned int> indices;
};

ModelData readObjFileFlat(std::string path);
ModelData readObjFileSmooth(std::string path);

END_XE_NAMESPACE
