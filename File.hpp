#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Util.hpp"

BEGIN_XE_NAMESPACE

class File
{
public:
	static std::string readAll(std::string path);
	static std::string readVertShaderText(std::string name);
	static std::string readFragShaderText(std::string name);
};

END_XE_NAMESPACE
