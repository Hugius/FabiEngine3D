#include "world_editor.hpp"


void WorldEditor::update(float delta)
{
	if (_isLoaded)
	{
		if (_currentWorldPart == WorldPart::NONE)
		{
			auto screen = _window->getScreen("worldManagement");
			_delta = delta;

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
					_window->setActiveScreen("skyManagement");
					_currentWorldPart = WorldPart::SKY;

					// Show sky
					if (_fe3d.skyEntity_isExisting("@sky"))
					{
						_fe3d.skyEntity_show("@sky");
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
				}
				else if (screen->getButton("terrain")->isHovered())
				{
					_window->setActiveScreen("terrainManagement");
					_currentWorldPart = WorldPart::TERRAIN;

					// Show sky
					if (_fe3d.skyEntity_isExisting("@sky"))
					{
						_fe3d.skyEntity_show("@sky");
					}

					// Show terrain
					if (_fe3d.terrainEntity_isExisting("@terrain"))
					{
						_fe3d.terrainEntity_show("@terrain");
					}

					// Hide water
					if (_fe3d.waterEntity_isExisting("@water"))
					{
						_fe3d.waterEntity_hide("@water");
					}
				}
				else if (screen->getButton("water")->isHovered())
				{
					_window->setActiveScreen("waterManagement");
					_currentWorldPart = WorldPart::WATER;

					// Show sky
					if (_fe3d.skyEntity_isExisting("@sky"))
					{
						_fe3d.skyEntity_show("@sky");
					}

					// Show terrain
					if (_fe3d.terrainEntity_isExisting("@terrain"))
					{
						_fe3d.terrainEntity_show("@terrain");
					}

					// Show water
					if (_fe3d.waterEntity_isExisting("@water"))
					{
						_fe3d.waterEntity_show("@water");
					}
				}
				else if (screen->getButton("back")->isHovered())
				{
					_window->setActiveScreen("main");
					unload();
				}
			}
		}
		else
		{
			// Update sub-menus
			_upateSkyManagement();
			_upateTerrainManagement();
			_upateWaterManagement();
			_updateMiscellaneous();
		}
	}
}