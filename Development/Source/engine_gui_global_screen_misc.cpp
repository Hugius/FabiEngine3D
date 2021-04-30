#include "engine_gui_global_screen.hpp"

void EngineGuiGlobalScreen::setFocus(bool focused)
{
	_isFocused = focused;
}

bool EngineGuiGlobalScreen::isFocused()
{
	return _isFocused;
}

void EngineGuiGlobalScreen::setValueFormButtonsPosition(Vec2 position)
{
	_valueFormButtonsPosition = position;
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, int value, Vec2 position, Vec2 size)
{
	_addValueForm(ID, title, to_string(value), position, size, true);
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, float value, Vec2 position, Vec2 size)
{
	_addValueForm(ID, title, to_string(static_cast<int>(value)), position, size, true);
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, double value, Vec2 position, Vec2 size)
{
	_addValueForm(ID, title, to_string(static_cast<int>(value)), position, size, true);
}

void EngineGuiGlobalScreen::addValueForm(const string& ID, string title, string value, Vec2 position, Vec2 size)
{
	_addValueForm(ID, title, value, position, size, false);
}

bool EngineGuiGlobalScreen::checkValueForm(const string& ID, int& value, vector<int> forbiddenValues)
{
	// Convert from integer to string
	vector<string> forbiddenValueStrings;
	for (auto forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(forbiddenValue));
	}

	int tempValue = value; // Dereference
	string valueString = to_string(tempValue); // Convert to string
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
		forbiddenValueStrings.push_back(to_string(static_cast<int>(forbiddenValue)));
	}

	int tempValue = static_cast<int>(value); // Dereference
	string valueString = to_string(tempValue); // Convert to string
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
		forbiddenValueStrings.push_back(to_string(static_cast<int>(forbiddenValue)));
	}

	int tempValue = static_cast<int>(value); // Dereference
	string valueString = to_string(tempValue); // Convert to string
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings); // Execute function
	value = result ? static_cast<double>(std::stoi(valueString)) : value; // Apply to value
	return result; // Return
}

bool EngineGuiGlobalScreen::checkValueForm(const string& ID, string& value, vector<string> forbiddenValues)
{
	return _checkValueForm(ID, value, forbiddenValues);
}

bool EngineGuiGlobalScreen::isValueFormExisting(const string& ID)
{
	return std::find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) != _valueFormIDs.end();
}

void EngineGuiGlobalScreen::_addValueForm(const string& ID, string title, string valueString, Vec2 position, Vec2 size, bool onlyNumbers)
{
	// Check if not already exists
	if (ID != "" && std::find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) == _valueFormIDs.end())
	{
		_valueFormIDs.push_back(ID);
		addRectangle(ID, position + Vec2(0.0f, 0.15f), Vec2(title.size() * 0.0275f, 0.125f), Vec3(0.0f));
		addTextfield(ID, position + Vec2(0.0f, 0.15f), Vec2(title.size() * 0.0275f, 0.125f), title, Vec3(1.0f));
		addWritefield(ID, position, size, Vec3(0.25f), Vec3(0.5f), Vec3(1.0f), Vec3(0.0f), false, onlyNumbers, onlyNumbers, onlyNumbers, onlyNumbers);
		getWritefield(ID)->setTextContent(valueString);

		// GUI focus & set first writefield active
		if (!_isFocused)
		{
			getWritefield(ID)->setActive(true);
			_isFocused = true;
		}

		// Add done & cancel buttons
		if (!checkButton("value_form_done"))
		{
			addButton("value_form_done", _valueFormButtonsPosition + Vec2(-0.15f, -0.2f), Vec2(0.15f, 0.1f), Vec3(0.0f, 0.5f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), "Done", Vec3(1.0f), Vec3(0.0f));
			addButton("value_form_cancel", _valueFormButtonsPosition + Vec2(0.15f, -0.2f), Vec2(0.15f, 0.1f), Vec3(0.5f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), "Cancel", Vec3(1.0f), Vec3(0.0f));
		}
	}
}

bool EngineGuiGlobalScreen::_checkValueForm(const string& ID, string& valueString, vector<string> forbiddenValueStrings)
{
	bool changed = false;

	if (std::find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) != _valueFormIDs.end())
	{
		bool done = _fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_done")->isHovered();
		bool cancelled = _fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_cancel")->isHovered();
		bool entered = getWritefield(ID)->confirmedInput();

		// Check if user confirmed or cancelled
		if (done || entered || cancelled)
		{
			if (done || entered) // Pressed done or ENTER
			{
				string content = getWritefield(ID)->getTextContent();
				
				// Check if writefield is not empty
				if (content == "")
				{
					return false;
				}

				// Check if written content is not forbidden
				for (const auto& forbiddenValue : forbiddenValueStrings)
				{
					if (content == forbiddenValue)
					{
						return false;
					}
				}

				// Apply to value
				valueString = content;
				changed = getWritefield(ID)->hasTextContentChanged();
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

void EngineGuiGlobalScreen::addChoiceForm(const string& ID, string title, Vec2 position, vector<string> buttonTitles)
{
	if (_choiceFormID == "")
	{
		// Add GUI elements
		addRectangle(ID, position + Vec2(0.0f, 0.475f), Vec2(title.size() * 0.0275f, 0.125f), Vec3(0.0f));
		addTextfield(ID, position + Vec2(0.0f, 0.475f), Vec2(title.size() * 0.025f, 0.1f), title, Vec3(1.0f));
		addScrollingList(ID, position, Vec2(0.5, 0.75f), Vec3(SCROLL_LIST_COLOR), BUTTON_COLOR, BUTTON_HOVER_COLOR, TEXT_COLOR, TEXT_HOVER_COLOR, Vec2(0.1f, 0.25f));
		addButton("choice_form_cancel", position + Vec2(0.0f, -0.45f), Vec2(0.15f, 0.1f), Vec3(0.5f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), "Cancel", Vec3(1.0f), Vec3(0.0f));

		// Add buttons to scrolling list
		for (const auto& buttonTitle : buttonTitles)
		{
			getScrollingList(ID)->addButton(buttonTitle, buttonTitle.empty() ? " " : buttonTitle);
		}
		
		// Miscellaneous
		_isFocused = true;
		_choiceFormID = ID;
	}
}

string EngineGuiGlobalScreen::getSelectedChoiceFormButtonID(const string& ID)
{
	if (ID == _choiceFormID)
	{
		for (const auto& button : getScrollingList(ID)->getButtons()) // For every button
		{
			if (button->isHovered()) // If button is hovered
			{
				return button->getID();
			}
		}
	}

	return "";
}

bool EngineGuiGlobalScreen::isChoiceFormCancelled(const string& ID)
{
	if (ID == _choiceFormID)
	{
		return (getButton("choice_form_cancel")->isHovered() && _fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT));
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
		deleteRectangle(_choiceFormID);
		deleteTextfield(_choiceFormID);
		deleteScrollingList(_choiceFormID);
		deleteButton("choice_form_cancel");
		_isFocused = false;
		_choiceFormID = "";
	}
}

bool EngineGuiGlobalScreen::isChoiceFormExisting(const string& ID)
{
	return (ID == _choiceFormID);
}

void EngineGuiGlobalScreen::addAnswerForm(const string& ID, string title, Vec2 position)
{
	if (_answerFormID == "")
	{
		addRectangle("question", position - Vec2(0.0f, 0.1f), Vec2(0.03f * title.size(), 0.5f), Vec3(0.25f));
		addTextfield("question", position, Vec2(0.025f * title.size(), 0.1f), title, Vec3(1.0f));
		addButton("answer_form_yes", position + Vec2(-0.1f, -0.2f), Vec2(0.075f, 0.1f), Vec3(0.0f, 0.5f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), "Yes", Vec3(1.0f), Vec3(0.0f));
		addButton("answer_form_no", position + Vec2(0.1f, -0.2f), Vec2(0.075f, 0.1f), Vec3(0.5f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), "No", Vec3(1.0f), Vec3(0.0f));
		_isFocused = true;
		_answerFormID = ID;
	}
}

bool EngineGuiGlobalScreen::isAnswerFormConfirmed(const string& ID)
{
	if (ID == _answerFormID)
	{
		if (getButton("answer_form_yes")->isHovered() && _fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			removeAnswerForm(ID);
			return true;
		}

		return false;
	}

	return false;
}

bool EngineGuiGlobalScreen::isAnswerFormDenied(const string& ID)
{
	if (checkButton("answer_form_no") && (ID == _answerFormID))
	{
		if (getButton("answer_form_no")->isHovered() && _fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
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

bool EngineGuiGlobalScreen::isAnswerFormExisting(const string& ID)
{
	return (ID == _answerFormID);
}

void EngineGuiGlobalScreen::_updateValueFilling()
{
	if (_exitValueFilling)
	{
		_exitValueFilling = false;
		_isFocused = false;

		// Remove valueforms
		for (const auto& tempID : _valueFormIDs)
		{
			deleteRectangle(tempID);
			deleteTextfield(tempID);
			deleteWritefield(tempID);
		}
		_valueFormIDs.clear();

		// Remove confirmation and cancellation buttons
		deleteButton("value_form_done");
		deleteButton("value_form_cancel");
	}
}

void EngineGuiGlobalScreen::_removeValueForm(const string& ID)
{
	if (std::find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) != _valueFormIDs.end())
	{
		deleteRectangle(ID);
		deleteTextfield(ID);
		deleteWritefield(ID);
		_valueFormIDs.erase(std::remove(_valueFormIDs.begin(), _valueFormIDs.end(), ID), _valueFormIDs.end());
	}
}