#include "captor_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

void CaptorEditor::_updateMainMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "captorEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createCaptor", "Create CAPTOR", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto captorIds = _loadedCaptorIds;

			for(auto & captorId : captorIds)
			{
				captorId = captorId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editCaptor", "Edit CAPTOR", RIGHT_CHOICE_FORM_POSITION, captorIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto captorIds = _loadedCaptorIds;

			for(auto & captorId : captorIds)
			{
				captorId = captorId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteCaptor", "Delete CAPTOR", RIGHT_CHOICE_FORM_POSITION, captorIds);
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
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "captorEditorMenuChoice")
	{
		const auto size = _fe3d->captor_getBaseSize(_currentCaptorId);
		const auto color = _fe3d->captor_getColor(_currentCaptorId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->captor_setVisible(_currentCaptorId, false);

			_gui->getOverlay()->getTextField(CAPTOR_TITLE_ID)->setVisible(false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("captorEditorMenuMain");

			_currentCaptorId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sizeX", "X", (size.x * SIZE_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("sizeY", "Y", (size.y * SIZE_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("sizeZ", "Z", (size.z * SIZE_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "R", (color.r * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "G", (color.g * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "B", (color.b * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "sizeX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->captor_setBaseSize(_currentCaptorId, fvec3((value / SIZE_FACTOR), size.y, size.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "sizeY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->captor_setBaseSize(_currentCaptorId, fvec3(size.x, (value / SIZE_FACTOR), size.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "sizeZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->captor_setBaseSize(_currentCaptorId, fvec3(size.x, size.y, (value / SIZE_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->captor_setColor(_currentCaptorId, fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->captor_setColor(_currentCaptorId, fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->captor_setColor(_currentCaptorId, fvec3(color.r, color.g, (value / COLOR_FACTOR)));
		}
	}
}