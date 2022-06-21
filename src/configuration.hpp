#pragma once

#include "mathematics.hpp"

#include <fstream>
#include <string>

using std::string;
using std::ifstream;

class Configuration final
{
public:
	Configuration();

	const string & getWindowTitle() const;

	const ivec2 & getWindowSize() const;
	const ivec2 & getDisplaySize() const;
	const ivec2 & getDisplayPosition() const;

	const bool isApplicationExported() const;

private:
	void _processOption(ifstream & file, const string & name, string & option);
	void _processOption(ifstream & file, const string & name, int & option, int minValue, int maxValue);

	static inline const string DEFAULT_WINDOW_TITLE = "FabiEngine3D";

	static inline const fvec2 DISPLAY_POSITION_MULTIPLIER = fvec2(0.125f, 0.2f);
	static inline const fvec2 DISPLAY_SIZE_MULTIPLIER = fvec2(0.75f, 0.75f);

	static inline constexpr float DEFAULT_WINDOW_SIZE_MULTIPLIER = 0.9f;

	string _windowTitle = "";

	ivec2 _windowSize = ivec2(0);
	ivec2 _displaySize = ivec2(0);
	ivec2 _displayPosition = ivec2(0);

	bool _isApplicationExported = false;
};