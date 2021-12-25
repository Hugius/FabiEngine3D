#pragma once

#include "mathematics.hpp"
#include "library_loader.hpp"

#include <SDL\\SDL.h>
#include <string>

using std::string;

class RenderWindow final
{
public:
	RenderWindow(LibraryLoader& libraryLoader);
	~RenderWindow();

	void setTitle(const string& title);
	void setSize(ivec2 size);
	void center();
	void setOpacity(float value);
	void enableColorKeying(fvec3 color);
	void disableColorKeying(fvec3 color);
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
	void setCursorPosition(ivec2 pos);

	const ivec2 getCursorPosition() const;

	const bool isCursorVisible() const;
	const bool isVsyncEnabled() const;

private:
	SDL_Window* _windowPointer = nullptr;
};