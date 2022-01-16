#include "sky_editor.hpp"

void SkyEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "skyEditorMenuMiscellaneous")
	{
		float rotation = _fe3d->sky_getRotation(_currentSkyID);
		float lightness = _fe3d->sky_getLightness(_currentSkyID);
		fvec3 color = _fe3d->sky_getColor(_currentSkyID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
		{
			_gui->getOverlay()->createValueForm("rotation", "Rotation", rotation * 1000.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->createValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->createValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("rotation", rotation))
		{
			_fe3d->sky_setRotation(_currentSkyID, rotation);
		}
		if(_gui->getOverlay()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d->sky_setLightness(_currentSkyID, lightness);
		}
		if(_gui->getOverlay()->checkValueForm("colorR", color.r))
		{
			color.r /= 255.0f;
			_fe3d->sky_setColor(_currentSkyID, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorG", color.g))
		{
			color.g /= 255.0f;
			_fe3d->sky_setColor(_currentSkyID, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorB", color.b))
		{
			color.b /= 255.0f;
			_fe3d->sky_setColor(_currentSkyID, color);
		}
	}
}