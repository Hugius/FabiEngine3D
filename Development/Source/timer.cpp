#include "timer.hpp"
#include "logger.hpp"

void Timer::start()
{
	// Error checking
	if (_isStarted)
	{
		Logger::throwWarning("Timer tried to start, but was already started!");
		return;
	}

	// Start
	QueryPerformanceFrequency(&_frequency);
	QueryPerformanceCounter(&_time1);
	_isStarted = true;
}

float Timer::stop()
{
	// Error checking
	if (!_isStarted)
	{
		Logger::throwWarning("Timer tried to stop, but was not started!");
		return 0.0f;
	}

	// Stop
	QueryPerformanceCounter(&_time2);
	_isStarted = false;
	return static_cast<float>((_time2.QuadPart - _time1.QuadPart) * 1000.0f / _frequency.QuadPart);
}

void Timer::startDeltaPart(const string& ID)
{
	// Error checking
	if (!_currentID.empty())
	{
		Logger::throwError("Timer tried to start delta part, but was already started!");
		return;
	}

	// Start
	QueryPerformanceFrequency(&_specificFrequency);
	QueryPerformanceCounter(&_specificTime1);
	_currentID = ID;
}

void Timer::stopDeltaPart()
{
	// Error checking
	if (_currentID.empty())
	{
		Logger::throwError("Timer tried to stop delta part, but was not started!");
		return;
	}

	// Stop
	QueryPerformanceCounter(&_specificTime2);
	_deltaParts[_currentID] = static_cast<float>((_specificTime2.QuadPart - _specificTime1.QuadPart) * 1000.0f / _specificFrequency.QuadPart);
	_currentID = "";
}

float Timer::getDeltaPart(const string& ID)
{
	return _deltaParts[ID];
}

float Timer::getDeltaPartSum()
{
	float sum = 0.0f;

	for (const auto& part : _deltaParts)
	{
		sum += part.second;
	}

	return sum;
}

void Timer::sleep(int microseconds)
{
	__int64 time1 = 0;
	__int64 time2 = 0;
	__int64 frequency = 0;

	QueryPerformanceCounter((LARGE_INTEGER *)&time1);
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	do 
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&time2);
	} 
	while ((time2 - time1) < microseconds);
}

void Timer::increasePassedFrameCount()
{
	_passedFrameCount++;
}

void Timer::clearDeltaParts()
{
	_deltaParts.clear();
}

int Timer::getPassedFrameCount()
{
	return _passedFrameCount;
}

bool Timer::isStarted()
{
	return _isStarted;
}

bool Timer::isDeltaPartStarted(const string& ID)
{
	return (!_currentID.empty()) && (ID == _currentID);
}