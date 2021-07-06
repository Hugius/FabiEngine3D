#include "scene_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void SceneEditor::_updateDofGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsDof")
	{
		// Temporary values
		bool isEnabled = _fe3d.gfx_isDofEnabled();
		bool dynamic = _fe3d.gfx_isDofDynamic();
		float blurDistance = _fe3d.gfx_getDofBlurDistance();
		float maxDistance = _fe3d.gfx_getaMaxDofDistance();

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				isEnabled = !isEnabled;
			}
			else if (screen->getButton("dynamic")->isHovered())
			{
				dynamic = !dynamic;
			}
			else if (screen->getButton("blurDistance")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("blurDistance", "Blur Distance", blurDistance, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("maxDistance")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("maxDistance", "DOF Distance", maxDistance, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
		}

		// Button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
		screen->getButton("dynamic")->changeTextContent(dynamic ? "Dynamic: YES" : "Dynamic: NO");

		// Blur distance value
		_gui.getGlobalScreen()->checkValueForm("blurDistance", blurDistance);
		blurDistance = std::max(0.0f, blurDistance);

		// Max distance value
		_gui.getGlobalScreen()->checkValueForm("maxDistance", maxDistance);
		maxDistance = std::max(0.0f, maxDistance);

		// Disable DOF
		if (_fe3d.gfx_isDofEnabled())
		{
			_fe3d.gfx_disableDOF();
		}

		// Enable DOF
		if (isEnabled)
		{
			_fe3d.gfx_enableDOF(dynamic, maxDistance, blurDistance);
		}

		// Update buttons hoverability
		screen->getButton("dynamic")->setHoverable(isEnabled);
		screen->getButton("blurDistance")->setHoverable(isEnabled);
		screen->getButton("maxDistance")->setHoverable(isEnabled && dynamic);
	}
}

void SceneEditor::_updateFogGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsFog")
	{
		// Temporary values
		bool isEnabled = _fe3d.gfx_isFogEnabled();
		float minDistance = _fe3d.gfx_getFogMinDistance();
		float maxDistance = _fe3d.gfx_getFogMaxDistance();
		float thickness = _fe3d.gfx_getFogThickness();
		Vec3 color = _fe3d.gfx_getFogColor();

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				isEnabled = !isEnabled;
			}
			else if (screen->getButton("minDistance")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("minDistance", "Min Distance", minDistance, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("maxDistance")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("maxDistance", "Max Distance", maxDistance, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("thickness")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("thickness", "Thickness", thickness * 100.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("colorR", "R", color.r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorG", "G", color.g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorB", "B", color.b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
			}
		}

		// Button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");

		// Min distance value
		_gui.getGlobalScreen()->checkValueForm("minDistance", minDistance);
		minDistance = std::max(0.0f, minDistance);

		// Max distance value
		_gui.getGlobalScreen()->checkValueForm("maxDistance", maxDistance);
		maxDistance = std::max(0.0f, maxDistance);

		// Thickness value
		thickness *= 100.0f;
		_gui.getGlobalScreen()->checkValueForm("thickness", thickness);
		thickness = std::clamp(thickness / 100.0f, 0.0f, 1.0f);

		// Color values
		color *= 255.0f;
		_gui.getGlobalScreen()->checkValueForm("colorR", color.r, { });
		_gui.getGlobalScreen()->checkValueForm("colorG", color.g, { });
		_gui.getGlobalScreen()->checkValueForm("colorB", color.b, { });
		color.r = std::clamp(color.r / 255.0f, 0.0f, 1.0f);
		color.g = std::clamp(color.g / 255.0f, 0.0f, 1.0f);
		color.b = std::clamp(color.b / 255.0f, 0.0f, 1.0f);

		// Disable fog
		if (_fe3d.gfx_isFogEnabled())
		{
			_fe3d.gfx_disableFog();
		}

		// Enable fog
		if (isEnabled)
		{
			_fe3d.gfx_enableFog(minDistance, maxDistance, thickness, color);
		}

		// Update buttons hoverability
		screen->getButton("minDistance")->setHoverable(isEnabled);
		screen->getButton("maxDistance")->setHoverable(isEnabled);
		screen->getButton("thickness")->setHoverable(isEnabled);
		screen->getButton("color")->setHoverable(isEnabled);
	}
}

void SceneEditor::_updateLensFlareGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsLensFlare")
	{
		// Temporary values
		const string rootDirectory = _fe3d.misc_getRootDirectory();
		const string targetDirectory = string("game_assets\\textures\\flare_maps\\");
		bool isEnabled = _fe3d.gfx_isLensFlareEnabled();
		string flareMapPath = _fe3d.gfx_getLensFlareMapPath();
		float intensity = _fe3d.gfx_getLensFlareIntensity();
		float multiplier = _fe3d.gfx_getLensFlareMultiplier();

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				isEnabled = !isEnabled;
			}
			else if (screen->getButton("loadFlareMap")->isHovered())
			{
				// Get the chosen filename
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						flareMapPath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(flareMapPath);

						// Save lens flare path
						if (_fe3d.gfx_isLensFlareEnabled())
						{
							_fe3d.gfx_disableLensFlare();
						}
						_fe3d.gfx_enableLensFlare(flareMapPath, intensity, multiplier);
						_fe3d.gfx_disableLensFlare();
					}
					else
					{
						Logger::throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("intensity")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("intensity", "Flare Intensity", intensity * 100.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("multiplier")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("multiplier", "Size Multiplier", multiplier * 100.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
		}

		// Button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");

		// Intensity value
		if (_gui.getGlobalScreen()->checkValueForm("intensity", intensity))
		{
			intensity = std::max(0.0f, intensity / 100.0f);
		}

		// Multiplier value
		if (_gui.getGlobalScreen()->checkValueForm("multiplier", multiplier))
		{
			multiplier = std::max(0.0f, multiplier / 100.0f);
		}

		// Disable lens flare
		if (_fe3d.gfx_isLensFlareEnabled())
		{
			_fe3d.gfx_disableLensFlare();
		}

		// Enable lens flare
		if (isEnabled && _fe3d.misc_isFileExisting(rootDirectory + flareMapPath))
		{
			_fe3d.gfx_enableLensFlare(flareMapPath, intensity, multiplier);
		}

		// Update buttons hoverability
		screen->getButton("enabled")->setHoverable(_fe3d.misc_isFileExisting(rootDirectory + flareMapPath));
		screen->getButton("intensity")->setHoverable(isEnabled);
		screen->getButton("multiplier")->setHoverable(isEnabled);
	}
}

void SceneEditor::_updateskyHdrGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsSkyHDR")
	{
		// Temporary values
		bool isEnabled = _fe3d.gfx_isSkyHdrEnabled();
		float intensity = _fe3d.gfx_getSkyHdrBrightnessFactor();

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				isEnabled = !isEnabled;
			}
			else if (screen->getButton("intensity")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("intensity", "Extra Intensity", intensity * 100.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
		}

		// Button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");

		// Extra intensity value
		if (_gui.getGlobalScreen()->checkValueForm("intensity", intensity))
		{
			intensity = std::max(0.0f, intensity / 100.0f);
		}

		// Disable skyHDR
		if (_fe3d.gfx_isSkyHdrEnabled())
		{
			_fe3d.gfx_disableSkyHDR();
		}

		// Enable skyHDR
		if (isEnabled)
		{
			_fe3d.gfx_enableSkyHDR(intensity);
		}

		// Update buttons hoverability
		screen->getButton("intensity")->setHoverable(isEnabled);
	}
}