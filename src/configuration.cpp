#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <windows.h>

using std::istringstream;

Configuration::Configuration()
{
	if(!SetProcessDPIAware())
	{
		abort();
	}

	const auto rootPath = Tools::getRootDirectoryPath();
	const auto monitorSize = Tools::getMonitorSize();

	auto file = ifstream(rootPath + "configuration.fe3d");

	if(file)
	{
		_processOption(file, _windowSizeMultiplier.x, "window_width");
		_processOption(file, _windowSizeMultiplier.y, "window_height");
		_processOption(file, _windowTitle, "window_title");

		if((_windowSizeMultiplier.x < 0.0f) || (_windowSizeMultiplier.x > 1.0f))
		{
			Logger::throwError("Configuration file @ option `window_width`: must be between 0.0 and 1.0");
		}

		if((_windowSizeMultiplier.y < 0.0f) || (_windowSizeMultiplier.y > 1.0f))
		{
			Logger::throwError("Configuration file @ option `window_height`: must be between 0.0 and 1.0");
		}

		_windowSize.x = static_cast<int>(static_cast<float>(monitorSize.x) * _windowSizeMultiplier.x);
		_windowSize.y = static_cast<int>(static_cast<float>(monitorSize.y) * _windowSizeMultiplier.y);
		_displaySize.x = static_cast<int>(static_cast<float>(_windowSize.x));
		_displaySize.y = static_cast<int>(static_cast<float>(_windowSize.y));
		_displayPosition.x = 0;
		_displayPosition.y = 0;

		_isApplicationExported = true;
	}
	else
	{
		_windowSizeMultiplier = fvec2(1.0f);
		_windowSize.x = static_cast<int>(static_cast<float>(monitorSize.x) * _windowSizeMultiplier.x);
		_windowSize.y = static_cast<int>(static_cast<float>(monitorSize.y) * _windowSizeMultiplier.y);
		_displaySize.x = static_cast<int>(static_cast<float>(_windowSize.x) * DISPLAY_SIZE_MULTIPLIER.x);
		_displaySize.y = static_cast<int>(static_cast<float>(_windowSize.y) * DISPLAY_SIZE_MULTIPLIER.y);
		_displayPosition.x = static_cast<int>(static_cast<float>(_windowSize.x) * DISPLAY_POSITION_MULTIPLIER.x);
		_displayPosition.y = static_cast<int>(static_cast<float>(_windowSize.y) * DISPLAY_POSITION_MULTIPLIER.y);

		_isApplicationExported = false;
	}
}

void Configuration::_processOption(ifstream & file, string & option, const string & name)
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

void Configuration::_processOption(ifstream & file, float & option, const string & name)
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

void Configuration::_processOption(ifstream & file, int & option, const string & name)
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

void Configuration::_processOption(ifstream & file, bool & option, const string & name)
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

const ivec2 & Configuration::getWindowSize() const
{
	return _windowSize;
}

const ivec2 & Configuration::getDisplayPosition() const
{
	return _displayPosition;
}

const string & Configuration::getWindowTitle() const
{
	return _windowTitle;
}

const fvec2 Configuration::getWindowSizeMultiplier() const
{
	return _windowSizeMultiplier;
}

const ivec2 & Configuration::getDisplaySize() const
{
	return _displaySize;
}

const bool Configuration::isApplicationExported() const
{
	return _isApplicationExported;
}