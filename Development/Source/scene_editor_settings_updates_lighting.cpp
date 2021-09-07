#include "scene_editor.hpp"

void SceneEditor::_updateLightingSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuSettingsLighting")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettings");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("ambient")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsLightingAmbient");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("directional")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsLightingDirectional");
		}
	}
}

void SceneEditor::_updateAmbientLightingSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuSettingsLightingAmbient")
	{
		// Temporary values
		bool isEnabled = _fe3d.gfx_isAmbientLightingEnabled();
		Vec3 ambientLightingColor = _fe3d.gfx_getAmbientLightingColor();
		float ambientLightingIntensity = _fe3d.gfx_getAmbientLightingIntensity();

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsLighting");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("enabled")->isHovered())
		{
			isEnabled = !isEnabled;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("ambientColorR", "R", ambientLightingColor.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("ambientColorG", "G", ambientLightingColor.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("ambientColorB", "B", ambientLightingColor.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("ambientIntensity", "Ambient Intensity", (ambientLightingIntensity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("ambientColorR", ambientLightingColor.r))
		{
			ambientLightingColor.r /= 255.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("ambientColorG", ambientLightingColor.g))
		{
			ambientLightingColor.g /= 255.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("ambientColorB", ambientLightingColor.b))
		{
			ambientLightingColor.b /= 255.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("ambientIntensity", ambientLightingIntensity))
		{
			ambientLightingIntensity /= 100.0f;
		}

		// Disable ambient lighting
		if (_fe3d.gfx_isAmbientLightingEnabled())
		{
			_fe3d.gfx_disableAmbientLighting();
		}

		// Enable ambient lighting
		if (isEnabled)
		{
			_fe3d.gfx_enableAmbientLighting(ambientLightingColor, ambientLightingIntensity);
		}

		// Update buttons hoverability
		screen->getButton("color")->setHoverable(isEnabled);
		screen->getButton("intensity")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
	}
}

void SceneEditor::_updateDirectionalLightingSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuSettingsLightingDirectional")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isDirectionalLightingEnabled();
		auto directionalLightingColor = _fe3d.gfx_getDirectionalLightingColor();
		auto directionalLightingPosition = _fe3d.gfx_getDirectionalLightingPosition();
		auto directionalLightingIntensity = _fe3d.gfx_getDirectionalLightingIntensity();
		auto billboardSize = _fe3d.billboardEntity_getSize("@@lightSource").x;

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettingsLighting");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("enabled")->isHovered())
		{
			isEnabled = !isEnabled;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("directionalColorR", "R", directionalLightingColor.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("directionalColorG", "G", directionalLightingColor.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("directionalColorB", "B", directionalLightingColor.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("positionX", "X", directionalLightingPosition.x, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("positionY", "Y", directionalLightingPosition.y, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("positionZ", "Z", directionalLightingPosition.z, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("directionalIntensity", "Directional Intensity", (directionalLightingIntensity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("billboardSize")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("billboardSize", "Billboard Size", billboardSize, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("directionalColorR", directionalLightingColor.r))
		{
			directionalLightingColor.r /= 255.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("directionalColorG", directionalLightingColor.g))
		{
			directionalLightingColor.g /= 255.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("directionalColorB", directionalLightingColor.b))
		{
			directionalLightingColor.b /= 255.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("directionalIntensity", directionalLightingIntensity))
		{
			directionalLightingIntensity /= 100.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("billboardSize", billboardSize))
		{
			billboardSize = max(0.0f, billboardSize);
		}
		_gui.getGlobalScreen()->checkValueForm("positionX", directionalLightingPosition.x);
		_gui.getGlobalScreen()->checkValueForm("positionY", directionalLightingPosition.y);
		_gui.getGlobalScreen()->checkValueForm("positionZ", directionalLightingPosition.z);

		// Update lightsource billboard
		_fe3d.billboardEntity_setPosition("@@lightSource", directionalLightingPosition);
		_fe3d.billboardEntity_setSize("@@lightSource", Vec2(billboardSize));
		_fe3d.billboardEntity_setColor("@@lightSource", directionalLightingColor);

		// Disable directional lighting
		if (_fe3d.gfx_isDirectionalLightingEnabled())
		{
			_fe3d.gfx_disableDirectionalLighting();
		}

		// Enable directional lighting
		if (isEnabled)
		{
			_fe3d.gfx_enableDirectionalLighting(directionalLightingPosition, directionalLightingColor, directionalLightingIntensity);
		}

		// Update buttons hoverability
		screen->getButton("color")->setHoverable(isEnabled);
		screen->getButton("position")->setHoverable(isEnabled);
		screen->getButton("intensity")->setHoverable(isEnabled);
		screen->getButton("billboardSize")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("enabled")->changeTextContent(isEnabled ? "Enabled: YES" : "Enabled: NO");
	}
}