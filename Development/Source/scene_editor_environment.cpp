#include "scene_editor.hpp"

void SceneEditor::_updateMainEnvironmentMenu()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuEnvironment")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuEnvironment");

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("sky")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuEnvironmentSky");
				}
				else if (screen->getButton("terrain")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuEnvironmentTerrain");
				}
				else if (screen->getButton("water")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuEnvironmentWater");
				}
				else if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuMain");
				}
			}
		}
	}
}

void SceneEditor::_updateSkyMenu()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuEnvironmentSky")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuEnvironmentSky");

			// Buttons hoverability
			screen->getButton("remove")->setHoverable(_currentSkyID != "");

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("choose")->isHovered())
				{
					// Retrieve created skies
					vector<string> skyNames;
					for (auto& name : _fe3d.skyEntity_getAllIDs()) 
					{ 
						// Check if not engine sky & not scene editor sky
						if (name[0] == '@' && name.substr(0, 2) != "@@")
						{
							skyNames.push_back(name.substr(1));
						}
					}

					// Add choice list
					_gui->getGlobalScreen()->addChoiceForm("skyList", "Select sky", vec2(-0.4f, 0.1f), skyNames);
				}
				else if (screen->getButton("remove")->isHovered())
				{
					_fe3d.skyEntity_delete(_currentSkyID);
					_currentSkyID = "";
				}
				else if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuEnvironment");
				}
			}

			// Update sky choosing
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("skyList");
				if (selectedButtonID != "")
				{
					_currentSkyID = selectedButtonID;
					_placeSky(_currentSkyID, "@" + selectedButtonID);
					_gui->getGlobalScreen()->removeChoiceForm("skyList");
				}
				else if (_gui->getGlobalScreen()->isChoiceFormCancelled("skyList"))
				{
					_gui->getGlobalScreen()->removeChoiceForm("skyList");
				}
			}

			// Update sky selection
			_fe3d.skyEntity_select(_currentSkyID);
		}
	}
}

void SceneEditor::_updateTerrainMenu()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuEnvironmentTerrain")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuEnvironmentTerrain");

			// Buttons hoverability
			screen->getButton("remove")->setHoverable(_currentTerrainID != "");

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("choose")->isHovered())
				{
					// Retrieve created skies
					vector<string> terrainNames;
					for (auto& name : _fe3d.terrainEntity_getAllIDs())
					{
						// Check if not engine terrain & not scene editor terrain
						if (name[0] == '@' && name.substr(0, 2) != "@@")
						{
							terrainNames.push_back(name.substr(1));
						}
					}

					// Add choice list
					_gui->getGlobalScreen()->addChoiceForm("terrainList", "Select terrain", vec2(-0.4f, 0.1f), terrainNames);
				}
				else if (screen->getButton("remove")->isHovered())
				{
					_fe3d.terrainEntity_delete(_currentTerrainID);
					_currentTerrainID = "";
				}
				else if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuEnvironment");
				}
			}

			// Update terrain choosing
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("terrainList");
				if (selectedButtonID != "")
				{
					_currentTerrainID = selectedButtonID;
					_placeTerrain(_currentTerrainID, "@" + selectedButtonID);
					_gui->getGlobalScreen()->removeChoiceForm("terrainList");
				}
				else if (_gui->getGlobalScreen()->isChoiceFormCancelled("terrainList"))
				{
					_gui->getGlobalScreen()->removeChoiceForm("terrainList");
				}
			}

			// Update terrain selection
			_fe3d.terrainEntity_select(_currentTerrainID);
		}
	}
}

void SceneEditor::_updateWaterMenu()
{

}