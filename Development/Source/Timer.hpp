#pragma once
#include <windows.h>
#include <map>
#include <string>

using std::string;

class Timer final
{
public:
	Timer()  = default;
	~Timer() = default;

	void setCustomDeltaTime(float delta);
	void calculateDeltaTime();
	void start(const string& ID);
	void stop();

	float getDeltaPart(const string& ID);
	float getDeltaTime();

	void uSleep(int waitTime);

private:
	LARGE_INTEGER p_frequency;
	LARGE_INTEGER p_time1, p_time2;

	std::map<string, float> p_deltaParts;

	string p_currentID = "";

	float p_deltaTime = 0.0f;
};