#pragma once

#include "TKey.hpp"
#include <vector>
#include <iostream>

BEGIN_XE_NAMESPACE

class Keyboard
{
public:
	bool justPressed(TKey key);
	bool justReleased(TKey key);
	bool isDown(TKey key);

	friend class InputController;
private:
	std::vector<TKey> _justPressed;
	std::vector<TKey> _justReleased;
	std::vector<TKey> _down;
};

END_XE_NAMESPACE
