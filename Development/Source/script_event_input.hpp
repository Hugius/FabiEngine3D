#pragma once

#include "script_event.hpp"

enum class InputEventType
{
	KEYBOARD,
	MOUSE,
	NONE
};

enum class InputEventMethod
{
	DOWN,
	PRESSED,
	TOGGLED,
	NONE
};

class ScriptEventInput final : public ScriptEvent
{
public:
	using ScriptEvent::ScriptEvent;

	void setInputType(InputEventType type);
	void setInputMethod(InputEventMethod method);
	void setInputElement(string name);
	void setInputElement(Input element);

	bool isTriggered() override;

	InputEventType getInputType();
	InputEventMethod getInputMethod();
	Input getInputElement();
	int getInputElementIndex();

private:
	InputEventType _inputType = InputEventType::NONE;
	InputEventMethod _inputMethod = InputEventMethod::NONE;
	Input _inputElement = Input::NONE;

	static inline const map<string, Input> _keyInputStringMap = 
	{
		{"KEY_A", Input::KEY_A},
		{"KEY_B", Input::KEY_B},
		{"KEY_C", Input::KEY_C},
		{"KEY_D", Input::KEY_D},
		{"KEY_E", Input::KEY_E},
		{"KEY_F", Input::KEY_F},
		{"KEY_G", Input::KEY_G},
		{"KEY_H", Input::KEY_H},
		{"KEY_I", Input::KEY_I},
		{"KEY_J", Input::KEY_J},
		{"KEY_K", Input::KEY_K},
		{"KEY_L", Input::KEY_L},
		{"KEY_M", Input::KEY_M},
		{"KEY_N", Input::KEY_N},
		{"KEY_O", Input::KEY_O},
		{"KEY_P", Input::KEY_P},
		{"KEY_Q", Input::KEY_Q},
		{"KEY_R", Input::KEY_R},
		{"KEY_S", Input::KEY_S},
		{"KEY_T", Input::KEY_T},
		{"KEY_U", Input::KEY_U},
		{"KEY_V", Input::KEY_V},
		{"KEY_W", Input::KEY_W},
		{"KEY_X", Input::KEY_X},
		{"KEY_Y", Input::KEY_Y},
		{"KEY_Z", Input::KEY_Z}
	};

	static inline const map<string, Input> _mouseInputStringMap =
	{
		{"BUTTON_LEFT", Input::MOUSE_BUTTON_LEFT},
		{"BUTTON_MIDDLE", Input::MOUSE_BUTTON_MIDDLE},
		{"BUTTON_RIGHT", Input::MOUSE_BUTTON_RIGHT},
		{"SCROLL_UP", Input::KEY_D},
		{"SCROLL_DOWN", Input::KEY_E}
	};
};