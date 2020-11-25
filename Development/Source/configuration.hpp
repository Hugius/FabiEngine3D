#pragma once

#include "mathematics.hpp"

#include <fstream>
#include <sstream>

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
	Ivec2 getWindowSize()        const;
	int   getWindowWidth()       const;
	int   getWindowHeight()      const;
	Ivec2 getVpPos()			 const;
	Ivec2 getVpSize()			 const;
	float getUpdateMsPerFrame()  const;

private:
	Config();
	~Config() = default;

	void _processOption(std::ifstream& file, bool& option);
	void _processOption(std::ifstream& file, int& option);
	void _processOption(std::ifstream& file, float& option);
	
	// Variables
	bool  _windowFullscreen = false;
	int   _windowWidth = 0;
	int   _windowHeight = 0;
	Ivec2 _viewportPosition = Ivec2(0);
	Ivec2 _viewportSize = Ivec2(0);
	float _updateMsPerFrame = 0.0f;
};