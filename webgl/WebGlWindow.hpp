#pragma once

#define NO_SDL_GLEXT 1
#define GLFW_INCLUDE_ES3
#define GLEW_USE_LIB_ES20

#include "../Util.hpp"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../gles2/Gles2Headers.hpp"
#include "../InputController.hpp"

BEGIN_XE_NAMESPACE

class WebGlWindow
{
public:
	WebGlWindow(std::string title, InputController inputController);
	~WebGlWindow();
	const std::string &title() const { return _title; }
	void loop(void (*func)(void));
	void startFrame();
	void endFrame();

	friend void keyCallback(
		GLFWwindow *glfwWindow, int key, int scanCode, int action, int mods);
private:
	std::string _title;
	GLFWwindow *_glfwWindow;
	InputController _inputController;
};

END_XE_NAMESPACE
