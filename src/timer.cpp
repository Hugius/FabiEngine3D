#include "timer.hpp"
#include "logger.hpp"

void Timer::start()
{
	if(_isStarted)
	{
		Logger::throwError("Timer::start");
	}

	QueryPerformanceFrequency(&_frequency);
	QueryPerformanceCounter(&_time1);
	_isStarted = true;
}

const float Timer::stop()
{
	if(!_isStarted)
	{
		Logger::throwError("Timer::stop");
	}

	QueryPerformanceCounter(&_time2);
	_isStarted = false;
	return static_cast<float>((_time2.QuadPart - _time1.QuadPart) * 1000.0f / _frequency.QuadPart);
}

void Timer::startDeltaPart(const string& id)
{
	if(!_currentID.empty())
	{
		Logger::throwError("Timer::startDeltaPart");
	}

	QueryPerformanceFrequency(&_specificFrequency);
	QueryPerformanceCounter(&_specificTime1);
	_currentID = id;
}

void Timer::stopDeltaPart()
{
	if(_currentID.empty())
	{
		Logger::throwError("Timer::stopDeltaPart");
	}

	QueryPerformanceCounter(&_specificTime2);
	_deltaParts[_currentID] = static_cast<float>((_specificTime2.QuadPart - _specificTime1.QuadPart) * 1000.0f / _specificFrequency.QuadPart);
	_currentID = "";
}

const float Timer::getDeltaPart(const string& id)
{
	return _deltaParts[id];
}

const float Timer::getDeltaPartSum() const
{
	float sum = 0.0f;

	for(const auto& part : _deltaParts)
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

	QueryPerformanceCounter((LARGE_INTEGER*)&time1);
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	do
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&time2);
	}
	while((time2 - time1) < microseconds);
}

void Timer::increasePassedFrameCount()
{
	_passedTickCount++;
}

void Timer::clearDeltaParts()
{
	_deltaParts.clear();
}

const unsigned int Timer::getPassedTickCount() const
{
	return _passedTickCount;
}

const bool Timer::isStarted() const
{
	return _isStarted;
}

const bool Timer::isDeltaPartStarted(const string& id) const
{
	return (!_currentID.empty()) && (id == _currentID);
}