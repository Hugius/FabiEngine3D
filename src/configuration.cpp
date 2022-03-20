#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <SDL.h>

using std::istringstream;

Configuration::Configuration()
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + "configuration.fe3d");

	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	_monitorSize.x = DM.w;
	_monitorSize.y = DM.h;

	auto file = ifstream(filePath);

	if(file)
	{
		_processOption(file, _windowSizeMultiplier, "window_size");
		_processOption(file, _isWindowFullscreen, "window_fullscreen");
		_processOption(file, _isWindowBorderless, "window_borderless");
		_processOption(file, _windowTitle, "window_title");

		if((_windowSizeMultiplier < 0.0f) || (_windowSizeMultiplier > 1.0f))
		{
			Logger::throwError("Configuration file @ option `window_size`: must be between 0.0 and 1.0");
		}

		_windowSize.x = static_cast<int>(static_cast<float>(_monitorSize.x) * _windowSizeMultiplier);
		_windowSize.y = static_cast<int>(static_cast<float>(_monitorSize.y) * _windowSizeMultiplier);
		_displaySize.x = static_cast<int>(static_cast<float>(_windowSize.x));
		_displaySize.y = static_cast<int>(static_cast<float>(_windowSize.y));
		_displayPosition.x = 0;
		_displayPosition.y = 0;

		_isApplicationExported = true;
	}
	else
	{
		_windowSizeMultiplier = DEFAULT_WINDOW_SIZE_MULTIPLIER;
		_isWindowFullscreen = false;
		_isWindowBorderless = false;
		_windowSize.x = static_cast<int>(static_cast<float>(_monitorSize.x) * _windowSizeMultiplier);
		_windowSize.y = static_cast<int>(static_cast<float>(_monitorSize.y) * _windowSizeMultiplier);
		_displaySize.x = static_cast<int>(static_cast<float>(_windowSize.x) * DISPLAY_SIZE_MULTIPLIER.x);
		_displaySize.y = static_cast<int>(static_cast<float>(_windowSize.y) * DISPLAY_SIZE_MULTIPLIER.y);
		_displayPosition.x = static_cast<int>(static_cast<float>(_windowSize.x) * DISPLAY_POSITION_MULTIPLIER.x);
		_displayPosition.y = static_cast<int>(static_cast<float>(_windowSize.y) * DISPLAY_POSITION_MULTIPLIER.y);

		_isApplicationExported = false;
	}
}

void Configuration::_processOption(ifstream& file, string& option, const string& name)
{
	string line;
	string field;
	string equals;

	getline(file, line);

	istringstream iss(line);

	iss
		>> field
		>> equals;

	if(field == name)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + name + "`: invalid option field");
	}
}

void Configuration::_processOption(ifstream& file, float& option, const string& name)
{
	string line;
	string field;
	string equals;

	getline(file, line);

	istringstream iss(line);

	iss
		>> field
		>> equals;

	if(field == name)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + name + "`: invalid option field");
	}
}

void Configuration::_processOption(ifstream& file, int& option, const string& name)
{
	string line;
	string field;
	string equals;

	getline(file, line);

	istringstream iss(line);

	iss
		>> field
		>> equals;

	if(field == name)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + name + "`: invalid option field");
	}
}

void Configuration::_processOption(ifstream& file, bool& option, const string& name)
{
	string line;
	string field;
	string equals;
	string value;

	getline(file, line);

	istringstream iss(line);

	iss
		>> field
		>> equals
		>> value;

	if(field == name)
	{
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
			Logger::throwError("Configuration file @ option `" + name + "`: invalid boolean value");
		}
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + name + "`: invalid option field");
	}
}

const string& Configuration::getWindowTitle() const
{
	return _windowTitle;
}

const ivec2& Configuration::getMonitorSize() const
{
	return _monitorSize;
}

const ivec2& Configuration::getWindowSize() const
{
	return _windowSize;
}

const ivec2& Configuration::getDisplayPosition() const
{
	return _displayPosition;
}

const float Configuration::getWindowSizeMultiplier() const
{
	return _windowSizeMultiplier;
}

const ivec2& Configuration::getDisplaySize() const
{
	return _displaySize;
}

const bool Configuration::isWindowFullscreen() const
{
	return _isWindowFullscreen;
}

const bool Configuration::isWindowBorderless() const
{
	return _isWindowBorderless;
}

const bool Configuration::isApplicationExported() const
{
	return _isApplicationExported;
}