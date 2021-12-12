#include "world_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void WorldEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuMain")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			unload();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("worldCreate", "Create World", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_isChoosingWorld = true;
			auto IDs = _getWorldIDs();
			sort(IDs.begin(), IDs.end());
			_gui.getGlobalScreen()->createChoiceForm("worldList", "Edit World", fvec2(0.0f, 0.1f), IDs);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_isDeletingWorld = true;
			auto IDs = _getWorldIDs();
			sort(IDs.begin(), IDs.end());
			_gui.getGlobalScreen()->createChoiceForm("worldList", "Delete World", fvec2(0.0f, 0.1f), IDs);
		}

		// Check if user filled in a new ID
		string newWorldName;
		if(_gui.getGlobalScreen()->checkValueForm("worldCreate", newWorldName, {}))
		{
			auto worldNames = _getWorldIDs();

			// If world ID not existing yet
			if(find(worldNames.begin(), worldNames.end(), newWorldName) == worldNames.end())
			{
				// Unselect background
				_fe3d.sky_selectMainSky("");

				// Create new world
				_currentWorldID = newWorldName;
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			}
			else
			{
				Logger::throwWarning("World with ID \"" + newWorldName + "\" already exists!");
			}
		}

		// Update world choice
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("worldList");
			if(!selectedButtonID.empty())
			{
				_currentWorldID = selectedButtonID;

				// Load selected world for editing
				if(_isChoosingWorld)
				{
					// Unselect background
					_fe3d.sky_selectMainSky("");

					// Try to load world
					if(loadEditorWorldFromFile(_currentWorldID))
					{
						// Change GUI
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
					}
					else
					{
						// Select background
						_fe3d.sky_selectMainSky("@@background");
					}
				}
				else if(_isDeletingWorld) // Prepare deleting confirmation
				{
					_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("worldList");
				_isChoosingWorld = false;
			}
			else if(_gui.getGlobalScreen()->isChoiceFormCancelled("worldList"))
			{
				_gui.getGlobalScreen()->deleteChoiceForm("worldList");
			}
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			_deleteWorldFile(_currentWorldID);
			_isDeletingWorld = false;
			_currentWorldID = "";
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isDeletingWorld = false;
			_currentWorldID = "";
		}
	}
}

void WorldEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "worldEditorMenuChoice")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("sky")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSky");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("terrain")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuTerrain");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("water")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuWater");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("models")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuModel");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("billboards")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuBillboard");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("sounds")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSound");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("pointlights")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("spotlights")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSpotlight");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflections")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuReflection");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("settings")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuSettings");
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			// Stop placing
			_currentPreviewModelID = "";
			_currentPreviewBillboardID = "";
			_currentPreviewSoundID = "";
			_isPlacingPointlight = false;
			_isPlacingSpotlight = false;
			_isPlacingReflection = false;

			// Save before closing
			saveEditorWorldToFile();

			// Clear whole world
			clearCurrentWorld();

			// Select background
			_fe3d.sky_selectMainSky("@@background");

			// No selected world
			_currentWorldID = "";
			_currentSkyID = "";
			_currentTerrainID = "";
			_currentWaterID = "";

			// Go to main menu
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuMain");
			return;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			// Stop placing
			_currentPreviewModelID = "";
			_currentPreviewBillboardID = "";
			_currentPreviewSoundID = "";
			_isPlacingPointlight = false;
			_isPlacingSpotlight = false;
			_isPlacingReflection = false;

			// Clear whole world
			clearCurrentWorld();

			// Select background
			_fe3d.sky_selectMainSky("@@background");

			// No selected world
			_currentWorldID = "";
			_currentSkyID = "";
			_currentTerrainID = "";
			_currentWaterID = "";

			// Go to main menu
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuMain");
			return;
		}
	}
}