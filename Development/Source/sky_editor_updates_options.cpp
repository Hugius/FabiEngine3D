#include "sky_editor.hpp"

void SkyEditor::_updateOptionsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "skyEditorMenuOptions")
	{
		// Temporary values
		float skyRotationSpeed = _fe3d.skyEntity_getRotationSpeed(_currentSkyID);
		float skyLightness = _fe3d.skyEntity_getLightness(_currentSkyID);
		Vec3 skyColor = _fe3d.skyEntity_getColor(_currentSkyID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotationSpeed")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("rotationSpeed", "Rotation Speed", skyRotationSpeed * 1000.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", (skyLightness * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("colorR", "R", skyColor.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorG", "G", skyColor.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorB", "B", skyColor.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("rotationSpeed", skyRotationSpeed))
		{
			skyRotationSpeed /= 1000.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("lightness", skyLightness))
		{
			skyLightness /= 100.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorR", skyColor.r))
		{
			skyColor.r /= 255.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorG", skyColor.g))
		{
			skyColor.g /= 255.0f;
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorB", skyColor.b))
		{
			skyColor.b /= 255.0f;
		}

		// Dynamically update sky options
		_fe3d.skyEntity_setRotationSpeed(_currentSkyID, skyRotationSpeed);
		_fe3d.skyEntity_setLightness(_currentSkyID, skyLightness);
		_fe3d.skyEntity_setColor(_currentSkyID, skyColor);
	}
}