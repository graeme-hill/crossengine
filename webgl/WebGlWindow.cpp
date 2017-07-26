#include "WebGlWindow.hpp"
#include <emscripten.h>
#include <iostream>

BEGIN_XE_NAMESPACE

WebGlWindowEventBuffer::WebGlWindowEventBuffer() : _buffer(20)
{ }

std::vector<WebGlWindowEvent>::iterator WebGlWindowEventBuffer::begin()
{
	return _buffer.begin();
}

std::vector<WebGlWindowEvent>::iterator WebGlWindowEventBuffer::end()
{
	return _buffer.end();
}

void WebGlWindowEventBuffer::clear()
{
	_buffer.clear();
}

void WebGlWindowEventBuffer::push(WebGlWindowEvent event)
{
	_buffer.push_back(event);
}

void framebufferResizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyCallback(
	GLFWwindow *glfwWindow, int key, int scanCode, int action, int mods)
{
	auto obj = glfwGetWindowUserPointer(glfwWindow);
	WebGlWindow *window = static_cast<WebGlWindow *>(obj);
	window->_eventBuffer.push({ key, scanCode, action, mods });
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

void WebGlWindow::handleEvents()
{
	for (auto event : _eventBuffer)
	{
		auto converted = (TKey)event.key;

		switch (event.action)
		{
		case GLFW_PRESS:
			_inputController.keyDown(converted);
			break;
		case GLFW_RELEASE:
			_inputController.keyUp(converted);
			break;
		case GLFW_REPEAT:
			break;
		case GLFW_KEY_UNKNOWN:
			break;
		default:
			break;
		}
	}

	_eventBuffer.clear();
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
	handleEvents();
}

void WebGlWindow::endFrame()
{
}

END_XE_NAMESPACE
