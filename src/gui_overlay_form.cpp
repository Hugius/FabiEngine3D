#include "gui_overlay.hpp"

void GuiOverlay::_updateForms()
{
	if(_mustCloseChoiceForm)
	{
		_closeChoiceForm();

		_mustCloseChoiceForm = false;
	}

	if(_mustCloseValueForm)
	{
		_closeValueForm();

		if(!_valueFormQueue.empty())
		{
			const auto parameters = _valueFormQueue.front();

			openValueForm(get<0>(parameters), get<1>(parameters), get<2>(parameters), get<3>(parameters), get<4>(parameters), get<5>(parameters), get<6>(parameters), get<7>(parameters));

			_valueFormQueue.erase(_valueFormQueue.begin());
		}

		_mustCloseValueForm = false;
	}

	if(_mustCloseAnswerForm)
	{
		_closeAnswerForm();

		_mustCloseAnswerForm = false;
	}

	if(!_choiceFormId.empty())
	{
		if(!getChoiceFormOptionId().empty() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
		{
			_mustCloseChoiceForm = true;
		}

		if(getButton("choice_form_cancel")->isHovered() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
		{
			_mustCloseChoiceForm = true;
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE))
		{
			_mustCloseChoiceForm = true;
		}
	}

	if(!_valueFormId.empty())
	{
		if(getButton("value_form_enter")->isHovered() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
		{
			_mustCloseValueForm = true;
		}

		if(getButton("value_form_cancel")->isHovered() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
		{
			_mustCloseValueForm = true;
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ENTER))
		{
			_mustCloseValueForm = true;
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE))
		{
			_mustCloseValueForm = true;
		}
	}

	if(!_answerFormId.empty())
	{
		if(getButton("answer_form_left")->isHovered() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
		{
			_mustCloseAnswerForm = true;
		}

		if(getButton("answer_form_cancel")->isHovered() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
		{
			_mustCloseAnswerForm = true;
		}

		if(getButton("answer_form_right")->isHovered() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
		{
			_mustCloseAnswerForm = true;
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE))
		{
			_mustCloseAnswerForm = true;
		}
	}
}

const bool GuiOverlay::isChoiceFormConfirmed() const
{
	if(_choiceFormId.empty())
	{
		abort();
	}

	if(!getScrollingList("choice_form_list")->getHoveredOptionId().empty() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
	{
		return true;
	}

	return false;
}

const bool GuiOverlay::isValueFormConfirmed() const
{
	if(_valueFormId.empty())
	{
		abort();
	}

	if(getButton("value_form_enter")->isHovered() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
	{
		return true;
	}

	if(_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ENTER))
	{
		return true;
	}

	return false;
}

const bool GuiOverlay::isAnswerFormConfirmed() const
{
	if(_answerFormId.empty())
	{
		abort();
	}

	if(getButton("answer_form_left")->isHovered() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
	{
		return true;
	}

	if(getButton("answer_form_right")->isHovered() && _fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT))
	{
		return true;
	}

	return false;
}

void GuiOverlay::openValueForm(const string & id, const string & title, const string & valueString, const fvec2 & position, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed)
{
	if(!_valueFormId.empty())
	{
		_valueFormQueue.push_back(make_tuple(id, title, valueString, position, maxCharacterCount, isLettersAllowed, isNumbersAllowed, isSpecialsAllowed));
		return;
	}

	createQuadField("value_form_title", (position + VF_TITLE_OFFSET), fvec2((title.size() * VF_TITLE_QUAD_SIZE.x), VF_TITLE_QUAD_SIZE.y), "", VF_TITLE_QUAD_COLOR, true);
	createTextField("value_form_title", (position + VF_TITLE_OFFSET), fvec2((title.size() * VF_TITLE_TEXT_SIZE.x), VF_TITLE_TEXT_SIZE.y), title, VF_TITLE_TEXT_COLOR, true);

	createInputBox("value_form_box", position, fvec2((static_cast<float>(maxCharacterCount) * VF_BOX_SIZE.x), VF_BOX_SIZE.y), VF_DEFAULT_BOX_QUAD_COLOR, VF_HOVERED_BOX_QUAD_COLOR, VF_DEFAULT_BOX_TEXT_COLOR, VF_HOVERED_BOX_TEXT_COLOR, maxCharacterCount, isLettersAllowed, isNumbersAllowed, isSpecialsAllowed, true);
	getInputBox("value_form_box")->setTextContent(valueString);
	getInputBox("value_form_box")->setActive(true);

	createButton("value_form_enter", (position + VF_ENTER_OFFSET), VF_ENTER_SIZE, "", VF_DEFAULT_ENTER_QUAD_COLOR, VF_HOVERED_ENTER_QUAD_COLOR, "Enter", VF_DEFAULT_ENTER_TEXT_COLOR, VF_HOVERED_ENTER_TEXT_COLOR, true);
	createButton("value_form_cancel", (position + VF_CANCEL_OFFSET), VF_CANCEL_SIZE, "", VF_DEFAULT_CANCEL_QUAD_COLOR, VF_HOVERED_CANCEL_QUAD_COLOR, "Cancel", VF_DEFAULT_CANCEL_TEXT_COLOR, VF_HOVERED_CANCEL_TEXT_COLOR, true);

	_valueFormId = id;

	_isFocused = true;
}

void GuiOverlay::openValueForm(const string & id, const string & title, float value, const fvec2 & position, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed)
{
	openValueForm(id, title, to_string(static_cast<int>(value)), position, maxCharacterCount, isLettersAllowed, isNumbersAllowed, isSpecialsAllowed);
}

void GuiOverlay::openValueForm(const string & id, const string & title, unsigned int value, const fvec2 & position, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed)
{
	openValueForm(id, title, to_string(value), position, maxCharacterCount, isLettersAllowed, isNumbersAllowed, isSpecialsAllowed);
}

void GuiOverlay::openValueForm(const string & id, const string & title, int value, const fvec2 & position, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed)
{
	openValueForm(id, title, to_string(value), position, maxCharacterCount, isLettersAllowed, isNumbersAllowed, isSpecialsAllowed);
}

void GuiOverlay::openChoiceForm(const string & id, const string & title, const fvec2 & position, const vector<string> & buttonTitles)
{
	if(!_choiceFormId.empty())
	{
		abort();
	}

	createQuadField("choice_form_title", (position + CF_TITLE_OFFSET), fvec2((title.size() * CF_TITLE_QUAD_SIZE.x), CF_TITLE_QUAD_SIZE.y), "", CF_TITLE_QUAD_COLOR, true);
	createTextField("choice_form_title", (position + CF_TITLE_OFFSET), fvec2((title.size() * CF_TITLE_TEXT_SIZE.x), CF_TITLE_TEXT_SIZE.y), title, CF_TITLE_TEXT_COLOR, true);

	createScrollingList("choice_form_list", position, CF_LIST_SIZE, CF_LIST_COLOR, CF_DEFAULT_OPTION_QUAD_COLOR, CF_HOVERED_OPTION_QUAD_COLOR, CF_DEFAULT_OPTION_TEXT_COLOR, CF_HOVERED_OPTION_TEXT_COLOR, CF_LIST_CHAR_SIZE, CF_SCROLLING_SPEED, true);

	for(const auto & buttonTitle : buttonTitles)
	{
		if(buttonTitle.empty())
		{
			abort();
		}

		getScrollingList("choice_form_list")->createOption(buttonTitle, buttonTitle);
	}

	createButton("choice_form_cancel", (position + CF_CANCEL_OFFSET), CF_CANCEL_SIZE, "", CF_DEFAULT_CANCEL_QUAD_COLOR, CF_HOVERED_CANCEL_QUAD_COLOR, "Cancel", CF_DEFAULT_CANCEL_TEXT_COLOR, CF_HOVERED_CANCEL_TEXT_COLOR, true);

	_choiceFormId = id;

	_isFocused = true;
}

const string GuiOverlay::getChoiceFormId() const
{
	return _choiceFormId;
}

const string GuiOverlay::getValueFormId() const
{
	return _valueFormId;
}

const string GuiOverlay::getAnswerFormId() const
{
	return _answerFormId;
}

const string GuiOverlay::getChoiceFormOptionId() const
{
	if(_choiceFormId.empty())
	{
		abort();
	}

	return getScrollingList("choice_form_list")->getHoveredOptionId();
}

const string GuiOverlay::getValueFormContent() const
{
	if(_valueFormId.empty())
	{
		abort();
	}

	return getInputBox("value_form_box")->getTextContent();
}

const string GuiOverlay::getAnswerFormDecision() const
{
	if(_answerFormId.empty())
	{
		abort();
	}

	if(getButton("answer_form_left")->isHovered())
	{
		return getButton("answer_form_left")->getTextContent();
	}

	if(getButton("answer_form_right")->isHovered())
	{
		return getButton("answer_form_right")->getTextContent();
	}

	return "";
}

void GuiOverlay::_closeChoiceForm()
{
	if(_choiceFormId.empty())
	{
		abort();
	}

	deleteQuadField("choice_form_title");
	deleteTextField("choice_form_title");
	deleteScrollingList("choice_form_list");
	deleteButton("choice_form_cancel");

	_choiceFormId = "";

	_isFocused = false;
}

void GuiOverlay::_closeValueForm()
{
	if(_valueFormId.empty())
	{
		abort();
	}

	deleteQuadField("value_form_title");
	deleteTextField("value_form_title");
	deleteInputBox("value_form_box");
	deleteButton("value_form_enter");
	deleteButton("value_form_cancel");

	_valueFormId = "";

	_isFocused = false;
}

void GuiOverlay::_closeAnswerForm()
{
	if(_answerFormId.empty())
	{
		abort();
	}

	deleteQuadField("answer_form_title");
	deleteTextField("answer_form_title");
	deleteButton("answer_form_left");
	deleteButton("answer_form_cancel");
	deleteButton("answer_form_right");

	_answerFormId = "";

	_isFocused = false;
}

void GuiOverlay::openAnswerForm(const string & id, const string & title, const string & left, const string & right, const fvec2 & position)
{
	if(!_answerFormId.empty())
	{
		abort();
	}

	const auto leftWidth = (static_cast<float>(left.size()) * AF_LEFT_CHAR_SIZE.x);
	const auto rightWidth = (static_cast<float>(right.size()) * AF_RIGHT_CHAR_SIZE.x);
	const auto maxWidth = max(leftWidth, rightWidth);

	createQuadField("answer_form_title", (position + AF_TITLE_OFFSET), fvec2((title.size() * AF_TITLE_QUAD_SIZE.x), AF_TITLE_QUAD_SIZE.y), "", AF_TITLE_QUAD_COLOR, true);
	createTextField("answer_form_title", (position + AF_TITLE_OFFSET), fvec2((title.size() * AF_TITLE_TEXT_SIZE.x), AF_TITLE_TEXT_SIZE.y), title, AF_TITLE_TEXT_COLOR, true);

	createButton("answer_form_left", (position + fvec2(-maxWidth, 0.0f)), fvec2(leftWidth, AF_LEFT_CHAR_SIZE.y), "", AF_DEFAULT_LEFT_QUAD_COLOR, AF_HOVERED_LEFT_QUAD_COLOR, left, AF_DEFAULT_LEFT_TEXT_COLOR, AF_HOVERED_LEFT_TEXT_COLOR, true);
	createButton("answer_form_cancel", (position + AF_CANCEL_OFFSET), AF_CANCEL_SIZE, "", AF_DEFAULT_CANCEL_QUAD_COLOR, AF_HOVERED_CANCEL_QUAD_COLOR, "Cancel", AF_DEFAULT_CANCEL_TEXT_COLOR, AF_HOVERED_CANCEL_TEXT_COLOR, true);
	createButton("answer_form_right", (position + fvec2(maxWidth, 0.0f)), fvec2(rightWidth, AF_RIGHT_CHAR_SIZE.y), "", AF_DEFAULT_RIGHT_QUAD_COLOR, AF_HOVERED_RIGHT_QUAD_COLOR, right, AF_DEFAULT_RIGHT_TEXT_COLOR, AF_HOVERED_RIGHT_TEXT_COLOR, true);

	_answerFormId = id;

	_isFocused = true;
}