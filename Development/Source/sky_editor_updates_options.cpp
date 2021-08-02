#include "sky_editor.hpp"

#include <algorithm>

using std::max;

void SkyEditor::_updateOptionsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "skyEditorMenuOptions")
	{
		// Temporary values
		float skyRotationSpeed = _fe3d.skyEntity_getRotationSpeed(_currentSkyID);
		float skyLightness = _fe3d.skyEntity_getLightness(_currentSkyID);
		Vec3 skyColor = _fe3d.skyEntity_getColor(_currentSkyID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
			}
			else if (screen->getButton("rotationSpeed")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("rotationSpeed", "Rotation Speed", skyRotationSpeed * 1000.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("lightness", "Lightness", skyLightness * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("colorR", "R", skyColor.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorG", "G", skyColor.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorB", "B", skyColor.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Speed value conversion
		if (_gui.getGlobalScreen()->hasValueFormChanged("rotationSpeed", skyRotationSpeed))
		{
			skyRotationSpeed /= 1000.0f;
		}

		// Lightness value conversion
		if (_gui.getGlobalScreen()->hasValueFormChanged("lightness", skyLightness))
		{
			skyLightness = max(0.0f, skyLightness / 100.0f);
		}

		// Color R values conversion
		if (_gui.getGlobalScreen()->hasValueFormChanged("colorR", skyColor.r))
		{
			skyColor.r = std::clamp(skyColor.r / 255.0f, 0.0f, 1.0f);
		}

		// Color G values conversion
		if (_gui.getGlobalScreen()->hasValueFormChanged("colorG", skyColor.g))
		{
			skyColor.g = std::clamp(skyColor.g / 255.0f, 0.0f, 1.0f);
		}

		// Color B values conversion
		if (_gui.getGlobalScreen()->hasValueFormChanged("colorB", skyColor.b))
		{
			skyColor.b = std::clamp(skyColor.b / 255.0f, 0.0f, 1.0f);
		}

		// Dynamically update sky options
		_fe3d.skyEntity_setRotationSpeed(_currentSkyID, skyRotationSpeed);
		_fe3d.skyEntity_setLightness(_currentSkyID, skyLightness);
		_fe3d.skyEntity_setColor(_currentSkyID, skyColor);
	}
}