#include "Tools.hpp"
#include "logger.hpp"

#include <ctime>
#include <sstream>
#include <filesystem>

using std::to_string;

Tools::Tools() :
	_generator(std::random_device{}())
{
	srand((unsigned int)time(NULL));
}

const string Tools::getRootDirectory()
{
	// Temporary values
	char buffer[256];
	size_t len = sizeof(buffer);

	// Get executable path
	GetModuleFileName(NULL, buffer, static_cast<DWORD>(len));

	// Create final string
	string rootDir = buffer;

	// Convert to absolute path if it's relative
	rootDir = std::filesystem::absolute(rootDir).string();

	// Cut to engine root directory
	rootDir = rootDir.substr(0, rootDir.size() - string("binaries\\FabiEngine3D.exe").size());

	// Return
	return rootDir;
}

int Tools::getRandomInt(int min, int max)
{
	std::uniform_int_distribution<> dist(min, max);
	return dist(_generator);
}

float Tools::getRandomFloat(float min, float max)
{
	std::uniform_real_distribution<> dist(static_cast<float>(min), static_cast<float>(max));
	return static_cast<float>(dist(_generator));

	// 2 different approaches, check which is the best <---
	
	//float randomNumber = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	//return randomNumber;
}

int Tools::DWORD_to_int(DWORD dword)
{
	std::ostringstream stream;
	stream << dword;
	string convertedDWORD = stream.str();
	int result = std::stoi(convertedDWORD);
	return result;
}