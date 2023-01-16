#pragma once

#include "mathematics.hpp"
#include "input_handler.hpp"

#include <string>
#include <windows.h>

using std::shared_ptr;
using std::string;

class RenderWindow final
{
public:
	void construct();
	void inject(shared_ptr<InputHandler> inputHandler);
	void update();
	void setPosition(const ivec2 & value);
	void setSize(const ivec2 & value);
	void setVisible(bool value);
	void setColorKeyingEnabled(bool value);
	void setKeyingColor(const fvec3 & value);
	void setTitle(const string & value);
	void setVsyncEnabled(bool value);
	void swapBuffer();

	const string getTitle() const;

	const fvec3 getKeyingColor() const;

	const bool isExisting() const;
	const bool isVisible() const;
	const bool isVsyncEnabled() const;

private:
	static inline constexpr float COLOR_FACTOR = 255.0f;

	static inline constexpr int MAX_TITLE_LENGTH = 100;

	shared_ptr<InputHandler> _inputHandler = nullptr;

	HWND _windowHandle = nullptr;
};