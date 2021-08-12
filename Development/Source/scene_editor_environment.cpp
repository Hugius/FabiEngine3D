#include "scene_editor.hpp"

void SceneEditor::_updateEnvironmentMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuEnvironment")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				return;
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

void SceneEditor::_updateSkyMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuEnvironmentSky")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuEnvironment");
				return;
			}
			else if (screen->getButton("choose")->isHovered())
			{
				// Retrieve created skies
				vector<string> skyNames;
				for (const auto& ID : _skyEditor.getLoadedSkyIDs())
				{
					// Check if not engine sky & not scene editor sky
					if (ID[0] == '@' && ID.substr(0, 2) != "@@")
					{
						skyNames.push_back(ID.substr(1));
					}
				}

				// Add choice list
				_gui.getGlobalScreen()->createChoiceForm("skyList", "Choose Sky", Vec2(-0.5f, 0.1f), skyNames);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_fe3d.skyEntity_delete(_currentSkyID);
				_currentSkyID = "";
			}
		}

		// Update sky choosing
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("skyList");
			if (selectedButtonID != "")
			{
				// Delete old
				if (_fe3d.skyEntity_isExisting(selectedButtonID))
				{
					_fe3d.skyEntity_delete(selectedButtonID);
				}

				// Create new
				_currentSkyID = selectedButtonID;
				_copyPreviewSky(_currentSkyID, "@" + selectedButtonID);
				_gui.getGlobalScreen()->deleteChoiceForm("skyList");
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("skyList"))
			{
				_gui.getGlobalScreen()->deleteChoiceForm("skyList");
			}
		}

		// Update buttons hoverability
		screen->getButton("delete")->setHoverable(_currentSkyID != "");

		// Update sky selection
		_fe3d.skyEntity_selectMainSky(_currentSkyID);
	}
}

void SceneEditor::_updateTerrainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuEnvironmentTerrain")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuEnvironment");
				return;
			}
			else if (screen->getButton("choose")->isHovered())
			{
				// Retrieve created skies
				vector<string> terrainNames;
				for (const auto& ID : _terrainEditor.getLoadedTerrainIDs())
				{
					// Check if not engine terrain & not scene editor terrain
					if (ID[0] == '@' && ID.substr(0, 2) != "@@")
					{
						terrainNames.push_back(ID.substr(1));
					}
				}

				// Add choice list
				_gui.getGlobalScreen()->createChoiceForm("terrainList", "Choose Terrain", Vec2(-0.5f, 0.1f), terrainNames);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_fe3d.terrainEntity_delete(_currentTerrainID);
				_currentTerrainID = "";
			}
		}

		// Update terrain choosing
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("terrainList");
			if (selectedButtonID != "")
			{
				// Delete old
				if (_fe3d.terrainEntity_isExisting(selectedButtonID))
				{
					_fe3d.terrainEntity_delete(selectedButtonID);
				}

				// Create new
				_currentTerrainID = selectedButtonID;
				_copyPreviewTerrain(_currentTerrainID, "@" + selectedButtonID);
				_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("terrainList"))
			{
				_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
			}
		}

		// Update terrain selection
		_fe3d.terrainEntity_select(_currentTerrainID);

		// Update buttons hoverability
		screen->getButton("delete")->setHoverable(_currentTerrainID != "");
	}
}

void SceneEditor::_updateWaterMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuEnvironmentWater")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuEnvironment");
				return;
			}
			else if (screen->getButton("choose")->isHovered())
			{
				// Retrieve created skies
				vector<string> waterNames;
				for (const auto& ID : _waterEditor.getLoadedWaterIDs())
				{
					// Check if not engine water & not scene editor water
					if (ID[0] == '@' && ID.substr(0, 2) != "@@")
					{
						waterNames.push_back(ID.substr(1));
					}
				}

				// Add choice list
				_gui.getGlobalScreen()->createChoiceForm("waterList", "Choose Water", Vec2(-0.5f, 0.1f), waterNames);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_fe3d.waterEntity_delete(_currentWaterID);
				_currentWaterID = "";
			}
		}

		// Update water choosing
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("waterList");
			if (selectedButtonID != "")
			{
				// Delete old
				if (_fe3d.waterEntity_isExisting(selectedButtonID))
				{
					_fe3d.waterEntity_delete(selectedButtonID);
				}

				// Create new
				_currentWaterID = selectedButtonID;
				_copyPreviewWater(_currentWaterID, "@" + selectedButtonID);
				_gui.getGlobalScreen()->deleteChoiceForm("waterList");
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("waterList"))
			{
				_gui.getGlobalScreen()->deleteChoiceForm("waterList");
			}
		}

		// Update buttons hoverability
		screen->getButton("delete")->setHoverable(_currentWaterID != "");

		// Update water selection
		_fe3d.waterEntity_select(_currentWaterID);
	}
}