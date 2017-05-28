#pragma once

#include "Util.hpp"



#ifdef PLATFORM_GLFW
#include "glfw/GlfwKey.hpp"

BEGIN_XE_NAMESPACE
typedef GlfwKey TKey;
END_XE_NAMESPACE
#endif
