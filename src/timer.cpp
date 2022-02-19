#include "timer.hpp"
#include "logger.hpp"

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;
using std::make_pair;
using std::make_unique;

void Timer::createClock(const string& id)
{
	if(isClockExisting(id))
	{
		abort();
	}

	_clocks.insert(make_pair(id, make_unique<Clock>()));
}

void Timer::deleteClock(const string& id)
{
	if(!isClockExisting(id))
	{
		abort();
	}

	_clocks.erase(id);
}

void Timer::startClock(const string& id)
{
	if(!isClockExisting(id))
	{
		abort();
	}
	if(isClockStarted(id))
	{
		abort();
	}

	const auto epoch = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();

	_clocks.at(id)->startEpoch = epoch;
	_clocks.at(id)->isStarted = true;
}

void Timer::pauseClock(const string& id)
{
	if(!isClockExisting(id))
	{
		abort();
	}
	if(!isClockStarted(id))
	{
		abort();
	}
	if(isClockPaused(id))
	{
		abort();
	}

	const auto epoch = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();

	_clocks.at(id)->pauseEpoch = epoch;
	_clocks.at(id)->isPaused = true;
}

void Timer::resumeClock(const string& id)
{
	if(!isClockExisting(id))
	{
		abort();
	}
	if(!isClockStarted(id))
	{
		abort();
	}
	if(!isClockPaused(id))
	{
		abort();
	}

	const auto epoch = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();

	const auto difference = (epoch - _clocks.at(id)->pauseEpoch);

	_clocks.at(id)->startEpoch += difference;
	_clocks.at(id)->isPaused = false;
}

void Timer::stopClock(const string& id)
{
	if(!isClockExisting(id))
	{
		abort();
	}
	if(!isClockStarted(id))
	{
		abort();
	}

	const auto epoch = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();

	_clocks.at(id)->stopEpoch = epoch;
	_clocks.at(id)->isStarted = false;
}

const float Timer::getClockDeltaTime(const string& id) const
{
	if(!isClockExisting(id))
	{
		abort();
	}
	if(isClockStarted(id))
	{
		abort();
	}

	const auto difference = (_clocks.at(id)->stopEpoch - _clocks.at(id)->startEpoch);
	const auto deltaTime = static_cast<float>(difference / 1000000.0f);

	return deltaTime;
}

const bool Timer::isClockExisting(const string& id) const
{
	return (_clocks.find(id) != _clocks.end());
}

const bool Timer::isClockStarted(const string& id) const
{
	if(!isClockExisting(id))
	{
		abort();
	}

	return _clocks.at(id)->isStarted;
}

const bool Timer::isClockPaused(const string& id) const
{
	if(!isClockExisting(id))
	{
		abort();
	}
	if(!isClockStarted(id))
	{
		abort();
	}

	return _clocks.at(id)->isPaused;
}

void Timer::increasePassedUpdateCount()
{
	_passedUpdateCount++;
}

const vector<string> Timer::getClockIds() const
{
	vector<string> result;

	for(const auto& [key, clock] : _clocks)
	{
		result.push_back(key);
	}

	return result;
}

const unsigned int Timer::getUpdateCountPerSecond() const
{
	return UPDATES_PER_SECOND;
}

const unsigned int Timer::getPassedUpdateCount() const
{
	return _passedUpdateCount;
}