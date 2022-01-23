#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WorldEditor::_updateShadowsGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSettingsGraphicsShadows")
	{
		auto isEnabled = _fe3d->gfx_isShadowsEnabled();
		auto isFollowingCamera = _fe3d->gfx_isShadowFollowingCamera();
		auto size = _fe3d->gfx_getShadowSize();
		auto lightness = _fe3d->gfx_getShadowLightness();
		auto eye = _fe3d->gfx_getShadowEyeOffset();
		auto center = _fe3d->gfx_getShadowCenterOffset();
		auto interval = _fe3d->gfx_getShadowInterval();
		auto quality = _fe3d->gfx_getShadowQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			_fe3d->misc_disableShadowFrameRendering();
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if(isEnabled)
			{
				_fe3d->gfx_enableShadows();
			}
			else
			{
				_fe3d->gfx_disableShadows(false);
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->createValueForm("size", "Size", size, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("eye")->isHovered())
		{
			_gui->getOverlay()->createValueForm("eyeX", "X", eye.x, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("eyeY", "Y", eye.y, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("eyeZ", "Z", eye.z, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("center")->isHovered())
		{
			_gui->getOverlay()->createValueForm("centerX", "X", center.x, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("centerY", "Y", center.y, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("centerZ", "Z", center.z, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("follow")->isHovered())
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
			_gui->getOverlay()->createValueForm("interval", "Frame Interval", interval, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->createValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("size", size))
		{
			_fe3d->gfx_setShadowSize(size);
			_fe3d->gfx_setShadowReach(size * 2.0f);
		}
		if(_gui->getOverlay()->checkValueForm("eyeX", eye.x))
		{
			_fe3d->gfx_setShadowEyeOffset(eye);
		}
		if(_gui->getOverlay()->checkValueForm("eyeY", eye.y))
		{
			_fe3d->gfx_setShadowEyeOffset(eye);
		}
		if(_gui->getOverlay()->checkValueForm("eyeZ", eye.z))
		{
			_fe3d->gfx_setShadowEyeOffset(eye);
		}
		if(_gui->getOverlay()->checkValueForm("centerX", center.x))
		{
			_fe3d->gfx_setShadowCenterOffset(center);
		}
		if(_gui->getOverlay()->checkValueForm("centerY", center.y))
		{
			_fe3d->gfx_setShadowCenterOffset(center);
		}
		if(_gui->getOverlay()->checkValueForm("centerZ", center.z))
		{
			_fe3d->gfx_setShadowCenterOffset(center);
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

		screen->getButton("size")->setHoverable(isEnabled);
		screen->getButton("eye")->setHoverable(isEnabled);
		screen->getButton("center")->setHoverable(isEnabled);
		screen->getButton("follow")->setHoverable(isEnabled);
		screen->getButton("lightness")->setHoverable(isEnabled);
		screen->getButton("interval")->setHoverable(isEnabled);
		screen->getButton("quality")->setHoverable(isEnabled);

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("follow")->changeTextContent(isFollowingCamera ? "Follow Cam: ON" : "Follow Cam: OFF");
	}
}

void WorldEditor::_updateReflectionsGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSettingsGraphicsReflections")
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

	if(screen->getID() == "worldEditorMenuSettingsGraphicsRefractions")
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

	if(screen->getID() == "worldEditorMenuSettingsGraphicsDof")
	{
		auto isEnabled = _fe3d->gfx_isDofEnabled();
		auto isDynamic = _fe3d->gfx_isDofDynamic();
		auto blurDistance = _fe3d->gfx_getDofBlurDistance();
		auto maxDistance = _fe3d->gfx_getDofDynamicDistance();
		auto quality = _fe3d->gfx_getDofQuality();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if(isEnabled)
			{
				_fe3d->gfx_enableDOF();
			}
			else
			{
				_fe3d->gfx_disableDOF(false);
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isDynamic")->isHovered())
		{
			isDynamic = !isDynamic;
			_fe3d->gfx_setDofDynamic(isDynamic);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("dynamicDistance")->isHovered())
		{
			_gui->getOverlay()->createValueForm("dynamicDistance", "Dynamic Distance", maxDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurDistance")->isHovered())
		{
			_gui->getOverlay()->createValueForm("blurDistance", "Blur Distance", blurDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui->getOverlay()->createValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("dynamicDistance", maxDistance))
		{
			_fe3d->gfx_setDofDynamicDistance(maxDistance);
		}
		if(_gui->getOverlay()->checkValueForm("blurDistance", blurDistance))
		{
			_fe3d->gfx_setDofBlurDistance(blurDistance);
		}
		if(_gui->getOverlay()->checkValueForm("quality", quality))
		{
			_fe3d->gfx_setDofQuality(quality);
		}

		screen->getButton("isDynamic")->setHoverable(isEnabled);
		screen->getButton("dynamicDistance")->setHoverable(isEnabled && isDynamic);
		screen->getButton("blurDistance")->setHoverable(isEnabled);
		screen->getButton("quality")->setHoverable(isEnabled);

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("isDynamic")->changeTextContent(isDynamic ? "Dynamic: ON" : "Dynamic: OFF");
	}
}

void WorldEditor::_updateFogGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSettingsGraphicsFog")
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
			if(isEnabled)
			{
				_fe3d->gfx_enableFog();
			}
			else
			{
				_fe3d->gfx_disableFog(false);
			}
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

		screen->getButton("minDistance")->setHoverable(isEnabled);
		screen->getButton("maxDistance")->setHoverable(isEnabled);
		screen->getButton("thickness")->setHoverable(isEnabled);
		screen->getButton("color")->setHoverable(isEnabled);

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateLensFlareGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSettingsGraphicsLensFlare")
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
			if(isEnabled)
			{
				_fe3d->gfx_enableLensFlare();
			}
			else
			{
				_fe3d->gfx_disableLensFlare(false);
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("flareMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("WorldEditor::_updateLensFlareGraphicsSettingsMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\misc\\flare_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			flareMapPath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(flareMapPath);
			_fe3d->gfx_setLensFlareMap(flareMapPath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("intensity", "Flare Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("sensitivity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("sensitivity", "Flare Sensitivity", (sensitivity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
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

		screen->getButton("intensity")->setHoverable(isEnabled);
		screen->getButton("sensitivity")->setHoverable(isEnabled);

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateSkyExposureGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSettingsGraphicsSkyExposure")
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
			if(isEnabled)
			{
				_fe3d->gfx_enableSkyExposure();
			}
			else
			{
				_fe3d->gfx_disableSkyExposure(false);
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("intensity", "Exposure Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui->getOverlay()->createValueForm("speed", "Exposure Speed", (speed * 10000.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
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

		screen->getButton("intensity")->setHoverable(isEnabled);
		screen->getButton("speed")->setHoverable(isEnabled);

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateBloomGraphicsSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuSettingsGraphicsBloom")
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
			if(isEnabled)
			{
				_fe3d->gfx_enableBloom();
			}
			else
			{
				_fe3d->gfx_disableBloom(false);
			}
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
			_gui->getOverlay()->createValueForm("intensity", "Bloom Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurCount")->isHovered())
		{
			_gui->getOverlay()->createValueForm("blurCount", "Amount Of Blurs", blurCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
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

		screen->getButton("type")->setHoverable(isEnabled);
		screen->getButton("intensity")->setHoverable(isEnabled);
		screen->getButton("blurCount")->setHoverable(isEnabled);
		screen->getButton("quality")->setHoverable(isEnabled);

		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("type")->changeTextContent((type == BloomType::EVERYTHING) ? "Type: EVERYTHING" : "Type: PARTS");
	}
}