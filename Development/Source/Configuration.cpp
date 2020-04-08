#include "Configuration.hpp"

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
	_processOption(file, window_width);
	_processOption(file, window_height);
	_processOption(file, window_zoom_scale);
	_processOption(file, msaa_quality);
	_processOption(file, shadow_quality);
	_processOption(file, water_quality);
	_processOption(file, reflection_quality);
	_processOption(file, max_audio_channels);
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
	return ivec2(window_width / window_zoom_scale, window_height / window_zoom_scale); 
}

const int Config::getWindowWidth() const 
{
	return int(float(window_width) / window_zoom_scale); 
}

const int Config::getWindowHeight() const 
{
	return int(float(window_height) / window_zoom_scale); 
}

const float Config::getWindowZoomScale() const
{
	return window_zoom_scale;
}

const int Config::getMsaaQuality() const 
{ 
	return msaa_quality; 
}

const int Config::getShadowQuality() const 
{ 
	return shadow_quality; 
}

const int Config::getWaterQuality() const
{
	return water_quality;
}

const int Config::getMaxAudioChannels() const
{
	return max_audio_channels;
}

const int Config::getReflectionQuality() const
{
	return reflection_quality;
}