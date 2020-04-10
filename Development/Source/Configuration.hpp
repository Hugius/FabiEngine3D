#pragma once
#include <fstream>
#include <GLM/glm.hpp>
#include <sstream>

using glm::ivec2;
using glm::ivec4;

#include "Logger.hpp"

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
	const float getWindowZoomScale()   const;
	const int   getMsaaQuality()       const;
	const int   getShadowQuality()     const;
	const int   getWaterQuality()      const;
	const int   getReflectionQuality() const;
	const int   getMaxAudioChannels()  const;
	const ivec2 getVpPos()			   const;
	const ivec2 getVpSize()			   const;

private:
	Config();
	~Config() = default;

	void _processOption(std::ifstream& file, bool& option);
	void _processOption(std::ifstream& file, int& option);
	void _processOption(std::ifstream& file, float& option);
	
	// Variables
	int   _windowWidth = 800;
	int   _windowHeight = 600;
	float _windowZoomScale = 1.0f;
	int   _msaaQuality = 16;
	int   _shadowQuality = 4096;
	int   _waterQuality = 1024;
	int   _reflectionQuality = 1024;
	int   _maxAudioChannels = 512;
	ivec2 _viewportPosition = ivec2(0);
	ivec2 _viewportSize = ivec2(0);
};