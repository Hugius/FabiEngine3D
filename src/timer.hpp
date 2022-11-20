#pragma once

#include "clock.hpp"

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

using std::string;
using std::unordered_map;
using std::unique_ptr;
using std::vector;

class Timer final
{
public:
	void createClock(const string & clockId);
	void startClock(const string & clockId);
	void pauseClock(const string & clockId);
	void resumeClock(const string & clockId);
	void stopClock(const string & clockId);
	void deleteClock(const string & clockId);
	void increasePassedUpdateCount();

	const vector<string> getClockIds() const;

	const float getClockDeltaTime(const string & clockId) const;

	const int getUpdateCountPerSecond() const;
	const int getPassedUpdateCount() const;

	const bool isClockExisting(const string & clockId) const;
	const bool isClockStarted(const string & clockId) const;
	const bool isClockPaused(const string & clockId) const;

private:
	static inline constexpr int UPDATES_PER_SECOND = 75;

	unordered_map<string, unique_ptr<Clock>> _clocks;

	int _passedUpdateCount = 0;
};