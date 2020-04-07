#pragma once

#include <SDL/SDL.h>
#include <GLM/glm.hpp>
#include <string>

using glm::ivec2;

class WindowManager final
{
public:
	WindowManager();
	~WindowManager();

	void setTitle(const std::string & title);
	void setSize(ivec2 size);
	void showBorder();
	void hideBorder();
	void enableFullscreen();
	void disableFullscreen();
	void swapBackBuffer();
	void showWindow();
	void hideWindow();
	void showMouseCursor();
	void hideMouseCursor();
	void setMousePos(ivec2 pos);

	const ivec2 getMousePos() const;

private:
	SDL_Window * _window = nullptr;

	SDL_GLContext _context;
};