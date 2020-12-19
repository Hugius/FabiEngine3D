#include "configuration.hpp"
#include "logger.hpp"

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
	string path = rootDir + "config.fe3d";
	std::ifstream file(path);
	if (!std::filesystem::exists(path))
	{
		Logger::throwError("Could not load engine configuration file!");
	}

	// Store config file content
	_processOption(file, _windowSizeMultiplier, "window_size_multiplier");
	_processOption(file, _selectedGame, "selected_game");
	
	// Set window dimensions
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	_windowWidth = static_cast<int>(static_cast<float>(DM.w) * _windowSizeMultiplier);
	_windowHeight = static_cast<int>(static_cast<float>(DM.h) * _windowSizeMultiplier);

	// Set viewport dimensions
	if (_selectedGame.empty()) // Engine preview
	{
		_viewportPosition.x = static_cast<int>(0.125f * static_cast<float>(_windowWidth));
		_viewportPosition.y = static_cast<int>(0.2f * static_cast<float>(_windowHeight));
		_viewportSize.x = static_cast<int>(0.75f * static_cast<float>(_windowWidth));
		_viewportSize.y = static_cast<int>(0.75f * static_cast<float>(_windowHeight));
	}
	else // Game preview
	{
		_viewportPosition.x = 0;
		_viewportPosition.y = 0;
		_viewportSize.x = static_cast<int>(static_cast<float>(_windowWidth));
		_viewportSize.y = static_cast<int>(static_cast<float>(_windowHeight));
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
		Logger::throwError("Configuration file: invalid option name!");
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
		Logger::throwError("Configuration file: invalid option name!");
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
		Logger::throwError("Configuration file: invalid option name!");
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
			Logger::throwError("Configuration file: wrong boolean value!");
		}
	}
	else
	{
		Logger::throwError("Configuration file: invalid option name!");
	}
}

Ivec2 Config::getWindowSize() const 
{ 
	return Ivec2(_windowWidth, _windowHeight); 
}

int Config::getWindowWidth() const 
{
	return _windowWidth;
}

int Config::getWindowHeight() const 
{
	return _windowHeight; 
}

Ivec2 Config::getVpPos() const
{
	return _viewportPosition;
}

Ivec2 Config::getVpSize() const
{
	return _viewportSize;
}

float Config::getUpdateMsPerFrame() const
{
	return _updateMsPerFrame;
}

string Config::getSelectedGame() const
{
	return _selectedGame;
}