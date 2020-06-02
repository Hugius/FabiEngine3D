#include "engine_gui_global_screen.hpp"

void EngineGuiGlobalScreen::setFocus(bool focused)
{
	_isFocused = focused;
}

bool EngineGuiGlobalScreen::isFocused()
{
	return _isFocused;
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, int value, vec2 position)
{
	_addValueForm(ID, title, std::to_string(value), position, true);
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, float value, vec2 position)
{
	_addValueForm(ID, title, std::to_string(static_cast<int>(value)), position, true);
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, double value, vec2 position)
{
	_addValueForm(ID, title, std::to_string(static_cast<int>(value)), position, true);
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, string value, vec2 position)
{
	_addValueForm(ID, title, value, position, false);
}

bool EngineGuiGlobalScreen::checkValueForm(const string& ID, int& value)
{
	int tempValue = value; // Dereference
	string valueString = std::to_string(tempValue); // Convert to string
	bool result = _checkValueForm(ID, valueString); // Execute function
	value = std::stoi(valueString); // Apply to value
	return result; // Return
}

bool EngineGuiGlobalScreen::checkValueForm(const string& ID, float& value)
{
	int tempValue = static_cast<int>(value); // Convert type
	bool result = checkValueForm(ID, tempValue); // Execute function
	value = static_cast<float>(tempValue); // Apply to value
	return result; // Return
}

bool EngineGuiGlobalScreen::checkValueForm(const string& ID, double& value)
{
	int tempValue = static_cast<int>(value); // Convert type
	bool result = checkValueForm(ID, tempValue); // Execute function
	value = static_cast<double>(tempValue); // Apply to value
	return result; // Return
}

bool EngineGuiGlobalScreen::checkValueForm(const string& ID, string& value)
{
	return _checkValueForm(ID, value);
}

void EngineGuiGlobalScreen::_addValueForm(const string& ID, string title, string valueString, vec2 position, bool onlyNumbers)
{
	if (ID != "" && std::find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) == _valueFormIDs.end())
	{
		_valueFormIDs.push_back(ID);
		addTextfield(ID, position + vec2(0.0f, 0.15f), vec2(title.size() * 0.025f, 0.1f), title, vec3(1.0f));
		addWriteField(ID, position, vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), !onlyNumbers, onlyNumbers, onlyNumbers, onlyNumbers);
		getWriteField(ID)->setTextContent(valueString);

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

bool EngineGuiGlobalScreen::_checkValueForm(const string& ID, string& valueString)
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
					string oldValueString = valueString;
					valueString = content;
					changed = (valueString != oldValueString);
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

void EngineGuiGlobalScreen::addAnswerForm(const string& ID, string title, vec2 position)
{
	if (_answerFormID == "")
	{
		addRectangle("question", position - vec2(0.0f, 0.1f), vec2(0.03f * title.size(), 0.5f), vec3(0.25f));
		addTextfield("question", position, vec2(0.025f * title.size(), 0.1f), title, vec3(1.0f));
		addButton("yes", position + vec2(-0.1f, -0.2f), vec2(0.075f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Yes", vec3(1.0f), vec3(0.0f));
		addButton("no", position + vec2(0.1f, -0.2f), vec2(0.075f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "No", vec3(1.0f), vec3(0.0f));
		_isFocused = true;
		_answerFormID = ID;
	}
}

bool EngineGuiGlobalScreen::checkAnswerFormConfirmed(const string& ID)
{
	if (checkButton("yes") && (ID == _answerFormID))
	{
		if (getButton("yes")->isHovered() && _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			removeAnswerForm(ID);
			return true;
		}

		return false;
	}

	return false;
}

bool EngineGuiGlobalScreen::checkAnswerFormDeclined(const string& ID)
{
	if (checkButton("no") && (ID == _answerFormID))
	{
		if (getButton("no")->isHovered() && _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			removeAnswerForm(ID);
			return true;
		}

		return false;
	}

	return false;
}

void EngineGuiGlobalScreen::removeAnswerForm(const string& ID)
{
	if (ID == _answerFormID)
	{
		deleteRectangle("question");
		deleteTextfield("question");
		deleteButton("yes");
		deleteButton("no");
		_isFocused = false;
		_answerFormID = "";
	}
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