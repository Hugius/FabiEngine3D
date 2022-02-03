#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WorldEditor::_updateShadowsGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsShadows")
	{
		auto isEnabled = _fe3d->gfx_isShadowsEnabled();
		auto isFollowingCamera = _fe3d->gfx_isShadowFollowingCamera();
		auto size = _fe3d->gfx_getShadowSize();
		auto lightness = _fe3d->gfx_getShadowLightness();
		auto position = _fe3d->gfx_getShadowPositionOffset();
		auto lookat = _fe3d->gfx_getShadowLookatOffset();
		auto interval = _fe3d->gfx_getShadowInterval();
		auto quality = _fe3d->gfx_getShadowQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			_fe3d->gfx_setShadowCircleEnabled(false);
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->gfx_setShadowsEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->createValueForm("size", "Size", size, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->createValueForm("positionX", "X", position.x, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("positionY", "Y", position.y, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("positionZ", "Z", position.z, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lookat")->isHovered())
		{
			_gui->getOverlay()->createValueForm("lookatX", "X", lookat.x, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("lookatY", "Y", lookat.y, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("lookatZ", "Z", lookat.z, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFollowingCamera")->isHovered())
		{
			isFollowingCamera = !isFollowingCamera;
			_fe3d->gfx_setShadowFollowingCamera(isFollowingCamera);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->createValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("interval")->isHovered())
		{
			_gui->getOverlay()->createValueForm("interval", "Interval", interval, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->createValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("size", size))
		{
			_fe3d->gfx_setShadowSize(size);
		}
		if(_gui->getOverlay()->checkValueForm("positionX", position.x))
		{
			_fe3d->gfx_setShadowPositionOffset(position);
		}
		if(_gui->getOverlay()->checkValueForm("positionY", position.y))
		{
			_fe3d->gfx_setShadowPositionOffset(position);
		}
		if(_gui->getOverlay()->checkValueForm("positionZ", position.z))
		{
			_fe3d->gfx_setShadowPositionOffset(position);
		}
		if(_gui->getOverlay()->checkValueForm("lookatX", lookat.x))
		{
			_fe3d->gfx_setShadowLookatOffset(lookat);
		}
		if(_gui->getOverlay()->checkValueForm("lookatY", lookat.y))
		{
			_fe3d->gfx_setShadowLookatOffset(lookat);
		}
		if(_gui->getOverlay()->checkValueForm("lookatZ", lookat.z))
		{
			_fe3d->gfx_setShadowLookatOffset(lookat);
		}
		if(_gui->getOverlay()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d->gfx_setShadowLightness(lightness);
		}
		if(_gui->getOverlay()->checkValueForm("interval", interval))
		{
			_fe3d->gfx_setShadowInterval(interval);
		}
		if(_gui->getOverlay()->checkValueForm("quality", quality))
		{
			_fe3d->gfx_setShadowQuality(quality);
		}

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("isFollowingCamera")->changeTextContent(isFollowingCamera ? "Follow Cam: ON" : "Follow Cam: OFF");
	}
}

void WorldEditor::_updateReflectionsGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsReflections")
	{
		auto planarHeight = _fe3d->gfx_getPlanarReflectionHeight();
		auto cubeQuality = _fe3d->gfx_getCubeReflectionQuality();
		auto planarQuality = _fe3d->gfx_getPlanarReflectionQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarHeight")->isHovered())
		{
			_gui->getOverlay()->createValueForm("planarHeight", "Planar Height", planarHeight, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("cubeQuality")->isHovered())
		{
			_gui->getOverlay()->createValueForm("cubeQuality", "Cube Quality", cubeQuality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarQuality")->isHovered())
		{
			_gui->getOverlay()->createValueForm("planarQuality", "Planar Quality", planarQuality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("planarHeight", planarHeight))
		{
			_fe3d->gfx_setPlanarReflectionHeight(planarHeight);
		}
		if(_gui->getOverlay()->checkValueForm("cubeQuality", cubeQuality))
		{
			_fe3d->gfx_setCubeReflectionQuality(cubeQuality);
		}
		if(_gui->getOverlay()->checkValueForm("planarQuality", planarQuality))
		{
			_fe3d->gfx_setPlanarReflectionQuality(planarQuality);
		}
	}
}

void WorldEditor::_updateRefractionsGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsRefractions")
	{
		auto planarQuality = _fe3d->gfx_getPlanarRefractionQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarQuality")->isHovered())
		{
			_gui->getOverlay()->createValueForm("planarQuality", "Planar Quality", planarQuality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("planarQuality", planarQuality))
		{
			_fe3d->gfx_setPlanarRefractionQuality(planarQuality);
		}
	}
}

void WorldEditor::_updateDofGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsDof")
	{
		auto isEnabled = _fe3d->gfx_isDofEnabled();
		auto isDynamic = _fe3d->gfx_isDofDynamic();
		auto blurDistance = _fe3d->gfx_getDofBlurDistance();
		auto dynamicDistance = _fe3d->gfx_getDofDynamicDistance();
		auto quality = _fe3d->gfx_getDofQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->gfx_setDofEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isDynamic")->isHovered())
		{
			isDynamic = !isDynamic;
			_fe3d->gfx_setDofDynamic(isDynamic);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("dynamicDistance")->isHovered())
		{
			_gui->getOverlay()->createValueForm("dynamicDistance", "Dynamic Distance", dynamicDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurDistance")->isHovered())
		{
			_gui->getOverlay()->createValueForm("blurDistance", "Blur Distance", blurDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->createValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("dynamicDistance", dynamicDistance))
		{
			_fe3d->gfx_setDofDynamicDistance(dynamicDistance);
		}
		if(_gui->getOverlay()->checkValueForm("blurDistance", blurDistance))
		{
			_fe3d->gfx_setDofBlurDistance(blurDistance);
		}
		if(_gui->getOverlay()->checkValueForm("quality", quality))
		{
			_fe3d->gfx_setDofQuality(quality);
		}

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("isDynamic")->changeTextContent(isDynamic ? "Dynamic: ON" : "Dynamic: OFF");
	}
}

void WorldEditor::_updateFogGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsFog")
	{
		auto isEnabled = _fe3d->gfx_isFogEnabled();
		auto minDistance = _fe3d->gfx_getFogMinDistance();
		auto maxDistance = _fe3d->gfx_getFogMaxDistance();
		auto thickness = _fe3d->gfx_getFogThickness();
		auto color = _fe3d->gfx_getFogColor();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->gfx_setFogEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("minDistance")->isHovered())
		{
			_gui->getOverlay()->createValueForm("minDistance", "Min Distance", minDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxDistance")->isHovered())
		{
			_gui->getOverlay()->createValueForm("maxDistance", "Max Distance", maxDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("thickness")->isHovered())
		{
			_gui->getOverlay()->createValueForm("thickness", "Thickness", (thickness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->createValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("minDistance", minDistance))
		{
			_fe3d->gfx_setFogMinDistance(minDistance);
		}
		if(_gui->getOverlay()->checkValueForm("maxDistance", maxDistance))
		{
			_fe3d->gfx_setFogMaxDistance(maxDistance);
		}
		if(_gui->getOverlay()->checkValueForm("thickness", thickness))
		{
			thickness /= 100.0f;
			_fe3d->gfx_setFogThickness(thickness);
		}
		if(_gui->getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d->gfx_setFogColor(color);
		}
		if(_gui->getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d->gfx_setFogColor(color);
		}
		if(_gui->getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d->gfx_setFogColor(color);
		}

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateLensFlareGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsLensFlare")
	{
		auto isEnabled = _fe3d->gfx_isLensFlareEnabled();
		auto flareMapPath = _fe3d->gfx_getLensFlareMapPath();
		auto intensity = _fe3d->gfx_getLensFlareIntensity();
		auto sensitivity = _fe3d->gfx_getLensFlareSensitivity();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->gfx_setLensFlareEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("flareMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + getCurrentProjectId() + "\\assets\\image\\misc\\flare_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) && filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");
				return;
			}

			flareMapPath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(flareMapPath);
			_fe3d->gfx_setLensFlareMap(flareMapPath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("sensitivity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("sensitivity", "Sensitivity", (sensitivity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d->gfx_setLensFlareIntensity(intensity);
		}
		if(_gui->getOverlay()->checkValueForm("sensitivity", sensitivity))
		{
			sensitivity /= 100.0f;
			_fe3d->gfx_setLensFlareSensitivity(sensitivity);
		}

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateSkyExposureGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsSkyExposure")
	{
		auto isEnabled = _fe3d->gfx_isSkyExposureEnabled();
		auto intensity = _fe3d->gfx_getSkyExposureIntensity();
		auto speed = _fe3d->gfx_getSkyExposureSpeed();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->gfx_setSkyExposureEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui->getOverlay()->createValueForm("speed", "Speed", (speed * 10000.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d->gfx_setSkyExposureIntensity(intensity);
		}
		if(_gui->getOverlay()->checkValueForm("speed", speed))
		{
			speed /= 10000.0f;
			_fe3d->gfx_setSkyExposureSpeed(speed);
		}

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateBloomGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsBloom")
	{
		auto isEnabled = _fe3d->gfx_isBloomEnabled();
		auto type = _fe3d->gfx_getBloomType();
		auto intensity = _fe3d->gfx_getBloomIntensity();
		auto blurCount = _fe3d->gfx_getBloomBlurCount();
		auto quality = _fe3d->gfx_getBloomQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->gfx_setBloomEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("type")->isHovered())
		{
			if(type == BloomType::EVERYTHING)
			{
				type = BloomType::PARTS;
			}
			else
			{
				type = BloomType::EVERYTHING;
			}
			_fe3d->gfx_setBloomType(type);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurCount")->isHovered())
		{
			_gui->getOverlay()->createValueForm("blurCount", "Blur Count", blurCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->createValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d->gfx_setBloomIntensity(intensity);
		}
		if(_gui->getOverlay()->checkValueForm("blurCount", blurCount))
		{
			_fe3d->gfx_setBloomBlurCount(blurCount);
		}
		if(_gui->getOverlay()->checkValueForm("quality", quality))
		{
			_fe3d->gfx_setBloomQuality(quality);
		}

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("type")->changeTextContent((type == BloomType::EVERYTHING) ? "Type: EVERYTHING" : "Type: PARTS");
	}
}