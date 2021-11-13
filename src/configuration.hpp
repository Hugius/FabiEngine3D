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

	// Voids
	void operator=(Config const&) = delete;

	// Strings
	const string& getWindowTitle() const;

	// Vectors
	const Ivec2 getMonitorSize() const;
	const Ivec2 getWindowSize()	const;
	const Ivec2 getViewportSize() const;
	const Ivec2 getViewportPosition() const;

	// Decimals
	static inline const float MS_PER_UPDATE = (1000.0f / 144.0f);

	// Integers
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

	// Booleans
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

	// Voids
	void _processOption(ifstream& file, string& option, string criteria);
	void _processOption(ifstream& file, float& option, string criteria);
	void _processOption(ifstream& file, int& option, string criteria);
	void _processOption(ifstream& file, bool& option, string criteria);

	// Strings
	string _windowTitle = "";

	// Vectors
	Ivec2 _monitorSize = Ivec2(0);
	Ivec2 _windowSize = Ivec2(0);
	Ivec2 _viewportSize = Ivec2(0);
	Ivec2 _viewportPosition = Ivec2(0);

	// Booleans
	bool _isWindowFullscreen = false;
	bool _isWindowBorderless = false;
	bool _isApplicationExported = false;
};