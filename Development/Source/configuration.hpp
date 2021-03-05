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
	string getWindowTitle()		 const;
	Ivec2  getMonitorSize()      const;
	Ivec2  getWindowSize()       const;
	Ivec2  getVpSize()			 const;
	Ivec2  getVpPos()			 const;
	bool   isWindowFullscreen()	 const;
	bool   isWindowBorderless()	 const;
	bool   isGameExported()		 const;

	// Constants
	static inline const float MS_PER_UPDATE = 6.94f; // 144 Hz

private:
	Config();
	~Config() = default;

	void _processOption(ifstream& file, string& option, string criteria);
	void _processOption(ifstream& file, float& option, string criteria);
	void _processOption(ifstream& file, int& option, string criteria);
	void _processOption(ifstream& file, bool& option, string criteria);
	
	string _windowTitle = "";
	Ivec2  _monitorSize = Ivec2(0);
	Ivec2  _windowSize = Ivec2(0);
	Ivec2  _viewportSize = Ivec2(0);
	Ivec2  _viewportPosition = Ivec2(0);
	bool   _isWindowFullscreen = false;
	bool   _isWindowBorderless = false;
	bool   _isGameExported = false;
};