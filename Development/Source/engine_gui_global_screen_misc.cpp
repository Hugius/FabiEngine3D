#include "engine_gui_global_screen.hpp"

void EngineGuiGlobalScreen::setFocus(bool focused)
{
	_isFocused = focused;
}

bool EngineGuiGlobalScreen::isFocused()
{
	return _isFocused;
}

void EngineGuiGlobalScreen::addValueForm(string ID, string title, float value, vec2 position)
{
	if (ID != "" && std::find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) == _valueFormIDs.end())
	{
		_valueFormIDs.push_back(ID);
		addTextfield(ID, position + vec2(0.0f, 0.15f), vec2(title.size() * 0.025f, 0.1f), title, vec3(1.0f));
		addWriteField(ID, position, vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
		getWriteField(ID)->setTextContent(std::to_string(int(value)));

		// GUI focus & set first writefield active
		if (!_isFocused)
		{
			getWriteField(ID)->setActive(true);
			_isFocused = true;
		}

		// Add done & cancel buttons
		if (!checkButton("done"))
		{
			addButton("done", vec2(-0.15f, -0.2f), vec2(0.15f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));
			addButton("cancel", vec2(0.15f, -0.2f), vec2(0.15f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "Cancel", vec3(1.0f), vec3(0.0f));
		}
	}
}


bool EngineGuiGlobalScreen::checkValueForm(string ID, float& value)
{
	bool changed = false;

	if (std::find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) != _valueFormIDs.end())
	{
		bool done = _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && getButton("done")->isHovered();
		bool cancelled = _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && getButton("cancel")->isHovered();
		bool entered = getWriteField(ID)->confirmedInput();
		bool escaped = getWriteField(ID)->cancelledInput();

		// Check if user confirmed or cancelled
		if (done || entered || cancelled || escaped)
		{
			if (done || entered) // Pressed done or ENTER
			{
				string content = getWriteField(ID)->getTextContent();

				// Check if writefield is not empty
				if (content != "")
				{
					float oldValue = value;
					value = float(std::stoi(content));
					changed = (value != oldValue);
				}
			}

			// Remove valueform(s)
			if (_valueFormIDs.size() == 1)
			{
				_removeValueForm(ID);
				deleteButton("done");
				deleteButton("cancel");
				_isFocused = false;
			}
			else
			{
				if (done || cancelled)
				{
					_exitValueFilling = true;
				}
			}
		}
	}

	return changed;
}

void EngineGuiGlobalScreen::_updateValueFilling()
{
	if (_exitValueFilling)
	{
		_exitValueFilling = false;
		_isFocused = false;

		// Remove valueforms
		for (auto& tempID : _valueFormIDs)
		{
			deleteTextfield(tempID);
			deleteWriteField(tempID);
		}
		_valueFormIDs.clear();

		// Remove confirmation and cancellation buttons
		deleteButton("done");
		deleteButton("cancel");
	}
}

void EngineGuiGlobalScreen::_removeValueForm(string ID)
{
	if (std::find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) != _valueFormIDs.end())
	{
		deleteTextfield(ID);
		deleteWriteField(ID);
		_valueFormIDs.erase(std::remove(_valueFormIDs.begin(), _valueFormIDs.end(), ID), _valueFormIDs.end());
	}
}