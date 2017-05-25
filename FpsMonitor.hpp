#pragma once

#include <chrono>
#include <functional>

BEGIN_XE_NAMESPACE

using Clock = std::chrono::high_resolution_clock;

class FpsMonitor
{
public:
	FpsMonitor(std::function<void(int)> fpsCallback) :
		_last(Clock::now()),
		_lastFpsUpdate(_last),
		_fps(0),
		_count(0),
		_fpsCallback(fpsCallback)
	{ }

	float tick()
	{
		auto now = Clock::now();
		auto diff = now - _last;
		auto sinceFpsUpdate = now - _lastFpsUpdate;
		std::chrono::seconds updateFrequency(1);

		std::chrono::duration<float> floatDuration = diff;
		float deltaMillis =
			std::chrono::duration_cast<std::chrono::nanoseconds>(
				floatDuration).count() / 1000000.0f;

		if (sinceFpsUpdate >= updateFrequency)
		{
			_fps = _count;
			_fpsCallback(_fps);
			_lastFpsUpdate = now;
			_count = 0;
		}
		_last = now;
		_count++;

		return deltaMillis;
	}

private:
	Clock::time_point _last;
	Clock::time_point _lastFpsUpdate;
	int _fps;
	int _count;

	std::function<void(int)> _fpsCallback;
};

END_XE_NAMESPACE
