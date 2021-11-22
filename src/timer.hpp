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
	// VOID
	void start();
	void startDeltaPart(const string& ID);
	void stopDeltaPart();
	void sleep(int microseconds);
	void increasePassedFrameCount();
	void clearDeltaParts();

	// FLOAT
	const float stop();
	const float getDeltaPart(const string& ID);
	const float getDeltaPartSum() const;

	// UNSIGNED INT
	const unsigned int getPassedTickCount() const;

	// BOOL
	const bool isStarted() const;
	const bool isDeltaPartStarted(const string& ID) const;

private:
	// STRING
	string _currentID = "";

	// FLOAT
	map<string, float> _deltaParts;

	// UNSIGNED INT
	unsigned int _passedTickCount = 0;

	// BOOL
	bool _isStarted = false;

	// MISCELLANEOUS
	LARGE_INTEGER _frequency = {};
	LARGE_INTEGER _time1 = {};
	LARGE_INTEGER _time2 = {};
	LARGE_INTEGER _specificFrequency = {};
	LARGE_INTEGER _specificTime1 = {};
	LARGE_INTEGER _specificTime2 = {};
};