#pragma once

#include "script_event.hpp"

enum class InputType
{
	KEYBOARD,
	MOUSE
};

enum class InputTypeMethod
{
	DOWN,
	PRESSED,
	TOGGLED
};

class ScriptEventInput final : public ScriptEvent
{
	class InputStringConverter
	{
	public:
		static InputStringConverter& getInst()
		{
			static InputStringConverter instance;
			return instance;
		}

		// Safe singleton
		InputStringConverter(InputStringConverter const&) = delete;
		void operator=(InputStringConverter const&) = delete;

		map<string, Input> getMap()
		{
			return _inputStringMap;
		}

	private:
		InputStringConverter();

		map<string, Input> _inputStringMap;
	};

public:
	ScriptEventInput(FabiEngine3D& fe3d, InputType inputType, InputTypeMethod inputTypeMethod, string inputElementName);

	bool isTriggered() override;

private:
	InputType _inputType;
	InputTypeMethod _inputTypeMethod;
	Input _inputElement;
};