#include "Keyboard.hpp"
#include <algorithm>
#include <iostream>

BEGIN_XE_NAMESPACE

bool Keyboard::justPressed(TKey key)
{
	auto &v = _justPressed;
	return std::find(v.begin(), v.end(), key) != v.end();
}

bool Keyboard::justReleased(TKey key)
{
	auto &v = _justReleased;
	return std::find(v.begin(), v.end(), key) != v.end();
}

bool Keyboard::isDown(TKey key)
{
	auto &v = _down;
	return std::find(v.begin(), v.end(), key) != v.end();
}

END_XE_NAMESPACE
