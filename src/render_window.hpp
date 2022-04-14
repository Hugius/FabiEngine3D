#pragma once

#include "mathematics.hpp"

#include <string>
#include <windows.h>

using std::string;

class RenderWindow final
{
public:
	RenderWindow();

	void update();
	void setPosition(const ivec2 & value);
	void setSize(const ivec2 & value);
	void setVisible(bool value);
	void setColorKeyingEnabled(bool value);
	void setKeyingColor(const fvec3 & value);
	void setTitle(const string & value);
	void swapBuffer();

	const string getTitle() const;

	const ivec2 getPosition() const;
	const ivec2 getSize() const;

	const bool isExisting() const;

private:
	static inline constexpr unsigned int MAX_TITLE_LENGTH = 100;

	HWND _windowHandle = nullptr;
};