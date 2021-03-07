#pragma once

#define NOMINMAX

#include <windows.h>
#include <map>
#include <string>

using std::string;

class Timer final
{
public:
	Timer()  = default;
	~Timer() = default;

	void start();
	void startDeltaPart(const string& ID);
	void stopDeltaPart();
	void sleep(int microseconds);
	void increasePassedFrameCount();

	float stop();
	float getDeltaPart(const string& ID);
	float getDeltaPartSum();

	int getPassedFrameCount();

	bool isTiming();

private:
	LARGE_INTEGER _frequency;
	LARGE_INTEGER _time1;
	LARGE_INTEGER _time2;
	LARGE_INTEGER _specificFrequency;
	LARGE_INTEGER _specificTime1;
	LARGE_INTEGER _specificTime2;

	std::map<string, float> _deltaParts;

	string _currentID = "";

	int _passedFrameCount = 0;

	bool _isTiming = false;
};