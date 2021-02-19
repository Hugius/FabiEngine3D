#include "scene_editor.hpp"

void SceneEditor::_updateMainEnvironmentMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuEnvironment")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				}
				else if (screen->getButton("sky")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuEnvironmentSky");
				}
				else if (screen->getButton("terrain")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuEnvironmentTerrain");
				}
				else if (screen->getButton("water")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuEnvironmentWater");
				}
			}
		}
	}
}

void SceneEditor::_updateSkyMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuEnvironmentSky")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuEnvironment");
				}
				else if (screen->getButton("choose")->isHovered())
				{
					// Retrieve created skies
					vector<string> skyNames;
					for (auto& name : _environmentEditor.getLoadedSkyIDs())
					{ 
						// Check if not engine sky & not scene editor sky
						if (name[0] == '@' && name.substr(0, 2) != "@@")
						{
							skyNames.push_back(name.substr(1));
						}
					}

					// Add choice list
					_gui.getGlobalScreen()->addChoiceForm("skyList", "Select sky", Vec2(-0.4f, 0.1f), skyNames);
				}
				else if (screen->getButton("delete")->isHovered())
				{
					_fe3d.skyEntity_delete(_currentSkyID);
					_currentSkyID = "";
				}			
			}

			// Update sky choosing
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("skyList");
				if (selectedButtonID != "")
				{
					_currentSkyID = selectedButtonID;
					_placeSky(_currentSkyID, "@" + selectedButtonID);
					_gui.getGlobalScreen()->removeChoiceForm("skyList");
				}
				else if (_gui.getGlobalScreen()->isChoiceFormCancelled("skyList"))
				{
					_gui.getGlobalScreen()->removeChoiceForm("skyList");
				}
			}

			// Buttons hoverability
			screen->getButton("delete")->setHoverable(_currentSkyID != "");

			// Update sky selection
			_fe3d.skyEntity_select(_currentSkyID);
		}
	}
}

void SceneEditor::_updateTerrainMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuEnvironmentTerrain")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuEnvironment");
				}
				else if (screen->getButton("choose")->isHovered())
				{
					// Retrieve created skies
					vector<string> terrainNames;
					for (auto& name : _environmentEditor.getLoadedTerrainIDs())
					{
						// Check if not engine terrain & not scene editor terrain
						if (name[0] == '@' && name.substr(0, 2) != "@@")
						{
							terrainNames.push_back(name.substr(1));
						}
					}

					// Add choice list
					_gui.getGlobalScreen()->addChoiceForm("terrainList", "Select terrain", Vec2(-0.4f, 0.1f), terrainNames);
				}
				else if (screen->getButton("delete")->isHovered())
				{
					_fe3d.terrainEntity_delete(_currentTerrainID);
					_currentTerrainID = "";
				}
			}

			// Update terrain choosing
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("terrainList");
				if (selectedButtonID != "")
				{
					_currentTerrainID = selectedButtonID;
					_placeTerrain(_currentTerrainID, "@" + selectedButtonID);
					_gui.getGlobalScreen()->removeChoiceForm("terrainList");
				}
				else if (_gui.getGlobalScreen()->isChoiceFormCancelled("terrainList"))
				{
					_gui.getGlobalScreen()->removeChoiceForm("terrainList");
				}
			}

			// Update terrain selection
			_fe3d.terrainEntity_select(_currentTerrainID);

			// Buttons hoverability
			screen->getButton("delete")->setHoverable(_currentTerrainID != "");
		}

		// Terrain raycasting
		if (_fe3d.terrainEntity_getSelectedID().empty())
		{
			_fe3d.misc_disableTerrainRaycasting();
		}
		else
		{
			_fe3d.misc_enableTerrainRaycasting(_fe3d.terrainEntity_getSize(_fe3d.terrainEntity_getSelectedID()), 0.1f);
		}
	}
}

void SceneEditor::_updateWaterMenu()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "sceneEditorMenuEnvironmentWater")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuEnvironment");
				}
				else if (screen->getButton("choose")->isHovered())
				{
					// Retrieve created skies
					vector<string> waterNames;
					for (auto& name : _environmentEditor.getLoadedWaterIDs())
					{
						// Check if not engine water & not scene editor water
						if (name[0] == '@' && name.substr(0, 2) != "@@")
						{
							waterNames.push_back(name.substr(1));
						}
					}

					// Add choice list
					_gui.getGlobalScreen()->addChoiceForm("waterList", "Select water", Vec2(-0.4f, 0.1f), waterNames);
				}
				else if (screen->getButton("delete")->isHovered())
				{
					_fe3d.waterEntity_delete(_currentWaterID);
					_currentWaterID = "";
				}
			}

			// Update water choosing
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("waterList");
				if (selectedButtonID != "")
				{
					_currentWaterID = selectedButtonID;
					_placeWater(_currentWaterID, "@" + selectedButtonID);
					_gui.getGlobalScreen()->removeChoiceForm("waterList");
				}
				else if (_gui.getGlobalScreen()->isChoiceFormCancelled("waterList"))
				{
					_gui.getGlobalScreen()->removeChoiceForm("waterList");
				}
			}

			// Buttons hoverability
			screen->getButton("delete")->setHoverable(_currentWaterID != "");

			// Update water selection
			_fe3d.waterEntity_select(_currentWaterID);
		}
	}
}