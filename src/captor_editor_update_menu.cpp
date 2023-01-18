#include "captor_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

void CaptorEditor::_updateMainMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "captorEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createCaptor", "Create Captor", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto captorIds = _loadedCaptorIds;

			for(auto & captorId : captorIds)
			{
				captorId = captorId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editCaptor", "Edit Captor", CENTER_CHOICE_FORM_POSITION, captorIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto captorIds = _loadedCaptorIds;

			for(auto & captorId : captorIds)
			{
				captorId = captorId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteCaptor", "Delete Captor", CENTER_CHOICE_FORM_POSITION, captorIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveCaptorsToFile();

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

void CaptorEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "captorEditorMenuChoice")
	{
		const auto reflectionQuality = _fe3d->captor_getReflectionQuality(_currentCaptorId);
		const auto refractionQuality = _fe3d->captor_getRefractionQuality(_currentCaptorId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setVisible(false);
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("captorEditorMenuMain");

			_currentCaptorId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("reflectionQuality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("reflectionQuality", "Reflection Quality", reflectionQuality, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("refractionQuality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("refractionQuality", "Refraction Quality", refractionQuality, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "reflectionQuality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->captor_setReflectionQuality(_currentCaptorId, value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "refractionQuality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->captor_setRefractionQuality(_currentCaptorId, value);
		}
	}
}