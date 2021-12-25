#pragma once

#define NOMINMAX

#include <windows.h>
#include <map>
#include <string>

using std::string;
using std::map;

class Timer final
{
public:
	void start();
	void startDeltaPart(const string& ID);
	void stopDeltaPart();
	void sleep(int microseconds);
	void increasePassedFrameCount();
	void clearDeltaParts();

	const float stop();
	const float getDeltaPart(const string& ID);
	const float getDeltaPartSum() const;

	const unsigned int getPassedTickCount() const;

	const bool isStarted() const;
	const bool isDeltaPartStarted(const string& ID) const;

private:
	string _currentID = "";

	map<string, float> _deltaParts;

	unsigned int _passedTickCount = 0;

	bool _isStarted = false;

	LARGE_INTEGER _frequency = {};
	LARGE_INTEGER _time1 = {};
	LARGE_INTEGER _time2 = {};
	LARGE_INTEGER _specificFrequency = {};
	LARGE_INTEGER _specificTime1 = {};
	LARGE_INTEGER _specificTime2 = {};
};