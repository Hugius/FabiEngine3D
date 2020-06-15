#include "engine_gui_global_screen.hpp"

void EngineGuiGlobalScreen::setFocus(bool focused)
{
	_isFocused = focused;
}

bool EngineGuiGlobalScreen::isFocused()
{
	return _isFocused;
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, int value, vec2 position, vec2 size)
{
	_addValueForm(ID, title, std::to_string(value), position, size, true);
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, float value, vec2 position, vec2 size)
{
	_addValueForm(ID, title, std::to_string(static_cast<int>(value)), position, size, true);
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, double value, vec2 position, vec2 size)
{
	_addValueForm(ID, title, std::to_string(static_cast<int>(value)), position, size, true);
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, string value, vec2 position, vec2 size)
{
	_addValueForm(ID, title, value, position, size, false);
}

bool EngineGuiGlobalScreen::checkValueForm(const string& ID, int& value, vector<int> forbiddenValues)
{
	// Convert from integer to string
	vector<string> forbiddenValueStrings;
	for (auto forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(std::to_string(forbiddenValue));
	}

	int tempValue = value; // Dereference
	string valueString = std::to_string(tempValue); // Convert to string
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings); // Execute function
	value = result ? std::stoi(valueString) : value; // Apply to value
	return result; // Return
}

bool EngineGuiGlobalScreen::checkValueForm(const string& ID, float& value, vector<float> forbiddenValues)
{
	// Convert from float to integer to string
	vector<string> forbiddenValueStrings;
	for (auto forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(std::to_string(static_cast<int>(forbiddenValue)));
	}

	int tempValue = static_cast<int>(value); // Dereference
	string valueString = std::to_string(tempValue); // Convert to string
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings); // Execute function
	value = result ? static_cast<float>(std::stoi(valueString)) : value; // Apply to value
	return result; // Return
}

bool EngineGuiGlobalScreen::checkValueForm(const string& ID, double& value, vector<double> forbiddenValues)
{
	// Convert from double to integer to string
	vector<string> forbiddenValueStrings;
	for (auto forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(std::to_string(static_cast<int>(forbiddenValue)));
	}

	int tempValue = static_cast<int>(value); // Dereference
	string valueString = std::to_string(tempValue); // Convert to string
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings); // Execute function
	value = result ? static_cast<double>(std::stoi(valueString)) : value; // Apply to value
	return result; // Return
}

bool EngineGuiGlobalScreen::checkValueForm(const string& ID, string& value, vector<string> forbiddenValues)
{
	return _checkValueForm(ID, value, forbiddenValues);
}

void EngineGuiGlobalScreen::_addValueForm(const string& ID, string title, string valueString, vec2 position, vec2 size, bool onlyNumbers)
{
	if (ID != "" && std::find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) == _valueFormIDs.end())
	{
		_valueFormIDs.push_back(ID);
		addTextfield(ID, position + vec2(0.0f, 0.15f), vec2(title.size() * 0.025f, 0.1f), title, vec3(1.0f));
		addWriteField(ID, position, size, vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), !onlyNumbers, onlyNumbers, onlyNumbers, onlyNumbers);
		getWriteField(ID)->setTextContent(valueString);

		// GUI focus & set first writefield active
		if (!_isFocused)
		{
			getWriteField(ID)->setActive(true);
			_isFocused = true;
		}

		// Add done & cancel buttons
		if (!checkButton("value_form_done"))
		{
			addButton("value_form_done", vec2(-0.15f, -0.2f), vec2(0.15f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));
			addButton("value_form_cancel", vec2(0.15f, -0.2f), vec2(0.15f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "Cancel", vec3(1.0f), vec3(0.0f));
		}
	}
}

bool EngineGuiGlobalScreen::_checkValueForm(const string& ID, string& valueString, vector<string> forbiddenValueStrings)
{
	bool changed = false;

	if (std::find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) != _valueFormIDs.end())
	{
		bool done = _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && getButton("value_form_done")->isHovered();
		bool cancelled = _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && getButton("value_form_cancel")->isHovered();
		bool entered = getWriteField(ID)->confirmedInput();
		bool escaped = getWriteField(ID)->cancelledInput();

		// Check if user confirmed or cancelled
		if (done || entered || cancelled || escaped)
		{
			if (done || entered) // Pressed done or ENTER
			{
				string content = getWriteField(ID)->getTextContent();

				// Check if writefield is not empty
				if (content == "")
				{
					return false;
				}

				// Check if written content is not forbidden
				for (auto& forbiddenValue : forbiddenValueStrings)
				{
					if (content == forbiddenValue)
					{
						return false;
					}
				}

				// Apply to value
				string oldValueString = valueString;
				valueString = content;
				changed = (valueString != oldValueString);
			}

			// Remove valueform(s)
			if (_valueFormIDs.size() == 1)
			{
				_removeValueForm(ID);
				deleteButton("value_form_done");
				deleteButton("value_form_cancel");
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

void EngineGuiGlobalScreen::addChoiceForm(const string& ID, string title, vec2 position, vector<string> buttonTitles)
{
	if (_choiceFormID == "")
	{
		// Add GUI elements
		addTextfield(ID, vec2(0.0f, 0.45f), vec2(0.3f, 0.1f), "Select project", vec3(1.0f));
		addScrollingList(ID, vec2(0.0f, 0.0f), vec2(0.5, 0.75f), vec3(_scrollListColor), _buttonColor, _buttonHoverColor, _textColor, _textHoverColor, vec2(0.1f, 0.25f));
		addButton("choice_form_cancel", vec2(0.0f, -0.45f), vec2(0.15f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "Cancel", vec3(1.0f), vec3(0.0f));

		// Add buttons to scrolling list
		for (auto& title : buttonTitles)
		{
			getScrollingList(ID)->addButton(title, title);
		}
		
		// Miscellaneous
		_isFocused = true;
		_choiceFormID = ID;
	}
}

string EngineGuiGlobalScreen::getClickedChoiceFormButtonID(const string& ID)
{
	if (ID == _choiceFormID)
	{
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT)) // LMB pressed
		{
			for (auto& button : getScrollingList(ID)->getButtons()) // For every button
			{
				if (button->isHovered()) // If button is clicked
				{
					string buttonID = button->getID();
					removeChoiceForm(ID);
					return buttonID;
				}
			}
		}
	}

	return "";
}

bool EngineGuiGlobalScreen::isChoiceFormCancelled(const string& ID)
{
	if (ID == _choiceFormID)
	{
		return (getButton("choice_form_cancel")->isHovered() && _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT));
	}
	else
	{
		return false;
	}
}

void EngineGuiGlobalScreen::removeChoiceForm(const string& ID)
{
	if (ID == _choiceFormID)
	{
		deleteTextfield(_choiceFormID);
		deleteScrollingList(_choiceFormID);
		deleteButton("choice_form_cancel");
		_isFocused = false;
		_choiceFormID = "";
	}
}

void EngineGuiGlobalScreen::addAnswerForm(const string& ID, string title, vec2 position)
{
	if (_answerFormID == "")
	{
		addRectangle("question", position - vec2(0.0f, 0.1f), vec2(0.03f * title.size(), 0.5f), vec3(0.25f));
		addTextfield("question", position, vec2(0.025f * title.size(), 0.1f), title, vec3(1.0f));
		addButton("answer_form_yes", position + vec2(-0.1f, -0.2f), vec2(0.075f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Yes", vec3(1.0f), vec3(0.0f));
		addButton("answer_form_no", position + vec2(0.1f, -0.2f), vec2(0.075f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "No", vec3(1.0f), vec3(0.0f));
		_isFocused = true;
		_answerFormID = ID;
	}
}

bool EngineGuiGlobalScreen::isAnswerFormConfirmed(const string& ID)
{
	if (ID == _answerFormID)
	{
		if (getButton("answer_form_yes")->isHovered() && _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			removeAnswerForm(ID);
			return true;
		}

		return false;
	}

	return false;
}

bool EngineGuiGlobalScreen::isAnswerFormCancelled(const string& ID)
{
	if (checkButton("answer_form_no") && (ID == _answerFormID))
	{
		if (getButton("answer_form_no")->isHovered() && _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
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
		deleteButton("answer_form_yes");
		deleteButton("answer_form_no");
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
		deleteButton("value_form_done");
		deleteButton("value_form_cancel");
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