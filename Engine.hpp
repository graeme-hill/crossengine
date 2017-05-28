#pragma once

#include "Util.hpp"
#include "Platform.hpp"
#include "FpsMonitor.hpp"
#include "Keyboard.hpp"
#include "InputController.hpp"
#include <iostream>

BEGIN_XE_NAMESPACE

template <typename TGame>
class Engine
{
public:
	Engine();
	~Engine();
	void run();
	void step();

	static Engine<TGame> *instance;
private:
	Keyboard _keyboard;
	TWindow _window;
	TRenderer _renderer;
	TGame _game;
	FpsMonitor _fps;
};

template <typename TGame>
Engine<TGame> *Engine<TGame>::instance = nullptr;

template <typename TGame>
void step()
{
	Engine<TGame>::instance->step();
}

template <typename TGame>
Engine<TGame>::Engine() :
	_window("(>^_^)>", InputController(_keyboard)),
	_renderer(),
	_game(_window, _renderer),
	_fps([](int c) { std::cout << c << "\n"; })
{
	Engine<TGame>::instance = this;
	std::cout << "Engine started with window '" << _window.title() << "'\n";
}

template <typename TGame>
void Engine<TGame>::run()
{
	_window.loop(::xe::step<TGame>);
}

template <typename TGame>
Engine<TGame>::~Engine()
{
	std::cout << "game ended\n";
}

template <typename TGame>
void Engine<TGame>::step()
{
	float delta = _fps.tick();
	_window.startFrame();
	_renderer.startFrame();
	_game.step(delta);
	_renderer.endFrame();
	_window.endFrame();
}

template <typename TGame>
void play()
{
	Engine<TGame> engine;
	engine.run();
	std::cout << "shutting down\n";
}

END_XE_NAMESPACE
