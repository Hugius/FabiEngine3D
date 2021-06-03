#include "tools.hpp"
#include "logger.hpp"

#include <sstream>
#include <filesystem>

const string Tools::getRootDirectory()
{
	// Temporary values
	char buffer[256];
	size_t len = sizeof(buffer);

	// Get executable path
	GetModuleFileName(nullptr, buffer, static_cast<DWORD>(len));

	// Create final string
	string rootDir = buffer;

	// Convert to absolute path if it's relative
	rootDir = std::filesystem::absolute(rootDir).string();

	// Cut to engine root directory
	rootDir = rootDir.substr(0, rootDir.size() - string("binaries\\FabiEngine3D.exe").size());

	// Return
	return rootDir;
}

const int Tools::getRandomInt(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(_generator);
}

const float Tools::getRandomFloat(float min, float max)
{	
	std::uniform_real_distribution<float> dist(min, max);
	return dist(_generator);
}

const unsigned Tools::getTimeSinceEpochMS()
{
	return static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}