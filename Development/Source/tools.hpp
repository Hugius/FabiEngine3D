#pragma once

#define NOMINMAX

#include <string>
#include <random>

using std::string;

class Tools final
{
public:
	// Global instance
	static Tools& getInst()
	{
		static Tools instance;
		return instance;
	}

	// Safe singleton
	Tools(Tools const&) = delete;
	void operator=(Tools const&) = delete;

	// String functions
	const string getRootDirectory();

	// Integer functions
	int getRandomInt(int min, int max);

	// Float functions
	float getRandomFloat(float min, float max);

	// Template functions
	template<typename T> inline const T& getMin(const T& first, const T& second)
	{
		return (first < second ? first : second);
	}
	template<typename T> inline const T& getMax(const T& first, const T& second)
	{
		return (first > second ? first : second);
	}

private:
	Tools();

	std::mt19937 _generator;
};

extern Tools g_tools;