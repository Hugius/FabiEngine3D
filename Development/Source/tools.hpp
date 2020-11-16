#pragma once

#define NOMINMAX

#include <string>
#include <random>
#include <windows.h>

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

	int   getRandomInt(int min, int max);
	int   DWORD_to_int(DWORD dword);

	float getRandomFloat(float min, float max);
	float degreeToRadians(float angle);
	float getPI();

	template<typename T> inline const T & getMin(const T & first, const T & second)
	{
		return (first < second ? first : second);
	}

	template<typename T> inline const T & getMax(const T & first, const T & second)
	{
		return (first > second ? first : second);
	}

	template<typename BufferType, typename ElementType>
	void storeData(BufferType buffer, int count, FILE * fileStream)
	{
		fread((void*)(buffer), sizeof(ElementType), count, fileStream);
	}

private:
	Tools();
	std::mt19937 _generator;
};

extern Tools g_tools;