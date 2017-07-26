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

struct WebGlWindowEvent
{
	int key;
	int scanCode;
	int action;
	int mods;
};

class WebGlWindowEventBuffer
{
public:
	WebGlWindowEventBuffer();
	std::vector<WebGlWindowEvent>::iterator begin();
	std::vector<WebGlWindowEvent>::iterator end();
	void push(WebGlWindowEvent event);
	void clear();

private:
	std::vector<WebGlWindowEvent> _buffer;
};

class WebGlWindow
{
public:
	WebGlWindow(std::string title, InputController inputController);
	~WebGlWindow();
	const std::string &title() const { return _title; }
	void loop(void (*func)(void));
	void startFrame();
	void endFrame();
	void handleEvents();

	friend void keyCallback(
		GLFWwindow *glfwWindow, int key, int scanCode, int action, int mods);
private:
	std::string _title;
	GLFWwindow *_glfwWindow;
	InputController _inputController;
	WebGlWindowEventBuffer _eventBuffer;
};

END_XE_NAMESPACE
