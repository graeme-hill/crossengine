#pragma once

#include "Util.hpp"

#ifdef PLATFORM_GLFW
#include "gl/GlHeaders.hpp"
#include "xt/FreeType.hpp"
#include "xt/OpenGlWriter.hpp"
BEGIN_XE_NAMESPACE
using TText = xt::TextPlatform<xt::FreeType<xt::OpenGlWriter>>;
END_XE_NAMESPACE
#endif

#ifdef PLATFORM_WEB
BEGIN_XE_NAMESPACE
using TText = xt::TextPlatform<xt::WebText<xt::WebWriter>>;
END_XE_NAMESPACE
#endif
