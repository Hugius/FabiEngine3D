#pragma once

class Clock final
{
	friend class Timer;

	long long startEpoch;
	long long pauseEpoch;
	long long stopEpoch;

	bool isStarted = false;
	bool isPaused = false;
};