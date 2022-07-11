#define GLEW_STATIC

#include "render_window.hpp"
#include "tools.hpp"
#include "logger.hpp"

#include <glew.h>
#include <wglew.h>

HDC windowContext = nullptr;
HGLRC openglContext = nullptr;

LRESULT CALLBACK processWindowMessage(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_CREATE:
		{
			PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {};

			pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pixelFormatDescriptor.nVersion = 1;
			pixelFormatDescriptor.dwFlags = (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER);
			pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
			pixelFormatDescriptor.cColorBits = 32;
			pixelFormatDescriptor.cRedBits = 0;
			pixelFormatDescriptor.cRedShift = 0;
			pixelFormatDescriptor.cGreenBits = 0;
			pixelFormatDescriptor.cGreenShift = 0;
			pixelFormatDescriptor.cBlueBits = 0;
			pixelFormatDescriptor.cBlueShift = 0;
			pixelFormatDescriptor.cAlphaBits = 0;
			pixelFormatDescriptor.cAlphaShift = 0;
			pixelFormatDescriptor.cAccumBits = 0;
			pixelFormatDescriptor.cAccumRedBits = 0;
			pixelFormatDescriptor.cAccumGreenBits = 0;
			pixelFormatDescriptor.cAccumBlueBits = 0;
			pixelFormatDescriptor.cAccumAlphaBits = 0;
			pixelFormatDescriptor.cDepthBits = 24;
			pixelFormatDescriptor.cStencilBits = 8;
			pixelFormatDescriptor.cAuxBuffers = 0;
			pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;
			pixelFormatDescriptor.bReserved = 0;
			pixelFormatDescriptor.dwLayerMask = 0;
			pixelFormatDescriptor.dwVisibleMask = 0;
			pixelFormatDescriptor.dwDamageMask = 0;

			windowContext = GetDC(windowHandle);

			const auto pixelFormat = ChoosePixelFormat(windowContext, &pixelFormatDescriptor);

			if(pixelFormat == 0)
			{
				abort();
			}

			SetPixelFormat(windowContext, pixelFormat, &pixelFormatDescriptor);

			openglContext = wglCreateContext(windowContext);

			wglMakeCurrent(windowContext, openglContext);

			break;
		}
		case WM_DESTROY:
		{
			wglDeleteContext(openglContext);
			ReleaseDC(windowHandle, windowContext);
			PostQuitMessage(0);

			openglContext = nullptr;
			windowContext = nullptr;

			break;
		}
		default:
		{
			return DefWindowProc(windowHandle, message, wParam, lParam);
		}
	}

	return 0;
}

RenderWindow::RenderWindow()
{
	WNDCLASS windowClass = {};

	windowClass.lpfnWndProc = processWindowMessage;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.lpszClassName = "RenderWindow";
	windowClass.style = CS_OWNDC;

	if(!RegisterClass(&windowClass))
	{
		abort();
	}

	_windowHandle = CreateWindow(windowClass.lpszClassName, "RenderWindow", WS_POPUP, 0, 0, 0, 0, 0, 0, windowClass.hInstance, 0);

	if(_windowHandle == nullptr)
	{
		abort();
	}

	SetCursor(LoadCursor(nullptr, IDC_ARROW));

	const auto glewStatus = glewInit();

	if(glewStatus != GLEW_OK)
	{
		Logger::throwError("GLEW could not be initialized: ", reinterpret_cast<const char *>(glewGetErrorString(glewStatus)));
	}
}

void RenderWindow::inject(shared_ptr<InputHandler> inputHandler)
{
	_inputHandler = inputHandler;
}

void RenderWindow::update()
{
	if(_windowHandle == nullptr)
	{
		abort();
	}

	if(!IsWindow(_windowHandle))
	{
		_windowHandle = nullptr;

		return;
	}

	MSG messageEvent = {};

	while(PeekMessage(&messageEvent, _windowHandle, 0, 0, PM_REMOVE))
	{
		switch(messageEvent.message)
		{
			case WM_LBUTTONDOWN:
			{
				_inputHandler->sendMouseDownEvent(MouseButtonType::BUTTON_LEFT);

				break;
			}
			case WM_LBUTTONUP:
			{
				_inputHandler->sendMouseUpEvent(MouseButtonType::BUTTON_LEFT);

				break;
			}
			case WM_MBUTTONDOWN:
			{
				_inputHandler->sendMouseDownEvent(MouseButtonType::BUTTON_MIDDLE);

				break;
			}
			case WM_MBUTTONUP:
			{
				_inputHandler->sendMouseUpEvent(MouseButtonType::BUTTON_MIDDLE);

				break;
			}
			case WM_RBUTTONDOWN:
			{
				_inputHandler->sendMouseDownEvent(MouseButtonType::BUTTON_RIGHT);

				break;
			}
			case WM_RBUTTONUP:
			{
				_inputHandler->sendMouseUpEvent(MouseButtonType::BUTTON_RIGHT);

				break;
			}
			case WM_MOUSEWHEEL:
			{
				const auto direction = GET_WHEEL_DELTA_WPARAM(messageEvent.wParam);

				if(direction > 0)
				{
					_inputHandler->sendMouseWheelEvent(MouseWheelType::WHEEL_FORWARD);
				}
				else if(direction < 0)
				{
					_inputHandler->sendMouseWheelEvent(MouseWheelType::WHEEL_BACKWARD);
				}

				break;
			}
			case WM_KEYDOWN:
			{
				_inputHandler->sendKeyboardDownEvent(KeyboardKeyType(messageEvent.wParam));

				break;
			}
			case WM_KEYUP:
			{
				_inputHandler->sendKeyboardUpEvent(KeyboardKeyType(messageEvent.wParam));

				break;
			}
			default:
			{
				DispatchMessage(&messageEvent);

				break;
			}
		}
	}
}

void RenderWindow::setPosition(const ivec2 & value)
{
	if(_windowHandle == nullptr)
	{
		abort();
	}

	SetWindowPos(_windowHandle, nullptr, value.x, value.y, 0, 0, SWP_NOSIZE);
}

void RenderWindow::setSize(const ivec2 & value)
{
	if(_windowHandle == nullptr)
	{
		abort();
	}

	if((value.x < 0) || (value.y < 0))
	{
		abort();
	}

	SetWindowPos(_windowHandle, nullptr, 0, 0, value.x, value.y, SWP_NOMOVE);
}

void RenderWindow::setColorKeyingEnabled(bool value)
{
	if(_windowHandle == nullptr)
	{
		abort();
	}

	SetWindowLong(_windowHandle, GWL_EXSTYLE, (value ? WS_EX_LAYERED : CS_OWNDC));
}

void RenderWindow::setKeyingColor(const fvec3 & value)
{
	if(_windowHandle == nullptr)
	{
		abort();
	}

	SetLayeredWindowAttributes(_windowHandle, RGB(static_cast<int>(value.r * COLOR_FACTOR), static_cast<int>(value.g * COLOR_FACTOR), static_cast<int>(value.b * COLOR_FACTOR)), 0, LWA_COLORKEY);
}

void RenderWindow::setTitle(const string & value)
{
	if(_windowHandle == nullptr)
	{
		abort();
	}

	if(value.size() > MAX_TITLE_LENGTH)
	{
		abort();
	}

	SetWindowText(_windowHandle, value.c_str());
}

void RenderWindow::setVsyncEnabled(bool value)
{
	if(windowContext == nullptr)
	{
		abort();
	}

	wglSwapIntervalEXT(static_cast<int>(value));
}

void RenderWindow::swapBuffer()
{
	if(windowContext == nullptr)
	{
		return;
	}

	if(!wglSwapLayerBuffers(windowContext, WGL_SWAP_MAIN_PLANE))
	{
		abort();
	}
}

const string RenderWindow::getTitle() const
{
	if(_windowHandle == nullptr)
	{
		abort();
	}

	char title[MAX_TITLE_LENGTH] = {};

	GetWindowText(_windowHandle, title, MAX_TITLE_LENGTH);

	return string(title);
}

const fvec3 RenderWindow::getKeyingColor() const
{
	if(_windowHandle == nullptr)
	{
		abort();
	}

	COLORREF color = {};

	GetLayeredWindowAttributes(_windowHandle, &color, nullptr, nullptr);

	return fvec3(GetRValue(color), GetGValue(color), GetBValue(color));
}

void RenderWindow::setVisible(bool value)
{
	if(_windowHandle == nullptr)
	{
		abort();
	}

	ShowWindow(_windowHandle, (value ? SW_SHOW : SW_HIDE));

	if(value)
	{
		SetFocus(_windowHandle);
	}
}

const bool RenderWindow::isExisting() const
{
	return (_windowHandle != nullptr);
}

const bool RenderWindow::isVisible() const
{
	if(_windowHandle == nullptr)
	{
		abort();
	}

	return IsWindowVisible(_windowHandle);
}

const bool RenderWindow::isVsyncEnabled() const
{
	if(windowContext == nullptr)
	{
		abort();
	}

	return static_cast<bool>(wglGetSwapIntervalEXT());
}