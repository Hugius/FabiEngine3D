#include "gui_overlay.hpp"
#include "logger.hpp"

void GuiOverlay::createValueForm(const string& ID, string title, unsigned int value, fvec2 position, fvec2 size, fvec2 buttonsPosition)
{
	_createValueForm(ID, title, to_string(static_cast<int>(value)), position, size, buttonsPosition, true, false);
}

void GuiOverlay::createValueForm(const string& ID, string title, int value, fvec2 position, fvec2 size, fvec2 buttonsPosition)
{
	_createValueForm(ID, title, to_string(value), position, size, buttonsPosition, true, true);
}

void GuiOverlay::createValueForm(const string& ID, string title, float value, fvec2 position, fvec2 size, fvec2 buttonsPosition)
{
	_createValueForm(ID, title, to_string(static_cast<int>(value)), position, size, buttonsPosition, true, true);
}

void GuiOverlay::createValueForm(const string& ID, string title, double value, fvec2 position, fvec2 size, fvec2 buttonsPosition)
{
	_createValueForm(ID, title, to_string(static_cast<int>(value)), position, size, buttonsPosition, true, true);
}

void GuiOverlay::createValueForm(const string& ID, string title, string value, fvec2 position, fvec2 size, fvec2 buttonsPosition)
{
	_createValueForm(ID, title, value, position, size, buttonsPosition, false, false);
}

const bool GuiOverlay::checkValueForm(const string& ID, unsigned int& value, const vector<unsigned int>& forbiddenValues)
{
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(forbiddenValue));
	}

	int tempValue = static_cast<int>(value);
	string valueString = to_string(tempValue);
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings);
	value = result ? static_cast<unsigned int>(stoi(valueString)) : value;
	return result;
}

const bool GuiOverlay::checkValueForm(const string& ID, int& value, const vector<int>& forbiddenValues)
{
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(forbiddenValue));
	}

	int tempValue = value;
	string valueString = to_string(tempValue);
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings);
	value = result ? stoi(valueString) : value;
	return result;
}

const bool GuiOverlay::checkValueForm(const string& ID, float& value, const vector<float>& forbiddenValues)
{
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(static_cast<int>(forbiddenValue)));
	}

	int tempValue = static_cast<int>(value);
	string valueString = to_string(tempValue);
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings);
	value = result ? static_cast<float>(stoi(valueString)) : value;
	return result;
}

const bool GuiOverlay::checkValueForm(const string& ID, double& value, const vector<double>& forbiddenValues)
{
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(static_cast<int>(forbiddenValue)));
	}

	int tempValue = static_cast<int>(value);
	string valueString = to_string(tempValue);
	bool result = _checkValueForm(ID, valueString, forbiddenValueStrings);
	value = result ? static_cast<double>(stoi(valueString)) : value;
	return result;
}

const bool GuiOverlay::checkValueForm(const string& ID, string& value, const vector<string>& forbiddenValues)
{
	return _checkValueForm(ID, value, forbiddenValues);
}

const bool GuiOverlay::isValueFormConfirmed() const
{
	return (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_done")->isHovered());
}

const bool GuiOverlay::isValueFormCancelled() const
{
	return (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_cancel")->isHovered());
}

const bool GuiOverlay::isValueFormExisting(const string& ID) const
{
	return find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) != _valueFormIDs.end();
}

void GuiOverlay::_createValueForm(const string& ID, string title, string valueString, fvec2 position, fvec2 size, fvec2 buttonsPosition, bool onlyNumbers, bool minusAllowed)
{
	if(isValueFormExisting(ID))
	{
		Logger::throwError("GuiOverlay::_createValueForm");
	}

	_valueFormIDs.push_back(ID);
	createRectangle(ID, position + fvec2(0.0f, 0.15f), fvec2(title.size() * 0.0275f, 0.125f), fvec3(0.0f), true);
	createTextField(ID, position + fvec2(0.0f, 0.15f), fvec2(title.size() * 0.025f, 0.1f), title, fvec3(1.0f), true, false);
	createWriteField(ID, position, size, fvec3(0.25f), fvec3(0.5f), fvec3(1.0f), fvec3(0.0f), false, onlyNumbers, onlyNumbers, onlyNumbers, (onlyNumbers && minusAllowed), true);
	getWriteField(ID)->changeTextContent(valueString);

	if(!_isFocused)
	{
		getWriteField(ID)->setActive(true);
		_isFocused = true;
	}

	if(!isButtonExisting("value_form_done"))
	{
		createButton("value_form_done", buttonsPosition + fvec2(-0.15f, -0.2f), fvec2(0.12f, 0.1f), fvec3(0.0f, 0.1f, 0.0f), fvec3(0.0f, 1.0f, 0.0f), "Done", fvec3(1.0f), fvec3(0.0f), true, true, true);
		createButton("value_form_cancel", buttonsPosition + fvec2(0.15f, -0.2f), fvec2(0.18f, 0.1f), fvec3(0.1f, 0.0f, 0.0f), fvec3(1.0f, 0.0f, 0.0f), "Cancel", fvec3(1.0f), fvec3(0.0f), true, true, true);
	}
}

const bool GuiOverlay::_checkValueForm(const string& ID, string& valueString, const vector<string>& forbiddenValueStrings)
{
	bool changed = false;

	if(find(_valueFormIDs.begin(), _valueFormIDs.end(), ID) != _valueFormIDs.end())
	{
		bool done = _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_done")->isHovered();
		bool cancelled = _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_cancel")->isHovered();
		bool entered = getWriteField(ID)->confirmedInput();

		if(done || entered || cancelled)
		{
			if(done || entered)
			{
				auto content = getWriteField(ID)->getTextContent();

				if(content.empty())
				{
					return false;
				}

				for(const auto& forbiddenValue : forbiddenValueStrings)
				{
					if(content == forbiddenValue)
					{
						return false;
					}
				}

				valueString = content;
				changed = getWriteField(ID)->hasTextContentChanged();
			}

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

void GuiOverlay::createChoiceForm(const string& ID, string title, fvec2 position, const vector<string>& buttonTitles)
{
	if(!_choiceFormID.empty())
	{
		Logger::throwError("GuiOverlay::createChoiceForm::1");
	}

	createRectangle(ID, position + fvec2(0.0f, 0.475f), fvec2(title.size() * 0.0275f, 0.125f), fvec3(0.0f), true);
	createTextField(ID, position + fvec2(0.0f, 0.475f), fvec2(title.size() * 0.025f, 0.1f), title, fvec3(1.0f), true, false);
	createScrollingList(ID, position, fvec2(0.5, 0.75f), fvec3(0.25f), fvec3(0.0f, 0.1f, 0.0f), fvec3(0.0f, 1.0f, 0.0f), fvec3(1.0f), fvec3(0.0f), fvec2(0.075f, 0.2f), true);
	createButton("choice_form_cancel", position + fvec2(0.0f, -0.45f), fvec2(0.15f, 0.1f), fvec3(0.1f, 0.0f, 0.0f), fvec3(1.0f, 0.0f, 0.0f), "Cancel", fvec3(1.0f), fvec3(0.0f), true, true, true);

	for(const auto& buttonTitle : buttonTitles)
	{
		if(buttonTitle.empty())
		{
			Logger::throwError("GuiOverlay::createChoiceForm::2");
		}

		getScrollingList(ID)->createButton(buttonTitle, buttonTitle);
	}

	_isFocused = true;
	_choiceFormID = ID;
}

const string GuiOverlay::checkChoiceForm(const string& ID)
{
	if(ID == _choiceFormID)
	{
		for(const auto& button : getScrollingList(ID)->getButtons())
		{
			if(button->isHovered())
			{
				return button->getID();
			}
		}
	}

	return "";
}

const bool GuiOverlay::isChoiceFormCancelled(const string& ID) const
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

void GuiOverlay::deleteChoiceForm(const string& ID)
{
	if(ID != _choiceFormID)
	{
		Logger::throwError("GuiOverlay::deleteChoiceForm");
	}

	deleteRectangle(_choiceFormID);
	deleteTextField(_choiceFormID);
	deleteScrollingList(_choiceFormID);
	deleteButton("choice_form_cancel");

	_isFocused = false;
	_choiceFormID = "";
}

const bool GuiOverlay::isChoiceFormExisting(const string& ID) const
{
	return (ID == _choiceFormID);
}

void GuiOverlay::createAnswerForm(const string& ID, string title, fvec2 position)
{
	if(!_answerFormID.empty())
	{
		Logger::throwError("GuiOverlay::createAnswerForm");
	}

	createRectangle("question", position, fvec2(title.size() * 0.0275f, 0.125f), fvec3(0.0f), true);
	createTextField("question", position, fvec2(title.size() * 0.025f, 0.1f), title, fvec3(1.0f), true, false);
	createButton("answer_form_yes", position + fvec2(-0.1f, -0.2f), fvec2(0.075f, 0.1f), fvec3(0.0f, 0.1f, 0.0f), fvec3(0.0f, 1.0f, 0.0f), "Yes", fvec3(1.0f), fvec3(0.0f), true, true, true);
	createButton("answer_form_no", position + fvec2(0.1f, -0.2f), fvec2(0.075f, 0.1f), fvec3(0.1f, 0.0f, 0.0f), fvec3(1.0f, 0.0f, 0.0f), "No", fvec3(1.0f), fvec3(0.0f), true, true, true);

	_isFocused = true;
	_answerFormID = ID;
}

const bool GuiOverlay::isAnswerFormConfirmed(const string& ID)
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

const bool GuiOverlay::isAnswerFormDenied(const string& ID)
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

void GuiOverlay::_deleteAnswerForm(const string& ID)
{
	if(ID != _answerFormID)
	{
		Logger::throwError("GuiOverlay::_deleteAnswerForm");
	}

	deleteRectangle("question");
	deleteTextField("question");
	deleteButton("answer_form_yes");
	deleteButton("answer_form_no");

	_isFocused = false;
	_answerFormID = "";
}

const bool GuiOverlay::isAnswerFormExisting(const string& ID) const
{
	return (ID == _answerFormID);
}

void GuiOverlay::_updateValueFormDeleting()
{
	if(_mustDeleteValueForms)
	{
		for(const auto& tempID : _valueFormIDs)
		{
			deleteRectangle(tempID);
			deleteTextField(tempID);
			deleteWriteField(tempID);
		}
		_valueFormIDs.clear();

		deleteButton("value_form_done");
		deleteButton("value_form_cancel");

		_mustDeleteValueForms = false;
		_isFocused = false;
	}
}