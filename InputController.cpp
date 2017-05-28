#include "InputController.hpp"
#include <algorithm>
#include <iostream>

BEGIN_XE_NAMESPACE

InputController::InputController(Keyboard &keyboard) :
	_keyboard(keyboard)
{ }

void InputController::newFrame()
{
	_keyboard._justPressed.clear();
	_keyboard._justReleased.clear();
}

void InputController::keyDown(TKey key)
{
	_keyboard._justPressed.push_back(key);
	_keyboard._down.push_back(key);
}

void InputController::keyUp(TKey key)
{
	_keyboard._justReleased.push_back(key);
	_keyboard._justPressed.erase(
		std::remove(_keyboard._justPressed.begin(),
			_keyboard._justPressed.end(), key),
		_keyboard._justPressed.end());
	_keyboard._down.erase(
		std::remove(_keyboard._down.begin(),
			_keyboard._down.end(), key),
		_keyboard._down.end());
}

void InputController::wipe()
{
	_keyboard._justPressed.clear();
	_keyboard._justReleased.clear();
	_keyboard._down.clear();
}

END_XE_NAMESPACE
