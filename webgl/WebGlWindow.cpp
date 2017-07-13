#include "WebGlWindow.hpp"
#include <emscripten.h>
#include <iostream>

BEGIN_XE_NAMESPACE

void framebufferResizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyCallback(
	GLFWwindow *glfwWindow, int key, int scanCode, int action, int mods)
{
	auto converted = (TKey)key;
	auto obj = glfwGetWindowUserPointer(glfwWindow);
	WebGlWindow *window = static_cast<WebGlWindow *>(obj);

	switch (action)
	{
	case GLFW_PRESS:
		window->_inputController.keyDown(converted);
		break;
	case GLFW_RELEASE:
		window->_inputController.keyUp(converted);
		break;
	case GLFW_REPEAT:
		break;
	case GLFW_KEY_UNKNOWN:
		break;
	default:
		break;
	}
}

WebGlWindow::WebGlWindow(std::string title, InputController inputController) :
	_title(title),
	_glfwWindow(nullptr),
	_inputController(inputController)
{
	if (!glfwInit())
	{
		std::cout << "ERROR: Could not init GLFW!\n";
	}

	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_glfwWindow = glfwCreateWindow(1600, 900, title.c_str(), NULL, NULL);
	if (!_glfwWindow)
	{
		glfwTerminate();
		std::cout << "ERROR: Could not create window\n";
	}

	glfwMakeContextCurrent(_glfwWindow);

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "glewInit failed!\n";
	}

	glfwSetWindowUserPointer(_glfwWindow, (void *)this);

	glfwSetKeyCallback(_glfwWindow, keyCallback);
	glfwSetFramebufferSizeCallback(_glfwWindow, framebufferResizeCallback);

	std::cout << "opening window\n";
}

WebGlWindow::~WebGlWindow()
{
	glfwTerminate();
	std::cout << "closing window\n";
}

void WebGlWindow::loop(void (*func)(void))
{
	std::cout << "start looping now!\n";
	emscripten_set_main_loop(func, 0, 1);
}

void WebGlWindow::startFrame()
{
	_inputController.newFrame();
}

void WebGlWindow::endFrame()
{
}

END_XE_NAMESPACE
