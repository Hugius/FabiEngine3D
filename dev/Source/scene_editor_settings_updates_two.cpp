#include "scene_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void SceneEditor::_updateFogGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "sceneEditorMenuSettingsGraphicsFog")
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
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
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
			_gui.getGlobalScreen()->createValueForm("minDistance", "Min Distance", minDistance, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxDistance")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("maxDistance", "Max Distance", maxDistance, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("thickness")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("thickness", "Thickness", (thickness * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("colorR", "R", color.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorG", "G", color.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorB", "B", color.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
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
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
	}
}

void SceneEditor::_updateLensFlareGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "sceneEditorMenuSettingsGraphicsLensFlare")
	{
		// Temporary values
		const auto rootDirectory = Tools::getRootDirectory();
		const string targetDirectory = string("game_assets\\textures\\flare_maps\\");
		auto isEnabled = _fe3d.gfx_isLensFlareEnabled();
		auto flareMapPath = _fe3d.gfx_getLensFlareMapPath();
		auto intensity = _fe3d.gfx_getLensFlareIntensity();
		auto sensitivity = _fe3d.gfx_getLensFlareSensitivity();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
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
			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
			   filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
				return;
			}

			// Save lens flare path
			flareMapPath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(flareMapPath);
			_fe3d.gfx_setLensFlareMap(flareMapPath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("intensity", "Flare Intensity", (intensity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("sensitivity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("sensitivity", "Flare Sensitivity", (sensitivity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
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
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
	}
}

void SceneEditor::_updateSkyExposureGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "sceneEditorMenuSettingsGraphicsSkyExposure")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isSkyExposureEnabled();
		auto intensity = _fe3d.gfx_getSkyExposureIntensity();
		auto speed = _fe3d.gfx_getSkyExposureSpeed();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
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
			_gui.getGlobalScreen()->createValueForm("intensity", "Exposure Intensity", (intensity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("speed", "Exposure Speed", (speed * 10000.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
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
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
	}
}

void SceneEditor::_updateBloomGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "sceneEditorMenuSettingsGraphicsBloom")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isBloomEnabled();
		auto type = _fe3d.gfx_getBloomType();
		auto intensity = _fe3d.gfx_getBloomIntensity();
		auto blurCount = _fe3d.gfx_getBloomBlurCount();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
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
			_gui.getGlobalScreen()->createValueForm("intensity", "Bloom Intensity", (intensity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurs")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("blurCount", "Amount Of Blurs", blurCount, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
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

		// Update buttons hoverability
		screen->getButton("type")->setHoverable(isEnabled);
		screen->getButton("intensity")->setHoverable(isEnabled);
		screen->getButton("blurs")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
		screen->getButton("type")->changeTextContent((type == BloomType::EVERYTHING) ? "Type: EVERYTHING" : "Type: PARTS");
	}
}