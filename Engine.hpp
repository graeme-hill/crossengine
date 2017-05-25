#pragma once

#include "Util.hpp"
#include "FpsMonitor.hpp"
#include <iostream>

BEGIN_XE_NAMESPACE

template <typename TPlatform, typename TGame>
class Engine
{
public:
	using TWindow = typename TPlatform::Window;
	using TRenderer = typename TPlatform::Renderer;

	Engine();
	~Engine();
	void run();
	void step();

	static Engine<TPlatform, TGame> *instance;
private:
	TWindow _window;
	TRenderer _renderer;
	TGame _game;
	FpsMonitor _fps;
};

template <typename TPlatform, typename TGame>
Engine<TPlatform, TGame> *Engine<TPlatform, TGame>::instance = nullptr;

template <typename TPlatform, typename TGame>
void step()
{
	Engine<TPlatform, TGame>::instance->step();
}

template <typename TPlatform, typename TGame>
Engine<TPlatform, TGame>::Engine() :
	_window("(>^_^)>"),
	_renderer(),
	_game(_window, _renderer),
	_fps([](int c) { std::cout << c << "\n"; })
{
	Engine<TPlatform, TGame>::instance = this;
	std::cout << "Engine started with window '" << _window.title() << "'\n";
}

template <typename TPlatform, typename TGame>
void Engine<TPlatform, TGame>::run()
{
	_window.loop(::xe::step<TPlatform, TGame>);
}

template <typename TPlatform, typename TGame>
Engine<TPlatform, TGame>::~Engine()
{
	std::cout << "game ended\n";
}

template <typename TPlatform, typename TGame>
void Engine<TPlatform, TGame>::step()
{
	float delta = _fps.tick();
	_window.startFrame();
	_renderer.startFrame();
	_game.step(delta);
	_renderer.endFrame();
	_window.endFrame();
}

template <typename TPlatform, typename TGame>
void runGame()
{
	Engine<TPlatform, TGame> engine;
	engine.run();
	std::cout << "shutting down\n";
}

END_XE_NAMESPACE
