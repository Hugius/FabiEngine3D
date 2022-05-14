#include "timer.hpp"

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;
using std::make_unique;

void Timer::createClock(const string & clockId)
{
	if(isClockExisting(clockId))
	{
		abort();
	}

	_clocks.insert({clockId, make_unique<Clock>()});
}

void Timer::deleteClock(const string & clockId)
{
	if(!isClockExisting(clockId))
	{
		abort();
	}

	_clocks.erase(clockId);
}

void Timer::startClock(const string & clockId)
{
	if(!isClockExisting(clockId))
	{
		abort();
	}
	if(isClockStarted(clockId))
	{
		abort();
	}

	const auto epoch = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();

	_clocks.at(clockId)->startEpoch = epoch;
	_clocks.at(clockId)->isStarted = true;
}

void Timer::pauseClock(const string & clockId)
{
	if(!isClockExisting(clockId))
	{
		abort();
	}
	if(!isClockStarted(clockId))
	{
		abort();
	}
	if(isClockPaused(clockId))
	{
		abort();
	}

	const auto epoch = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();

	_clocks.at(clockId)->pauseEpoch = epoch;
	_clocks.at(clockId)->isPaused = true;
}

void Timer::resumeClock(const string & clockId)
{
	if(!isClockExisting(clockId))
	{
		abort();
	}
	if(!isClockStarted(clockId))
	{
		abort();
	}
	if(!isClockPaused(clockId))
	{
		abort();
	}

	const auto epoch = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();

	const auto difference = (epoch - _clocks.at(clockId)->pauseEpoch);

	_clocks.at(clockId)->startEpoch += difference;
	_clocks.at(clockId)->isPaused = false;
}

void Timer::stopClock(const string & clockId)
{
	if(!isClockExisting(clockId))
	{
		abort();
	}
	if(!isClockStarted(clockId))
	{
		abort();
	}

	const auto epoch = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();

	_clocks.at(clockId)->stopEpoch = epoch;
	_clocks.at(clockId)->isStarted = false;
}

const float Timer::getClockDeltaTime(const string & clockId) const
{
	if(!isClockExisting(clockId))
	{
		abort();
	}
	if(isClockStarted(clockId))
	{
		abort();
	}

	const auto difference = (_clocks.at(clockId)->stopEpoch - _clocks.at(clockId)->startEpoch);
	const auto deltaTime = static_cast<float>(difference / 1000000.0f);

	return deltaTime;
}

const bool Timer::isClockExisting(const string & clockId) const
{
	return (_clocks.find(clockId) != _clocks.end());
}

const bool Timer::isClockStarted(const string & clockId) const
{
	if(!isClockExisting(clockId))
	{
		abort();
	}

	return _clocks.at(clockId)->isStarted;
}

const bool Timer::isClockPaused(const string & clockId) const
{
	if(!isClockExisting(clockId))
	{
		abort();
	}
	if(!isClockStarted(clockId))
	{
		abort();
	}

	return _clocks.at(clockId)->isPaused;
}

void Timer::increasePassedUpdateCount()
{
	_passedUpdateCount++;
}

const vector<string> Timer::getClockIds() const
{
	vector<string> result = {};

	for(const auto & [clockId, clock] : _clocks)
	{
		result.push_back(clockId);
	}

	return result;
}

const int Timer::getUpdateCountPerSecond() const
{
	return UPDATES_PER_SECOND;
}

const int Timer::getPassedUpdateCount() const
{
	return _passedUpdateCount;
}