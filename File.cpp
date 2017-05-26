#include "File.hpp"

BEGIN_XE_NAMESPACE

std::string File::readAll(std::string filePath)
{
	std::string content;
	std::ifstream fileStream(filePath.c_str(), std::ios::in);

	if (!fileStream.is_open())
	{
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

std::string File::readVertShaderText(std::string name)
{
	auto path = std::string("assets/") + name + "-vert.glsl";
	return readAll(path);
}

std::string File::readFragShaderText(std::string name)
{
	auto path = std::string("assets/") + name + "-frag.glsl";
	return readAll(path);
}

END_XE_NAMESPACE
