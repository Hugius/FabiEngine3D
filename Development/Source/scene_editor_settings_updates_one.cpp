#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuSettings")
	{
		// Temporary values
		auto lodDistance = _fe3d.misc_getLevelOfDetailDistance();
		auto reflectionHeight = _fe3d.gfx_getPlanarReflectionHeight();

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsLighting");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("graphics")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("editorSpeed")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("editorSpeed", "Editor Speed", _editorSpeed, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lodDistance")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("lodDistance", "LOD Distance", lodDistance, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("planarHeight")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("planarHeight", "Planar Reflection Height", reflectionHeight, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("editorSpeed", _editorSpeed, {}))
		{
			_editorSpeed = max(0.0f, _editorSpeed);
		}
		if (_gui.getGlobalScreen()->checkValueForm("lodDistance", lodDistance, {}))
		{
			_fe3d.misc_setLevelOfDetailDistance(lodDistance);
		}
		if (_gui.getGlobalScreen()->checkValueForm("planarHeight", reflectionHeight, {}))
		{
			_fe3d.gfx_setPlanarReflectionHeight(reflectionHeight);
		}
	}
}

void SceneEditor::_updateGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuSettingsGraphics")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettings");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("shadows")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsShadows");
			_fe3d.misc_enableShadowFrameRendering();
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("motionBlur")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsMotionBlur");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("dof")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsDof");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("fog")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsFog");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lensFlare")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsLensFlare");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("skyExposure")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsSkyExposure");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("bloom")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphicsBloom");
		}
	}
}

void SceneEditor::_updateShadowGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsShadows")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isShadowsEnabled();
		auto isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();
		auto size = _fe3d.gfx_getShadowSize();
		auto lightness = _fe3d.gfx_getShadowLightness();
		auto position = _fe3d.gfx_getShadowEye();
		auto center = _fe3d.gfx_getShadowCenter();
		auto interval = _fe3d.gfx_getShadowInterval();

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			_fe3d.misc_disableShadowFrameRendering();
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if (isEnabled)
			{
				_fe3d.gfx_enableShadows();
			}
			else
			{
				_fe3d.gfx_disableShadows();
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("size", "Size", size, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("positionX", "X", position.x, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("positionY", "Y", position.y, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("positionZ", "Z", position.z, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("center")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("centerX", "X", center.x, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("centerY", "Y", center.y, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("centerZ", "Z", center.z, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("follow")->isHovered())
		{
			isFollowingCamera = !isFollowingCamera;
			_fe3d.gfx_setShadowFollowingCamera(isFollowingCamera);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", (lightness * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("interval")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("interval", "Frame Interval", interval, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("size", size))
		{
			_fe3d.gfx_setShadowAreaSize(size);
			_fe3d.gfx_setShadowAreaReach(size * 2.0f);
		}
		if (_gui.getGlobalScreen()->checkValueForm("positionX", position.x))
		{
			_fe3d.gfx_setShadowEyePosition(position);
		}
		if (_gui.getGlobalScreen()->checkValueForm("positionY", position.y))
		{
			_fe3d.gfx_setShadowEyePosition(position);
		}
		if (_gui.getGlobalScreen()->checkValueForm("positionZ", position.z))
		{
			_fe3d.gfx_setShadowEyePosition(position);
		}
		if (_gui.getGlobalScreen()->checkValueForm("centerX", center.x))
		{
			_fe3d.gfx_setShadowCenterPosition(center);
		}
		if (_gui.getGlobalScreen()->checkValueForm("centerY", center.y))
		{
			_fe3d.gfx_setShadowCenterPosition(center);
		}
		if (_gui.getGlobalScreen()->checkValueForm("centerZ", center.z))
		{
			_fe3d.gfx_setShadowCenterPosition(center);
		}
		if (_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d.gfx_setShadowLightness(lightness);
		}
		if (_gui.getGlobalScreen()->checkValueForm("interval", interval))
		{
			_fe3d.gfx_setShadowInterval(interval);
		}

		// Update buttons hoverability
		screen->getButton("size")->setHoverable(isEnabled);
		screen->getButton("position")->setHoverable(isEnabled);
		screen->getButton("center")->setHoverable(isEnabled);
		screen->getButton("follow")->setHoverable(isEnabled);
		screen->getButton("lightness")->setHoverable(isEnabled);
		screen->getButton("interval")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
		screen->getButton("follow")->changeTextContent(isFollowingCamera ? "Follow Cam: ON" : "Follow Cam: OFF");
	}
}

void SceneEditor::_updateMotionBlurGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsMotionBlur")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isMotionBlurEnabled();
		auto strength = _fe3d.gfx_getMotionBlurStrength();

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if (isEnabled)
			{
				_fe3d.gfx_enableMotionBlur();
			}
			else
			{
				_fe3d.gfx_disableMotionBlur();
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("strength")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("strength", "Strength", (strength * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
	
		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("strength", strength))
		{
			strength /= 100.0f;
			_fe3d.gfx_setMotionBlurStrength(strength);
		}

		// Update buttons hoverability
		screen->getButton("strength")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
	}
}

void SceneEditor::_updateDofGraphicsSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuSettingsGraphicsDof")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isDofEnabled();
		auto isDynamic = _fe3d.gfx_isDofDynamic();
		auto blurDistance = _fe3d.gfx_getDofBlurDistance();
		auto maxDistance = _fe3d.gfx_getaMaxDofDistance();

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsGraphics");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if (isEnabled)
			{
				_fe3d.gfx_enableDOF();
			}
			else
			{
				_fe3d.gfx_disableDOF();
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("dynamic")->isHovered())
		{
			isDynamic = !isDynamic;
			_fe3d.gfx_setDofDynamic(isDynamic);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blurDistance")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("blurDistance", "Blur Distance", blurDistance, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxDistance")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("maxDistance", "Max Distance", maxDistance, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("blurDistance", blurDistance))
		{
			_fe3d.gfx_setDofBlurDistance(blurDistance);
		}
		if (_gui.getGlobalScreen()->checkValueForm("maxDistance", maxDistance))
		{
			_fe3d.gfx_setDofMaxDistance(maxDistance);
		}

		// Update buttons hoverability
		screen->getButton("dynamic")->setHoverable(isEnabled);
		screen->getButton("blurDistance")->setHoverable(isEnabled);
		screen->getButton("maxDistance")->setHoverable(isEnabled && isDynamic);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
		screen->getButton("dynamic")->changeTextContent(isDynamic ? "Dynamic: YES" : "Dynamic: NO");
	}
}