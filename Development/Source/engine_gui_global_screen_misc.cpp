#include "engine_gui_global_screen.hpp"
#include "logger.hpp"

void EngineGuiGlobalScreen::createValueForm(const string& ID, string title, unsigned int value, Vec2 position, Vec2 size, Vec2 buttonsPosition)
{
	_createValueForm(ID, title, to_string(static_cast<int>(value)), position, size, buttonsPosition, true, false);
}

void EngineGuiGlobalScreen::createValueForm(const string& ID, string title, int value, Vec2 position, Vec2 size, Vec2 buttonsPosition)
{
	_createValueForm(ID, title, to_string(value), position, size, buttonsPosition, true, true);
}

void EngineGuiGlobalScreen::createValueForm(const string& ID, string title, float value, Vec2 position, Vec2 size, Vec2 buttonsPosition)
{
	_createValueForm(ID, title, to_string(static_cast<int>(value)), position, size, buttonsPosition, true, true);
}

void EngineGuiGlobalScreen::createValueForm(const string& ID, string title, double value, Vec2 position, Vec2 size, Vec2 buttonsPosition)
{
	_createValueForm(ID, title, to_string(static_cast<int>(value)), position, size, buttonsPosition, true, true);
}

void EngineGuiGlobalScreen::createValueForm(const string& ID, string title, string value, Vec2 position, Vec2 size, Vec2 buttonsPosition)
{
	_createValueForm(ID, title, value, position, size, buttonsPosition, false, false);
}

const bool EngineGuiGlobalScreen::checkValueForm(const string& ID, unsigned int& value, const vector<unsigned int>& forbiddenValues)
{
	// Convert from unsigned integer to string
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(forbiddenValue));
	}

	int tempValue = static_cast<int>(value); // Dereference
	string valueString = to_string(tempValue); // Convert to string
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings); // Execute function
	value = result ? static_cast<unsigned int>(stoi(valueString)) : value; // Apply to value
	return result; // Return
}

const bool EngineGuiGlobalScreen::checkValueForm(const string& ID, int& value, const vector<int>& forbiddenValues)
{
	// Convert from integer to string
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(forbiddenValue));
	}

	int tempValue = value; // Dereference
	string valueString = to_string(tempValue); // Convert to string
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings); // Execute function
	value = result ? stoi(valueString) : value; // Apply to value
	return result; // Return
}

const bool EngineGuiGlobalScreen::checkValueForm(const string& ID, float& value, const vector<float>& forbiddenValues)
{
	// Convert from float to integer to string
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(static_cast<int>(forbiddenValue)));
	}

	int tempValue = static_cast<int>(value); // Dereference
	string valueString = to_string(tempValue); // Convert to string
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings); // Execute function
	value = result ? static_cast<float>(stoi(valueString)) : value; // Apply to value
	return result; // Return
}

const bool EngineGuiGlobalScreen::checkValueForm(const string& ID, double& value, const vector<double>& forbiddenValues)
{
	// Convert from double to integer to string
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(static_cast<int>(forbiddenValue)));
	}

	int tempValue = static_cast<int>(value); // Dereference
	string valueString = to_string(tempValue); // Convert to string
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings); // Execute function
	value = result ? static_cast<double>(stoi(valueString)) : value; // Apply to value
	return result; // Return
}

const bool EngineGuiGlobalScreen::checkValueForm(const string& ID, string& value, const vector<string>& forbiddenValues)
{
	return _checkValueForm(ID, value, forbiddenValues);
}

const bool EngineGuiGlobalScreen::isValueFormConfirmed() const
{
	return (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_done")->isHovered());
}

const bool EngineGuiGlobalScreen::isValueFormCancelled() const
{
	return (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_cancel")->isHovered());
}

const bool EngineGuiGlobalScreen::isValueFormExisting(const string& ID) const
{
	return find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) != _valueFormIDs.end();
}

void EngineGuiGlobalScreen::_createValueForm(const string& ID, string title, string valueString, Vec2 position, Vec2 size, Vec2 buttonsPosition, bool onlyNumbers, bool minusAllowed)
{
	// Validate existence
	if(isValueFormExisting(ID))
	{
		Logger::throwError("EngineGuiGlobalScreen::_createValueForm");
	}

	// Create value form
	_valueFormIDs.push_back(ID);
	createRectangle(ID, position + Vec2(0.0f, 0.15f), Vec2(title.size() * 0.0275f, 0.125f), Vec3(0.0f));
	createTextField(ID, position + Vec2(0.0f, 0.15f), Vec2(title.size() * 0.025f, 0.1f), title, Vec3(1.0f), true);
	createWriteField(ID, position, size, Vec3(0.25f), Vec3(0.5f), Vec3(1.0f), Vec3(0.0f), false, onlyNumbers, onlyNumbers, onlyNumbers, (onlyNumbers && minusAllowed));
	getWriteField(ID)->changeTextContent(valueString);

	// GUI focus & set first writeField active
	if(!_isFocused)
	{
		getWriteField(ID)->setActive(true);
		_isFocused = true;
	}

	// Add done & cancel buttons
	if(!isButtonExisting("value_form_done"))
	{
		createButton("value_form_done", buttonsPosition + Vec2(-0.15f, -0.2f), Vec2(0.12f, 0.1f), Vec3(0.0f, 0.1f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), "Done", Vec3(1.0f), Vec3(0.0f));
		createButton("value_form_cancel", buttonsPosition + Vec2(0.15f, -0.2f), Vec2(0.18f, 0.1f), Vec3(0.1f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), "Cancel", Vec3(1.0f), Vec3(0.0f));
	}
}

const bool EngineGuiGlobalScreen::_checkValueForm(const string& ID, string& valueString, const vector<string>& forbiddenValueStrings)
{
	bool changed = false;

	if(find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) != _valueFormIDs.end())
	{
		bool done = _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_done")->isHovered();
		bool cancelled = _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_cancel")->isHovered();
		bool entered = getWriteField(ID)->confirmedInput();

		// Check if user confirmed or cancelled
		if(done || entered || cancelled)
		{
			if(done || entered) // Pressed done or ENTER
			{
				// Retrieve content
				auto content = getWriteField(ID)->getTextContent();

				// Check if writeField is not empty
				if(content.empty())
				{
					return false;
				}

				// Check if written content is not forbidden
				for(const auto& forbiddenValue : forbiddenValueStrings)
				{
					if(content == forbiddenValue)
					{
						return false;
					}
				}

				// Apply to value
				valueString = content;
				changed = getWriteField(ID)->hasTextContentChanged();
			}

			// Remove valueform(s)
			if(_valueFormIDs.size() == 1)
			{
				_mustDeleteValueForms = true;
			}
			else
			{
				if(done || cancelled)
				{
					_mustDeleteValueForms = true;
				}
			}
		}
	}

	return changed;
}

void EngineGuiGlobalScreen::createChoiceForm(const string& ID, string title, Vec2 position, const vector<string>& buttonTitles)
{
	// Validate existence
	if(!_choiceFormID.empty())
	{
		Logger::throwError("EngineGuiGlobalScreen::createChoiceForm::1");
	}

	// Create choice form
	createRectangle(ID, position + Vec2(0.0f, 0.475f), Vec2(title.size() * 0.0275f, 0.125f), Vec3(0.0f));
	createTextField(ID, position + Vec2(0.0f, 0.475f), Vec2(title.size() * 0.025f, 0.1f), title, Vec3(1.0f), true);
	createScrollingList(ID, position, Vec2(0.5, 0.75f), Vec3(0.25f), Vec3(0.0f, 0.1f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f), Vec3(0.0f), Vec2(0.075f, 0.2f));
	createButton("choice_form_cancel", position + Vec2(0.0f, -0.45f), Vec2(0.15f, 0.1f), Vec3(0.1f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), "Cancel", Vec3(1.0f), Vec3(0.0f));

	// Add buttons to scrolling list
	for(const auto& buttonTitle : buttonTitles)
	{
		// Validate button title
		if(buttonTitle.empty())
		{
			Logger::throwError("EngineGuiGlobalScreen::createChoiceForm::2");
		}

		// Add button
		getScrollingList(ID)->createButton(buttonTitle, buttonTitle);
	}

	// Miscellaneous
	_isFocused = true;
	_choiceFormID = ID;
}

const string& EngineGuiGlobalScreen::checkChoiceForm(const string& ID)
{
	if(ID == _choiceFormID)
	{
		for(const auto& button : getScrollingList(ID)->getButtons()) // For every button
		{
			if(button->isHovered()) // If button is hovered
			{
				return button->getID();
			}
		}
	}

	return "";
}

const bool EngineGuiGlobalScreen::isChoiceFormCancelled(const string& ID) const
{
	if(ID == _choiceFormID)
	{
		return (getButton("choice_form_cancel")->isHovered() && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT));
	}
	else
	{
		return false;
	}
}

void EngineGuiGlobalScreen::deleteChoiceForm(const string& ID)
{
	// Validate existence
	if(ID != _choiceFormID)
	{
		Logger::throwError("EngineGuiGlobalScreen::deleteChoiceForm");
	}

	// Delete choice form
	deleteRectangle(_choiceFormID);
	deleteTextField(_choiceFormID);
	deleteScrollingList(_choiceFormID);
	deleteButton("choice_form_cancel");

	// Miscellaneous
	_isFocused = false;
	_choiceFormID = "";
}

const bool EngineGuiGlobalScreen::isChoiceFormExisting(const string& ID) const
{
	return (ID == _choiceFormID);
}

void EngineGuiGlobalScreen::createAnswerForm(const string& ID, string title, Vec2 position)
{
	// Validate existence
	if(!_answerFormID.empty())
	{
		Logger::throwError("EngineGuiGlobalScreen::createAnswerForm");
	}

	// Create answer form
	createRectangle("question", position, Vec2(title.size() * 0.0275f, 0.125f), Vec3(0.0f));
	createTextField("question", position, Vec2(title.size() * 0.025f, 0.1f), title, Vec3(1.0f), true);
	createButton("answer_form_yes", position + Vec2(-0.1f, -0.2f), Vec2(0.075f, 0.1f), Vec3(0.0f, 0.1f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), "Yes", Vec3(1.0f), Vec3(0.0f));
	createButton("answer_form_no", position + Vec2(0.1f, -0.2f), Vec2(0.075f, 0.1f), Vec3(0.1f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), "No", Vec3(1.0f), Vec3(0.0f));

	// Miscellaneous
	_isFocused = true;
	_answerFormID = ID;
}

const bool EngineGuiGlobalScreen::isAnswerFormConfirmed(const string& ID)
{
	if(ID == _answerFormID)
	{
		if(getButton("answer_form_yes")->isHovered() && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_deleteAnswerForm(ID);
			return true;
		}

		return false;
	}

	return false;
}

const bool EngineGuiGlobalScreen::isAnswerFormDenied(const string& ID)
{
	if(isButtonExisting("answer_form_no") && (ID == _answerFormID))
	{
		if(getButton("answer_form_no")->isHovered() && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_deleteAnswerForm(ID);
			return true;
		}

		return false;
	}

	return false;
}

void EngineGuiGlobalScreen::_deleteAnswerForm(const string& ID)
{
	// Validate existence
	if(ID != _answerFormID)
	{
		Logger::throwError("EngineGuiGlobalScreen::_deleteAnswerForm");
	}

	// Delete answer form
	deleteRectangle("question");
	deleteTextField("question");
	deleteButton("answer_form_yes");
	deleteButton("answer_form_no");

	// Miscellaneous
	_isFocused = false;
	_answerFormID = "";
}

const bool EngineGuiGlobalScreen::isAnswerFormExisting(const string& ID) const
{
	return (ID == _answerFormID);
}

void EngineGuiGlobalScreen::_updateValueFormDeleting()
{
	if(_mustDeleteValueForms)
	{
		// Remove valueforms
		for(const auto& tempID : _valueFormIDs)
		{
			deleteRectangle(tempID);
			deleteTextField(tempID);
			deleteWriteField(tempID);
		}
		_valueFormIDs.clear();

		// Remove confirmation and cancellation buttons
		deleteButton("value_form_done");
		deleteButton("value_form_cancel");

		// Miscellaneous
		_mustDeleteValueForms = false;
		_isFocused = false;
	}
}

void EngineGuiGlobalScreen::setFocus(bool focused)
{
	_isFocused = focused;
}

const bool EngineGuiGlobalScreen::isFocused() const
{
	return _isFocused;
}