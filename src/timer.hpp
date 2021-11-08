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
	// Voids
	void start();
	void startDeltaPart(const string& ID);
	void stopDeltaPart();
	void sleep(int microseconds);
	void increasePassedFrameCount();
	void clearDeltaParts();

	// Decimals
	const float stop();
	const float getDeltaPart(const string& ID);
	const float getDeltaPartSum() const;

	// Integers
	const unsigned int getPassedTickCount() const;

	// Booleans
	const bool isStarted() const;
	const bool isDeltaPartStarted(const string& ID) const;

private:
	// Strings
	string _currentID = "";

	// Decimals
	map<string, float> _deltaParts;

	// Integers
	LARGE_INTEGER _frequency = {};
	LARGE_INTEGER _time1 = {};
	LARGE_INTEGER _time2 = {};
	LARGE_INTEGER _specificFrequency = {};
	LARGE_INTEGER _specificTime1 = {};
	LARGE_INTEGER _specificTime2 = {};
	unsigned int _passedTickCount = 0;

	// Booleans
	bool _isStarted = false;
};