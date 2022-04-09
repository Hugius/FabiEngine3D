#pragma once

#include "input_type.hpp"

#include <vector>
#include <string>

using std::vector;

class InputHandler final
{
public:
	void update();

	const int getHorizontalMouseWheel() const;
	const int getVerticalMouseWheel() const;

	const bool isMouseButtonHeld(InputType button) const;
	const bool isMouseButtonPressed(InputType button) const;
	const bool isKeyboardKeyHeld(InputType key) const;
	const bool isKeyboardKeyPressed(InputType key) const;

private:
	static inline const vector<InputType> _mouseButtons =
	{
		InputType::MOUSE_BUTTON_LEFT,
		InputType::MOUSE_BUTTON_MIDDLE,
		InputType::MOUSE_BUTTON_RIGHT,
	};
	static inline const vector<InputType> _keyboardKeys =
	{
		InputType::KEY_BACKSPACE,
		InputType::KEY_TAB,
		InputType::KEY_ENTER,
		InputType::KEY_SHIFT,
		InputType::KEY_CONTROL,
		InputType::KEY_ALT,
		InputType::KEY_CAPSLOCK,
		InputType::KEY_ESCAPE,
		InputType::KEY_SPACEBAR,
		InputType::KEY_PAGEUP,
		InputType::KEY_PAGEDOWN,
		InputType::KEY_END,
		InputType::KEY_HOME,
		InputType::KEY_LEFT,
		InputType::KEY_UP,
		InputType::KEY_RIGHT,
		InputType::KEY_DOWN,
		InputType::KEY_INSERT,
		InputType::KEY_DELETE,
		InputType::KEY_0,
		InputType::KEY_1,
		InputType::KEY_2,
		InputType::KEY_3,
		InputType::KEY_4,
		InputType::KEY_5,
		InputType::KEY_6,
		InputType::KEY_7,
		InputType::KEY_8,
		InputType::KEY_9,
		InputType::KEY_A,
		InputType::KEY_B,
		InputType::KEY_C,
		InputType::KEY_D,
		InputType::KEY_E,
		InputType::KEY_F,
		InputType::KEY_G,
		InputType::KEY_H,
		InputType::KEY_I,
		InputType::KEY_J,
		InputType::KEY_K,
		InputType::KEY_L,
		InputType::KEY_M,
		InputType::KEY_N,
		InputType::KEY_O,
		InputType::KEY_P,
		InputType::KEY_Q,
		InputType::KEY_R,
		InputType::KEY_S,
		InputType::KEY_T,
		InputType::KEY_U,
		InputType::KEY_V,
		InputType::KEY_W,
		InputType::KEY_X,
		InputType::KEY_Y,
		InputType::KEY_Z,
		InputType::KEY_F1,
		InputType::KEY_F2,
		InputType::KEY_F3,
		InputType::KEY_F4,
		InputType::KEY_F5,
		InputType::KEY_F6,
		InputType::KEY_F7,
		InputType::KEY_F8,
		InputType::KEY_F9,
		InputType::KEY_F10,
		InputType::KEY_F11,
		InputType::KEY_F12,
		InputType::KEY_F13,
		InputType::KEY_F14,
		InputType::KEY_F15,
		InputType::KEY_F16,
		InputType::KEY_F17,
		InputType::KEY_F18,
		InputType::KEY_F19,
		InputType::KEY_F20,
		InputType::KEY_F21,
		InputType::KEY_F22,
		InputType::KEY_F23,
		InputType::KEY_F24,
		InputType::KEY_SEMICOLON,
		InputType::KEY_PLUS,
		InputType::KEY_COMMA,
		InputType::KEY_MINUS,
		InputType::KEY_PERIOD,
		InputType::KEY_FORWARDSLASH,
		InputType::KEY_GRAVE,
		InputType::KEY_LEFTBRACKET,
		InputType::KEY_BACKWARDSLASH,
		InputType::KEY_RIGHTBRACKET,
		InputType::KEY_QUOTE,
	};

	vector<InputType> _heldKeyboardKeys = {};
	vector<InputType> _heldMouseButtons = {};
	vector<InputType> _pressedKeyboardKeys = {};
	vector<InputType> _pressedMouseButtons = {};

	int _horizontalMouseWheel = 0;
	int _verticalMouseWheel = 0;
};