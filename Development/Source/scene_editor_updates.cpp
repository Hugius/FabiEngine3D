#include "scene_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void SceneEditor::update()
{
	// Main updates
	_updateMainMenu();
	_updateChoiceMenu();

	// Environment updates
	_updateEnvironmentMenu();
	_updateSkyMenu();
	_updateTerrainMenu();
	_updateWaterMenu();

	// Model updates
	_updateModelMenu();
	_updateModelPlacingMenu();
	_updateModelChoosingMenu();
	_updateModelPlacing();
	_updateModelEditing();

	// Billboard updates
	_updateBillboardMenu();
	_updateBillboardPlacingMenu();
	_updateBillboardChoosingMenu();
	_updateBillboardPlacing();
	_updateBillboardEditing();

	// Lighting updates
	_updateLightingMenu();
	_updateAmbientLightingMenu();
	_updateDirectionalLightingMenu();
	_updatePointLightingMenu();
	_updateLightPlacing();
	_updateLightEditing();

	// Sound updates
	_updateSoundMenu();
	_updateSoundPlacingMenu();
	_updateSoundChoosingMenu();
	_updateSoundPlacing();
	_updateSoundEditing();

	// Settings updates
	_updateSettingsMenu();
	_updateGraphicsSettingsMenu();
	_updateShadowGraphicsSettingsMenu();
	_updateMotionBlurGraphicsSettingsMenu();
	_updateDofGraphicsSettingsMenu();
	_updateFogGraphicsSettingsMenu();
	_updateLensFlareGraphicsSettingsMenu();
	_updateSkyExposureGraphicsSettingsMenu();
	_updateBloomGraphicsSettingsMenu();

	// Miscellaneous
	_updateCamera();
	_updateMiscellaneous();
}

void SceneEditor::_updateMainMenu()
{
	if (_isEditorLoaded)
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
				}
				else if (screen->getButton("add")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("newSceneName", "New Scene Name", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
				}
				else if (screen->getButton("edit")->isHovered())
				{
					_isChoosingScene = true;
					auto IDs = _loadSceneIDs();
					std::sort(IDs.begin(), IDs.end());
					_gui.getGlobalScreen()->addChoiceForm("sceneList", "Select Scene", Vec2(0.0f, 0.1f), IDs);
				}
				else if (screen->getButton("delete")->isHovered())
				{
					_isDeletingScene = true;
					auto IDs = _loadSceneIDs();
					std::sort(IDs.begin(), IDs.end());
					_gui.getGlobalScreen()->addChoiceForm("sceneList", "Select Scene", Vec2(0.0f, 0.1f), IDs);
				}
			}

			// Update scene creation
			string newSceneName;
			if (_gui.getGlobalScreen()->checkValueForm("newSceneName", newSceneName, {}))
			{
				auto sceneNames = _loadSceneIDs();

				// If scene name not existing yet
				if (std::find(sceneNames.begin(), sceneNames.end(), newSceneName) == sceneNames.end())
				{
					// Disable engine background
					_fe3d.skyEntity_selectMainSky("");

					// Create new scene
					_currentSceneID = newSceneName;
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				}
				else
				{
					Logger::throwWarning("Scene name \"" + newSceneName + "\" already exists!");
				}
			}

			// Update scene choice
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("sceneList");
				if (selectedButtonID != "")
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
						_gui.getGlobalScreen()->addAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
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
}

void SceneEditor::_updateChoiceMenu()
{
	if (_isEditorLoaded)
	{
		// Temporary values
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();
		
		// GUI management
		if (screen->getID() == "sceneEditorMenuChoice")
		{
			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_gui.getGlobalScreen()->addAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
				}
				else if (screen->getButton("environment")->isHovered()) // Environment button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuEnvironment");
				}
				else if (screen->getButton("model")->isHovered()) // Model button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModel");
				}
				else if (screen->getButton("billboard")->isHovered()) // Billboard button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuBillboard");
				}
				else if (screen->getButton("lighting")->isHovered()) // Lighting button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuLighting");
				}
				else if (screen->getButton("sound")->isHovered()) // Sound button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSound");
				}
				else if (screen->getButton("settings")->isHovered()) // Settings button
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuSettings");
				}
			}

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
			{
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
}

void SceneEditor::_updateCamera()
{
	if (_isEditorLoaded)
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
}