#include "world_editor.hpp"

void WorldEditor::_updateAmbientLightingSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsLightingAmbient")
	{
		bool isEnabled = _fe3d->graphics_isAmbientLightingEnabled();
		fvec3 color = _fe3d->graphics_getAmbientLightingColor();
		float intensity = _fe3d->graphics_getAmbientLightingIntensity();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsLighting");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->graphics_setAmbientLightingEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->createValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("colorR", color.r))
		{
			color.r /= 255.0f;
			_fe3d->graphics_setAmbientLightingColor(color);
		}
		if(_gui->getOverlay()->checkValueForm("colorG", color.g))
		{
			color.g /= 255.0f;
			_fe3d->graphics_setAmbientLightingColor(color);
		}
		if(_gui->getOverlay()->checkValueForm("colorB", color.b))
		{
			color.b /= 255.0f;
			_fe3d->graphics_setAmbientLightingColor(color);
		}
		if(_gui->getOverlay()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d->graphics_setAmbientLightingIntensity(intensity);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}

void WorldEditor::_updateDirectionalLightingSettingsMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSettingsLightingDirectional")
	{
		auto isEnabled = _fe3d->graphics_isDirectionalLightingEnabled();
		auto color = _fe3d->graphics_getDirectionalLightingColor();
		auto position = _fe3d->graphics_getDirectionalLightingPosition();
		auto intensity = _fe3d->graphics_getDirectionalLightingIntensity();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuSettingsLighting");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEnabled")->isHovered())
		{
			isEnabled = !isEnabled;
			_fe3d->graphics_setDirectionalLightingEnabled(isEnabled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->createValueForm("positionX", "X", position.x, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("positionY", "Y", position.y, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("positionZ", "Z", position.z, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->createValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("intensity", "Intensity", (intensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("positionX", position.x))
		{
			_fe3d->graphics_setDirectionalLightingPosition(position);
		}
		if(_gui->getOverlay()->checkValueForm("positionY", position.y))
		{
			_fe3d->graphics_setDirectionalLightingPosition(position);
		}
		if(_gui->getOverlay()->checkValueForm("positionZ", position.z))
		{
			_fe3d->graphics_setDirectionalLightingPosition(position);
		}
		if(_gui->getOverlay()->checkValueForm("colorR", color.r))
		{
			color.r /= 255.0f;
			_fe3d->graphics_setDirectionalLightingColor(color);
		}
		if(_gui->getOverlay()->checkValueForm("colorG", color.g))
		{
			color.g /= 255.0f;
			_fe3d->graphics_setDirectionalLightingColor(color);
		}
		if(_gui->getOverlay()->checkValueForm("colorB", color.b))
		{
			color.b /= 255.0f;
			_fe3d->graphics_setDirectionalLightingColor(color);
		}
		if(_gui->getOverlay()->checkValueForm("intensity", intensity))
		{
			intensity /= 100.0f;
			_fe3d->graphics_setDirectionalLightingIntensity(intensity);
		}

		screen->getButton("isEnabled")->setTextContent(isEnabled ? "Enabled: ON" : "Enabled: OFF");
	}
}