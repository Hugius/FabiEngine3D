#include "environment_editor.hpp"

void EnvironmentEditor::update()
{
	if (_isEditorLoaded)
	{
		// Update main menu
		if (_isInMainMenu)
		{
			// Temporary values
			auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

			// Select the default sky
			_fe3d.skyEntity_select("@@engineBackground");

			// No terrain
			_fe3d.terrainEntity_select("");

			// No water
			_fe3d.waterEntity_select("");

			// GUI management
			if (screen->getID() == "environmentEditorMenu")
			{
				// Check if input received
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
				{
					if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
					{
						_gui.getGlobalScreen()->addAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
					}
					else if (screen->getButton("sky")->isHovered())
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuMain");
						_currentEnvironmentType = EnvironmentType::SKY;
						_isInMainMenu = false;
					}
					else if (screen->getButton("terrain")->isHovered())
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuMain");
						_currentEnvironmentType = EnvironmentType::TERRAIN;
						_isInMainMenu = false;
					}
					else if (screen->getButton("water")->isHovered())
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMain");
						_currentEnvironmentType = EnvironmentType::WATER;
						_isInMainMenu = false;
					}
				}

				// Check if user wants to save changes
				if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
				{
					saveSkyEntitiesToFile();
					saveTerrainEntitiesToFile();
					saveWaterEntitiesToFile();
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
					unload();
				}
				else if (_gui.getGlobalScreen()->isAnswerFormDenied("exit"))
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