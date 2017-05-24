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

END_XE_NAMESPACE
