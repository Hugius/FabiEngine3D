#pragma once

#include <string>
#include <random>
#include <ctime>

using std::string;

class Tools final
{
public:
	Tools() = delete;

	static const string getRootDirectory();
	static const int getRandomInteger(int min, int max);
	static const float getRandomFloat(float min, float max);
	static const long long getTimeSinceEpochMS();

private:
	static inline std::mt19937 _generator = std::mt19937(static_cast<unsigned int>(time(nullptr)));
};