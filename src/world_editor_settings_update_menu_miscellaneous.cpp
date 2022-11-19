#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WorldEditor::_updateFogSettingsMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsFog")
	{
		const auto isEnabled = _fe3d->graphics_isFogEnabled();
		const auto minDistance = _fe3d->graphics_getFogMinDistance();
		const auto maxDistance = _fe3d->graphics_getFogMaxDistance();
		const auto thickness = _fe3d->graphics_getFogThickness();
		const auto color = _fe3d->graphics_getFogColor();

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setFogEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("minDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("minDistance", "Min Distance", minDistance, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("maxDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxDistance", "Max Distance", maxDistance, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("thickness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("thickness", "Thickness", (thickness * FOG_THICKNESS_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "minDistance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setFogMinDistance(value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "maxDistance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setFogMaxDistance(value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "thickness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setFogThickness(value / FOG_THICKNESS_FACTOR);
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setFogColor(fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setFogColor(fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setFogColor(fvec3(color.r, color.g, (value / COLOR_FACTOR)));
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateSkyExposureSettingsMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsSkyExposure")
	{
		const auto isEnabled = _fe3d->graphics_isSkyExposureEnabled();
		const auto intensity = _fe3d->graphics_getSkyExposureIntensity();
		const auto speed = _fe3d->graphics_getSkyExposureSpeed();

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setSkyExposureEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * SKY_EXPOSURE_INTENSITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("speed", "Speed", (speed * SKY_EXPOSURE_SPEED_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setSkyExposureIntensity(value / SKY_EXPOSURE_INTENSITY_FACTOR);
		}
		else if((_gui->getOverlay()->getValueFormId() == "speed") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setSkyExposureSpeed(value / SKY_EXPOSURE_SPEED_FACTOR);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}