#pragma once

#define NOMINMAX

#include <windows.h>
#include <map>
#include <string>

using std::string;

class Timer final
{
public:
	void start();
	void startDeltaPart(const string& ID);
	void stopDeltaPart();
	void sleep(int microseconds);
	void increasePassedFrameCount();
	void clearDeltaParts();

	float stop();
	float getDeltaPart(const string& ID);
	float getDeltaPartSum();

	int getPassedFrameCount();

	bool isStarted();
	bool isDeltaPartStarted(const string& ID);

private:
	LARGE_INTEGER _frequency;
	LARGE_INTEGER _time1;
	LARGE_INTEGER _time2;
	LARGE_INTEGER _specificFrequency;
	LARGE_INTEGER _specificTime1;
	LARGE_INTEGER _specificTime2;

	std::map<string, float> _deltaParts;

	string _currentID = "";

	unsigned int _passedFrameCount = 0;

	bool _isStarted = false;
};