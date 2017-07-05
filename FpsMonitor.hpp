#pragma once

#include <chrono>
#include <functional>
#include "Util.hpp"
#include "Common.hpp"

BEGIN_XE_NAMESPACE

using Clock = std::chrono::high_resolution_clock;

class FpsMonitor
{
public:
	FpsMonitor(std::function<void(int, uint64_t)> fpsCallback) :
		_last(Clock::now()),
		_lastFpsUpdate(_last),
		_epoch(_last),
		_fps(0),
		_count(0),
		_fpsCallback(fpsCallback)
	{ }

	Frame tick()
	{
		auto now = Clock::now();
		auto diff = now - _last;
		auto elapsed = now - _epoch;
		auto sinceFpsUpdate = now - _lastFpsUpdate;
		std::chrono::seconds updateFrequency(1);

		//std::chrono::duration<std::chrono::nanoseconds> elapsedNanos = elapsed;
		std::chrono::duration<float> floatDuration = diff;
		float deltaMillis =
			std::chrono::duration_cast<std::chrono::nanoseconds>(
				floatDuration).count() / 1000000.0f;
		uint64_t elapsedNanos =
			std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

		if (sinceFpsUpdate >= updateFrequency)
		{
			_fps = _count;
			_fpsCallback(_fps, elapsedNanos);
			_lastFpsUpdate = now;
			_count = 0;
		}
		_last = now;
		_count++;

		return { deltaMillis, elapsedNanos };
	}

private:
	Clock::time_point _last;
	Clock::time_point _lastFpsUpdate;
	Clock::time_point _epoch;
	int _fps;
	int _count;

	std::function<void(int, uint64_t)> _fpsCallback;
};

END_XE_NAMESPACE
