#pragma once

#include "Util.hpp"
#include <iostream>

BEGIN_CG_NAMESPACE

template <typename TPlatform, typename TGame>
class Engine
{
public:
	using TWindow = typename TPlatform::Window;
	using TRenderer = typename TPlatform::Renderer;

	Engine();
	~Engine();
	void run();

	static Engine<TPlatform, TGame> *instance;
private:
	TWindow _window;
	TRenderer _renderer;
	TGame _game;
};

template <typename TPlatform, typename TGame>
Engine<TPlatform, TGame>::Engine() :
	_window("(>^_^)>"),
	_renderer(),
	_game(_window, _renderer)
{
	//Engine<TPlatform, TGame>::instance = this;
	std::cout << "Engine started with window '" << _window.title() << "'\n";
}

template <typename TPlatform, typename TGame>
void Engine<TPlatform, TGame>::run()
{
	_window.loop();
}

template <typename TPlatform, typename TGame>
Engine<TPlatform, TGame>::~Engine()
{
	std::cout << "game ended\n";
}

void step();

template <typename TPlatform, typename TGame>
void runGame()
{
	Engine<TPlatform, TGame> engine;
	engine.run();
	std::cout << "shutting down\n";
}

END_CG_NAMESPACE
