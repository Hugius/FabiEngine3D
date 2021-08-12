#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateSettingsMenu()
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
				return;
			}
			else if (screen->getButton("graphics")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
			else if (screen->getButton("setSpeed")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("setSpeed", "Camera Speed", _editorSpeed, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("lodDistance")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("lodDistance", "LOD Distance", lodDistance, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("reflectionHeight")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("reflectionHeight", "Scene reflection height", reflectionHeight, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("setSpeed", _editorSpeed, {}))
		{
			_editorSpeed = max(0.0f, _editorSpeed);
		}
		if (_gui.getGlobalScreen()->checkValueForm("lodDistance", lodDistance, {}))
		{
			lodDistance = max(0.0f, lodDistance);
			_fe3d.misc_setLevelOfDetailDistance(lodDistance);
		}
		if (_gui.getGlobalScreen()->checkValueForm("reflectionHeight", reflectionHeight, {}))
		{
			_fe3d.gfx_setSceneReflectionHeight(reflectionHeight);
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
				return;
			}
			else if (screen->getButton("shadows")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsShadows");
				_fe3d.misc_enableShadowFrameRendering();
			}
			else if (screen->getButton("motionBlur")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsMotionBlur");
			}
			else if (screen->getButton("dof")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsDof");
			}
			else if (screen->getButton("fog")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsFog");
			}
			else if (screen->getButton("lensFlare")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsLensFlare");
			}
			else if (screen->getButton("skyExposure")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsSkyExposure");
			}
			else if (screen->getButton("bloom")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsBloom");
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
				return;
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				isEnabled = !isEnabled;
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("size", "Size", size, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("position")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("positionX", "X", position.x, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("positionY", "Y", position.y, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("positionZ", "Z", position.z, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("center")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("centerX", "X", center.x, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("centerY", "Y", center.y, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("centerZ", "Z", center.z, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("follow")->isHovered())
			{
				isFollowingCamera = !isFollowingCamera;
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", lightness * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("interval")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("interval", "Frame Interval", interval, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("size", size))
		{
			size = max(0.0f, size);
		}
		if (_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness = max(0.0f, lightness / 100.0f);
		}
		if (_gui.getGlobalScreen()->checkValueForm("interval", interval))
		{
			interval = max(0, interval);
		}
		_gui.getGlobalScreen()->checkValueForm("positionX", position.x);
		_gui.getGlobalScreen()->checkValueForm("positionY", position.y);
		_gui.getGlobalScreen()->checkValueForm("positionZ", position.z);
		_gui.getGlobalScreen()->checkValueForm("centerX", center.x);
		_gui.getGlobalScreen()->checkValueForm("centerY", center.y);
		_gui.getGlobalScreen()->checkValueForm("centerZ", center.z);

		// Disable shadows
		if (_fe3d.gfx_isShadowsEnabled())
		{
			_fe3d.gfx_disableShadows();
		}

		// Enable shadows
		if (isEnabled)
		{
			_fe3d.gfx_enableShadows(position, center, size, size * 2.0f, lightness, isFollowingCamera, interval);
		}

		// Update buttons hoverability
		screen->getButton("size")->setHoverable(isEnabled);
		screen->getButton("position")->setHoverable(isEnabled);
		screen->getButton("center")->setHoverable(isEnabled);
		screen->getButton("follow")->setHoverable(isEnabled);
		screen->getButton("lightness")->setHoverable(isEnabled);
		screen->getButton("interval")->setHoverable(isEnabled && isFollowingCamera);

		// Update button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
		screen->getButton("follow")->changeTextContent(isFollowingCamera ? "Follow Cam: ON" : "Follow Cam: OFF");
	}
}

void SceneEditor::_updateMotionBlurGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsMotionBlur")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isMotionBlurEnabled();
		auto strength = _fe3d.gfx_getMotionBlurStrength();

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
				return;
			}
			else if (screen->getButton("enabled")->isHovered())
			{
				isEnabled = !isEnabled;
			}
			else if (screen->getButton("strength")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("strength", "Strength", strength * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}
	

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("strength", strength))
		{
			strength = max(0.0f, strength / 100.0f);
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

		// Update button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
	}
}

void SceneEditor::_updateDofGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsDof")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isDofEnabled();
		auto dynamic = _fe3d.gfx_isDofDynamic();
		auto blurDistance = _fe3d.gfx_getDofBlurDistance();
		auto maxDistance = _fe3d.gfx_getaMaxDofDistance();

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
				return;
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
				_gui.getGlobalScreen()->createValueForm("blurDistance", "Blur Distance", blurDistance, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("maxDistance")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("maxDistance", "DOF Distance", maxDistance, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("blurDistance", blurDistance))
		{
			blurDistance = max(0.0f, blurDistance);
		}
		if (_gui.getGlobalScreen()->checkValueForm("maxDistance", maxDistance))
		{
			maxDistance = max(0.0f, maxDistance);
		}

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

		// Update button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
		screen->getButton("dynamic")->changeTextContent(dynamic ? "Dynamic: YES" : "Dynamic: NO");
	}
}