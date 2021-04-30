#include "Timer.hpp"

void Timer::start()
{
	// Stop last
	if (_isTiming)
	{
		stop();
	}

	// Start new
	QueryPerformanceFrequency(&_frequency);
	QueryPerformanceCounter(&_time1);
	_isTiming = true;
}

float Timer::stop()
{
	if (_isTiming)
	{
		QueryPerformanceCounter(&_time2);
		_isTiming = false;
		return static_cast<float>((_time2.QuadPart - _time1.QuadPart) * 1000.0f / _frequency.QuadPart);
	}
	else
	{
		return 0.0f;
	}
}

void Timer::startDeltaPart(const string& ID)
{
	// Stop last
	if (!_currentID.empty())
	{
		stopDeltaPart();
	}

	// Start new
	QueryPerformanceFrequency(&_specificFrequency);
	QueryPerformanceCounter(&_specificTime1);
	_currentID = ID;
}

void Timer::stopDeltaPart()
{
	if (!_currentID.empty())
	{
		QueryPerformanceCounter(&_specificTime2);
		_deltaParts[_currentID] = static_cast<float>((_specificTime2.QuadPart - _specificTime1.QuadPart) * 1000.0f / _specificFrequency.QuadPart);
	}
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
	__int64 time1 = 0, time2 = 0, freq = 0;

	QueryPerformanceCounter((LARGE_INTEGER *)&time1);
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

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

int Timer::getPassedFrameCount()
{
	return _passedFrameCount;
}

bool Timer::isTiming()
{
	return _isTiming;
}