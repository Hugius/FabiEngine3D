#pragma once

#include "mathematics.hpp"

#include <fstream>
#include <sstream>
#include <string>

using std::string;
using std::ifstream;

class Config final
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
	const string& getApplicationTitle()	  const;
	const string& getWindowTitle()		  const;
	const Ivec2   getMonitorSize()		  const;
	const Ivec2   getWindowSize()		  const;
	const Ivec2   getVpSize()			  const;
	const Ivec2   getVpPos()			  const;
	const bool    isWindowFullscreen()	  const;
	const bool    isWindowBorderless()	  const;
	const bool    isApplicationExported() const;

	// Constants
	static inline const unsigned int MIN_BLOOM_SIZE = 1;
	static inline const unsigned int MAX_BLOOM_SIZE = 5;
	static inline const unsigned int MIN_DOF_SIZE = 1;
	static inline const unsigned int MAX_DOF_SIZE = 5;
	static inline const unsigned int MIN_MOTION_BLUR_SIZE = 1;
	static inline const unsigned int MAX_MOTION_BLUR_SIZE = 5;
	static inline const unsigned int MIN_ANISOTROPIC_FILTERING_QUALITY = 1;
	static inline const unsigned int MAX_ANISOTROPIC_FILTERING_QUALITY = 16;
	static inline const unsigned int MIN_SHADOW_QUALITY = 2048;
	static inline const unsigned int MAX_SHADOW_QUALITY = 8192;
	static inline const unsigned int MIN_REFLECTION_QUALITY = 256;
	static inline const unsigned int MAX_REFLECTION_QUALITY = 1024;
	static inline const unsigned int MIN_REFRACTION_QUALITY = 256;
	static inline const unsigned int MAX_REFRACTION_QUALITY = 1024;
	static inline const unsigned int MIN_AUDIO_CHANNELS = 64;
	static inline const unsigned int MAX_AUDIO_CHANNELS = 512;
	static inline const unsigned int UPDATES_PER_SECOND = 144;
	static inline const float MS_PER_UPDATE = (1000.0f / static_cast<float>(UPDATES_PER_SECOND));

private:
	Config();

	void _processOption(ifstream& file, string& option, string criteria);
	void _processOption(ifstream& file, float& option, string criteria);
	void _processOption(ifstream& file, int& option, string criteria);
	void _processOption(ifstream& file, bool& option, string criteria);
	
	string _applicationTitle = "";
	string _windowTitle = "";
	Ivec2  _monitorSize = Ivec2(0);
	Ivec2  _windowSize = Ivec2(0);
	Ivec2  _viewportSize = Ivec2(0);
	Ivec2  _viewportPosition = Ivec2(0);
	bool   _isWindowFullscreen = false;
	bool   _isWindowBorderless = false;
	bool   _isApplicationExported = false;
};