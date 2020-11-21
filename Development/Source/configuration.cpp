#include "configuration.hpp"
#include "logger.hpp"

#include <SDL\\SDL.h>
#include <filesystem>

Config::Config()
{
	// Get application root directory
	char buffer[256]; size_t len = sizeof(buffer);
	GetModuleFileName(NULL, buffer, len);
	string rootDir = buffer;
	rootDir = rootDir.substr(0, rootDir.size() - string("bin\\FabiEngine3D.exe").size());

	// Open config file
	string path = rootDir + "config.fe3d";
	std::ifstream file(path);
	if (!std::filesystem::exists(path))
	{
		Logger::throwError("Could not load engine configuration file!");
	}

	// Store config file content
	_processOption(file, _windowFullscreen);
	
	// Set window dimensions
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	if (_windowFullscreen)
	{
		_windowWidth  = static_cast<int>(static_cast<float>(DM.w));
		_windowHeight = static_cast<int>(static_cast<float>(DM.h));
	}
	else
	{
		_windowWidth  = static_cast<int>(static_cast<float>(DM.w) * 0.9f);
		_windowHeight = static_cast<int>(static_cast<float>(DM.h) * 0.9f);
	}

	// Set viewport dimensions
	_viewportPosition.x = static_cast<int>(0.125f * static_cast<float>(_windowWidth));
	_viewportPosition.y = static_cast<int>(0.2f * static_cast<float>(_windowHeight));
	_viewportSize.x		= static_cast<int>(0.75f * static_cast<float>(_windowWidth));
	_viewportSize.y		= static_cast<int>(0.75f * static_cast<float>(_windowHeight));

	// Set update speed
	_updateMsPerFrame = 6.94f; // 144 hz
}

void Config::_processOption(std::ifstream& file, bool& option)
{
	// Loading
	string line;
	string temp;
	string value;
	std::getline(file, line);
	std::istringstream iss(line);
	iss >> temp >> temp >> value;

	// Parsing to boolean value
	if (value == "true")
	{
		option = true;
	}
	else if (value == "false")
	{
		option = false;
	}
	else
	{
		Logger::throwError("Configuration file: wrong boolean value");
	}
}

void Config::_processOption(std::ifstream& file, int& option)
{
	// Loading
	string line;
	string temp;
	std::getline(file, line);
	std::istringstream iss(line);
	iss >> temp >> temp >> option;
}

void Config::_processOption(std::ifstream& file, float& option)
{
	// Loading
	string line;
	string temp;
	std::getline(file, line);
	std::istringstream iss(line);
	iss >> temp >> temp >> option;
}

Ivec2 Config::getWindowSize() const 
{ 
	return Ivec2(_windowWidth, _windowHeight); 
}

int Config::getWindowWidth() const 
{
	return _windowWidth;
}

int Config::getWindowHeight() const 
{
	return _windowHeight; 
}

Ivec2 Config::getVpPos() const
{
	return _viewportPosition;
}

Ivec2 Config::getVpSize() const
{
	return _viewportSize;
}

float Config::getUpdateMsPerFrame() const
{
	return _updateMsPerFrame;
}