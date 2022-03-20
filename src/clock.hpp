#pragma once

class Clock final
{
	friend class Timer;

	long long startEpoch = 0;
	long long pauseEpoch = 0;
	long long stopEpoch = 0;

	bool isStarted = false;
	bool isPaused = false;
};