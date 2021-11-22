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
	Config(Config const&) = delete;

	// VOID
	void operator=(Config const&) = delete;

	// STRING
	const string& getWindowTitle() const;

	// FVEC2
	const ivec2 getMonitorSize() const;
	const ivec2 getWindowSize()	const;
	const ivec2 getViewportSize() const;
	const ivec2 getViewportPosition() const;

	// FLOAT
	static inline const float MS_PER_UPDATE = (1000.0f / 144.0f);

	// UNSIGNED INT
	static inline const unsigned int MIN_BLOOM_SIZE = 1;
	static inline const unsigned int MAX_BLOOM_SIZE = 5;
	static inline const unsigned int MIN_DOF_SIZE = 1;
	static inline const unsigned int MAX_DOF_SIZE = 5;
	static inline const unsigned int MIN_MOTION_BLUR_SIZE = 1;
	static inline const unsigned int MAX_MOTION_BLUR_SIZE = 5;
	static inline const unsigned int MIN_ANISOTROPIC_FILTERING_QUALITY = 1;
	static inline const unsigned int MAX_ANISOTROPIC_FILTERING_QUALITY = 16;
	static inline const unsigned int MIN_SHADOW_QUALITY = 2048;
	static inline const unsigned int MAX_SHADOW_QUALITY = 16384;
	static inline const unsigned int MIN_REFLECTION_QUALITY = 128;
	static inline const unsigned int MAX_REFLECTION_QUALITY = 1024;
	static inline const unsigned int MIN_REFRACTION_QUALITY = 128;
	static inline const unsigned int MAX_REFRACTION_QUALITY = 1024;
	static inline const unsigned int MIN_AUDIO_CHANNELS = 64;
	static inline const unsigned int MAX_AUDIO_CHANNELS = 512;
	static inline const unsigned int UPDATES_PER_SECOND = 144;

	// BOOL
	const bool isWindowFullscreen()	const;
	const bool isWindowBorderless()	const;
	const bool isApplicationExported() const;

	// Miscellaneous
	static Config& getInst()
	{
		static Config instance;
		return instance;
	}

private:
	Config();

	// VOID
	void _processOption(ifstream& file, string& option, string criteria);
	void _processOption(ifstream& file, float& option, string criteria);
	void _processOption(ifstream& file, int& option, string criteria);
	void _processOption(ifstream& file, bool& option, string criteria);

	// STRING
	string _windowTitle = "";

	// FVEC2
	ivec2 _monitorSize = ivec2(0);
	ivec2 _windowSize = ivec2(0);
	ivec2 _viewportSize = ivec2(0);
	ivec2 _viewportPosition = ivec2(0);

	// BOOL
	bool _isWindowFullscreen = false;
	bool _isWindowBorderless = false;
	bool _isApplicationExported = false;
};