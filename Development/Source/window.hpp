#pragma once

#include "mathematics.hpp"
#include "library_loader.hpp"

#include <SDL\\SDL.h>
#include <string>

using std::string;

class Window final
{
public:
	Window(LibraryLoader& libraryLoader);
	~Window();
	
	void setTitle(const string& title);
	void setSize(Ivec2 size);
	void center();
	void setOpacity(float value);
	void enableColorKeying(Vec3 color);
	void disableColorKeying(Vec3 color);
	void showBorder();
	void hideBorder();
	void enableFullscreen();
	void disableFullscreen();
	void enableVsync();
	void disableVsync();
	void swapBackBuffer();
	void showWindow();
	void hideWindow();
	void showCursor();
	void hideCursor();
	void setCursorPosition(Ivec2 pos);

	const Ivec2 getCursorPosition();
	bool isCursorVisible();
	const bool isVsyncEnabled();

private:
	SDL_Window* _windowPointer = nullptr;
};