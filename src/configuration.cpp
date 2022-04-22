#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <windows.h>

using std::istringstream;
using std::clamp;

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
		string title = "";
		int width = 0;
		int height = 0;

		_processOption(file, "window_title", title);
		_processOption(file, "window_width", width, 0, 100);
		_processOption(file, "window_height", height, 0, 100);

		_windowTitle = title;
		_windowSizeMultiplier.x = (static_cast<float>(width) / 100.0f);
		_windowSizeMultiplier.y = (static_cast<float>(height) / 100.0f);

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
		_windowTitle = "FabiEngine3D";
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

void Configuration::_processOption(ifstream & file, const string & name, string & option)
{
	string line;

	getline(file, line);

	if(line.size() < (name.size() + 4))
	{
		Logger::throwError("Configuration file option `" + name + "` is corrupted");
	}
	if(line.substr(0, name.size()) != name)
	{
		Logger::throwError("Configuration file option `" + name + "`: name is missing");
	}
	if(line.at(name.size()) != '=')
	{
		Logger::throwError("Configuration file option `" + name + "`: separator is missing");
	}
	if(line.at(name.size() + 1) != '"')
	{
		Logger::throwError("Configuration file option `" + name + "`: value is invalid");
	}
	if(line.back() != '"')
	{
		Logger::throwError("Configuration file option `" + name + "`: value is invalid");
	}

	option = line.substr(name.size() + 2);
	option.pop_back();
}

void Configuration::_processOption(ifstream & file, const string & name, int & option, int minValue, int maxValue)
{
	string line;

	getline(file, line);

	if(line.size() < (name.size() + 2))
	{
		Logger::throwError("Configuration file option `" + name + "` is corrupted");
	}
	if(line.substr(0, name.size()) != name)
	{
		Logger::throwError("Configuration file option `" + name + "`: name is missing");
	}
	if(line.at(name.size()) != '=')
	{
		Logger::throwError("Configuration file option `" + name + "`: separator is missing");
	}
	if(!Tools::isInteger(line.substr(name.size() + 1)))
	{
		Logger::throwError("Configuration file option `" + name + "`: value is invalid");
	}

	option = Tools::parseInteger(line.substr(name.size() + 1));

	if(option < minValue)
	{
		Logger::throwError("Configuration file option `" + name + "`: value is too low");
	}
	if(option > maxValue)
	{
		Logger::throwError("Configuration file option `" + name + "`: value is too high");
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