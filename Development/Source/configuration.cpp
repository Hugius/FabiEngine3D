#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <SDL\\SDL.h>
#include <filesystem>

using std::istringstream;
using std::filesystem::exists;

Config::Config()
{
	// Get application root directory
	char buffer[256];
	size_t len = sizeof(buffer);
	GetModuleFileName(nullptr, buffer, static_cast<DWORD>(len));
	string rootDir = buffer;
	rootDir = rootDir.substr(0, rootDir.size() - string("binaries\\FabiEngine3D.exe").size());

	// Open config file
	auto path = string(rootDir + "config.fe3d");
	ifstream file(path);
	if (!exists(path))
	{
		Logger::throwError("Cannot load `config.fe3d`!");
	}

	// Store config file content
	float windowSizeMultiplier = 0.0f;
	_processOption(file, windowSizeMultiplier, "window_size_multiplier");
	_processOption(file, _isWindowFullscreen, "window_fullscreen");
	_processOption(file, _isWindowBorderless, "window_borderless");
	_processOption(file, _windowTitle, "window_title");
	_processOption(file, _applicationTitle, "application_title");
	_processOption(file, _isApplicationExported, "application_exported");
	
	// Check if multiplier is between 0.0 and 1.0
	if (windowSizeMultiplier < 0.0f || windowSizeMultiplier > 1.0f)
	{
		Logger::throwError("Option `window_size_multiplier` in configuration file must be between 0.0 and 1.0!");
	}

	// Save monitor dimensions
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	_monitorSize.x = DM.w;
	_monitorSize.y = DM.h;

	// Set window & viewport dimensions
	if (_isApplicationExported) // Application preview
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
	getline(file, line);
	istringstream iss(line);
	iss >> name >> equals;

	// Check criteria
	if (name == criteria)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + criteria + "`: invalid option name!");
	}
}

void Config::_processOption(ifstream& file, float& option, string criteria)
{
	// Temporary values
	string line;
	string name;
	string equals;
	getline(file, line);
	istringstream iss(line);
	iss >> name >> equals;

	// Check criteria
	if (name == criteria)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + criteria + "`: invalid option name!");
	}
}

void Config::_processOption(ifstream& file, int& option, string criteria)
{
	// Temporary values
	string line;
	string name;
	string equals;
	getline(file, line);
	istringstream iss(line);
	iss >> name >> equals;

	// Check criteria
	if (name == criteria)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + criteria + "`: invalid option name!");
	}
}

void Config::_processOption(ifstream& file, bool& option, string criteria)
{
	// Temporary values
	string line;
	string name;
	string equals;
	string value;

	// Read line
	getline(file, line);
	istringstream iss(line);
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
			Logger::throwError("Configuration file @ option `" + criteria + "`: invalid boolean value!");
		}
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + criteria + "`: invalid option name!");
	}
}

const string& Config::getApplicationTitle() const
{
	return _applicationTitle;
}

const string& Config::getWindowTitle() const
{
	return _windowTitle;
}

const Ivec2 Config::getMonitorSize() const
{
	return _monitorSize;
}

const Ivec2 Config::getWindowSize() const
{ 
	return _windowSize;
}

const Ivec2 Config::getVpPos() const
{
	return _viewportPosition;
}

const Ivec2 Config::getVpSize() const
{
	return _viewportSize;
}

const bool Config::isWindowFullscreen() const
{
	return _isWindowFullscreen;
}

const bool Config::isWindowBorderless() const
{
	return _isWindowBorderless;
}

const bool Config::isApplicationExported() const
{
	return _isApplicationExported;
}