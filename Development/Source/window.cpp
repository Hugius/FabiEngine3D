#include "window.hpp"
#include "logger.hpp"
#include "configuration.hpp"

#include <SDL\\SDL_syswm.h>

Window::Window(LibraryLoader& libraryLoader)
	:
	_windowPointer(libraryLoader.getWindowPointer())
{
	hideBorder();
	disableVsync();
}

Window::~Window()
{
	SDL_DestroyWindow(_windowPointer);
}

void Window::setTitle(const string& title)
{
	SDL_SetWindowTitle(_windowPointer, title.c_str());
}

void Window::setSize(Ivec2 size)
{
	SDL_SetWindowSize(_windowPointer, size.x, size.y);
	center();
}

void Window::center()
{
	SDL_SetWindowPosition(_windowPointer, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Window::setOpacity(float value)
{
	SDL_SetWindowOpacity(_windowPointer, value);
}

void Window::enableColorKeying(Vec3 color)
{
	// Get window handle
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_windowPointer, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;

	// Set transparency color
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(static_cast<int>(color.r * 255.0f), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255)), 0, LWA_COLORKEY);
}

void Window::disableColorKeying(Vec3 color)
{
	// Get window handle
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_windowPointer, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;

	// Remove opaqueness property
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(static_cast<int>(color.r * 255.0f), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255)), 0, LWA_ALPHA);
}

void Window::showBorder()
{
	SDL_SetWindowBordered(_windowPointer, SDL_TRUE);
}

void Window::hideBorder()
{
	SDL_SetWindowBordered(_windowPointer, SDL_FALSE);
}

void Window::enableFullscreen()
{
	SDL_SetWindowFullscreen(_windowPointer, SDL_TRUE);
}

void Window::disableFullscreen()
{
	SDL_SetWindowFullscreen(_windowPointer, SDL_FALSE);
}

void Window::enableVsync()
{
	SDL_GL_SetSwapInterval(1);
}

void Window::disableVsync()
{
	SDL_GL_SetSwapInterval(0);
}

void Window::swapBackBuffer()
{
	SDL_GL_SwapWindow(_windowPointer);
}

void Window::showWindow()
{
	SDL_ShowWindow(_windowPointer);
}

void Window::hideWindow()
{
	SDL_HideWindow(_windowPointer);
}

void Window::showCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}

void Window::hideCursor()
{
	SDL_ShowCursor(SDL_DISABLE);
}

void Window::setCursorPosition(Ivec2 pos)
{
	SDL_WarpMouseInWindow(_windowPointer, pos.x, pos.y);
}

const Ivec2 Window::getCursorPosition() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return Ivec2(x, y);
}

const bool Window::isCursorVisible() const
{
	return static_cast<bool>(SDL_ShowCursor(SDL_QUERY));
}

const bool Window::isVsyncEnabled() const
{
	return SDL_GL_GetSwapInterval();
}