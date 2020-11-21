#pragma once

#include "mathematics.hpp"

#include <SDL\\SDL.h>
#include <string>

class WindowManager final
{
public:
	WindowManager();
	~WindowManager();
	
	void setTitle(const std::string & title);
	void setSize(Ivec2 size);
	void setOpacity(float value);
	void enableOpaqueness(Vec3 color);
	void disableOpaqueness(Vec3 color);
	void showBorder();
	void hideBorder();
	void enableFullscreen();
	void disableFullscreen();
	void swapBackBuffer();
	void showWindow();
	void hideWindow();
	void showMouseCursor();
	void hideMouseCursor();
	void setMousePos(Ivec2 pos);

	const Ivec2 getMousePos() const;

private:
	SDL_Window * _window = nullptr;

	SDL_GLContext _context;
};