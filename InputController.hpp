#pragma once

#include "Keyboard.hpp"
#include <vector>

BEGIN_XE_NAMESPACE

class InputController
{
public:
	InputController(Keyboard &keyboard);
	void newFrame();
	void keyDown(TKey key);
	void keyUp(TKey key);
	void wipe();

private:
	Keyboard &_keyboard;
};

END_XE_NAMESPACE
