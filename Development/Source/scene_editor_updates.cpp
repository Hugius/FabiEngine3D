#include "scene_editor.hpp"

void SceneEditor::update()
{
	// Main updates
	_updateMainMenu();
	_updateChoiceMenu();

	// Environment updates
	_updateMainEnvironmentMenu();
	_updateSkyMenu();
	_updateTerrainMenu();
	_updateWaterMenu();

	// Model updates
	_updateMainModelMenu();
	_updateModelPlacingMenu();
	_updateModelChoosingMenu();
	_updateModelPlacing();
	_updateModelEditing();

	// Billboard updates
	_updateMainBillboardMenu();
	_updateBilboardPlacingMenu();
	_updateBillboardChoosingMenu();
	_updateBillboardPlacing();
	_updateBillboardEditing();

	// Lighting updates
	_updateMainLightingMenu();
	_updateAmbientLightingMenu();
	_updateDirectionalLightingMenu();
	_updatePointLightingMenu();
	_updateLightPlacing();
	_updateLightEditing();

	// Settings updates
	_updateMainSettingsMenu();
	_updateGraphicsSettingsMenu();
	_updateShadowGraphicsSettingsMenu();
	_updateMotionblurGraphicsSettingsMenu();
	_updateDofGraphicsSettingsMenu();
	_updateFogGraphicsSettingsMenu();
	_updateLensFlareGraphicsSettingsMenu();
	_updateskyHdrGraphicsSettingsMenu();

	// Miscellaneous
	_updateCamera();
	_updateMiscellaneous();
}

void SceneEditor::_updateMainMenu()
{
	if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuMain")
	{
		auto screen = _leftWindow->getScreen("sceneEditorMenuMain");

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("newSceneName", "New scene name", "", vec2(0.0f), vec2(0.5f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_isChoosingScene = true;
				_gui.getGlobalScreen()->addChoiceForm("sceneList", "Select scene", vec2(0.0f, 0.1f), _loadSceneNames());
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_isDeletingScene = true;
				_gui.getGlobalScreen()->addChoiceForm("sceneList", "Select scene", vec2(0.0f, 0.1f), _loadSceneNames());
			}
			else if (screen->getButton("back")->isHovered())
			{
				unload();
				_leftWindow->setActiveScreen("main");
			}
		}

		// Update scene creation
		string newSceneName;
		if (_gui.getGlobalScreen()->checkValueForm("newSceneName", newSceneName, {}))
		{
			auto sceneNames = _loadSceneNames();

			// If scene name not existing yet
			if (std::find(sceneNames.begin(), sceneNames.end(), newSceneName) == sceneNames.end())
			{
				_currentSceneName = newSceneName;
				_leftWindow->setActiveScreen("sceneEditorMenuChoice");
			}
			else
			{
				_fe3d.logger_throwWarning("Scene name \"" + newSceneName + "\" already exists!");
			}
		}

		// Update scene choice
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("sceneList");
			if (selectedButtonID != "")
			{
				_currentSceneName = selectedButtonID;

				// Load selected scene for editing
				if (_isChoosingScene)
				{
					loadScene(_currentSceneName);
					_leftWindow->setActiveScreen("sceneEditorMenuChoice");
				}
				else if (_isDeletingScene) // Prepare deletion confirmation
				{
					_gui.getGlobalScreen()->addAnswerForm("deleteScene", "Are you sure?", vec2(0.0f));
				}

				// Miscellaneous
				_gui.getGlobalScreen()->removeChoiceForm("sceneList");
				_isChoosingScene = false;
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("sceneList"))
			{
				_gui.getGlobalScreen()->removeChoiceForm("sceneList");
			}
		}

		// Update scene deletion if chosen
		if (_isDeletingScene && _currentSceneName != "")
		{
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("deleteScene")) // Confirmed
			{
				_deleteSceneFile(_currentSceneName);
				_isDeletingScene = false;
				_currentSceneName = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormCancelled("deleteScene")) // Cancelled
			{
				_isDeletingScene = false;
				_currentSceneName = "";
			}
		}
	}
}

void SceneEditor::_updateChoiceMenu()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuChoice")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuChoice");

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("environment")->isHovered()) // Environment button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuEnvironment");
				}
				else if (screen->getButton("model")->isHovered()) // Model button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuModel");
				}
				else if (screen->getButton("billboard")->isHovered()) // Billboard button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuBillboard");
				}
				else if (screen->getButton("lighting")->isHovered()) // Lighting button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuLighting");
				}
				else if (screen->getButton("settings")->isHovered()) // Settings button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuSettings");
				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_gui.getGlobalScreen()->addAnswerForm("exitSceneEditor", "Save changes?", vec2(0.0f, 0.25f));
				}
			}

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitSceneEditor"))
			{
				save();
				clearScene();
				_fe3d.skyEntity_select("@@engineBackground");
				_currentSceneName = "";
				_leftWindow->setActiveScreen("sceneEditorMenuMain");
			}
			else if (_gui.getGlobalScreen()->isAnswerFormCancelled("exitSceneEditor"))
			{
				clearScene();
				_fe3d.skyEntity_select("@@engineBackground");
				_currentSceneName = "";
				_leftWindow->setActiveScreen("sceneEditorMenuMain");
			}
		}
	}
}

void SceneEditor::_updateCamera()
{
	if (_isLoaded)
	{
		if (_currentSceneName != "")
		{
			// Camera looking
			if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT) && !_gui.getGlobalScreen()->isFocused())
			{
				if (_fe3d.misc_isCursorInsideViewport())
				{
					_fe3d.camera_enableFirstPersonView();
					_fe3d.camera_disableLookat();
				}

				// Disable cursor while in FPS mode
				if (_fe3d.camera_isFirstPersonViewEnabled())
				{
					_fe3d.guiEntity_hide("@@cursor");
				}
			}
			else
			{
				_fe3d.camera_disableFirstPersonView();

				// Cannot show cursor if outside of engine window
				if (_fe3d.misc_isCursorInsideWindow())
				{
					_fe3d.guiEntity_show("@@cursor");
				}
			}

			// Camera movement
			if (!_gui.getGlobalScreen()->isFocused())
			{
				// X movement
				if (_fe3d.input_getKeyDown(InputType::KEY_A))
				{
					_fe3d.camera_translateFollowX(-_customCameraSpeed);
				}
				else if (_fe3d.input_getKeyDown(InputType::KEY_D))
				{
					_fe3d.camera_translateFollowX(_customCameraSpeed);
				}

				// Y movement
				if (_fe3d.input_getKeyDown(InputType::KEY_SPACE))
				{
					_fe3d.camera_translate(vec3(0.0f, _customCameraSpeed / 50.0f, 0.0f));
				}
				else if (_fe3d.input_getKeyDown(InputType::KEY_LSHIFT))
				{
					_fe3d.camera_translate(vec3(0.0f, -(_customCameraSpeed / 50.0f), 0.0f));
				}

				// Z movement
				if (_fe3d.input_getKeyDown(InputType::KEY_W))
				{
					_fe3d.camera_translateFollowZ(_customCameraSpeed);
				}
				else if (_fe3d.input_getKeyDown(InputType::KEY_S))
				{
					_fe3d.camera_translateFollowZ(-_customCameraSpeed);
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