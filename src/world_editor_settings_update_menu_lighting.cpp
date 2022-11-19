#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WorldEditor::_updateAmbientLightingSettingsMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsAmbient")
	{
		const auto color = _fe3d->graphics_getAmbientLightingColor();
		const auto intensity = _fe3d->graphics_getAmbientLightingIntensity();
		const auto isEnabled = _fe3d->graphics_isAmbientLightingEnabled();

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setAmbientLightingEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * INTENSITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setAmbientLightingColor(fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setAmbientLightingColor(fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setAmbientLightingColor(fvec3(color.r, color.g, (value / COLOR_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setAmbientLightingIntensity(value / INTENSITY_FACTOR);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateDirectionalLightingSettingsMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsDirectional")
	{
		const auto isEnabled = _fe3d->graphics_isDirectionalLightingEnabled();
		const auto color = _fe3d->graphics_getDirectionalLightingColor();
		const auto position = _fe3d->graphics_getDirectionalLightingPosition();
		const auto intensity = _fe3d->graphics_getDirectionalLightingIntensity();

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setDirectionalLightingEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->openValueForm("positionX", "X", position.x, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("positionY", "Y", position.y, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("positionZ", "Z", position.z, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * INTENSITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setDirectionalLightingPosition(fvec3(value, position.y, position.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setDirectionalLightingPosition(fvec3(position.x, value, position.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setDirectionalLightingPosition(fvec3(position.x, position.y, value));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setDirectionalLightingColor(fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setDirectionalLightingColor(fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setDirectionalLightingColor(fvec3(color.r, color.g, (value / COLOR_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setDirectionalLightingIntensity(value / INTENSITY_FACTOR);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateShadowsSettingsMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsShadows")
	{
		const auto isEnabled = _fe3d->graphics_isShadowsEnabled();
		const auto isFollowingCameraX = _fe3d->graphics_isShadowFollowingCameraX();
		const auto isFollowingCameraY = _fe3d->graphics_isShadowFollowingCameraY();
		const auto isFollowingCameraZ = _fe3d->graphics_isShadowFollowingCameraZ();
		const auto size = _fe3d->graphics_getShadowSize();
		const auto lightness = _fe3d->graphics_getShadowLightness();
		const auto position = _fe3d->graphics_getShadowPositionOffset();
		const auto lookat = _fe3d->graphics_getShadowLookatOffset();
		const auto interval = _fe3d->graphics_getShadowInterval();
		const auto pcfCount = _fe3d->graphics_getShadowPcfCount();
		const auto quality = _fe3d->graphics_getShadowQuality();
		const auto bias = _fe3d->graphics_getShadowBias();

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");
			_fe3d->graphics_setShadowCircleEnabled(false);

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setShadowsEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("size", "Size", size, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->openValueForm("positionX", "X", position.x, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("positionY", "Y", position.y, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("positionZ", "Z", position.z, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lookat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lookatX", "X", lookat.x, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("lookatY", "Y", lookat.y, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("lookatZ", "Z", lookat.z, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * SHADOW_LIGHTNESS_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("bias")->isHovered())
		{
			_gui->getOverlay()->openValueForm("bias", "Bias", (bias * SHADOW_BIAS_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("interval")->isHovered())
		{
			_gui->getOverlay()->openValueForm("interval", "Interval", interval, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("pcfCount")->isHovered())
		{
			_gui->getOverlay()->openValueForm("pcfCount", "PCF Count", pcfCount, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isFollowingCameraX")->isHovered())
		{
			_fe3d->graphics_setShadowFollowingCameraX(!isFollowingCameraX);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isFollowingCameraY")->isHovered())
		{
			_fe3d->graphics_setShadowFollowingCameraY(!isFollowingCameraY);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isFollowingCameraZ")->isHovered())
		{
			_fe3d->graphics_setShadowFollowingCameraZ(!isFollowingCameraZ);
		}

		if((_gui->getOverlay()->getValueFormId() == "size") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setShadowSize(value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setShadowPositionOffset(fvec3(value, position.y, position.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setShadowPositionOffset(fvec3(position.x, value, position.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setShadowPositionOffset(fvec3(position.x, position.y, value));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lookatX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setShadowLookatOffset(fvec3(value, position.y, position.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lookatY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setShadowLookatOffset(fvec3(position.x, value, position.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lookatZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setShadowLookatOffset(fvec3(position.x, position.y, value));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setShadowLightness(value / SHADOW_LIGHTNESS_FACTOR);
		}
		else if((_gui->getOverlay()->getValueFormId() == "bias") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setShadowBias(value / SHADOW_BIAS_FACTOR);
		}
		else if((_gui->getOverlay()->getValueFormId() == "interval") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->graphics_setShadowInterval(value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "pcfCount") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->graphics_setShadowPcfCount(value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "quality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->graphics_setShadowQuality(value);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("isFollowingCameraX")->setTextContent(isFollowingCameraX ? "Follow Cam X: ON" : "Follow Cam X: OFF");
		screen->getButton("isFollowingCameraY")->setTextContent(isFollowingCameraY ? "Follow Cam Y: ON" : "Follow Cam Y: OFF");
		screen->getButton("isFollowingCameraZ")->setTextContent(isFollowingCameraZ ? "Follow Cam Z: ON" : "Follow Cam Z: OFF");
	}
}

void WorldEditor::_updatePlanarReflectionsSettingsMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsPlanarReflections")
	{
		const auto height = _fe3d->graphics_getPlanarReflectionHeight();
		const auto quality = _fe3d->graphics_getPlanarReflectionQuality();

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("height")->isHovered())
		{
			_gui->getOverlay()->openValueForm("height", "Height", height, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "height") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setPlanarReflectionHeight(value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "quality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->graphics_setPlanarReflectionQuality(value);
		}
	}
}

void WorldEditor::_updatePlanarRefractionsSettingsMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsPlanarRefractions")
	{
		const auto height = _fe3d->graphics_getPlanarRefractionHeight();
		const auto quality = _fe3d->graphics_getPlanarRefractionQuality();

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettings");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("height")->isHovered())
		{
			_gui->getOverlay()->openValueForm("height", "Height", height, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "height") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->graphics_setPlanarRefractionHeight(value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "quality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->graphics_setPlanarRefractionQuality(value);
		}
	}
}