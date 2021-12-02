#include "world_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void WorldEditor::update()
{
	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSkyMenu();
	}
	if(_isEditorLoaded)
	{
		_updateTerrainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateWaterMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelPlacingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateModelEditing();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardPlacingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardEditing();
	}
	if(_isEditorLoaded)
	{
		_updateSoundMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSoundPlacingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSoundChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSoundPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateSoundEditing();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightMenu();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightPlacing();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightEditing();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightEditing();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionMenu();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionEditing();
	}
	if(_isEditorLoaded)
	{
		_updateSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateLightingSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateAmbientLightingSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateDirectionalLightingSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateShadowGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateMotionBlurGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateDofGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateFogGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateLensFlareGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSkyExposureGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBloomGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateCamera();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

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

void WorldEditor::_updateCamera()
{
	if(_currentWorldID != "")
	{
		// Camera looking
		if(_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT) && !_gui.getGlobalScreen()->isFocused())
		{
			// Enable first person view
			if(_fe3d.misc_isCursorInsideViewport() && !_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.camera_enableFirstPersonView(_fe3d.camera_getFirstPersonYaw(), _fe3d.camera_getFirstPersonPitch());
			}

			// Disable cursor while in FPS mode
			if(_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.image_setVisible("@@cursor", false);
			}
		}
		else
		{
			// Disable first person view
			if(_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.camera_disableFirstPersonView();
			}

			// Cannot show cursor if outside of engine window
			if(_fe3d.misc_isCursorInsideWindow())
			{
				_fe3d.image_setVisible("@@cursor", true);
			}
		}

		// Camera movement
		if(!_gui.getGlobalScreen()->isFocused())
		{
			// X movement
			if(_fe3d.input_isKeyDown(InputType::KEY_A))
			{
				_fe3d.camera_moveFollowX(-_editorSpeed / 100.0f);
			}
			if(_fe3d.input_isKeyDown(InputType::KEY_D))
			{
				_fe3d.camera_moveFollowX(_editorSpeed / 100.0f);
			}

			// Y movement
			if(_fe3d.input_isKeyDown(InputType::KEY_SPACE))
			{
				_fe3d.camera_move(fvec3(0.0f, _editorSpeed / 75.0f, 0.0f));
			}
			if(_fe3d.input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_isKeyDown(InputType::KEY_RSHIFT))
			{
				_fe3d.camera_move(fvec3(0.0f, -(_editorSpeed / 75.0f), 0.0f));
			}

			// Z movement
			if(_fe3d.input_isKeyDown(InputType::KEY_W))
			{
				_fe3d.camera_moveFollowZ(_editorSpeed / 100.0f);
			}
			if(_fe3d.input_isKeyDown(InputType::KEY_S))
			{
				_fe3d.camera_moveFollowZ(-_editorSpeed / 100.0f);
			}
		}
	}
	else
	{
		// Reset camera view
		_fe3d.camera_setYaw(0.0f);
		_fe3d.camera_setPitch(0.0f);
	}
}