#pragma once

#include <glm/glm.hpp>
#include "Util.hpp"

BEGIN_XE_NAMESPACE

struct Intersection
{
	bool found;
	glm::vec3 point;

	static Intersection no()
	{
		return { false, glm::vec3(0.0f, 0.0f, 0.0f) };
	}

	static Intersection yes(glm::vec3 p)
	{
		return { true, p };
	}
};

END_XE_NAMESPACE
