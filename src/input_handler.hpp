#pragma once

#include "mouse_wheel_type.hpp"
#include "mouse_button_type.hpp"
#include "keyboard_key_type.hpp"

#include <vector>

using std::vector;

class InputHandler final
{
public:
	void update();
	void sendMouseWheelEvent(MouseWheelType wheel);
	void sendMouseDownEvent(MouseButtonType button);
	void sendMouseUpEvent(MouseButtonType button);
	void sendKeyboardDownEvent(KeyboardKeyType key);
	void sendKeyboardUpEvent(KeyboardKeyType key);

	const bool isMouseScrolled(MouseWheelType wheel) const;
	const bool isMouseHeld(MouseButtonType button) const;
	const bool isMousePressed(MouseButtonType button) const;
	const bool isMouseToggled(MouseButtonType button) const;
	const bool isKeyboardHeld(KeyboardKeyType key) const;
	const bool isKeyboardPressed(KeyboardKeyType key) const;
	const bool isKeyboardToggled(KeyboardKeyType key) const;

private:
	static inline const vector<MouseButtonType> _mouseButtons =
	{
		MouseButtonType::BUTTON_LEFT,
		MouseButtonType::BUTTON_MIDDLE,
		MouseButtonType::BUTTON_RIGHT,
	};
	static inline const vector<KeyboardKeyType> _keyboardKeys =
	{
		KeyboardKeyType::KEY_BACKSPACE,
		KeyboardKeyType::KEY_TAB,
		KeyboardKeyType::KEY_ENTER,
		KeyboardKeyType::KEY_SHIFT,
		KeyboardKeyType::KEY_CONTROL,
		KeyboardKeyType::KEY_ALT,
		KeyboardKeyType::KEY_CAPSLOCK,
		KeyboardKeyType::KEY_ESCAPE,
		KeyboardKeyType::KEY_SPACEBAR,
		KeyboardKeyType::KEY_PAGEUP,
		KeyboardKeyType::KEY_PAGEDOWN,
		KeyboardKeyType::KEY_END,
		KeyboardKeyType::KEY_HOME,
		KeyboardKeyType::KEY_LEFT,
		KeyboardKeyType::KEY_UP,
		KeyboardKeyType::KEY_RIGHT,
		KeyboardKeyType::KEY_DOWN,
		KeyboardKeyType::KEY_INSERT,
		KeyboardKeyType::KEY_DELETE,
		KeyboardKeyType::KEY_0,
		KeyboardKeyType::KEY_1,
		KeyboardKeyType::KEY_2,
		KeyboardKeyType::KEY_3,
		KeyboardKeyType::KEY_4,
		KeyboardKeyType::KEY_5,
		KeyboardKeyType::KEY_6,
		KeyboardKeyType::KEY_7,
		KeyboardKeyType::KEY_8,
		KeyboardKeyType::KEY_9,
		KeyboardKeyType::KEY_A,
		KeyboardKeyType::KEY_B,
		KeyboardKeyType::KEY_C,
		KeyboardKeyType::KEY_D,
		KeyboardKeyType::KEY_E,
		KeyboardKeyType::KEY_F,
		KeyboardKeyType::KEY_G,
		KeyboardKeyType::KEY_H,
		KeyboardKeyType::KEY_I,
		KeyboardKeyType::KEY_J,
		KeyboardKeyType::KEY_K,
		KeyboardKeyType::KEY_L,
		KeyboardKeyType::KEY_M,
		KeyboardKeyType::KEY_N,
		KeyboardKeyType::KEY_O,
		KeyboardKeyType::KEY_P,
		KeyboardKeyType::KEY_Q,
		KeyboardKeyType::KEY_R,
		KeyboardKeyType::KEY_S,
		KeyboardKeyType::KEY_T,
		KeyboardKeyType::KEY_U,
		KeyboardKeyType::KEY_V,
		KeyboardKeyType::KEY_W,
		KeyboardKeyType::KEY_X,
		KeyboardKeyType::KEY_Y,
		KeyboardKeyType::KEY_Z,
		KeyboardKeyType::KEY_NUMPAD0,
		KeyboardKeyType::KEY_NUMPAD1,
		KeyboardKeyType::KEY_NUMPAD2,
		KeyboardKeyType::KEY_NUMPAD3,
		KeyboardKeyType::KEY_NUMPAD4,
		KeyboardKeyType::KEY_NUMPAD5,
		KeyboardKeyType::KEY_NUMPAD6,
		KeyboardKeyType::KEY_NUMPAD7,
		KeyboardKeyType::KEY_NUMPAD8,
		KeyboardKeyType::KEY_NUMPAD9,
		KeyboardKeyType::KEY_MULTIPLY,
		KeyboardKeyType::KEY_ADD,
		KeyboardKeyType::KEY_SUBTRACT,
		KeyboardKeyType::KEY_DECIMAL,
		KeyboardKeyType::KEY_DIVIDE,
		KeyboardKeyType::KEY_F1,
		KeyboardKeyType::KEY_F2,
		KeyboardKeyType::KEY_F3,
		KeyboardKeyType::KEY_F4,
		KeyboardKeyType::KEY_F5,
		KeyboardKeyType::KEY_F6,
		KeyboardKeyType::KEY_F7,
		KeyboardKeyType::KEY_F8,
		KeyboardKeyType::KEY_F9,
		KeyboardKeyType::KEY_F10,
		KeyboardKeyType::KEY_F11,
		KeyboardKeyType::KEY_F12,
		KeyboardKeyType::KEY_F13,
		KeyboardKeyType::KEY_F14,
		KeyboardKeyType::KEY_F15,
		KeyboardKeyType::KEY_F16,
		KeyboardKeyType::KEY_F17,
		KeyboardKeyType::KEY_F18,
		KeyboardKeyType::KEY_F19,
		KeyboardKeyType::KEY_F20,
		KeyboardKeyType::KEY_F21,
		KeyboardKeyType::KEY_F22,
		KeyboardKeyType::KEY_F23,
		KeyboardKeyType::KEY_F24,
		KeyboardKeyType::KEY_SEMICOLON,
		KeyboardKeyType::KEY_EQUAL,
		KeyboardKeyType::KEY_COMMA,
		KeyboardKeyType::KEY_MINUS,
		KeyboardKeyType::KEY_PERIOD,
		KeyboardKeyType::KEY_FORWARDSLASH,
		KeyboardKeyType::KEY_GRAVE,
		KeyboardKeyType::KEY_LEFTBRACKET,
		KeyboardKeyType::KEY_BACKWARDSLASH,
		KeyboardKeyType::KEY_RIGHTBRACKET,
		KeyboardKeyType::KEY_QUOTE,
	};

	vector<MouseWheelType> _mouseWheelEvents = {};
	vector<MouseWheelType> _scrolledMouseWheels = {};
	vector<MouseButtonType> _mouseDownEvents = {};
	vector<MouseButtonType> _mouseUpEvents = {};
	vector<MouseButtonType> _heldMouseButtons = {};
	vector<MouseButtonType> _pressedMouseButtons = {};
	vector<MouseButtonType> _toggledMouseButtons = {};
	vector<KeyboardKeyType> _keyboardDownEvents = {};
	vector<KeyboardKeyType> _keyboardUpEvents = {};
	vector<KeyboardKeyType> _heldKeyboardKeyTypes = {};
	vector<KeyboardKeyType> _pressedKeyboardKeyTypes = {};
	vector<KeyboardKeyType> _toggledKeyboardKeyTypes = {};
};