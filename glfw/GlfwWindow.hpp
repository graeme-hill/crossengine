#pragma once

#define GLEW_STATIC
#include "../Util.hpp"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../gl/GlHeaders.hpp"
#include "../InputController.hpp"

BEGIN_XE_NAMESPACE

class GlfwWindow
{
public:
	GlfwWindow(std::string title, InputController inputController);
	~GlfwWindow();
	const std::string &title() const { return _title; }
	void loop(void (*func)(void));
	void startFrame();
	void endFrame();

private:
	std::string _title;
	GLFWwindow *_glfwWindow;
	InputController _inputController;
};

END_XE_NAMESPACE
