#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

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
	auto path = string(rootDir + "config.fe3d");
	std::ifstream file(path);
	if (!std::filesystem::exists(path))
	{
		Logger::throwError("Could not load engine configuration file!");
	}

	// Store config file content
	float windowSizeMultiplier = 0.0f;
	_processOption(file, windowSizeMultiplier, "window_size_multiplier");
	_processOption(file, _isWindowFullscreen, "window_fullscreen");
	_processOption(file, _isWindowBorderless, "window_borderless");
	_processOption(file, _windowTitle, "window_title");
	_processOption(file, _isGameExported, "game_exported");
	
	// Save monitor dimensions
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	_monitorSize.x = DM.w;
	_monitorSize.y = DM.h;

	// Set window & viewport dimensions
	if (_isGameExported) // Game preview
	{
		_windowSize.x = static_cast<int>(static_cast<float>(DM.w) * windowSizeMultiplier);
		_windowSize.y = static_cast<int>(static_cast<float>(DM.h) * windowSizeMultiplier);
		_viewportSize.x = static_cast<int>(static_cast<float>(_windowSize.x));
		_viewportSize.y = static_cast<int>(static_cast<float>(_windowSize.y));
		_viewportPosition.x = 0;
		_viewportPosition.y = 0;
	}
	else // Engine preview
	{
		_isWindowFullscreen = false;
		_isWindowBorderless = false;
		_windowSize.x = static_cast<int>(static_cast<float>(DM.w) * 0.9f);
		_windowSize.y = static_cast<int>(static_cast<float>(DM.h) * 0.9f);
		_viewportSize.x = static_cast<int>(0.75f * static_cast<float>(_windowSize.x));
		_viewportSize.y = static_cast<int>(0.75f * static_cast<float>(_windowSize.y));
		_viewportPosition.x = static_cast<int>(0.125f * static_cast<float>(_windowSize.x));
		_viewportPosition.y = static_cast<int>(0.2f * static_cast<float>(_windowSize.y));
	}
}

void Config::_processOption(ifstream& file, string& option, string criteria)
{
	// Temporary values
	string line;
	string name;
	string equals;
	std::getline(file, line);
	std::istringstream iss(line);
	iss >> name >> equals;

	// Check criteria
	if (name == criteria)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option \"" + criteria + "\": invalid option name!");
	}
}

void Config::_processOption(std::ifstream& file, float& option, string criteria)
{
	// Temporary values
	string line;
	string name;
	string equals;
	std::getline(file, line);
	std::istringstream iss(line);
	iss >> name >> equals;

	// Check criteria
	if (name == criteria)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option \"" + criteria + "\": invalid option name!");
	}
}

void Config::_processOption(std::ifstream& file, int& option, string criteria)
{
	// Temporary values
	string line;
	string name;
	string equals;
	std::getline(file, line);
	std::istringstream iss(line);
	iss >> name >> equals;

	// Check criteria
	if (name == criteria)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option \"" + criteria + "\": invalid option name!");
	}
}

void Config::_processOption(std::ifstream& file, bool& option, string criteria)
{
	// Temporary values
	string line;
	string name;
	string equals;
	string value;

	// Read line
	std::getline(file, line);
	std::istringstream iss(line);
	iss >> name >> equals >> value;

	// Check criteria
	if (name == criteria)
	{
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
			Logger::throwError("Configuration file @ option \"" + criteria + "\": invalid boolean value!");
		}
	}
	else
	{
		Logger::throwError("Configuration file @ option \"" + criteria + "\": invalid option name!");
	}
}

string Config::getWindowTitle() const
{
	return _windowTitle;
}

Ivec2 Config::getMonitorSize() const
{
	return _monitorSize;
}

Ivec2 Config::getWindowSize() const
{ 
	return _windowSize;
}

Ivec2 Config::getVpPos() const
{
	return _viewportPosition;
}

Ivec2 Config::getVpSize() const
{
	return _viewportSize;
}

bool Config::isWindowFullscreen() const
{
	return _isWindowFullscreen;
}

bool Config::isWindowBorderless() const
{
	return _isWindowBorderless;
}

bool Config::isGameExported() const
{
	return _isGameExported;
}