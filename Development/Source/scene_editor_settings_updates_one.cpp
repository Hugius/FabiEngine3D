#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateMainSettingsMenu()
{
	if (_isEditorLoaded)
	{
		// Temporary values
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuSettings")
		{
			// Temporary values
			auto lodDistance = _fe3d.misc_getLevelOfDetailDistance();
			auto reflectionHeight = _fe3d.gfx_getSceneReflectionHeight();

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				}
				else if (screen->getButton("graphics")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
				}
				else if (screen->getButton("setSpeed")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("setSpeed", "Camera Speed", _editorSpeed, Vec2(0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("lodDistance")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("lodDistance", "LOD Distance", lodDistance, Vec2(0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("reflectionHeight")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("reflectionHeight", "Scene reflection height", reflectionHeight, Vec2(0.0f), Vec2(0.15f, 0.1f));
				}
			}

			// Setting custom camera speed
			_gui.getGlobalScreen()->checkValueForm("setSpeed", _editorSpeed, {});
			_editorSpeed = std::max(0.0f, _editorSpeed);

			// Setting LOD distance
			if (_gui.getGlobalScreen()->checkValueForm("lodDistance", lodDistance, {}))
			{
				lodDistance = std::max(0.0f, lodDistance);
				_fe3d.misc_setLevelOfDetailDistance(lodDistance);
			}

			// Setting reflection height
			if (_gui.getGlobalScreen()->checkValueForm("reflectionHeight", reflectionHeight, {}))
			{
				_fe3d.gfx_disableSceneReflections();
				_fe3d.gfx_enableSceneReflections(0.5f, reflectionHeight);
			}
		}
	}
}

void SceneEditor::_updateGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSettingsGraphics")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
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
			else if (screen->getButton("skyExposure")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsSkyExposure");
			}
		}
	}
}

void SceneEditor::_updateShadowGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsShadows")
	{
		// Temporary values
		bool isEnabled = _fe3d.gfx_isShadowsEnabled();
		bool isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
		bool isLighted = _fe3d.gfx_isLightedShadowingEnabled();
		float size = _fe3d.gfx_getShadowSize();
		float lightness = _fe3d.gfx_getShadowLightness();
		Vec3 position = _fe3d.gfx_getShadowEye();
		Vec3 center = _fe3d.gfx_getShadowCenter();
		int interval = _fe3d.gfx_getShadowInterval();

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
				_fe3d.misc_disableShadowFrameRendering();
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				isEnabled = !isEnabled;
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("size", "Size", size, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("position")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("positionX", "X", position.x, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("positionY", "Y", position.y, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("positionZ", "Z", position.z, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("center")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("centerX", "X", center.x, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("centerY", "Y", center.y, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("centerZ", "Z", center.z, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("follow")->isHovered())
			{
				isFollowingCamera = !isFollowingCamera;
			}
			else if (screen->getButton("lighted")->isHovered())
			{
				isLighted = !isLighted;
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("lightness", "Lightness", lightness * 100.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("interval")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("interval", "Frame Interval", interval, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
			}
		}

		// Button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");

		// Size value
		_gui.getGlobalScreen()->checkValueForm("size", size);
		size = std::max(0.0f, size);

		// Position values
		_gui.getGlobalScreen()->checkValueForm("positionX", position.x);
		_gui.getGlobalScreen()->checkValueForm("positionY", position.y);
		_gui.getGlobalScreen()->checkValueForm("positionZ", position.z);

		// Center values
		_gui.getGlobalScreen()->checkValueForm("centerX", center.x);
		_gui.getGlobalScreen()->checkValueForm("centerY", center.y);
		_gui.getGlobalScreen()->checkValueForm("centerZ", center.z);

		// Button text contents
		screen->getButton("follow")->changeTextContent(isFollowingCamera ? "Follow Cam: ON" : "Follow Cam: OFF");
		screen->getButton("lighted")->changeTextContent(isLighted ? "Lighted: ON" : "Lighted : OFF");

		// Lightness value
		if (_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness = std::max(0.0f, lightness / 100.0f);
		}

		// Interval value
		_gui.getGlobalScreen()->checkValueForm("interval", interval);
		interval = std::max(0, interval);

		// Disable shadows
		if (_fe3d.gfx_isShadowsEnabled())
		{
			_fe3d.gfx_disableShadows();
		}

		// Enable shadows
		if (isEnabled)
		{
			_fe3d.gfx_enableShadows(position, center, size, size * 2.0f, lightness, isFollowingCamera, isLighted, interval);
		}

		// Update buttons hoverability
		screen->getButton("size")->setHoverable(isEnabled);
		screen->getButton("position")->setHoverable(isEnabled);
		screen->getButton("center")->setHoverable(isEnabled);
		screen->getButton("follow")->setHoverable(isEnabled);
		screen->getButton("lighted")->setHoverable(isEnabled);
		screen->getButton("lightness")->setHoverable(isEnabled);
		screen->getButton("interval")->setHoverable(isEnabled && isFollowingCamera);
	}
}

void SceneEditor::_updateMotionblurGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsMotionblur")
	{
		// Temporary values
		bool isEnabled = _fe3d.gfx_isMotionBlurEnabled();
		float strength = _fe3d.gfx_getMotionBlurStrength();

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
			else if (screen->getButton("strength")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("strength", "Strength", strength * 100.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
		}
		
		// Button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");

		// Strength value
		if (_gui.getGlobalScreen()->checkValueForm("strength", strength))
		{
			strength = std::max(0.0f, strength / 100.0f);
		}

		// Disable motion blur
		if (_fe3d.gfx_isMotionBlurEnabled())
		{
			_fe3d.gfx_disableMotionBlur();
		}

		// Enable motion blur
		if (isEnabled)
		{
			_fe3d.gfx_enableMotionBlur(strength);
		}

		// Update buttons hoverability
		screen->getButton("strength")->setHoverable(isEnabled);
	}
}