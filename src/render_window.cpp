#include "render_window.hpp"
#include "logger.hpp"
#include "configuration.hpp"

#include <SDL\\SDL_syswm.h>

RenderWindow::RenderWindow(LibraryLoader& libraryLoader)
	:
	_windowPointer(libraryLoader.getWindowPointer())
{
	hideBorder();
	disableVsync();
}

RenderWindow::~RenderWindow()
{
	SDL_DestroyWindow(_windowPointer);
}

void RenderWindow::setTitle(const string& title)
{
	SDL_SetWindowTitle(_windowPointer, title.c_str());
}

void RenderWindow::setSize(ivec2 size)
{
	SDL_SetWindowSize(_windowPointer, size.x, size.y);
	center();
}

void RenderWindow::center()
{
	SDL_SetWindowPosition(_windowPointer, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void RenderWindow::setOpacity(float value)
{
	SDL_SetWindowOpacity(_windowPointer, value);
}

void RenderWindow::enableColorKeying(fvec3 color)
{
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_windowPointer, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;

	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(static_cast<int>(color.r * 255.0f), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255)), 0, LWA_COLORKEY);
}

void RenderWindow::disableColorKeying(fvec3 color)
{
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_windowPointer, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;

	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(static_cast<int>(color.r * 255.0f), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255)), 0, LWA_ALPHA);
}

void RenderWindow::showBorder()
{
	SDL_SetWindowBordered(_windowPointer, SDL_TRUE);
}

void RenderWindow::hideBorder()
{
	SDL_SetWindowBordered(_windowPointer, SDL_FALSE);
}

void RenderWindow::enableFullscreen()
{
	SDL_SetWindowFullscreen(_windowPointer, SDL_TRUE);
}

void RenderWindow::disableFullscreen()
{
	SDL_SetWindowFullscreen(_windowPointer, SDL_FALSE);
}

void RenderWindow::enableVsync()
{
	SDL_GL_SetSwapInterval(1);
}

void RenderWindow::disableVsync()
{
	SDL_GL_SetSwapInterval(0);
}

void RenderWindow::swapBackBuffer()
{
	SDL_GL_SwapWindow(_windowPointer);
}

void RenderWindow::showWindow()
{
	SDL_ShowWindow(_windowPointer);
}

void RenderWindow::hideWindow()
{
	SDL_HideWindow(_windowPointer);
}

void RenderWindow::showCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}

void RenderWindow::hideCursor()
{
	SDL_ShowCursor(SDL_DISABLE);
}

void RenderWindow::setCursorPosition(ivec2 pos)
{
	SDL_WarpMouseInWindow(_windowPointer, pos.x, pos.y);
}

const ivec2 RenderWindow::getCursorPosition() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return ivec2(x, y);
}

const bool RenderWindow::isCursorVisible() const
{
	return static_cast<bool>(SDL_ShowCursor(SDL_QUERY));
}

const bool RenderWindow::isVsyncEnabled() const
{
	return SDL_GL_GetSwapInterval();
}