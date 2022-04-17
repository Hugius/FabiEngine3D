#pragma once

#include "mouse_wheel.hpp"
#include "mouse_button.hpp"
#include "keyboard_key.hpp"

#include <vector>

using std::vector;

class InputHandler final
{
public:
	void update();
	void sendMouseWheelEvent(MouseWheel wheel);
	void sendMouseDownEvent(MouseButton button);
	void sendMouseUpEvent(MouseButton button);
	void sendKeyboardDownEvent(KeyboardKey key);
	void sendKeyboardUpEvent(KeyboardKey key);

	const bool isMouseScrolled(MouseWheel wheel) const;
	const bool isMouseHeld(MouseButton button) const;
	const bool isMousePressed(MouseButton button) const;
	const bool isMouseToggled(MouseButton button) const;
	const bool isKeyboardHeld(KeyboardKey key) const;
	const bool isKeyboardPressed(KeyboardKey key) const;
	const bool isKeyboardToggled(KeyboardKey key) const;

private:
	static inline const vector<MouseButton> _mouseButtons =
	{
		MouseButton::BUTTON_LEFT,
		MouseButton::BUTTON_MIDDLE,
		MouseButton::BUTTON_RIGHT,
	};
	static inline const vector<KeyboardKey> _keyboardKeys =
	{
		KeyboardKey::KEY_BACKSPACE,
		KeyboardKey::KEY_TAB,
		KeyboardKey::KEY_ENTER,
		KeyboardKey::KEY_SHIFT,
		KeyboardKey::KEY_CONTROL,
		KeyboardKey::KEY_ALT,
		KeyboardKey::KEY_CAPSLOCK,
		KeyboardKey::KEY_ESCAPE,
		KeyboardKey::KEY_SPACEBAR,
		KeyboardKey::KEY_PAGEUP,
		KeyboardKey::KEY_PAGEDOWN,
		KeyboardKey::KEY_END,
		KeyboardKey::KEY_HOME,
		KeyboardKey::KEY_LEFT,
		KeyboardKey::KEY_UP,
		KeyboardKey::KEY_RIGHT,
		KeyboardKey::KEY_DOWN,
		KeyboardKey::KEY_INSERT,
		KeyboardKey::KEY_DELETE,
		KeyboardKey::KEY_0,
		KeyboardKey::KEY_1,
		KeyboardKey::KEY_2,
		KeyboardKey::KEY_3,
		KeyboardKey::KEY_4,
		KeyboardKey::KEY_5,
		KeyboardKey::KEY_6,
		KeyboardKey::KEY_7,
		KeyboardKey::KEY_8,
		KeyboardKey::KEY_9,
		KeyboardKey::KEY_A,
		KeyboardKey::KEY_B,
		KeyboardKey::KEY_C,
		KeyboardKey::KEY_D,
		KeyboardKey::KEY_E,
		KeyboardKey::KEY_F,
		KeyboardKey::KEY_G,
		KeyboardKey::KEY_H,
		KeyboardKey::KEY_I,
		KeyboardKey::KEY_J,
		KeyboardKey::KEY_K,
		KeyboardKey::KEY_L,
		KeyboardKey::KEY_M,
		KeyboardKey::KEY_N,
		KeyboardKey::KEY_O,
		KeyboardKey::KEY_P,
		KeyboardKey::KEY_Q,
		KeyboardKey::KEY_R,
		KeyboardKey::KEY_S,
		KeyboardKey::KEY_T,
		KeyboardKey::KEY_U,
		KeyboardKey::KEY_V,
		KeyboardKey::KEY_W,
		KeyboardKey::KEY_X,
		KeyboardKey::KEY_Y,
		KeyboardKey::KEY_Z,
		KeyboardKey::KEY_NUMPAD0,
		KeyboardKey::KEY_NUMPAD1,
		KeyboardKey::KEY_NUMPAD2,
		KeyboardKey::KEY_NUMPAD3,
		KeyboardKey::KEY_NUMPAD4,
		KeyboardKey::KEY_NUMPAD5,
		KeyboardKey::KEY_NUMPAD6,
		KeyboardKey::KEY_NUMPAD7,
		KeyboardKey::KEY_NUMPAD8,
		KeyboardKey::KEY_NUMPAD9,
		KeyboardKey::KEY_MULTIPLY,
		KeyboardKey::KEY_ADD,
		KeyboardKey::KEY_SUBTRACT,
		KeyboardKey::KEY_DECIMAL,
		KeyboardKey::KEY_DIVIDE,
		KeyboardKey::KEY_F1,
		KeyboardKey::KEY_F2,
		KeyboardKey::KEY_F3,
		KeyboardKey::KEY_F4,
		KeyboardKey::KEY_F5,
		KeyboardKey::KEY_F6,
		KeyboardKey::KEY_F7,
		KeyboardKey::KEY_F8,
		KeyboardKey::KEY_F9,
		KeyboardKey::KEY_F10,
		KeyboardKey::KEY_F11,
		KeyboardKey::KEY_F12,
		KeyboardKey::KEY_F13,
		KeyboardKey::KEY_F14,
		KeyboardKey::KEY_F15,
		KeyboardKey::KEY_F16,
		KeyboardKey::KEY_F17,
		KeyboardKey::KEY_F18,
		KeyboardKey::KEY_F19,
		KeyboardKey::KEY_F20,
		KeyboardKey::KEY_F21,
		KeyboardKey::KEY_F22,
		KeyboardKey::KEY_F23,
		KeyboardKey::KEY_F24,
		KeyboardKey::KEY_SEMICOLON,
		KeyboardKey::KEY_EQUAL,
		KeyboardKey::KEY_COMMA,
		KeyboardKey::KEY_MINUS,
		KeyboardKey::KEY_PERIOD,
		KeyboardKey::KEY_FORWARDSLASH,
		KeyboardKey::KEY_GRAVE,
		KeyboardKey::KEY_LEFTBRACKET,
		KeyboardKey::KEY_BACKWARDSLASH,
		KeyboardKey::KEY_RIGHTBRACKET,
		KeyboardKey::KEY_QUOTE,
	};

	vector<MouseWheel> _mouseWheelEvents = {};
	vector<MouseWheel> _scrolledMouseWheels = {};
	vector<MouseButton> _mouseDownEvents = {};
	vector<MouseButton> _mouseUpEvents = {};
	vector<MouseButton> _heldMouseButtons = {};
	vector<MouseButton> _pressedMouseButtons = {};
	vector<MouseButton> _toggledMouseButtons = {};
	vector<KeyboardKey> _keyboardDownEvents = {};
	vector<KeyboardKey> _keyboardUpEvents = {};
	vector<KeyboardKey> _heldKeyboardKeys = {};
	vector<KeyboardKey> _pressedKeyboardKeys = {};
	vector<KeyboardKey> _toggledKeyboardKeys = {};
};