#include "spotlight_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

void SpotlightEditor::_updateMainMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "spotlightEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createSpotlight", "Create Spotlight", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto spotlightIds = _loadedSpotlightIds;

			for(auto & spotlightId : spotlightIds)
			{
				spotlightId = spotlightId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editSpotlight", "Edit Spotlight", fvec2(-0.5f, 0.1f), spotlightIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto spotlightIds = _loadedSpotlightIds;

			for(auto & spotlightId : spotlightIds)
			{
				spotlightId = spotlightId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteSpotlight", "Delete Spotlight", fvec2(-0.5f, 0.1f), spotlightIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveSpotlightsToFile();
				unload();

				return;
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void SpotlightEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "spotlightEditorMenuChoice")
	{
		const auto color = _fe3d->spotlight_getColor(_currentSpotlightId);
		const auto intensity = _fe3d->spotlight_getIntensity(_currentSpotlightId);
		const auto angle = _fe3d->spotlight_getAngle(_currentSpotlightId);
		const auto distance = _fe3d->spotlight_getDistance(_currentSpotlightId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->spotlight_setVisible(_currentSpotlightId, false);
			_fe3d->model_setVisible("@@spotlight", false);
			_gui->getOverlay()->getTextField("spotlightId")->setVisible(false);

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("spotlightEditorMenuMain");

			_currentSpotlightId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "R", (color.r * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "G", (color.g * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "B", (color.b * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * INTENSITY_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("angle")->isHovered())
		{
			_gui->getOverlay()->openValueForm("angle", "Angle", angle, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("distance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("distance", "Distance", (distance * DISTANCE_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->spotlight_setColor(_currentSpotlightId, fvec3((value / COLOR_MULTIPLIER), color.g, color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->spotlight_setColor(_currentSpotlightId, fvec3(color.r, (value / COLOR_MULTIPLIER), color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->spotlight_setColor(_currentSpotlightId, fvec3(color.r, color.g, (value / COLOR_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->spotlight_setIntensity(_currentSpotlightId, (value / INTENSITY_MULTIPLIER));
		}
		if((_gui->getOverlay()->getValueFormId() == "angle") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->spotlight_setAngle(_currentSpotlightId, value);
		}
		if((_gui->getOverlay()->getValueFormId() == "distance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->spotlight_setDistance(_currentSpotlightId, (value / DISTANCE_MULTIPLIER));
		}
	}
}