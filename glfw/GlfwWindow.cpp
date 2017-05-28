#include "GlfwWindow.hpp"
#include <iostream>

BEGIN_XE_NAMESPACE

void keyCallback(
	GLFWwindow *window, int key, int scanCode, int action, int mode)
{
	std::cout << "Key: " << key << " Scan Code: " << scanCode << std::endl;
}

GlfwWindow::GlfwWindow(std::string title) :
	_title(title),
	_glfwWindow(nullptr)
{
	if (!glfwInit())
	{
		std::cout << "ERROR: Could not init GLFW!\n";
	}

	_glfwWindow = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
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

	glfwSetKeyCallback(_glfwWindow, keyCallback);

	glClearColor(0.0, 0.0, 1.0, 0.0);

	std::cout << "opening window\n";
}

GlfwWindow::~GlfwWindow()
{
	glfwTerminate();
	std::cout << "closing window\n";
}

void GlfwWindow::loop(void (*func)(void))
{
	std::cout << "start looping now!\n";
	while (!glfwWindowShouldClose(_glfwWindow))
	{
		func();
	}
}

void GlfwWindow::startFrame()
{
	glfwPollEvents();
}

void GlfwWindow::endFrame()
{
	glfwSwapBuffers(_glfwWindow);
	glFlush();
}

END_XE_NAMESPACE
