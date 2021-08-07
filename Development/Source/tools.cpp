#include "tools.hpp"
#include "logger.hpp"

#include <sstream>
#include <filesystem>

using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::filesystem::absolute;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

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
	rootDir = absolute(rootDir).string();

	// Cut to engine root directory
	rootDir = rootDir.substr(0, rootDir.size() - string("binaries\\FabiEngine3D.exe").size());

	// Return
	return rootDir;
}

const int Tools::getRandomInteger(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(_generator);
}

const float Tools::getRandomFloat(float min, float max)
{	
	uniform_real_distribution<float> dist(min, max);
	return dist(_generator);
}

const long long Tools::getTimeSinceEpochMS()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}