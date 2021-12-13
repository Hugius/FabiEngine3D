#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WorldEditor::_updateShadowsGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSettingsGraphicsShadows")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isShadowsEnabled();
		auto isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
		auto size = _fe3d.gfx_getShadowSize();
		auto lightness = _fe3d.gfx_getShadowLightness();
		auto position = _fe3d.gfx_getShadowEyePosition();
		auto center = _fe3d.gfx_getShadowCenterPosition();
		auto interval = _fe3d.gfx_getShadowInterval();
		auto quality = _fe3d.gfx_getShadowQuality();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			_fe3d.misc_disableShadowFrameRendering();
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if(isEnabled)
			{
				_fe3d.gfx_enableShadows();
			}
			else
			{
				_fe3d.gfx_disableShadows(false);
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("size", "Size", size, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("positionX", "X", position.x, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("positionY", "Y", position.y, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("positionZ", "Z", position.z, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("center")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("centerX", "X", center.x, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("centerY", "Y", center.y, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("centerZ", "Z", center.z, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("follow")->isHovered())
		{
			isFollowingCamera = !isFollowingCamera;
			_fe3d.gfx_setShadowFollowingCamera(isFollowingCamera);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("interval")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("interval", "Frame Interval", interval, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("size", size))
		{
			_fe3d.gfx_setShadowAreaSize(size);
			_fe3d.gfx_setShadowAreaReach(size * 2.0f);
		}
		if(_gui.getGlobalScreen()->checkValueForm("positionX", position.x))
		{
			_fe3d.gfx_setShadowEyePosition(position);
		}
		if(_gui.getGlobalScreen()->checkValueForm("positionY", position.y))
		{
			_fe3d.gfx_setShadowEyePosition(position);
		}
		if(_gui.getGlobalScreen()->checkValueForm("positionZ", position.z))
		{
			_fe3d.gfx_setShadowEyePosition(position);
		}
		if(_gui.getGlobalScreen()->checkValueForm("centerX", center.x))
		{
			_fe3d.gfx_setShadowCenterPosition(center);
		}
		if(_gui.getGlobalScreen()->checkValueForm("centerY", center.y))
		{
			_fe3d.gfx_setShadowCenterPosition(center);
		}
		if(_gui.getGlobalScreen()->checkValueForm("centerZ", center.z))
		{
			_fe3d.gfx_setShadowCenterPosition(center);
		}
		if(_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d.gfx_setShadowLightness(lightness);
		}
		if(_gui.getGlobalScreen()->checkValueForm("interval", interval))
		{
			_fe3d.gfx_setShadowInterval(interval);
		}
		if (_gui.getGlobalScreen()->checkValueForm("quality", quality))
		{
			_fe3d.gfx_setShadowQuality(quality);
		}

		// Update buttons hoverability
		screen->getButton("size")->setHoverable(isEnabled);
		screen->getButton("position")->setHoverable(isEnabled);
		screen->getButton("center")->setHoverable(isEnabled);
		screen->getButton("follow")->setHoverable(isEnabled);
		screen->getButton("lightness")->setHoverable(isEnabled);
		screen->getButton("interval")->setHoverable(isEnabled);
		screen->getButton("quality")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("follow")->changeTextContent(isFollowingCamera ? "Follow Cam: ON" : "Follow Cam: OFF");
	}
}

void WorldEditor::_updateReflectionsGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSettingsGraphicsReflections")
	{
		// Temporary values
		auto planarHeight = _fe3d.gfx_getPlanarReflectionHeight();
		auto cubeQuality = _fe3d.gfx_getCubeReflectionQuality();
		auto planarQuality = _fe3d.gfx_getPlanarReflectionQuality();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarHeight")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("planarHeight", "Planar Height", planarHeight, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("cubeQuality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("cubeQuality", "Cube Quality", cubeQuality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarQuality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("planarQuality", "Planar Quality", planarQuality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("planarHeight", planarHeight))
		{
			_fe3d.gfx_setPlanarReflectionHeight(planarHeight);
		}
		if (_gui.getGlobalScreen()->checkValueForm("cubeQuality", cubeQuality))
		{
			_fe3d.gfx_setCubeReflectionQuality(cubeQuality);
		}
		if (_gui.getGlobalScreen()->checkValueForm("planarQuality", planarQuality))
		{
			_fe3d.gfx_setPlanarReflectionQuality(planarQuality);
		}
	}
}

void WorldEditor::_updateRefractionsGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "worldEditorMenuSettingsGraphicsRefractions")
	{
		// Temporary values
		auto planarQuality = _fe3d.gfx_getPlanarRefractionQuality();

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarQuality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("planarQuality", "Planar Quality", planarQuality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("planarQuality", planarQuality))
		{
			_fe3d.gfx_setPlanarRefractionQuality(planarQuality);
		}
	}
}

void WorldEditor::_updateDofGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSettingsGraphicsDof")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isDofEnabled();
		auto isDynamic = _fe3d.gfx_isDofDynamic();
		auto blurDistance = _fe3d.gfx_getDofBlurDistance();
		auto maxDistance = _fe3d.gfx_getMaxDofDistance();
		auto quality = _fe3d.gfx_getDofQuality();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if(isEnabled)
			{
				_fe3d.gfx_enableDOF();
			}
			else
			{
				_fe3d.gfx_disableDOF(false);
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isDynamic")->isHovered())
		{
			isDynamic = !isDynamic;
			_fe3d.gfx_setDofDynamic(isDynamic);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("dynamicDistance")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("dynamicDistance", "Dynamic Distance", maxDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurDistance")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("blurDistance", "Blur Distance", blurDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("dynamicDistance", maxDistance))
		{
			_fe3d.gfx_setDofMaxDistance(maxDistance);
		}
		if(_gui.getGlobalScreen()->checkValueForm("blurDistance", blurDistance))
		{
			_fe3d.gfx_setDofBlurDistance(blurDistance);
		}
		if (_gui.getGlobalScreen()->checkValueForm("quality", quality))
		{
			_fe3d.gfx_setDofQuality(quality);
		}

		// Update buttons hoverability
		screen->getButton("isDynamic")->setHoverable(isEnabled);
		screen->getButton("dynamicDistance")->setHoverable(isEnabled && isDynamic);
		screen->getButton("blurDistance")->setHoverable(isEnabled);
		screen->getButton("quality")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("isDynamic")->changeTextContent(isDynamic ? "Dynamic: ON" : "Dynamic: OFF");
	}
}

void WorldEditor::_updateFogGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSettingsGraphicsFog")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isFogEnabled();
		auto minDistance = _fe3d.gfx_getFogMinDistance();
		auto maxDistance = _fe3d.gfx_getFogMaxDistance();
		auto thickness = _fe3d.gfx_getFogThickness();
		auto color = _fe3d.gfx_getFogColor();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if(isEnabled)
			{
				_fe3d.gfx_enableFog();
			}
			else
			{
				_fe3d.gfx_disableFog(false);
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("minDistance")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("minDistance", "Min Distance", minDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxDistance")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("maxDistance", "Max Distance", maxDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("thickness")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("thickness", "Thickness", (thickness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("colorR", "R", color.r * 255.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorG", "G", color.g * 255.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorB", "B", color.b * 255.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("minDistance", minDistance))
		{
			_fe3d.gfx_setFogMinDistance(minDistance);
		}
		if(_gui.getGlobalScreen()->checkValueForm("maxDistance", maxDistance))
		{
			_fe3d.gfx_setFogMaxDistance(maxDistance);
		}
		if(_gui.getGlobalScreen()->checkValueForm("thickness", thickness))
		{
			thickness /= 100.0f;
			_fe3d.gfx_setFogThickness(thickness);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d.gfx_setFogColor(color);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d.gfx_setFogColor(color);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d.gfx_setFogColor(color);
		}

		// Update buttons hoverability
		screen->getButton("minDistance")->setHoverable(isEnabled);
		screen->getButton("maxDistance")->setHoverable(isEnabled);
		screen->getButton("thickness")->setHoverable(isEnabled);
		screen->getButton("color")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateLensFlareGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSettingsGraphicsLensFlare")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isLensFlareEnabled();
		auto flareMapPath = _fe3d.gfx_getLensFlareMapPath();
		auto intensity = _fe3d.gfx_getLensFlareIntensity();
		auto sensitivity = _fe3d.gfx_getLensFlareSensitivity();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if(isEnabled)
			{
				_fe3d.gfx_enableLensFlare();
			}
			else
			{
				_fe3d.gfx_disableLensFlare(false);
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("flareMap")->isHovered())
		{
			// Validate project ID
			if(_currentProjectID.empty())
			{
				Logger::throwError("WorldEditor::_updateLensFlareGraphicsSettingsMenu");
			}

			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\textures\\flare_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			// Get the chosen file name
			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			// Save lens flare path
			flareMapPath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clear2dTextureCache(flareMapPath);
			_fe3d.gfx_setLensFlareMap(flareMapPath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("intensity", "Flare Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("sensitivity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("sensitivity", "Flare Sensitivity", (sensitivity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d.gfx_setLensFlareIntensity(intensity);
		}
		if(_gui.getGlobalScreen()->checkValueForm("sensitivity", sensitivity))
		{
			sensitivity /= 100.0f;
			_fe3d.gfx_setLensFlareSensitivity(sensitivity);
		}

		// Update buttons hoverability
		screen->getButton("intensity")->setHoverable(isEnabled);
		screen->getButton("sensitivity")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateSkyExposureGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSettingsGraphicsSkyExposure")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isSkyExposureEnabled();
		auto intensity = _fe3d.gfx_getSkyExposureIntensity();
		auto speed = _fe3d.gfx_getSkyExposureSpeed();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if(isEnabled)
			{
				_fe3d.gfx_enableSkyExposure();
			}
			else
			{
				_fe3d.gfx_disableSkyExposure(false);
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("intensity", "Exposure Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("speed", "Exposure Speed", (speed * 10000.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d.gfx_setSkyExposureIntensity(intensity);
		}
		if(_gui.getGlobalScreen()->checkValueForm("speed", speed))
		{
			speed /= 10000.0f;
			_fe3d.gfx_setSkyExposureSpeed(speed);
		}

		// Update buttons hoverability
		screen->getButton("intensity")->setHoverable(isEnabled);
		screen->getButton("speed")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateBloomGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSettingsGraphicsBloom")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isBloomEnabled();
		auto type = _fe3d.gfx_getBloomType();
		auto intensity = _fe3d.gfx_getBloomIntensity();
		auto blurCount = _fe3d.gfx_getBloomBlurCount();
		auto quality = _fe3d.gfx_getBloomQuality();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettingsGraphics");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if(isEnabled)
			{
				_fe3d.gfx_enableBloom();
			}
			else
			{
				_fe3d.gfx_disableBloom(false);
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("type")->isHovered())
		{
			if(type == BloomType::EVERYTHING)
			{
				type = BloomType::PARTS;
			}
			else
			{
				type = BloomType::EVERYTHING;
			}
			_fe3d.gfx_setBloomType(type);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("intensity", "Bloom Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurs")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("blurCount", "Amount Of Blurs", blurCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("quality", "Quality", quality, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d.gfx_setBloomIntensity(intensity);
		}
		if(_gui.getGlobalScreen()->checkValueForm("blurCount", blurCount))
		{
			_fe3d.gfx_setBloomBlurCount(blurCount);
		}
		if (_gui.getGlobalScreen()->checkValueForm("quality", quality))
		{
			_fe3d.gfx_setBloomQuality(quality);
		}

		// Update buttons hoverability
		screen->getButton("type")->setHoverable(isEnabled);
		screen->getButton("intensity")->setHoverable(isEnabled);
		screen->getButton("blurs")->setHoverable(isEnabled);
		screen->getButton("quality")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
		screen->getButton("type")->changeTextContent((type == BloomType::EVERYTHING) ? "Type: EVERYTHING" : "Type: PARTS");
	}
}