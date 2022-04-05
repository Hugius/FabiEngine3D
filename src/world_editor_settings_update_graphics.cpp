#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WorldEditor::_updateShadowsGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsShadows")
	{
		auto isEnabled = _fe3d->graphics_isShadowsEnabled();
		auto isFollowingCamera = _fe3d->graphics_isShadowFollowingCamera();
		auto size = _fe3d->graphics_getShadowSize();
		auto lightness = _fe3d->graphics_getShadowLightness();
		auto position = _fe3d->graphics_getShadowPositionOffset();
		auto lookat = _fe3d->graphics_getShadowLookatOffset();
		auto interval = _fe3d->graphics_getShadowInterval();
		auto quality = _fe3d->graphics_getShadowQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			_fe3d->graphics_setShadowCircleEnabled(false);
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->graphics_setShadowsEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("size", "Size", size, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->openValueForm("positionX", "X", position.x, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("positionY", "Y", position.y, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("positionZ", "Z", position.z, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lookat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lookatX", "X", lookat.x, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("lookatY", "Y", lookat.y, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("lookatZ", "Z", lookat.z, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFollowingCamera")->isHovered())
		{
			isFollowingCamera = !isFollowingCamera;
			_fe3d->graphics_setShadowFollowingCamera(isFollowingCamera);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("interval")->isHovered())
		{
			_gui->getOverlay()->openValueForm("interval", "Interval", interval, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("size", size))
		{
			_fe3d->graphics_setShadowSize(size);
		}
		//if(_gui->getOverlay()->checkValueForm("positionX", position.x))
		{
			_fe3d->graphics_setShadowPositionOffset(position);
		}
		//if(_gui->getOverlay()->checkValueForm("positionY", position.y))
		{
			_fe3d->graphics_setShadowPositionOffset(position);
		}
		//if(_gui->getOverlay()->checkValueForm("positionZ", position.z))
		{
			_fe3d->graphics_setShadowPositionOffset(position);
		}
		//if(_gui->getOverlay()->checkValueForm("lookatX", lookat.x))
		{
			_fe3d->graphics_setShadowLookatOffset(lookat);
		}
		//if(_gui->getOverlay()->checkValueForm("lookatY", lookat.y))
		{
			_fe3d->graphics_setShadowLookatOffset(lookat);
		}
		//if(_gui->getOverlay()->checkValueForm("lookatZ", lookat.z))
		{
			_fe3d->graphics_setShadowLookatOffset(lookat);
		}
		//if(_gui->getOverlay()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d->graphics_setShadowLightness(lightness);
		}
		//if(_gui->getOverlay()->checkValueForm("interval", interval))
		{
			_fe3d->graphics_setShadowInterval(interval);
		}
		//if(_gui->getOverlay()->checkValueForm("quality", quality))
		{
			_fe3d->graphics_setShadowQuality(quality);
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
		auto planarHeight = _fe3d->graphics_getPlanarReflectionHeight();
		auto cubeQuality = _fe3d->graphics_getCubeReflectionQuality();
		auto planarQuality = _fe3d->graphics_getPlanarReflectionQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarHeight")->isHovered())
		{
			_gui->getOverlay()->openValueForm("planarHeight", "Planar Height", planarHeight, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("cubeQuality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("cubeQuality", "Cube Quality", cubeQuality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarQuality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("planarQuality", "Planar Quality", planarQuality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("planarHeight", planarHeight))
		{
			_fe3d->graphics_setPlanarReflectionHeight(planarHeight);
		}
		//if(_gui->getOverlay()->checkValueForm("cubeQuality", cubeQuality))
		{
			_fe3d->graphics_setCubeReflectionQuality(cubeQuality);
		}
		//if(_gui->getOverlay()->checkValueForm("planarQuality", planarQuality))
		{
			_fe3d->graphics_setPlanarReflectionQuality(planarQuality);
		}
	}
}

void WorldEditor::_updateRefractionsGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsRefractions")
	{
		auto planarQuality = _fe3d->graphics_getPlanarRefractionQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarQuality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("planarQuality", "Planar Quality", planarQuality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("planarQuality", planarQuality))
		{
			_fe3d->graphics_setPlanarRefractionQuality(planarQuality);
		}
	}
}

void WorldEditor::_updateDofGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsDof")
	{
		auto isEnabled = _fe3d->graphics_isDofEnabled();
		auto isDynamic = _fe3d->graphics_isDofDynamic();
		auto blurDistance = _fe3d->graphics_getDofBlurDistance();
		auto dynamicDistance = _fe3d->graphics_getDofDynamicDistance();
		auto quality = _fe3d->graphics_getDofQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->graphics_setDofEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isDynamic")->isHovered())
		{
			isDynamic = !isDynamic;
			_fe3d->graphics_setDofDynamic(isDynamic);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("dynamicDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("dynamicDistance", "Dynamic Distance", dynamicDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("blurDistance", "Blur Distance", blurDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("dynamicDistance", dynamicDistance))
		{
			_fe3d->graphics_setDofDynamicDistance(dynamicDistance);
		}
		//if(_gui->getOverlay()->checkValueForm("blurDistance", blurDistance))
		{
			_fe3d->graphics_setDofBlurDistance(blurDistance);
		}
		//if(_gui->getOverlay()->checkValueForm("quality", quality))
		{
			_fe3d->graphics_setDofQuality(quality);
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
		auto isEnabled = _fe3d->graphics_isFogEnabled();
		auto minDistance = _fe3d->graphics_getFogMinDistance();
		auto maxDistance = _fe3d->graphics_getFogMaxDistance();
		auto thickness = _fe3d->graphics_getFogThickness();
		auto color = _fe3d->graphics_getFogColor();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->graphics_setFogEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("minDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("minDistance", "Min Distance", minDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxDistance", "Max Distance", maxDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("thickness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("thickness", "Thickness", (thickness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("minDistance", minDistance))
		{
			_fe3d->graphics_setFogMinDistance(minDistance);
		}
		//if(_gui->getOverlay()->checkValueForm("maxDistance", maxDistance))
		{
			_fe3d->graphics_setFogMaxDistance(maxDistance);
		}
		//if(_gui->getOverlay()->checkValueForm("thickness", thickness))
		{
			thickness /= 100.0f;
			_fe3d->graphics_setFogThickness(thickness);
		}
		//if(_gui->getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d->graphics_setFogColor(color);
		}
		//if(_gui->getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d->graphics_setFogColor(color);
		}
		//if(_gui->getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d->graphics_setFogColor(color);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateLensFlareGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsLensFlare")
	{
		auto isEnabled = _fe3d->graphics_isLensFlareEnabled();
		auto flareMapPath = _fe3d->graphics_getLensFlareMapPath();
		auto intensity = _fe3d->graphics_getLensFlareIntensity();
		auto sensitivity = _fe3d->graphics_getLensFlareSensitivity();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->graphics_setLensFlareEnabled(isEnabled);
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

			flareMapPath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(flareMapPath);
			_fe3d->graphics_setLensFlareMap(flareMapPath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("sensitivity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sensitivity", "Sensitivity", (sensitivity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d->graphics_setLensFlareIntensity(intensity);
		}
		//if(_gui->getOverlay()->checkValueForm("sensitivity", sensitivity))
		{
			sensitivity /= 100.0f;
			_fe3d->graphics_setLensFlareSensitivity(sensitivity);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateSkyExposureGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsSkyExposure")
	{
		auto isEnabled = _fe3d->graphics_isSkyExposureEnabled();
		auto intensity = _fe3d->graphics_getSkyExposureIntensity();
		auto speed = _fe3d->graphics_getSkyExposureSpeed();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->graphics_setSkyExposureEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("speed", "Speed", (speed * 10000.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d->graphics_setSkyExposureIntensity(intensity);
		}
		//if(_gui->getOverlay()->checkValueForm("speed", speed))
		{
			speed /= 10000.0f;
			_fe3d->graphics_setSkyExposureSpeed(speed);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateBloomGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsGraphicsBloom")
	{
		auto isEnabled = _fe3d->graphics_isBloomEnabled();
		auto type = _fe3d->graphics_getBloomType();
		auto intensity = _fe3d->graphics_getBloomIntensity();
		auto blurCount = _fe3d->graphics_getBloomBlurCount();
		auto quality = _fe3d->graphics_getBloomQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->graphics_setBloomEnabled(isEnabled);
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
			_fe3d->graphics_setBloomType(type);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurCount")->isHovered())
		{
			_gui->getOverlay()->openValueForm("blurCount", "Blur Count", blurCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->openValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d->graphics_setBloomIntensity(intensity);
		}
		//if(_gui->getOverlay()->checkValueForm("blurCount", blurCount))
		{
			_fe3d->graphics_setBloomBlurCount(blurCount);
		}
		//if(_gui->getOverlay()->checkValueForm("quality", quality))
		{
			_fe3d->graphics_setBloomQuality(quality);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("type")->setTextContent((type == BloomType::EVERYTHING) ? "Type: EVERYTHING" : "Type: PARTS");
	}
}