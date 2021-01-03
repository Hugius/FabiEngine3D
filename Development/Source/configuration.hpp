#pragma once

#include "mathematics.hpp"

#include <fstream>
#include <sstream>
#include <string>

using std::string;
using std::ifstream;

class Config
{
public:
	// Global instance
	static Config& getInst()
	{
		static Config instance;
		return instance;
	}

	// Safe singleton
	Config(Config const&) = delete;
	void operator=(Config const&) = delete;

	// Interface functions
	Ivec2  getMonitorSize()      const;
	int    getMonitorWidth()     const;
	int    getMonitorHeight()    const;
	Ivec2  getWindowSize()       const;
	int    getWindowWidth()      const;
	int    getWindowHeight()     const;
	Ivec2  getVpPos()			 const;
	Ivec2  getVpSize()			 const;
	float  getUpdateMsPerFrame() const;
	string getSelectedGame()	 const;
	bool   isWindowFullscreen()	 const;
	bool   isWindowBorderless()	 const;

private:
	Config();
	~Config() = default;

	void _processOption(ifstream& file, string& option, string criteria);
	void _processOption(ifstream& file, float& option, string criteria);
	void _processOption(ifstream& file, int& option, string criteria);
	void _processOption(ifstream& file, bool& option, string criteria);
	
	// Variables
	int   _monitorWidth = 0;
	int   _monitorHeight = 0;
	int   _windowWidth = 0;
	int   _windowHeight = 0;
	Ivec2 _viewportPosition = Ivec2(0);
	Ivec2 _viewportSize = Ivec2(0);
	float _windowSizeMultiplier = 0.0f;
	string _selectedGame = "";
	bool _isWindowFullscreen = false;
	bool _isWindowBorderless = false;

	// Constants
	const float _updateMsPerFrame = 6.94f; // 144 hz
};