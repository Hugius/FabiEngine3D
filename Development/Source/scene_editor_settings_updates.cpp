#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateMainSettingsMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		if (screen->getID() == "sceneEditorMenuSettings")
		{
			// Temporary values
			float lodDistance = _fe3d.gameEntity_getLevelOfDetailDistance();

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				}
				else if (screen->getButton("graphics")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
				}
				else if (screen->getButton("setSpeed")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("setSpeed", "Camera speed", _customEditorSpeed, Vec2(0.0f), Vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("lodDistance")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("lodDistance", "LOD Distance", lodDistance, Vec2(0.0f), Vec2(0.3f, 0.1f));
				}
			}

			// Setting custom camera speed
			_gui.getGlobalScreen()->checkValueForm("setSpeed", _customEditorSpeed, {});

			// Setting LOD distance
			if (_gui.getGlobalScreen()->checkValueForm("lodDistance", lodDistance, {}))
			{
				_fe3d.gameEntity_setLevelOfDetailDistance(lodDistance);
			}
		}
	}
}

void SceneEditor::_updateGraphicsSettingsMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSettingsGraphics")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettings");
			}
			else if (screen->getButton("shadows")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsShadows");
				_fe3d.misc_enableShadowFrameRendering();
			}
			else if (screen->getButton("motionblur")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsMotionblur");
			}
			else if (screen->getButton("dof")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsDof");
			}
			else if (screen->getButton("fog")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsFog");
			}
			else if (screen->getButton("lensflare")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsLensFlare");
			}
			else if (screen->getButton("skyHdr")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsSkyHDR");
			}
		}
	}
}

void SceneEditor::_updateShadowGraphicsSettingsMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if (screen->getID() == "sceneEditorMenuSettingsGraphicsShadows")
	{
		// Temporary values
		bool enabled = _fe3d.gfx_isShadowsEnabled();
		float size = _fe3d.gfx_getShadowSize();
		Vec3 position = _fe3d.gfx_getShadowEyePosition();
		Vec3 center = _fe3d.gfx_getShadowCenter();
		bool isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
		int interval = _fe3d.gfx_getShadowInterval();

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
				_fe3d.misc_disableShadowFrameRendering();
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				enabled = !enabled;
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("size", "Size", _fe3d.gfx_getShadowSize(), Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("position")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("positionX", "X", _fe3d.gfx_getShadowEyePosition().x, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("positionY", "Y", _fe3d.gfx_getShadowEyePosition().y, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("positionZ", "Z", _fe3d.gfx_getShadowEyePosition().z, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("center")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("centerX", "X", _fe3d.gfx_getShadowCenter().x, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("centerY", "Y", _fe3d.gfx_getShadowCenter().y, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("centerZ", "Z", _fe3d.gfx_getShadowCenter().z, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("follow")->isHovered())
			{
				isFollowingCamera = !isFollowingCamera;
			}
			else if (screen->getButton("interval")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("interval", "Frame interval", _fe3d.gfx_getShadowInterval(), Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
			}
		}

		// Enabled button content
		_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), enabled ? "Enabled: YES" : "Enabled: NO");

		// Size value
		_gui.getGlobalScreen()->checkValueForm("size", size);

		// Position values
		_gui.getGlobalScreen()->checkValueForm("positionX", position.x);
		_gui.getGlobalScreen()->checkValueForm("positionY", position.y);
		_gui.getGlobalScreen()->checkValueForm("positionZ", position.z);

		// Center values
		_gui.getGlobalScreen()->checkValueForm("centerX", center.x);
		_gui.getGlobalScreen()->checkValueForm("centerY", center.y);
		_gui.getGlobalScreen()->checkValueForm("centerZ", center.z);

		// Following button content
		_fe3d.textEntity_setTextContent(screen->getButton("follow")->getTextfield()->getEntityID(), isFollowingCamera ? "Follow cam: ON" : "Follow cam: OFF");

		// Interval value
		_gui.getGlobalScreen()->checkValueForm("interval", interval);

		// Enable or disable shadows
		if (enabled)
		{
			_fe3d.gfx_enableShadows(position, center, size, size * 1.5f, isFollowingCamera, interval);
		}
		else
		{
			_fe3d.gfx_disableShadows();
		}

		// Update buttons hoverability
		screen->getButton("size")->setHoverable(enabled);
		screen->getButton("position")->setHoverable(enabled);
		screen->getButton("center")->setHoverable(enabled);
		screen->getButton("follow")->setHoverable(enabled);
		screen->getButton("interval")->setHoverable(enabled && isFollowingCamera);
	}
}

void SceneEditor::_updateMotionblurGraphicsSettingsMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if (screen->getID() == "sceneEditorMenuSettingsGraphicsMotionblur")
	{
		// Temporary values
		bool enabled = _fe3d.gfx_isMotionBlurEnabled();
		float strength = _fe3d.gfx_getMotionBlurStrength();

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				enabled = !enabled;
			}
			else if (screen->getButton("strength")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("strength", "Strength (%)", strength * 100.0f, Vec2(0.0f), Vec2(0.2f, 0.1f));
			}
		}
		
		// Enabled button content
		_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), enabled ? "Enabled: YES" : "Enabled: NO");

		// Strength value
		if (_gui.getGlobalScreen()->checkValueForm("strength", strength))
		{
			strength /= 100.0f;
		}

		// Enable or disable motionblur
		if (enabled)
		{
			_fe3d.gfx_enableMotionBlur(strength);
		}
		else
		{
			_fe3d.gfx_disableMotionBlur();
		}

		// Update buttons hoverability
		screen->getButton("strength")->setHoverable(enabled);
	}
}

void SceneEditor::_updateDofGraphicsSettingsMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if (screen->getID() == "sceneEditorMenuSettingsGraphicsDof")
	{
		// Temporary values
		bool enabled = _fe3d.gfx_isDofEnabled();
		bool dynamic = _fe3d.gfx_isDofDynamic();
		float blurDistance = _fe3d.gfx_getDofBlurDistance();
		float maxDistance = _fe3d.gfx_getDofMaxDistance();

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				enabled = !enabled;
			}
			else if (screen->getButton("dynamic")->isHovered())
			{
				dynamic = !dynamic;
			}
			else if (screen->getButton("blurDistance")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("blurDistance", "Blur distance", blurDistance, Vec2(0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("maxDistance")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("maxDistance", "DOF distance", maxDistance, Vec2(0.0f), Vec2(0.2f, 0.1f));
			}
		}

		// Enabled button content
		_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), enabled ? "Enabled: YES" : "Enabled: NO");
		_fe3d.textEntity_setTextContent(screen->getButton("dynamic")->getTextfield()->getEntityID(), dynamic ? "Dynamic: YES" : "Dynamic: NO");

		// Blur distance value
		_gui.getGlobalScreen()->checkValueForm("blurDistance", blurDistance);

		// Max distance value
		_gui.getGlobalScreen()->checkValueForm("maxDistance", maxDistance);

		// Enable or disable DOF
		if (enabled)
		{
			_fe3d.gfx_enableDOF(dynamic, maxDistance, blurDistance);
		}
		else
		{
			_fe3d.gfx_disableDOF();
		}

		// Update buttons hoverability
		screen->getButton("dynamic")->setHoverable(enabled);
		screen->getButton("blurDistance")->setHoverable(enabled);
		screen->getButton("maxDistance")->setHoverable(enabled && dynamic);
	}
}

void SceneEditor::_updateFogGraphicsSettingsMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if (screen->getID() == "sceneEditorMenuSettingsGraphicsFog")
	{
		// Temporary values
		bool enabled = _fe3d.gfx_isFogEnabled();
		float minDistance = _fe3d.gfx_getFogMinDistance();
		float maxDistance = _fe3d.gfx_getFogMaxDistance();
		float defaultFactor = _fe3d.gfx_getFogDefaultFactor();
		Vec3 color = _fe3d.gfx_getFogColor();

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				enabled = !enabled;
			}
			else if (screen->getButton("minDistance")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("minDistance", "Min distance", minDistance, Vec2(0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("maxDistance")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("maxDistance", "Max distance", maxDistance, Vec2(0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("defaultFactor")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("defaultFactor", "Default factor (0-100%)", defaultFactor * 100.0f, Vec2(0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("colorR", "R(0-255)", color.r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorG", "G(0-255)", color.g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorB", "B(0-255)", color.b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
			}
		}

		// Enabled button content
		_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), enabled ? "Enabled: YES" : "Enabled: NO");

		// Min distance value
		_gui.getGlobalScreen()->checkValueForm("minDistance", minDistance);

		// Max distance value
		_gui.getGlobalScreen()->checkValueForm("maxDistance", maxDistance);

		// Default factor distance value
		defaultFactor *= 100.0f;
		_gui.getGlobalScreen()->checkValueForm("defaultFactor", defaultFactor);
		defaultFactor = std::clamp(defaultFactor / 100.0f, 0.0f, 1.0f);

		// Color values
		color *= 255.0f;
		_gui.getGlobalScreen()->checkValueForm("colorR", color.r, { });
		_gui.getGlobalScreen()->checkValueForm("colorG", color.g, { });
		_gui.getGlobalScreen()->checkValueForm("colorB", color.b, { });
		color.r = std::clamp(color.r / 255.0f, 0.0f, 1.0f);
		color.g = std::clamp(color.g / 255.0f, 0.0f, 1.0f);
		color.b = std::clamp(color.b / 255.0f, 0.0f, 1.0f);

		// Enable or disable DOF
		if (enabled)
		{
			_fe3d.gfx_enableFog(minDistance, maxDistance, defaultFactor, color);
		}
		else
		{
			_fe3d.gfx_disableFog();
		}

		// Update buttons hoverability
		screen->getButton("minDistance")->setHoverable(enabled);
		screen->getButton("maxDistance")->setHoverable(enabled);
		screen->getButton("defaultFactor")->setHoverable(enabled);
		screen->getButton("color")->setHoverable(enabled);
	}
}

void SceneEditor::_updateLensFlareGraphicsSettingsMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if (screen->getID() == "sceneEditorMenuSettingsGraphicsLensFlare")
	{
		// Temporary values
		bool enabled = _fe3d.gfx_isLensFlareEnabled();
		string flareMapPath = _fe3d.gfx_getLensFlareMapPath();
		float intensity = _fe3d.gfx_getLensFlareIntensity();
		float multiplier = _fe3d.gfx_getLensFlareMultiplier();

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				enabled = !enabled;
			}
			else if (screen->getButton("loadFlareMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\flare_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache(newFilePath);
						_fe3d.gfx_enableLensFlare(newFilePath, intensity, multiplier);
						_fe3d.gfx_disableLensFlare();
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("intensity")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("intensity", "Flare intensity (%)", intensity * 100.0f, Vec2(0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("multiplier")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("multiplier", "Size multiplier (%)", multiplier * 100.0f, Vec2(0.0f), Vec2(0.2f, 0.1f));
			}
		}

		// Enabled button content
		_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), enabled ? "Enabled: YES" : "Enabled: NO");

		// Intensity value
		if (_gui.getGlobalScreen()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
		}

		// Multiplier value
		if (_gui.getGlobalScreen()->checkValueForm("multiplier", multiplier))
		{
			multiplier /= 100.0f;
		}

		// Enable or disable skyHDR
		if (enabled)
		{
			_fe3d.gfx_enableLensFlare(flareMapPath, intensity, multiplier);
		}
		else
		{
			_fe3d.gfx_disableLensFlare();
		}

		// Update buttons hoverability
		screen->getButton("enabled")->setHoverable(flareMapPath != "");
		screen->getButton("intensity")->setHoverable(enabled);
		screen->getButton("multiplier")->setHoverable(enabled);
	}
}

void SceneEditor::_updateskyHdrGraphicsSettingsMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if (screen->getID() == "sceneEditorMenuSettingsGraphicsSkyHDR")
	{
		// Temporary values
		bool enabled = _fe3d.gfx_isSkyHdrEnabled();
		float intensity = _fe3d.gfx_getSkyHdrBrightnessFactor();

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				enabled = !enabled;
			}
			else if (screen->getButton("intensity")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("intensity", "Extra intensity (%)", intensity * 100.0f, Vec2(0.0f), Vec2(0.2f, 0.1f));
			}
		}

		// Enabled button content
		_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), enabled ? "Enabled: YES" : "Enabled: NO");

		// Extra intensity value
		if (_gui.getGlobalScreen()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
		}

		// Enable or disable skyHDR
		if (enabled)
		{
			_fe3d.gfx_enableSkyHDR(intensity);
		}
		else
		{
			_fe3d.gfx_disableSkyHDR();
		}

		// Update buttons hoverability
		screen->getButton("intensity")->setHoverable(enabled);
	}
}