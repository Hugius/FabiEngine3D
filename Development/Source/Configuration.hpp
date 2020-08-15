#pragma once

#include "logger.hpp"

#include <fstream>
#include <GLM\\glm.hpp>
#include <sstream>

using glm::ivec2;
using glm::ivec4;

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
	const ivec2 getWindowSize()        const;
	const int   getWindowWidth()       const;
	const int   getWindowHeight()      const;
	const int   getMsaaQuality()       const;
	const int   getShadowQuality()     const;
	const int   getRefractionQuality() const;
	const int   getReflectionQuality() const;
	const int   getMaxAudioChannels()  const;
	const float getMouseSensitivity()  const;
	const ivec2 getVpPos()			   const;
	const ivec2 getVpSize()			   const;
	const float getUpdateMsPerFrame()  const;

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
	int   _msaaQuality = 0;
	int   _shadowQuality = 0;
	int   _refractionQuality = 0;
	int   _reflectionQuality = 0;
	int   _maxAudioChannels = 0;
	float _mouseSensitivity = 0.0f;
	ivec2 _viewportPosition = ivec2(0);
	ivec2 _viewportSize = ivec2(0);
	float _updateMsPerFrame = 0.0f;
};