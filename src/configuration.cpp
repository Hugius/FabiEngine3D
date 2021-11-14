#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <SDL\\SDL.h>

using std::istringstream;

Config::Config()
{
	// Temporary values
	const string filePath = string(Tools::getRootDirectoryPath() + "config.fe3d");

	// Check if config file exists
	if(Tools::isFileExisting(filePath))
	{
		// Open config file
		ifstream file(filePath);

		// Store config file content
		float windowSizeMultiplier = 0.0f;
		_processOption(file, windowSizeMultiplier, "window_size");
		_processOption(file, _isWindowFullscreen, "window_fullscreen");
		_processOption(file, _isWindowBorderless, "window_borderless");
		_processOption(file, _windowTitle, "window_title");

		// Check if multiplier is between 0.0 and 1.0
		if((windowSizeMultiplier < 0.0f) || (windowSizeMultiplier > 1.0f))
		{
			Logger::throwFatalWarning("Configuration file @ option `window_size`: must be between 0.0 and 1.0!");
		}

		// Save monitor dimensions
		SDL_DisplayMode DM;
		SDL_GetDesktopDisplayMode(0, &DM);
		_monitorSize.x = DM.w;
		_monitorSize.y = DM.h;

		// Set window & viewport dimensions
		_windowSize.x = static_cast<int>(static_cast<float>(DM.w) * windowSizeMultiplier);
		_windowSize.y = static_cast<int>(static_cast<float>(DM.h) * windowSizeMultiplier);
		_viewportSize.x = static_cast<int>(static_cast<float>(_windowSize.x));
		_viewportSize.y = static_cast<int>(static_cast<float>(_windowSize.y));
		_viewportPosition.x = 0;
		_viewportPosition.y = 0;

		// Miscellaneous 
		_isApplicationExported = true;
	}
	else
	{
		// Save monitor dimensions
		SDL_DisplayMode DM;
		SDL_GetDesktopDisplayMode(0, &DM);
		_monitorSize.x = DM.w;
		_monitorSize.y = DM.h;

		// Set window & viewport dimensions
		_isWindowFullscreen = false;
		_isWindowBorderless = false;
		_windowSize.x = static_cast<int>(static_cast<float>(DM.w) * 0.9f);
		_windowSize.y = static_cast<int>(static_cast<float>(DM.h) * 0.9f);
		_viewportSize.x = static_cast<int>(0.75f * static_cast<float>(_windowSize.x));
		_viewportSize.y = static_cast<int>(0.75f * static_cast<float>(_windowSize.y));
		_viewportPosition.x = static_cast<int>(0.125f * static_cast<float>(_windowSize.x));
		_viewportPosition.y = static_cast<int>(0.2f * static_cast<float>(_windowSize.y));

		// Miscellaneous 
		_isApplicationExported = false;
	}
}

void Config::_processOption(ifstream& file, string& option, string criteria)
{
	// Temporary values
	string line;
	string field;
	string equals;
	getline(file, line);
	istringstream iss(line);
	iss >> field >> equals;

	// Check criteria
	if(field == criteria)
	{
		iss >> option;
	}
	else
	{
		Logger::throwFatalWarning("Configuration file @ option `" + criteria + "`: invalid option field!");
	}
}

void Config::_processOption(ifstream& file, float& option, string criteria)
{
	// Temporary values
	string line;
	string field;
	string equals;
	getline(file, line);
	istringstream iss(line);
	iss >> field >> equals;

	// Check criteria
	if(field == criteria)
	{
		iss >> option;
	}
	else
	{
		Logger::throwFatalWarning("Configuration file @ option `" + criteria + "`: invalid option field!");
	}
}

void Config::_processOption(ifstream& file, int& option, string criteria)
{
	// Temporary values
	string line;
	string field;
	string equals;
	getline(file, line);
	istringstream iss(line);
	iss >> field >> equals;

	// Check criteria
	if(field == criteria)
	{
		iss >> option;
	}
	else
	{
		Logger::throwFatalWarning("Configuration file @ option `" + criteria + "`: invalid option field!");
	}
}

void Config::_processOption(ifstream& file, bool& option, string criteria)
{
	// Temporary values
	string line;
	string field;
	string equals;
	string value;

	// Read line
	getline(file, line);
	istringstream iss(line);
	iss >> field >> equals >> value;

	// Check criteria
	if(field == criteria)
	{
		// Parsing to boolean value
		if(value == "true")
		{
			option = true;
		}
		else if(value == "false")
		{
			option = false;
		}
		else
		{
			Logger::throwFatalWarning("Configuration file @ option `" + criteria + "`: invalid boolean value!");
		}
	}
	else
	{
		Logger::throwFatalWarning("Configuration file @ option `" + criteria + "`: invalid option field!");
	}
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

const Ivec2 Config::getViewportPosition() const
{
	return _viewportPosition;
}

const Ivec2 Config::getViewportSize() const
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