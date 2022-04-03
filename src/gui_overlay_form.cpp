#include "gui_overlay.hpp"

void GuiOverlay::_updateForms()
{
	if(_mustCloseChoiceForm)
	{
		closeChoiceForm();

		_mustCloseChoiceForm = false;
	}

	if(_mustCloseValueForm)
	{
		closeValueForm();

		_mustCloseValueForm = false;
	}

	if(_mustCloseAnswerForm)
	{
		closeAnswerForm();

		_mustCloseAnswerForm = false;
	}

	if(!_choiceFormId.empty())
	{
		if(!getChoiceFormOptionId().empty() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_mustCloseChoiceForm = true;
		}

		if(getButton("choice_form_cancel")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_mustCloseChoiceForm = true;
		}

		if(_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			_mustCloseChoiceForm = true;
		}
	}

	if(!_valueFormId.empty())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if(getButton("value_form_confirm")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_mustCloseValueForm = true;
			}

			if(getButton("value_form_cancel")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_mustCloseValueForm = true;
			}
		}

		if(_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			_mustCloseValueForm = true;
		}
	}

	if(!_answerFormId.empty())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if(getButton("answer_form_left")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_mustCloseValueForm = true;
			}

			if(getButton("value_form_cancel")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_mustCloseValueForm = true;
			}

			if(getButton("answer_form_right")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_mustCloseValueForm = true;
			}
		}

		if(_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE))
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

	if(!getScrollingList("choice_form_list")->getHoveredOptionId().empty() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
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

	if(getButton("value_form_confirm")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		return true;
	}

	if(getInputBox("value_form_box")->isEntered())
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

	if(getButton("answer_form_left")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		return true;
	}

	if(getButton("answer_form_right")->isHovered() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		return true;
	}

	return false;
}

void GuiOverlay::openValueForm(const string & id, const string & title, const string & valueString, const fvec2 & position, unsigned int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed)
{
	if(!_valueFormId.empty())
	{
		abort();
	}

	createQuadField("value_form_title", position + fvec2(0.0f, 0.15f), fvec2(title.size() * 0.0275f, 0.125f), "", FORM_TITLE_QUAD_COLOR, true);
	createTextField("value_form_title", position + fvec2(0.0f, 0.15f), fvec2(title.size() * 0.025f, 0.1f), title, FORM_TITLE_TEXT_COLOR, true);

	createInputBox("value_form_box", position, fvec2(static_cast<float>(maxCharacterCount) * 0.0275f, 0.1f), fvec3(0.25f), fvec3(0.5f), fvec3(1.0f), fvec3(0.0f), maxCharacterCount, isLettersAllowed, isNumbersAllowed, isSpecialsAllowed, true);
	getInputBox("value_form_box")->setTextContent(valueString);
	getInputBox("value_form_box")->setActive(true);

	createButton("value_form_confirm", position + fvec2(-0.15f, -0.2f), fvec2(0.21f, 0.1f), "", fvec3(0.0f, 0.1f, 0.0f), fvec3(0.0f, 1.0f, 0.0f), "Confirm", fvec3(1.0f), fvec3(0.0f), true);
	createButton("value_form_cancel", position + fvec2(0.15f, -0.2f), fvec2(0.18f, 0.1f), "", fvec3(0.1f, 0.0f, 0.0f), fvec3(1.0f, 0.0f, 0.0f), "Cancel", fvec3(1.0f), fvec3(0.0f), true);

	_valueFormId = id;

	_isFocused = true;
}

void GuiOverlay::openChoiceForm(const string & id, const string & title, const fvec2 & position, const vector<string> & buttonTitles)
{
	if(!_choiceFormId.empty())
	{
		abort();
	}

	createQuadField("choice_form_title", position + fvec2(0.0f, 0.475f), fvec2(title.size() * 0.0275f, 0.125f), "", FORM_TITLE_QUAD_COLOR, true);
	createTextField("choice_form_title", position + fvec2(0.0f, 0.475f), fvec2(title.size() * 0.025f, 0.1f), title, FORM_TITLE_TEXT_COLOR, true);

	createScrollingList("choice_form_list", position, fvec2(0.5, 0.75f), fvec3(0.25f), fvec3(0.0f, 0.1f, 0.0f), fvec3(0.0f, 1.0f, 0.0f), fvec3(1.0f), fvec3(0.0f), fvec2(0.1f, 0.175f), 0.25f, true);

	createButton("choice_form_cancel", position + fvec2(0.0f, -0.45f), fvec2(0.15f, 0.1f), "", fvec3(0.1f, 0.0f, 0.0f), fvec3(1.0f, 0.0f, 0.0f), "Cancel", fvec3(1.0f), fvec3(0.0f), true);

	for(const auto & buttonTitle : buttonTitles)
	{
		if(buttonTitle.empty())
		{
			abort();
		}

		getScrollingList("choice_form_list")->createOption(buttonTitle, buttonTitle);
	}

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

void GuiOverlay::closeChoiceForm()
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

void GuiOverlay::closeValueForm()
{
	if(_valueFormId.empty())
	{
		abort();
	}

	deleteQuadField("value_form_title");
	deleteTextField("value_form_title");
	deleteInputBox("value_form_box");
	deleteButton("value_form_confirm");
	deleteButton("value_form_cancel");

	_valueFormId = "";

	_isFocused = false;
}

void GuiOverlay::closeAnswerForm()
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

	createQuadField("answer_form_title", position, fvec2(title.size() * 0.0275f, 0.125f), "", FORM_TITLE_QUAD_COLOR, true);
	createTextField("answer_form_title", position, fvec2(title.size() * 0.025f, 0.1f), title, FORM_TITLE_TEXT_COLOR, true);

	createButton("answer_form_left", position + fvec2(-0.1f, -0.2f), fvec2(0.075f, 0.1f), "", fvec3(0.0f, 0.1f, 0.0f), fvec3(0.0f, 1.0f, 0.0f), left, fvec3(1.0f), fvec3(0.0f), true);
	createButton("answer_form_cancel", position + fvec2(0.0f, -0.2f), fvec2(0.075f, 0.1f), "", fvec3(0.1f, 0.0f, 0.0f), fvec3(1.0f, 0.0f, 0.0f), "Cancel", fvec3(1.0f), fvec3(0.0f), true);
	createButton("answer_form_right", position + fvec2(0.1f, -0.2f), fvec2(0.075f, 0.1f), "", fvec3(0.0f, 0.1f, 0.0f), fvec3(0.0f, 1.0f, 0.0f), right, fvec3(1.0f), fvec3(0.0f), true);

	_answerFormId = id;

	_isFocused = true;
}