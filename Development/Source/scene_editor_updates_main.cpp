#include "scene_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void SceneEditor::update()
{
	if (_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if (_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if (_isEditorLoaded)
	{
		_updateSkyMenu();
	}
	if (_isEditorLoaded)
	{
		_updateTerrainMenu();
	}
	if (_isEditorLoaded)
	{
		_updateWaterMenu();
	}
	if (_isEditorLoaded)
	{
		_updateModelMenu();
	}
	if (_isEditorLoaded)
	{
		_updateModelPlacingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateModelChoosingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateModelPlacing();
	}
	if (_isEditorLoaded)
	{
		_updateModelEditing();
	}
	if (_isEditorLoaded)
	{
		_updateBillboardMenu();
	}
	if (_isEditorLoaded)
	{
		_updateBillboardPlacingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateBillboardChoosingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateBillboardPlacing();
	}
	if (_isEditorLoaded)
	{
		_updateBillboardEditing();
	}
	if (_isEditorLoaded)
	{
		_updateSoundMenu();
	}
	if (_isEditorLoaded)
	{
		_updateSoundPlacingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateSoundChoosingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateSoundPlacing();
	}
	if (_isEditorLoaded)
	{
		_updateSoundEditing();
	}
	if (_isEditorLoaded)
	{
		_updateLightMenu();
	}
	if (_isEditorLoaded)
	{
		_updateLightPlacing();
	}
	if (_isEditorLoaded)
	{
		_updateLightEditing();
	}
	if (_isEditorLoaded)
	{
		_updateReflectionMenu();
	}
	if (_isEditorLoaded)
	{
		_updateReflectionPlacing();
	}
	if (_isEditorLoaded)
	{
		_updateReflectionEditing();
	}
	if (_isEditorLoaded)
	{
		_updateSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateLightingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateAmbientLightingSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateDirectionalLightingSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateGraphicsSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateShadowGraphicsSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateMotionBlurGraphicsSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateDofGraphicsSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateFogGraphicsSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateLensFlareGraphicsSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateSkyExposureGraphicsSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateBloomGraphicsSettingsMenu();
	}
	if (_isEditorLoaded)
	{
		_updateCamera();
	}
	if (_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void SceneEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuMain")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				unload();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
				return;
			}
			else if (screen->getButton("create")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("sceneCreate", "Create Scene", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_isChoosingScene = true;
				auto IDs = _loadSceneIDs();
				sort(IDs.begin(), IDs.end());
				_gui.getGlobalScreen()->createChoiceForm("sceneList", "Edit Scene", Vec2(0.0f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_isDeletingScene = true;
				auto IDs = _loadSceneIDs();
				sort(IDs.begin(), IDs.end());
				_gui.getGlobalScreen()->createChoiceForm("sceneList", "Delete Scene", Vec2(0.0f, 0.1f), IDs);
			}
		}

		// Check if user filled in a new ID
		string newSceneName;
		if (_gui.getGlobalScreen()->checkValueForm("sceneCreate", newSceneName, {}))
		{
			auto sceneNames = _loadSceneIDs();

			// If scene ID not existing yet
			if (find(sceneNames.begin(), sceneNames.end(), newSceneName) == sceneNames.end())
			{
				// Disable engine background
				_fe3d.skyEntity_selectMainSky("");

				// Create new scene
				_currentSceneID = newSceneName;
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
			}
			else
			{
				Logger::throwWarning("Scene with ID \"" + newSceneName + "\" already exists!");
			}
		}

		// Update scene choice
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("sceneList");
			if (!selectedButtonID.empty())
			{
				_currentSceneID = selectedButtonID;

				// Load selected scene for editing
				if (_isChoosingScene)
				{
					// Disable engine background
					_fe3d.skyEntity_selectMainSky("");

					// Try to load scene
					if (loadEditorSceneFromFile(_currentSceneID))
					{
						// Change GUI
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
					}
					else
					{
						// Enable engine background
						_fe3d.skyEntity_selectMainSky("@@engineBackground");
					}
				}
				else if (_isDeletingScene) // Prepare deleting confirmation
				{
					_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("sceneList");
				_isChoosingScene = false;
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("sceneList"))
			{
				_gui.getGlobalScreen()->deleteChoiceForm("sceneList");
			}
		}

		// Update scene deleting if chosen
		if (_isDeletingScene && _currentSceneID != "")
		{
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete")) // Confirmed
			{
				_deleteSceneFile(_currentSceneID);
				_isDeletingScene = false;
				_currentSceneID = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete")) // Cancelled
			{
				_isDeletingScene = false;
				_currentSceneID = "";
			}
		}
	}
}

void SceneEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuChoice")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getGlobalScreen()->createAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
				return;
			}
			else if (screen->getButton("sky")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSky");
			}
			else if (screen->getButton("terrain")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuTerrain");
			}
			else if (screen->getButton("water")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuWater");
			}
			else if (screen->getButton("models")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModel");
			}
			else if (screen->getButton("billboards")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboard");
			}
			else if (screen->getButton("sounds")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSound");
			}
			else if (screen->getButton("lights")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLight");
			}
			else if (screen->getButton("reflections")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuReflection");
			}
			else if (screen->getButton("settings")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettings");
			}
		}

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
		{
			// Stop placing
			_currentPreviewModelID = "";
			_currentPreviewBillboardID = "";
			_currentPreviewSoundID = "";
			_isPlacingLight = false;

			// Save before closing
			saveEditorSceneToFile();

			// Clear whole scene
			clearCurrentScene();

			// Enable engine background
			_fe3d.skyEntity_selectMainSky("@@engineBackground");

			// No selected scene
			_currentSceneID = "";
			_currentSkyID = "";
			_currentTerrainID = "";
			_currentWaterID = "";

			// Go to main menu
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuMain");
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("exit"))
		{
			// Stop placing
			_currentPreviewModelID = "";
			_currentPreviewBillboardID = "";
			_currentPreviewSoundID = "";
			_isPlacingLight = false;

			// Clear whole scene
			clearCurrentScene();

			// Enable engine background
			_fe3d.skyEntity_selectMainSky("@@engineBackground");

			// No selected scene
			_currentSceneID = "";
			_currentSkyID = "";
			_currentTerrainID = "";
			_currentWaterID = "";

			// Go to main menu
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuMain");
		}
	}
}

void SceneEditor::_updateCamera()
{
	if (_currentSceneID != "")
	{
		// Camera looking
		if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT) && !_gui.getGlobalScreen()->isFocused())
		{
			// Enable first person view
			if (_fe3d.misc_isCursorInsideViewport() && !_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.camera_enableFirstPersonView(_fe3d.camera_getFirstPersonYaw(), _fe3d.camera_getFirstPersonPitch());
			}

			// Disable cursor while in FPS mode
			if (_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.imageEntity_setVisible("@@cursor", false);
			}
		}
		else
		{
			// Disable first person view
			if (_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.camera_disableFirstPersonView();
			}

			// Cannot show cursor if outside of engine window
			if (_fe3d.misc_isCursorInsideWindow())
			{
				_fe3d.imageEntity_setVisible("@@cursor", true);
			}
		}

		// Camera movement
		if (!_gui.getGlobalScreen()->isFocused())
		{
			// X movement
			if (_fe3d.input_isKeyDown(InputType::KEY_A))
			{
				_fe3d.camera_moveFollowX(-_editorSpeed / 100.0f);
			}
			else if (_fe3d.input_isKeyDown(InputType::KEY_D))
			{
				_fe3d.camera_moveFollowX(_editorSpeed / 100.0f);
			}

			// Y movement
			if (_fe3d.input_isKeyDown(InputType::KEY_SPACE))
			{
				_fe3d.camera_move(Vec3(0.0f, _editorSpeed / 75.0f, 0.0f));
			}
			else if (_fe3d.input_isKeyDown(InputType::KEY_LSHIFT))
			{
				_fe3d.camera_move(Vec3(0.0f, -(_editorSpeed / 75.0f), 0.0f));
			}

			// Z movement
			if (_fe3d.input_isKeyDown(InputType::KEY_W))
			{
				_fe3d.camera_moveFollowZ(_editorSpeed / 100.0f);
			}
			else if (_fe3d.input_isKeyDown(InputType::KEY_S))
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