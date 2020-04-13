#include "Configuration.hpp"

#include <SDL/SDL.h>

Config::Config()
{
	std::ifstream file;

	// Open config file
	file.open("../Config.fe3d");
	if (errno != 0)
	{
		Logger::getInst().throwError("Could not load engine configuration file!");
	}

	// Store config file content
	_processOption(file, _windowFullscreen);
	_processOption(file, _msaaQuality);
	_processOption(file, _shadowQuality);
	_processOption(file, _waterQuality);
	_processOption(file, _reflectionQuality);
	_processOption(file, _maxAudioChannels);
	
	// Set window dimensions
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	if (_windowFullscreen)
	{
		_windowWidth = int(float(DM.w));
		_windowHeight = int(float(DM.h));
	}
	else
	{
		_windowWidth = int(float(DM.w) * 0.83f);
		_windowHeight = int(float(DM.h) * 0.83f);
	}

	// Set viewport dimensions
	_viewportPosition.x = int(0.125f * float(_windowWidth));
	_viewportPosition.y = int(0.2f * float(_windowHeight));
	_viewportSize.x		= int(0.75f * float(_windowWidth));
	_viewportSize.y		= int(0.75f * float(_windowHeight));
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
		Logger::getInst().throwError("Configuration file: wrong boolean value");
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

const ivec2 Config::getWindowSize() const 
{ 
	return ivec2(_windowWidth, _windowHeight); 
}

const int Config::getWindowWidth() const 
{
	return _windowWidth;
}

const int Config::getWindowHeight() const 
{
	return _windowHeight; 
}

const int Config::getMsaaQuality() const 
{ 
	return _msaaQuality; 
}

const int Config::getShadowQuality() const 
{ 
	return _shadowQuality; 
}

const int Config::getWaterQuality() const
{
	return _waterQuality;
}

const int Config::getMaxAudioChannels() const
{
	return _maxAudioChannels;
}

const ivec2 Config::getVpPos() const
{
	return _viewportPosition;
}

const ivec2 Config::getVpSize() const
{
	return _viewportSize;
}

const int Config::getReflectionQuality() const
{
	return _reflectionQuality;
}