#include "Tools.hpp"
#include "logger.hpp"

#include <ctime>
#include <iostream>
#include <sstream>

#define PI      3.14159265359f
#define DEG2RAD 0.01745329251994329576923690768489f

using std::to_string;

Tools::Tools() :
	_generator(std::random_device{}())
{
	srand((unsigned int)time(NULL));
}

void Tools::printInteger(int val)
{
	std::cout << to_string(val) << std::endl;
}

void Tools::printFloat(float val)
{
	std::cout << to_string(val) << std::endl;
}

void Tools::printDouble(double val)
{
	std::cout << to_string(val) << std::endl;
}

int Tools::getRandomInt(int min, int max) 
{
	std::uniform_int_distribution<> dist(min, max);
	return dist(_generator);
}

float Tools::getRandomFloat(float min, float max)
{
	//std::unifor_real_distribution<> dist(static_cast<float>(min), static_cast<float>(max));
	//return static_cast<float>(dist(_generator));

	float randomNumber = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return randomNumber;
}

float Tools::degreeToRadians(float degree)
{
	return (degree * DEG2RAD);
}

float Tools::getPI()
{
	return PI;
}

float Tools::squared(float val)
{
	return val * val;
}

bool Tools::compareData_string(const string& firstString, string targetString, string errorMsg)
{
	if (firstString != targetString) {
		Logger::throwError(errorMsg);
		return false;
	}
	else {
		return true;
	}
}

int Tools::DWORD_to_int(DWORD dword)
{
	std::ostringstream stream;
	stream << dword;
	string convertedDWORD = stream.str();
	int result = std::stoi(convertedDWORD);
	return result;
}