#include "gui_overlay.hpp"
#include "logger.hpp"

void GuiOverlay::createValueForm(const string& id, const string& title, unsigned int value, const fvec2& position, const fvec2& size, const fvec2& buttonsPosition)
{
	_createValueForm(id, title, to_string(static_cast<int>(value)), position, size, buttonsPosition, true, false);
}

void GuiOverlay::createValueForm(const string& id, const string& title, int value, const fvec2& position, const fvec2& size, const fvec2& buttonsPosition)
{
	_createValueForm(id, title, to_string(value), position, size, buttonsPosition, true, true);
}

void GuiOverlay::createValueForm(const string& id, const string& title, float value, const fvec2& position, const fvec2& size, const fvec2& buttonsPosition)
{
	_createValueForm(id, title, to_string(static_cast<int>(value)), position, size, buttonsPosition, true, true);
}

void GuiOverlay::createValueForm(const string& id, const string& title, double value, const fvec2& position, const fvec2& size, const fvec2& buttonsPosition)
{
	_createValueForm(id, title, to_string(static_cast<int>(value)), position, size, buttonsPosition, true, true);
}

void GuiOverlay::createValueForm(const string& id, const string& title, const string& value, const fvec2& position, const fvec2& size, const fvec2& buttonsPosition)
{
	_createValueForm(id, title, value, position, size, buttonsPosition, false, false);
}

const bool GuiOverlay::checkValueForm(const string& id, unsigned int& value, const vector<unsigned int>& forbiddenValues)
{
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(forbiddenValue));
	}

	int tempValue = static_cast<int>(value);
	string valueString = to_string(tempValue);
	bool result = _checkValueForm(id, valueString, forbiddenValueStrings);
	value = result ? static_cast<unsigned int>(stoi(valueString)) : value;
	return result;
}

const bool GuiOverlay::checkValueForm(const string& id, int& value, const vector<int>& forbiddenValues)
{
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(forbiddenValue));
	}

	int tempValue = value;
	string valueString = to_string(tempValue);
	bool result = _checkValueForm(id, valueString, forbiddenValueStrings);
	value = result ? stoi(valueString) : value;
	return result;
}

const bool GuiOverlay::checkValueForm(const string& id, float& value, const vector<float>& forbiddenValues)
{
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(static_cast<int>(forbiddenValue)));
	}

	int tempValue = static_cast<int>(value);
	string valueString = to_string(tempValue);
	bool result = _checkValueForm(id, valueString, forbiddenValueStrings);
	value = result ? static_cast<float>(stoi(valueString)) : value;
	return result;
}

const bool GuiOverlay::checkValueForm(const string& id, double& value, const vector<double>& forbiddenValues)
{
	vector<string> forbiddenValueStrings;
	for(const auto& forbiddenValue : forbiddenValues)
	{
		forbiddenValueStrings.push_back(to_string(static_cast<int>(forbiddenValue)));
	}

	int tempValue = static_cast<int>(value);
	string valueString = to_string(tempValue);
	bool result = _checkValueForm(id, valueString, forbiddenValueStrings);
	value = result ? static_cast<double>(stoi(valueString)) : value;
	return result;
}

const bool GuiOverlay::checkValueForm(const string& id, string& value, const vector<string>& forbiddenValues)
{
	return _checkValueForm(id, value, forbiddenValues);
}

const bool GuiOverlay::isValueFormConfirmed() const
{
	return (_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_done")->isHovered());
}

const bool GuiOverlay::isValueFormCancelled() const
{
	return (_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_cancel")->isHovered());
}

const bool GuiOverlay::isValueFormExisting(const string& id) const
{
	return find(_valueFormIds.begin(), _valueFormIds.end(), id) != _valueFormIds.end();
}

void GuiOverlay::_createValueForm(const string& id, const string& title, const string& valueString, const fvec2& position, const fvec2& size, const fvec2& buttonsPosition, bool onlyNumbers, bool minusAllowed)
{
	if(isValueFormExisting(id))
	{
		Logger::throwError("GuiOverlay::_createValueForm");
	}

	_valueFormIds.push_back(id);
	createRectangle(id, position + fvec2(0.0f, 0.15f), fvec2(title.size() * 0.0275f, 0.125f), FORM_TITLE_RECT_COLOR, true);
	createTextField(id, position + fvec2(0.0f, 0.15f), fvec2(title.size() * 0.025f, 0.1f), title, FORM_TITLE_TEXT_COLOR, true);
	createWriteField(id, position, size, fvec3(0.25f), fvec3(0.5f), fvec3(1.0f), fvec3(0.0f), false, onlyNumbers, onlyNumbers, onlyNumbers, (onlyNumbers && minusAllowed), true);
	getWriteField(id)->changeTextContent(valueString);

	if(!_isFocused)
	{
		getWriteField(id)->setActive(true);
		_isFocused = true;
	}

	if(!isButtonExisting("value_form_done"))
	{
		createButton("value_form_done", buttonsPosition + fvec2(-0.15f, -0.2f), fvec2(0.12f, 0.1f), fvec3(0.0f, 0.1f, 0.0f), fvec3(0.0f, 1.0f, 0.0f), "Done", fvec3(1.0f), fvec3(0.0f), true);
		createButton("value_form_cancel", buttonsPosition + fvec2(0.15f, -0.2f), fvec2(0.18f, 0.1f), fvec3(0.1f, 0.0f, 0.0f), fvec3(1.0f, 0.0f, 0.0f), "Cancel", fvec3(1.0f), fvec3(0.0f), true);
	}
}

const bool GuiOverlay::_checkValueForm(const string& id, string& valueString, const vector<string>& forbiddenValueStrings)
{
	bool changed = false;

	if(find(_valueFormIds.begin(), _valueFormIds.end(), id) != _valueFormIds.end())
	{
		bool done = _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_done")->isHovered();
		bool cancelled = _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && getButton("value_form_cancel")->isHovered();
		bool entered = getWriteField(id)->confirmedInput();

		if(done || entered || cancelled)
		{
			if(done || entered)
			{
				auto content = getWriteField(id)->getTextContent();

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
				changed = getWriteField(id)->hasTextContentChanged();
			}

			if(_valueFormIds.size() == 1)
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

void GuiOverlay::createChoiceForm(const string& id, const string& title, const fvec2& position, const vector<string>& buttonTitles)
{
	if(!_choiceFormID.empty())
	{
		Logger::throwError("GuiOverlay::createChoiceForm::1");
	}

	createRectangle(id, position + fvec2(0.0f, 0.475f), fvec2(title.size() * 0.0275f, 0.125f), FORM_TITLE_RECT_COLOR, true);
	createTextField(id, position + fvec2(0.0f, 0.475f), fvec2(title.size() * 0.025f, 0.1f), title, FORM_TITLE_TEXT_COLOR, true);
	createScrollingList(id, position, fvec2(0.5, 0.75f), fvec3(0.25f), fvec3(0.0f, 0.1f, 0.0f), fvec3(0.0f, 1.0f, 0.0f), fvec3(1.0f), fvec3(0.0f), fvec2(0.075f, 0.2f), true);
	createButton("choice_form_cancel", position + fvec2(0.0f, -0.45f), fvec2(0.15f, 0.1f), fvec3(0.1f, 0.0f, 0.0f), fvec3(1.0f, 0.0f, 0.0f), "Cancel", fvec3(1.0f), fvec3(0.0f), true);

	for(const auto& buttonTitle : buttonTitles)
	{
		if(buttonTitle.empty())
		{
			Logger::throwError("GuiOverlay::createChoiceForm::2");
		}

		getScrollingList(id)->createButton(buttonTitle, buttonTitle);
	}

	_isFocused = true;
	_choiceFormID = id;
}

const string GuiOverlay::checkChoiceForm(const string& id)
{
	if(id == _choiceFormID)
	{
		for(const auto& button : getScrollingList(id)->getButtons())
		{
			if(button->isHovered())
			{
				return button->getId();
			}
		}
	}

	return "";
}

const bool GuiOverlay::isChoiceFormCancelled(const string& id) const
{
	if(id == _choiceFormID)
	{
		return (getButton("choice_form_cancel")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT));
	}
	else
	{
		return false;
	}
}

void GuiOverlay::deleteChoiceForm(const string& id)
{
	if(id != _choiceFormID)
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

const bool GuiOverlay::isChoiceFormExisting(const string& id) const
{
	return (id == _choiceFormID);
}

void GuiOverlay::createAnswerForm(const string& id, const string& title, const fvec2& position)
{
	if(!_answerFormID.empty())
	{
		Logger::throwError("GuiOverlay::createAnswerForm");
	}

	createRectangle("question", position, fvec2(title.size() * 0.0275f, 0.125f), FORM_TITLE_RECT_COLOR, true);
	createTextField("question", position, fvec2(title.size() * 0.025f, 0.1f), title, FORM_TITLE_TEXT_COLOR, true);
	createButton("answer_form_yes", position + fvec2(-0.1f, -0.2f), fvec2(0.075f, 0.1f), fvec3(0.0f, 0.1f, 0.0f), fvec3(0.0f, 1.0f, 0.0f), "Yes", fvec3(1.0f), fvec3(0.0f), true);
	createButton("answer_form_no", position + fvec2(0.1f, -0.2f), fvec2(0.075f, 0.1f), fvec3(0.1f, 0.0f, 0.0f), fvec3(1.0f, 0.0f, 0.0f), "No", fvec3(1.0f), fvec3(0.0f), true);

	_isFocused = true;
	_answerFormID = id;
}

const bool GuiOverlay::isAnswerFormConfirmed(const string& id)
{
	if(id == _answerFormID)
	{
		if(getButton("answer_form_yes")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_deleteAnswerForm(id);
			return true;
		}

		return false;
	}

	return false;
}

const bool GuiOverlay::isAnswerFormDenied(const string& id)
{
	if(isButtonExisting("answer_form_no") && (id == _answerFormID))
	{
		if(getButton("answer_form_no")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_deleteAnswerForm(id);
			return true;
		}

		return false;
	}

	return false;
}

void GuiOverlay::_deleteAnswerForm(const string& id)
{
	if(id != _answerFormID)
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

const bool GuiOverlay::isAnswerFormExisting(const string& id) const
{
	return (id == _answerFormID);
}

void GuiOverlay::_updateValueFormDeleting()
{
	if(_mustDeleteValueForms)
	{
		for(const auto& tempID : _valueFormIds)
		{
			deleteRectangle(tempID);
			deleteTextField(tempID);
			deleteWriteField(tempID);
		}
		_valueFormIds.clear();

		deleteButton("value_form_done");
		deleteButton("value_form_cancel");

		_mustDeleteValueForms = false;
		_isFocused = false;
	}
}