#pragma once

#include "button_type.hpp"
#include "key_type.hpp"

#include <vector>

using std::vector;

class InputHandler final
{
public:
	void update();
	//void sendWheelEvent();
	void sendMouseDownEvent(ButtonType button);
	void sendMouseUpEvent(ButtonType button);
	void sendKeyboardDownEvent(KeyType key);
	void sendKeyboardUpEvent(KeyType key);

	const int getVerticalMouseWheel() const;

	const bool isMouseHeld(ButtonType button) const;
	const bool isMousePressed(ButtonType button) const;
	const bool isMouseToggled(ButtonType button) const;
	const bool isKeyboardHeld(KeyType key) const;
	const bool isKeyboardPressed(KeyType key) const;
	const bool isKeyboardToggled(KeyType key) const;

private:
	static inline const vector<ButtonType> _mouseButtons =
	{
		ButtonType::BUTTON_LEFT,
		ButtonType::BUTTON_MIDDLE,
		ButtonType::BUTTON_RIGHT,
	};
	static inline const vector<KeyType> _keyboardKeys =
	{
		KeyType::KEY_BACKSPACE,
		KeyType::KEY_TAB,
		KeyType::KEY_ENTER,
		KeyType::KEY_SHIFT,
		KeyType::KEY_CONTROL,
		KeyType::KEY_ALT,
		KeyType::KEY_CAPSLOCK,
		KeyType::KEY_ESCAPE,
		KeyType::KEY_SPACEBAR,
		KeyType::KEY_PAGEUP,
		KeyType::KEY_PAGEDOWN,
		KeyType::KEY_END,
		KeyType::KEY_HOME,
		KeyType::KEY_LEFT,
		KeyType::KEY_UP,
		KeyType::KEY_RIGHT,
		KeyType::KEY_DOWN,
		KeyType::KEY_INSERT,
		KeyType::KEY_DELETE,
		KeyType::KEY_0,
		KeyType::KEY_1,
		KeyType::KEY_2,
		KeyType::KEY_3,
		KeyType::KEY_4,
		KeyType::KEY_5,
		KeyType::KEY_6,
		KeyType::KEY_7,
		KeyType::KEY_8,
		KeyType::KEY_9,
		KeyType::KEY_A,
		KeyType::KEY_B,
		KeyType::KEY_C,
		KeyType::KEY_D,
		KeyType::KEY_E,
		KeyType::KEY_F,
		KeyType::KEY_G,
		KeyType::KEY_H,
		KeyType::KEY_I,
		KeyType::KEY_J,
		KeyType::KEY_K,
		KeyType::KEY_L,
		KeyType::KEY_M,
		KeyType::KEY_N,
		KeyType::KEY_O,
		KeyType::KEY_P,
		KeyType::KEY_Q,
		KeyType::KEY_R,
		KeyType::KEY_S,
		KeyType::KEY_T,
		KeyType::KEY_U,
		KeyType::KEY_V,
		KeyType::KEY_W,
		KeyType::KEY_X,
		KeyType::KEY_Y,
		KeyType::KEY_Z,
		KeyType::KEY_NUMPAD0,
		KeyType::KEY_NUMPAD1,
		KeyType::KEY_NUMPAD2,
		KeyType::KEY_NUMPAD3,
		KeyType::KEY_NUMPAD4,
		KeyType::KEY_NUMPAD5,
		KeyType::KEY_NUMPAD6,
		KeyType::KEY_NUMPAD7,
		KeyType::KEY_NUMPAD8,
		KeyType::KEY_NUMPAD9,
		KeyType::KEY_MULTIPLY,
		KeyType::KEY_ADD,
		KeyType::KEY_SUBTRACT,
		KeyType::KEY_DECIMAL,
		KeyType::KEY_DIVIDE,
		KeyType::KEY_F1,
		KeyType::KEY_F2,
		KeyType::KEY_F3,
		KeyType::KEY_F4,
		KeyType::KEY_F5,
		KeyType::KEY_F6,
		KeyType::KEY_F7,
		KeyType::KEY_F8,
		KeyType::KEY_F9,
		KeyType::KEY_F10,
		KeyType::KEY_F11,
		KeyType::KEY_F12,
		KeyType::KEY_F13,
		KeyType::KEY_F14,
		KeyType::KEY_F15,
		KeyType::KEY_F16,
		KeyType::KEY_F17,
		KeyType::KEY_F18,
		KeyType::KEY_F19,
		KeyType::KEY_F20,
		KeyType::KEY_F21,
		KeyType::KEY_F22,
		KeyType::KEY_F23,
		KeyType::KEY_F24,
		KeyType::KEY_SEMICOLON,
		KeyType::KEY_EQUAL,
		KeyType::KEY_COMMA,
		KeyType::KEY_MINUS,
		KeyType::KEY_PERIOD,
		KeyType::KEY_FORWARDSLASH,
		KeyType::KEY_GRAVE,
		KeyType::KEY_LEFTBRACKET,
		KeyType::KEY_BACKWARDSLASH,
		KeyType::KEY_RIGHTBRACKET,
		KeyType::KEY_QUOTE,
	};

	vector<ButtonType> _mouseDownEvents = {};
	vector<ButtonType> _mouseUpEvents = {};
	vector<ButtonType> _heldMouseButtons = {};
	vector<ButtonType> _pressedMouseButtons = {};
	vector<ButtonType> _toggledMouseButtons = {};
	vector<KeyType> _keyboardDownEvents = {};
	vector<KeyType> _keyboardUpEvents = {};
	vector<KeyType> _heldKeyboardKeys = {};
	vector<KeyType> _pressedKeyboardKeys = {};
	vector<KeyType> _toggledKeyboardKeys = {};

	int _horizontalMouseWheel = 0;
	int _verticalMouseWheel = 0;
};