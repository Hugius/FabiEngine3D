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
	void createClock(const string& id);
	void startClock(const string& id);
	void pauseClock(const string& id);
	void resumeClock(const string& id);
	void stopClock(const string& id);
	void deleteClock(const string& id);
	void increasePassedUpdateCount();

	const vector<string> getClockIds() const;

	const float getClockDeltaTime(const string& id) const;

	const unsigned int getUpdateCountPerSecond() const;
	const unsigned int getPassedUpdateCount() const;

	const bool isClockExisting(const string& id) const;
	const bool isClockStarted(const string& id) const;
	const bool isClockPaused(const string& id) const;

private:
	unordered_map<string, unique_ptr<Clock>> _clocks;

	unsigned int _passedUpdateCount = -1;

	static inline const unsigned int UPDATES_PER_SECOND = 144;
};