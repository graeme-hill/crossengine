#include "AssetReaders.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

BEGIN_XE_NAMESPACE

bool startsWith(std::string s, std::string prefix)
{
	if (s.size() < prefix.size())
		return false;
	auto start = s.substr(0, prefix.size());
	return start == prefix;
}

void appendFromObjLine3f(std::vector<float> &target, std::istringstream &iss)
{
	float x, y, z;
	iss >> x >> y >> z;
	target.push_back(x);
	target.push_back(y);
	target.push_back(z);
}

void appendFromObjLine2f(std::vector<float> &target, std::istringstream &iss)
{
	float x, y;
	iss >> x >> y;
	target.push_back(x);
	target.push_back(y);
}

void appendVertexFlat(
	ModelData &data,
	std::vector<float> &rawPositions,
	std::vector<float> &rawUvs,
	std::vector<float> &rawNormals,
	unsigned int vp,
	unsigned int vuv,
	unsigned int vn)
{
	auto pOffset = (vp - 1) * 3;
	auto uvOffset = (vuv - 1) * 2;
	auto nOffset = (vn - 1) * 3;

	data.positions.push_back(rawPositions[pOffset + 0]);
	data.positions.push_back(rawPositions[pOffset + 1]);
	data.positions.push_back(rawPositions[pOffset + 2]);

	data.uvs.push_back(rawUvs[uvOffset + 0]);
	data.uvs.push_back(rawUvs[uvOffset + 1]);

	data.normals.push_back(rawNormals[nOffset + 0]);
	data.normals.push_back(rawNormals[nOffset + 1]);
	data.normals.push_back(rawNormals[nOffset + 2]);
}

void appendVertexSmooth(
	ModelData &data,
	std::vector<float> &rawPositions,
	std::vector<float> &rawUvs,
	std::vector<float> &rawNormals,
	unsigned int vp,
	unsigned int vuv,
	unsigned int vn)
{
	auto uvSource = (vuv - 1) * 2;
	auto uvDest = (vp - 1) * 2;
	auto nSource = (vn - 1) * 3;
	auto nDest = (vp - 1) * 3;

	data.uvs[uvDest + 0] = rawUvs[uvSource + 0];
	data.uvs[uvDest + 1] = rawUvs[uvSource + 1];

	data.normals[nDest + 0] = rawNormals[nSource + 0];
	data.normals[nDest + 1] = rawNormals[nSource + 1];
	data.normals[nDest + 2] = rawNormals[nSource + 2];
}

void appendFaceFromObjLineFlat(
	ModelData &data,
	std::vector<float> &rawPositions,
	std::vector<float> &rawUvs,
	std::vector<float> &rawNormals,
	std::istringstream &iss)
{
	char _;
	unsigned int v1p, v1uv, v1n, v2p, v2uv, v2n, v3p, v3uv, v3n;
	iss >> v1p >> _ >> v1uv >> _ >> v1n >> v2p >> _ >> v2uv >> _ >> v2n >> v3p
		>> _ >> v3uv >> _ >> v3n;

	appendVertexFlat(data, rawPositions, rawUvs, rawNormals, v1p, v1uv, v1n);
	appendVertexFlat(data, rawPositions, rawUvs, rawNormals, v2p, v2uv, v2n);
	appendVertexFlat(data, rawPositions, rawUvs, rawNormals, v3p, v3uv, v3n);

	auto faceIndex = data.indices.size();
	data.indices.push_back(faceIndex + 0);
	data.indices.push_back(faceIndex + 1);
	data.indices.push_back(faceIndex + 2);
}

void appendFaceFromObjLineSmooth(
	ModelData &data,
	std::vector<float> &rawPositions,
	std::vector<float> &rawUvs,
	std::vector<float> &rawNormals,
	std::istringstream &iss)
{
	char _;
	unsigned int v1p, v1uv, v1n, v2p, v2uv, v2n, v3p, v3uv, v3n;
	iss >> v1p >> _ >> v1uv >> _ >> v1n >> v2p >> _ >> v2uv >> _ >> v2n >> v3p
		>> _ >> v3uv >> _ >> v3n;

	appendVertexSmooth(data, rawPositions, rawUvs, rawNormals, v1p, v1uv, v1n);
	appendVertexSmooth(data, rawPositions, rawUvs, rawNormals, v2p, v2uv, v2n);
	appendVertexSmooth(data, rawPositions, rawUvs, rawNormals, v3p, v3uv, v3n);

	data.indices.push_back(v1p);
	data.indices.push_back(v2p);
	data.indices.push_back(v3p);
}

ModelData readObjFileSmooth(std::string path)
{
	ModelData data;
	std::ifstream infile(path);
	std::string line;

	std::vector<float> rawPositions;
	std::vector<float> rawNormals;
	std::vector<float> rawUvs;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v")
		{
			appendFromObjLine3f(rawPositions, iss);
		}
		else if (prefix == "vt")
		{
			appendFromObjLine2f(rawUvs, iss);
		}
		else if (prefix == "vn")
		{
			appendFromObjLine3f(rawNormals, iss);
		}
		else if (prefix == "f")
		{
			if (data.positions.size() == 0)
			{
				data.positions = rawPositions;

				if (rawNormals.size() != 0)
				{
					data.normals = std::vector<float>(rawPositions.size());
				}
				if (rawUvs.size() != 0)
				{
					data.uvs =
						std::vector<float>((rawPositions.size() / 3) * 2);
				}
			}

			appendFaceFromObjLineSmooth(
				data, rawPositions, rawUvs, rawNormals, iss);
		}
	}

	return data;
}

ModelData readObjFileFlat(std::string path)
{
	ModelData data;
	std::ifstream infile(path);
	std::string line;

	std::vector<float> rawPositions;
	std::vector<float> rawNormals;
	std::vector<float> rawUvs;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v")
		{
			appendFromObjLine3f(rawPositions, iss);
		}
		else if (prefix == "vt")
		{
			appendFromObjLine2f(rawUvs, iss);
		}
		else if (prefix == "vn")
		{
			appendFromObjLine3f(rawNormals, iss);
		}
		else if (prefix == "f")
		{
			appendFaceFromObjLineFlat(
				data, rawPositions, rawUvs, rawNormals, iss);
		}
	}

	return data;
}

END_XE_NAMESPACE
