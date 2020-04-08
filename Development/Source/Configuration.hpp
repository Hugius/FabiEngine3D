#pragma once
#include <fstream>
#include <GLM/glm.hpp>
#include <sstream>

using glm::ivec2;

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

private:
	Config();
	~Config() = default;

	void _processOption(std::ifstream& file, bool& option);
	void _processOption(std::ifstream& file, int& option);
	void _processOption(std::ifstream& file, float& option);
	
	// Variables
	int   window_width = 800;
	int   window_height = 600;
	float window_zoom_scale = 1.0f;
	int   msaa_quality = 16;
	int   shadow_quality = 4096;
	int   water_quality = 1024;
	int   reflection_quality = 1024;
	int   max_audio_channels = 512;
};