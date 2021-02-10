#include "environment_editor.hpp"

void EnvironmentEditor::update()
{
	if (_isEditorLoaded)
	{
		// Update main menu
		if (_currentEnvironmentType == EnvironmentType::NONE)
		{
			auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

			// Set default camera view
			_fe3d.camera_setPosition(Vec3(0.0f));
			_fe3d.camera_setYaw(0.0f);
			_fe3d.camera_setPitch(0.0f);
			_fe3d.camera_disableLookatView();

			// Select the default sky
			_fe3d.skyEntity_select("@@engineBackground");

			// No terrain
			_fe3d.terrainEntity_select("");

			// No water
			_fe3d.waterEntity_select("");

			// GUI management
			if (screen->getID() == "environmentEditorMenu")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
				{
					if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
					{
						_gui.getGlobalScreen()->addAnswerForm("exitEnvironmentEditor", "Save changes?", Vec2(0.0f, 0.25f));
					}
					else if (screen->getButton("sky")->isHovered())
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuMain");
						_currentEnvironmentType = EnvironmentType::SKY;
					}
					else if (screen->getButton("terrain")->isHovered())
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuMain");
						_currentEnvironmentType = EnvironmentType::TERRAIN;
					}
					else if (screen->getButton("water")->isHovered())
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMain");
						_currentEnvironmentType = EnvironmentType::WATER;
					}
				}

				// Check if user wants to save changes
				if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitEnvironmentEditor"))
				{
					save();
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
					unload();
				}
				else if (_gui.getGlobalScreen()->isAnswerFormDenied("exitEnvironmentEditor"))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
					unload();
				}
			}
		}
		else
		{
			// Update editors
			_updateSkyEditor();
			_updateTerrainEditor();
			_updateWaterEditor();
		}

		// Update miscellaneous
		_updateMiscellaneous();
	}
}