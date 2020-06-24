#include "world_editor.hpp"

void WorldEditor::update()
{
	if (_isLoaded)
	{
		if (_currentWorldPart == WorldPart::NONE)
		{
			auto screen = _window->getScreen("worldManagement");

			// Select the default sky
			_fe3d.skyEntity_select("@defaultSky");

			// Hide sky
			if (_fe3d.skyEntity_isExisting("@sky"))
			{
				_fe3d.skyEntity_hide("@sky");
			}

			// Hide terrain
			if (_fe3d.terrainEntity_isExisting("@terrain"))
			{
				_fe3d.terrainEntity_hide("@terrain");
			}

			// Hide water
			if (_fe3d.waterEntity_isExisting("@water"))
			{
				_fe3d.waterEntity_hide("@water");
			}

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("sky")->isHovered())
				{
					_window->setActiveScreen("skyMenu");
					_currentWorldPart = WorldPart::SKY;
				}
				else if (screen->getButton("terrain")->isHovered())
				{
					_window->setActiveScreen("terrainMenu");
					_currentWorldPart = WorldPart::TERRAIN;
				}
				else if (screen->getButton("water")->isHovered())
				{
					_window->setActiveScreen("waterMenu");
					_currentWorldPart = WorldPart::WATER;
				}
				else if (screen->getButton("back")->isHovered())
				{
					_gui->getGlobalScreen()->addAnswerForm("exitWorldEditor", "Save changes?", vec2(0.0f, 0.25f));
				}
			}

			// Check if user wants to save changes
			if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitWorldEditor"))
			{
				save();
				_window->setActiveScreen("main");
				unload();
			}
			else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitWorldEditor"))
			{
				_window->setActiveScreen("main");
				unload();
			}
		}
		else
		{
			// Update sub-menus
			_updateSkyMenu();
			_updateTerrainMenu();
			_updateWaterMenu();
		}
	}
}