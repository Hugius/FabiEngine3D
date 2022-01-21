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

	void operator=(Config const&) = delete;

	const string& getWindowTitle() const;

	const ivec2& getMonitorSize() const;
	const ivec2& getWindowSize()	const;
	const ivec2& getViewportSize() const;
	const ivec2& getViewportPosition() const;

	static inline constexpr float MS_PER_UPDATE = (1000.0f / 144.0f);

	static inline constexpr unsigned int MIN_BLOOM_QUALITY = 1;
	static inline constexpr unsigned int MAX_BLOOM_QUALITY = 5;
	static inline constexpr unsigned int MIN_DOF_QUALITY = 1;
	static inline constexpr unsigned int MAX_DOF_QUALITY = 5;
	static inline constexpr unsigned int MIN_MOTION_BLUR_QUALITY = 1;
	static inline constexpr unsigned int MAX_MOTION_BLUR_QUALITY = 5;
	static inline constexpr unsigned int MIN_ANISOTROPIC_FILTERING_QUALITY = 1;
	static inline constexpr unsigned int MAX_ANISOTROPIC_FILTERING_QUALITY = 16;
	static inline constexpr unsigned int MIN_SHADOW_QUALITY = 2048;
	static inline constexpr unsigned int MAX_SHADOW_QUALITY = 16384;
	static inline constexpr unsigned int MIN_REFLECTION_QUALITY = 128;
	static inline constexpr unsigned int MAX_REFLECTION_QUALITY = 1024;
	static inline constexpr unsigned int MIN_REFRACTION_QUALITY = 128;
	static inline constexpr unsigned int MAX_REFRACTION_QUALITY = 1024;
	static inline constexpr unsigned int UPDATES_PER_SECOND = 144;

	const bool isWindowFullscreen()	const;
	const bool isWindowBorderless()	const;
	const bool isApplicationExported() const;

	static Config& getInst()
	{
		static Config instance;
		return instance;
	}

private:
	Config();

	void _processOption(ifstream& file, string& option, string name);
	void _processOption(ifstream& file, float& option, string name);
	void _processOption(ifstream& file, int& option, string name);
	void _processOption(ifstream& file, bool& option, string name);

	string _windowTitle = "";

	ivec2 _monitorSize = ivec2(0);
	ivec2 _windowSize = ivec2(0);
	ivec2 _viewportSize = ivec2(0);
	ivec2 _viewportPosition = ivec2(0);

	bool _isWindowFullscreen = false;
	bool _isWindowBorderless = false;
	bool _isApplicationExported = false;
};