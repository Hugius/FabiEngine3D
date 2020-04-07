#include "Timer.hpp"
	
void Timer::setCustomDeltaTime(float delta)
{
	_deltaTime = delta;
}

void Timer::calculateDeltaTime()
{
	_deltaTime = 0.0f;

	for (auto& element : _deltaParts)
	{
		_deltaTime += element.second;
	}
}

// Start measuring time
void Timer::start(const string& ID)
{
	QueryPerformanceFrequency(&_frequency);
	QueryPerformanceCounter(&_time1);
	_currentID = ID;
}

// Calculate the delta time
void Timer::stop()
{
	QueryPerformanceCounter(&_time2);
	_deltaParts[_currentID] = static_cast<float>((_time2.QuadPart - _time1.QuadPart) * 1000.0f / _frequency.QuadPart);
}

float Timer::getDeltaPart(const string& ID)
{
	return _deltaParts[ID];
}

float Timer::getDeltaTime()
{
	return _deltaTime;
}

void Timer::uSleep(int waitTime)
{
	__int64 time1 = 0, time2 = 0, freq = 0;

	QueryPerformanceCounter((LARGE_INTEGER *)&time1);
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

	do 
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&time2);
	} 
	while ((time2 - time1) < waitTime);
}