#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <SDL.h>

using std::istringstream;

Config::Config()
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + "config.fe3d");

	if(Tools::isFileExisting(filePath))
	{
		auto file = ifstream(filePath);
		if(!file)
		{
			Logger::throwFatalWarning("Cannot load `config.fe3d`!");
		}

		float windowSizeMultiplier = 0.0f;
		_processOption(file, windowSizeMultiplier, "window_size");
		_processOption(file, _isWindowFullscreen, "window_fullscreen");
		_processOption(file, _isWindowBorderless, "window_borderless");
		_processOption(file, _windowTitle, "window_title");

		if((windowSizeMultiplier < 0.0f) || (windowSizeMultiplier > 1.0f))
		{
			Logger::throwFatalWarning("Configuration file @ option `window_size`: must be between 0.0 and 1.0!");
		}

		SDL_DisplayMode DM;
		SDL_GetDesktopDisplayMode(0, &DM);
		_monitorSize.x = DM.w;
		_monitorSize.y = DM.h;

		_windowSize.x = static_cast<int>(static_cast<float>(DM.w) * windowSizeMultiplier);
		_windowSize.y = static_cast<int>(static_cast<float>(DM.h) * windowSizeMultiplier);
		_viewportSize.x = static_cast<int>(static_cast<float>(_windowSize.x));
		_viewportSize.y = static_cast<int>(static_cast<float>(_windowSize.y));
		_viewportPosition.x = 0;
		_viewportPosition.y = 0;

		_isApplicationExported = true;
	}
	else
	{
		SDL_DisplayMode DM;
		SDL_GetDesktopDisplayMode(0, &DM);
		_monitorSize.x = DM.w;
		_monitorSize.y = DM.h;

		_isWindowFullscreen = false;
		_isWindowBorderless = false;
		_windowSize.x = static_cast<int>(static_cast<float>(DM.w) * 0.9f);
		_windowSize.y = static_cast<int>(static_cast<float>(DM.h) * 0.9f);
		_viewportSize.x = static_cast<int>(0.75f * static_cast<float>(_windowSize.x));
		_viewportSize.y = static_cast<int>(0.75f * static_cast<float>(_windowSize.y));
		_viewportPosition.x = static_cast<int>(0.125f * static_cast<float>(_windowSize.x));
		_viewportPosition.y = static_cast<int>(0.2f * static_cast<float>(_windowSize.y));

		_isApplicationExported = false;
	}
}

void Config::_processOption(ifstream& file, string& option, string name)
{
	string line;
	string field;
	string equals;
	getline(file, line);
	istringstream iss(line);
	iss >> field >> equals;

	if(field == name)
	{
		iss >> option;
	}
	else
	{
		Logger::throwFatalWarning("Configuration file @ option `" + name + "`: invalid option field!");
	}
}

void Config::_processOption(ifstream& file, float& option, string name)
{
	string line;
	string field;
	string equals;
	getline(file, line);
	istringstream iss(line);
	iss >> field >> equals;

	if(field == name)
	{
		iss >> option;
	}
	else
	{
		Logger::throwFatalWarning("Configuration file @ option `" + name + "`: invalid option field!");
	}
}

void Config::_processOption(ifstream& file, int& option, string name)
{
	string line;
	string field;
	string equals;
	getline(file, line);
	istringstream iss(line);
	iss >> field >> equals;

	if(field == name)
	{
		iss >> option;
	}
	else
	{
		Logger::throwFatalWarning("Configuration file @ option `" + name + "`: invalid option field!");
	}
}

void Config::_processOption(ifstream& file, bool& option, string name)
{
	string line;
	string field;
	string equals;
	string value;

	getline(file, line);
	istringstream iss(line);
	iss >> field >> equals >> value;

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
			Logger::throwFatalWarning("Configuration file @ option `" + name + "`: invalid boolean value!");
		}
	}
	else
	{
		Logger::throwFatalWarning("Configuration file @ option `" + name + "`: invalid option field!");
	}
}

const string& Config::getWindowTitle() const
{
	return _windowTitle;
}

const ivec2 Config::getMonitorSize() const
{
	return _monitorSize;
}

const ivec2 Config::getWindowSize() const
{
	return _windowSize;
}

const ivec2 Config::getViewportPosition() const
{
	return _viewportPosition;
}

const ivec2 Config::getViewportSize() const
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