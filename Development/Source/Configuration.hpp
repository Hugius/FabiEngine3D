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
	const ivec2 getWindowSize()         const;
	const float getWindowScale()        const;
	const int   getWindowWidth()        const;
	const int   getWindowHeight()       const;
	const bool  isWindowFullscreen()    const;
	const bool  isWindowBorderless()    const;
	const bool  isWindowVsynced()       const;
	const int   getMsaaQuality()        const;
	const int   getShadowQuality()      const;
	const int   getWaterQuality()       const;
	const int   getBloomQuality()       const;
	const int   getMaxLights()          const;
	const int   getTotalAudioChannels() const;
	const int   getSSRQuality()         const;

private:
	Config();
	~Config() = default;

	void p_processOption(std::ifstream& file, bool& option);
	void p_processOption(std::ifstream& file, int& option);
	void p_processOption(std::ifstream& file, float& option);
	
	// Variables
	int   window_width;
	int   window_height;
	bool  window_fullscreen;
	bool  window_borderless;
	bool  window_vsync;
	float window_dpi_scale;
	int   msaa_quality;
	int   shadow_quality;
	int   water_quality;
	int   bloom_quality;
	int   max_lights;
	int   audio_channels;
	int   ssr_quality;
};