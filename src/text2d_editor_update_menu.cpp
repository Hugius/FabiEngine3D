#include "text2d_editor.hpp"
#include "tools.hpp"

void Text2dEditor::_updateMainMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text2dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createText2d", "Create Text2D", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto text2dIds = _loadedText2dIds;

			for(auto & text2dId : text2dIds)
			{
				text2dId = text2dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editText2d", "Edit Text2D", LEFT_CHOICE_FORM_POSITION, text2dIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto text2dIds = _loadedText2dIds;

			for(auto & text2dId : text2dIds)
			{
				text2dId = text2dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteText2d", "Delete Text2D", LEFT_CHOICE_FORM_POSITION, text2dIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveText2dsToFile();

				unload();

				return;
			}
			else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void Text2dEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text2dEditorMenuChoice")
	{
		const auto color = _fe3d->text2d_getColor(_currentText2dId);
		const auto opacity = _fe3d->text2d_getOpacity(_currentText2dId);
		const auto lightness = _fe3d->text2d_getLightness(_currentText2dId);
		const auto isHorizontallyFlipped = _fe3d->text2d_isHorizontallyFlipped(_currentText2dId);
		const auto isVerticallyFlipped = _fe3d->text2d_isVerticallyFlipped(_currentText2dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->text2d_setVisible(_currentText2dId, false);

			_gui->getOverlay()->getTextField(TEXT2D_TITLE_ID)->setVisible(false);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuMain");

			_currentText2dId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * OPACITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * LIGHTNESS_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isHorizontallyFlipped")->isHovered())
		{
			_fe3d->text2d_setHorizontallyFlipped(_currentText2dId, !isHorizontallyFlipped);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isVerticallyFlipped")->isHovered())
		{
			_fe3d->text2d_setVerticallyFlipped(_currentText2dId, !isVerticallyFlipped);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->text2d_setColor(_currentText2dId, fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->text2d_setColor(_currentText2dId, fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->text2d_setColor(_currentText2dId, fvec3(color.r, color.g, (value / COLOR_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "opacity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->text2d_setOpacity(_currentText2dId, (value / OPACITY_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->text2d_setLightness(_currentText2dId, (value / LIGHTNESS_FACTOR));
		}

		screen->getButton("isHorizontallyFlipped")->setTextContent(isHorizontallyFlipped ? "Flipped X: ON" : "Flipped X: OFF");
		screen->getButton("isVerticallyFlipped")->setTextContent(isVerticallyFlipped ? "Flipped Y: ON" : "Flipped Y: OFF");
	}
}