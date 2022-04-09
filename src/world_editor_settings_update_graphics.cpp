#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WorldEditor::_updateShadowsGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsShadows")
	{
		const auto isEnabled = _fe3d->graphics_isShadowsEnabled();
		const auto isFollowingCamera = _fe3d->graphics_isShadowFollowingCamera();
		const auto size = _fe3d->graphics_getShadowSize();
		const auto lightness = _fe3d->graphics_getShadowLightness();
		const auto position = _fe3d->graphics_getShadowPositionOffset();
		const auto lookat = _fe3d->graphics_getShadowLookatOffset();
		const auto interval = _fe3d->graphics_getShadowInterval();
		const auto quality = _fe3d->graphics_getShadowQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			_fe3d->graphics_setShadowCircleEnabled(false);
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setShadowsEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("size", "Size", size, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->openValueForm("positionX", "X", position.x, fvec2(-0.25f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("positionY", "Y", position.y, fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("positionZ", "Z", position.z, fvec2(0.25f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lookat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lookatX", "X", lookat.x, fvec2(-0.25f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("lookatY", "Y", lookat.y, fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("lookatZ", "Z", lookat.z, fvec2(0.25f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFollowingCamera")->isHovered())
		{
			_fe3d->graphics_setShadowFollowingCamera(!isFollowingCamera);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("interval")->isHovered())
		{
			_gui->getOverlay()->openValueForm("interval", "Interval", interval, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "size") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setShadowSize(content);
		}
		if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setShadowPositionOffset(fvec3((content / COLOR_MULTIPLIER), position.y, position.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setShadowPositionOffset(fvec3(position.x, (content / COLOR_MULTIPLIER), position.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setShadowPositionOffset(fvec3(position.x, position.y, (content / COLOR_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "lookatX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setShadowLookatOffset(fvec3((content / COLOR_MULTIPLIER), position.y, position.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "lookatY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setShadowLookatOffset(fvec3(position.x, (content / COLOR_MULTIPLIER), position.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "lookatZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setShadowLookatOffset(fvec3(position.x, position.y, (content / COLOR_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setShadowLightness(content / 100.0f);
		}
		if((_gui->getOverlay()->getValueFormId() == "interval") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseUnsignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->graphics_setShadowInterval(content);
		}
		if((_gui->getOverlay()->getValueFormId() == "quality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseUnsignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->graphics_setShadowQuality(content);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("isFollowingCamera")->setTextContent(isFollowingCamera ? "Follow Cam: ON" : "Follow Cam: OFF");
	}
}

void WorldEditor::_updateReflectionsGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsReflections")
	{
		const auto planarHeight = _fe3d->graphics_getPlanarReflectionHeight();
		const auto cubeQuality = _fe3d->graphics_getCubeReflectionQuality();
		const auto planarQuality = _fe3d->graphics_getPlanarReflectionQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarHeight")->isHovered())
		{
			_gui->getOverlay()->openValueForm("planarHeight", "Planar Height", planarHeight, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("cubeQuality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("cubeQuality", "Cube Quality", cubeQuality, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarQuality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("planarQuality", "Planar Quality", planarQuality, fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "planarHeight") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setPlanarReflectionHeight(content);
		}
		if((_gui->getOverlay()->getValueFormId() == "cubeQuality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseUnsignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->graphics_setCubeReflectionQuality(content);
		}
		if((_gui->getOverlay()->getValueFormId() == "planarQuality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseUnsignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->graphics_setPlanarReflectionQuality(content);
		}
	}
}

void WorldEditor::_updateRefractionsGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsRefractions")
	{
		const auto planarQuality = _fe3d->graphics_getPlanarRefractionQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarQuality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("planarQuality", "Planar Quality", planarQuality, fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "planarQuality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseUnsignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->graphics_setPlanarRefractionQuality(content);
		}
	}
}

void WorldEditor::_updateDofGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsDof")
	{
		const auto isEnabled = _fe3d->graphics_isDofEnabled();
		const auto isDynamic = _fe3d->graphics_isDofDynamic();
		const auto blurDistance = _fe3d->graphics_getDofBlurDistance();
		const auto dynamicDistance = _fe3d->graphics_getDofDynamicDistance();
		const auto quality = _fe3d->graphics_getDofQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setDofEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isDynamic")->isHovered())
		{
			_fe3d->graphics_setDofDynamic(!isDynamic);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("dynamicDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("dynamicDistance", "Dynamic Distance", dynamicDistance, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("blurDistance", "Blur Distance", blurDistance, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "dynamicDistance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setDofDynamicDistance(content);
		}
		if((_gui->getOverlay()->getValueFormId() == "blurDistance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setDofBlurDistance(content);
		}
		if((_gui->getOverlay()->getValueFormId() == "quality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseUnsignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->graphics_setDofQuality(content);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("isDynamic")->setTextContent(isDynamic ? "Dynamic: ON" : "Dynamic: OFF");
	}
}

void WorldEditor::_updateFogGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsFog")
	{
		const auto isEnabled = _fe3d->graphics_isFogEnabled();
		const auto minDistance = _fe3d->graphics_getFogMinDistance();
		const auto maxDistance = _fe3d->graphics_getFogMaxDistance();
		const auto thickness = _fe3d->graphics_getFogThickness();
		const auto color = _fe3d->graphics_getFogColor();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setFogEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("minDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("minDistance", "Min Distance", minDistance, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxDistance", "Max Distance", maxDistance, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("thickness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("thickness", "Thickness", (thickness * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "R", (color.r * COLOR_MULTIPLIER), fvec2(-0.25f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "G", (color.g * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "B", (color.b * COLOR_MULTIPLIER), fvec2(0.25f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "minDistance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setFogMinDistance(content);
		}
		if((_gui->getOverlay()->getValueFormId() == "maxDistance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setFogMaxDistance(content);
		}
		if((_gui->getOverlay()->getValueFormId() == "thickness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setFogThickness(content / 100.0f);
		}
		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setFogColor(fvec3((content / COLOR_MULTIPLIER), color.g, color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setFogColor(fvec3(color.r, (content / COLOR_MULTIPLIER), color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setFogColor(fvec3(color.r, color.g, (content / COLOR_MULTIPLIER)));
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateLensFlareGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsLensFlare")
	{
		const auto isEnabled = _fe3d->graphics_isLensFlareEnabled();
		const auto flareMapPath = _fe3d->graphics_getLensFlareMapPath();
		const auto intensity = _fe3d->graphics_getLensFlareIntensity();
		const auto sensitivity = _fe3d->graphics_getLensFlareSensitivity();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setLensFlareEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("flareMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\misc\\flare_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");
				return;
			}

			_fe3d->misc_clearImageCache(filePath.substr(rootPath.size()));
			_fe3d->graphics_setLensFlareMap(filePath.substr(rootPath.size()));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("sensitivity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sensitivity", "Sensitivity", (sensitivity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setLensFlareIntensity(content / 100.0f);
		}
		if((_gui->getOverlay()->getValueFormId() == "sensitivity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setLensFlareSensitivity(content / 100.0f);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateSkyExposureGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsSkyExposure")
	{
		const auto isEnabled = _fe3d->graphics_isSkyExposureEnabled();
		const auto intensity = _fe3d->graphics_getSkyExposureIntensity();
		const auto speed = _fe3d->graphics_getSkyExposureSpeed();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setSkyExposureEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("speed", "Speed", (speed * 10000.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setSkyExposureIntensity(content / 100.0f);
		}
		if((_gui->getOverlay()->getValueFormId() == "speed") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setSkyExposureSpeed(content / 100.0f);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateBloomGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsBloom")
	{
		const auto isEnabled = _fe3d->graphics_isBloomEnabled();
		const auto type = _fe3d->graphics_getBloomType();
		const auto intensity = _fe3d->graphics_getBloomIntensity();
		const auto blurCount = _fe3d->graphics_getBloomBlurCount();
		const auto quality = _fe3d->graphics_getBloomQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			_fe3d->graphics_setBloomEnabled(!isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("type")->isHovered())
		{
			if(type == BloomType::EVERYTHING)
			{
				_fe3d->graphics_setBloomType(BloomType::PARTS);
			}
			else
			{
				_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurCount")->isHovered())
		{
			_gui->getOverlay()->openValueForm("blurCount", "Blur Count", blurCount, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->graphics_setBloomIntensity(content / 100.0f);
		}
		if((_gui->getOverlay()->getValueFormId() == "blurCount") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseUnsignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->graphics_setBloomBlurCount(content);
		}
		if((_gui->getOverlay()->getValueFormId() == "quality") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseUnsignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->graphics_setBloomQuality(content);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("type")->setTextContent((type == BloomType::EVERYTHING) ? "Type: EVERYTHING" : "Type: PARTS");
	}
}