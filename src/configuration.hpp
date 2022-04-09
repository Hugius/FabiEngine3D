#pragma once

#include "mathematics.hpp"

#include <fstream>
#include <sstream>
#include <string>

using std::string;
using std::ifstream;

class Configuration final
{
public:
	Configuration(Configuration const &) = delete;

	void operator=(Configuration const &) = delete;

	const string & getWindowTitle() const;

	const ivec2 & getMonitorSize() const;
	const ivec2 & getWindowSize()	const;
	const ivec2 & getDisplaySize() const;
	const ivec2 & getDisplayPosition() const;

	const float getWindowSizeMultiplier() const;

	const bool isWindowFullscreen()	const;
	const bool isWindowBorderless()	const;
	const bool isApplicationExported() const;

	static Configuration & getInst()
	{
		static Configuration instance;

		return instance;
	}

private:
	Configuration();

	void _processOption(ifstream & file, string & option, const string & name);
	void _processOption(ifstream & file, float & option, const string & name);
	void _processOption(ifstream & file, int & option, const string & name);
	void _processOption(ifstream & file, bool & option, const string & name);

	static inline const fvec2 DISPLAY_POSITION_MULTIPLIER = fvec2(0.125f, 0.2f);
	static inline const fvec2 DISPLAY_SIZE_MULTIPLIER = fvec2(0.75f, 0.75f);

	static inline constexpr float DEFAULT_WINDOW_SIZE_MULTIPLIER = 0.9f;

	string _windowTitle = "";

	ivec2 _monitorSize = ivec2(0);
	ivec2 _windowSize = ivec2(0);
	ivec2 _displaySize = ivec2(0);
	ivec2 _displayPosition = ivec2(0);

	float _windowSizeMultiplier = 0.0f;

	bool _isWindowFullscreen = false;
	bool _isWindowBorderless = false;
	bool _isApplicationExported = false;
};