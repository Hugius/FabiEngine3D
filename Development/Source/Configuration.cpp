#include "Configuration.hpp"

Config::Config()
{
	std::ifstream file;

	// Open config file
	file.open("../Config.we3d");
	if (errno != 0)
	{
		Logger::getInst().throwError("Could not load config file!");
	}

	// Store config file content
	_processOption(file, window_width);
	_processOption(file, window_height);
	_processOption(file, window_fullscreen);
	_processOption(file, window_borderless);
	_processOption(file, window_vsync);
	_processOption(file, window_dpi_scale);
	_processOption(file, msaa_quality);
	_processOption(file, shadow_quality);
	_processOption(file, water_quality);
	_processOption(file, bloom_quality);
	_processOption(file, max_lights);
	_processOption(file, audio_channels);
	_processOption(file, ssr_quality);
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
	return ivec2(window_width / window_dpi_scale, window_height / window_dpi_scale); 
}

const float Config::getWindowScale() const 
{
	return window_dpi_scale; 
}

const int Config::getWindowWidth() const 
{
	return int(float(window_width) / window_dpi_scale); 
}

const int Config::getWindowHeight() const 
{
	return int(float(window_height) / window_dpi_scale); 
}

const bool Config::isWindowFullscreen() const 
{
	return window_fullscreen; 
}

const bool Config::isWindowBorderless() const
{ 
	return window_borderless; 
}

const bool Config::isWindowVsynced() const 
{ 
	return window_vsync; 
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

const int Config::getSSRQuality() const 
{ 
	return ssr_quality; 
}

const int Config::getBloomQuality() const 
{ 
	return bloom_quality; 
}

const int Config::getMaxLights() const 
{ 
	return max_lights; 
}

const int Config::getTotalAudioChannels() const
{
	return audio_channels;
}