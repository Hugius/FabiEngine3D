#include "world_editor.hpp"

void WorldEditor::_updateAmbientLightingSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSettingsLightingAmbient")
	{
		// Temporary values
		bool isEnabled = _fe3d.gfx_isAmbientLightingEnabled();
		fvec3 color = _fe3d.gfx_getAmbientLightingColor();
		float intensity = _fe3d.gfx_getAmbientLightingIntensity();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettingsLighting");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if(isEnabled)
			{
				_fe3d.gfx_enableAmbientLighting();
			}
			else
			{
				_fe3d.gfx_disableAmbientLighting(false);
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("colorR", "R", color.r * 255.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorG", "G", color.g * 255.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorB", "B", color.b * 255.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("intensity", "Ambient Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("colorR", color.r))
		{
			color.r /= 255.0f;
			_fe3d.gfx_setAmbientLightingColor(color);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorG", color.g))
		{
			color.g /= 255.0f;
			_fe3d.gfx_setAmbientLightingColor(color);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorB", color.b))
		{
			color.b /= 255.0f;
			_fe3d.gfx_setAmbientLightingColor(color);
		}
		if(_gui.getGlobalScreen()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d.gfx_setAmbientLightingIntensity(intensity);
		}

		// Update buttons hoverability
		screen->getButton("color")->setHoverable(isEnabled);
		screen->getButton("intensity")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateDirectionalLightingSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuSettingsLightingDirectional")
	{
		// Temporary values
		auto isEnabled = _fe3d.gfx_isDirectionalLightingEnabled();
		auto color = _fe3d.gfx_getDirectionalLightingColor();
		auto position = _fe3d.gfx_getDirectionalLightingPosition();
		auto intensity = _fe3d.gfx_getDirectionalLightingIntensity();
		auto billboardSize = _fe3d.billboard_getSize("@@directionalLightSource").x;

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettingsLighting");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			if(isEnabled)
			{
				_fe3d.gfx_enableDirectionalLighting();
			}
			else
			{
				_fe3d.gfx_disableDirectionalLighting(false);
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("positionX", "X", position.x, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("positionY", "Y", position.y, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("positionZ", "Z", position.z, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("colorR", "R", color.r * 255.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorG", "G", color.g * 255.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorB", "B", color.b * 255.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("intensity", "Directional Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("billboardSize")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("billboardSize", "Billboard Size", billboardSize, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("positionX", position.x))
		{
			_fe3d.gfx_setDirectionalLightingPosition(position);
			_fe3d.billboard_setPosition("@@directionalLightSource", position);
		}
		if(_gui.getGlobalScreen()->checkValueForm("positionY", position.y))
		{
			_fe3d.gfx_setDirectionalLightingPosition(position);
			_fe3d.billboard_setPosition("@@directionalLightSource", position);
		}
		if(_gui.getGlobalScreen()->checkValueForm("positionZ", position.z))
		{
			_fe3d.gfx_setDirectionalLightingPosition(position);
			_fe3d.billboard_setPosition("@@directionalLightSource", position);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorR", color.r))
		{
			color.r /= 255.0f;
			_fe3d.gfx_setDirectionalLightingColor(color);
			_fe3d.billboard_setColor("@@directionalLightSource", color);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorG", color.g))
		{
			color.g /= 255.0f;
			_fe3d.gfx_setDirectionalLightingColor(color);
			_fe3d.billboard_setColor("@@directionalLightSource", color);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorB", color.b))
		{
			color.b /= 255.0f;
			_fe3d.gfx_setDirectionalLightingColor(color);
			_fe3d.billboard_setColor("@@directionalLightSource", color);
		}
		if(_gui.getGlobalScreen()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d.gfx_setDirectionalLightingIntensity(intensity);
		}
		if(_gui.getGlobalScreen()->checkValueForm("billboardSize", billboardSize))
		{
			billboardSize = max(0.0f, billboardSize);
			_fe3d.billboard_setSize("@@directionalLightSource", fvec2(billboardSize));
			_fe3d.billboard_setVisible("@@directionalLightSource", (billboardSize != 0.0f));
		}

		// Update buttons hoverability
		screen->getButton("color")->setHoverable(isEnabled);
		screen->getButton("position")->setHoverable(isEnabled);
		screen->getButton("intensity")->setHoverable(isEnabled);
		screen->getButton("billboardSize")->setHoverable(isEnabled);

		// Update button text contents
		screen->getButton("isEnabled")->changeTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}