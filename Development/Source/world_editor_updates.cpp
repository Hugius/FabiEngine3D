#include "world_editor.hpp"

void WorldEditor::update()
{
	if (_isLoaded)
	{
		// Update main menu
		if (_currentWorldPart == WorldPart::NONE)
		{
			auto screen = _leftWindow->getScreen("worldEditorMenu");

			// Set default camera view
			_fe3d.camera_setPosition(vec3(0.0f));
			_fe3d.camera_setYaw(0.0f);
			_fe3d.camera_setPitch(0.0f);
			_fe3d.camera_disableLookat();

			// Select the default sky
			_fe3d.skyEntity_select("@@defaultSky");

			// Hide sky
			if (_fe3d.skyEntity_isExisting(_currentSkyID))
			{
				_fe3d.skyEntity_hide(_currentSkyID);
			}

			// Hide terrain
			if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
			{
				_fe3d.terrainEntity_hide(_currentTerrainID);
			}

			// Hide water
			if (_fe3d.waterEntity_isExisting(_currentWaterID))
			{
				_fe3d.waterEntity_hide(_currentWaterID);
			}

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("sky")->isHovered())
				{
					_leftWindow->setActiveScreen("skyEditorMenuMain");
					_currentWorldPart = WorldPart::SKY;
				}
				else if (screen->getButton("terrain")->isHovered())
				{
					_leftWindow->setActiveScreen("terrainEditorMenuMain");
					_currentWorldPart = WorldPart::TERRAIN;
				}
				else if (screen->getButton("water")->isHovered())
				{
					_leftWindow->setActiveScreen("waterEditorMenuMain");
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
				_leftWindow->setActiveScreen("main");
				unload();
			}
			else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitWorldEditor"))
			{
				_leftWindow->setActiveScreen("main");
				unload();
			}
		}
		else
		{
			// Update sub-menus
			_updateSkyMenuMain();
			_updateTerrainMenuMain();
			_updateWaterMenuMain();
		}

		// Update miscellaneous
		_updateSkyCreation();
		_updateSkyChoosing();
		_updateSkyRemoval();
		_updateTerrainCreation();
		_updateTerrainChoosing();
		_updateTerrainRemoval();
		_updateWaterCreation();
		_updateWaterChoosing();
		_updateWaterRemoval();
		_updateMiscellaneous();
	}
}