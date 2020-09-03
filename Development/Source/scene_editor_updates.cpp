#include "scene_editor.hpp"

void SceneEditor::update()
{
	// Model updates
	_updateMainModelMenu();
	_updateModelPlacingMenu();
	_updateModelChoosingMenu();
	_updateModelPlacing();
	_updateModelEditing();

	// Billboard updates
	_updateMainBillboardMenu();
	_updateBilboardPlacingMenu();
	_updateBillboardEditingMenu();

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
	_updateMainMenu();
	_updateCamera();
	_updateMiscellaneous();
}

void SceneEditor::_updateMainMenu()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuMain")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuMain");

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("sceneEditorMenuModel")->isHovered()) // Model button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuModel");
				}
				else if (screen->getButton("sceneEditorMenuBillboard")->isHovered()) // Billboard button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuBillboard");
				}
				else if (screen->getButton("sceneEditorMenuLighting")->isHovered()) // Lighting button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuLighting");
				}
				else if (screen->getButton("sceneEditorMenuSettings")->isHovered()) // Settings button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuSettings");
				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_gui->getGlobalScreen()->addAnswerForm("exitSceneEditor", "Save changes?", vec2(0.0f, 0.25f));
				}
			}

			// Check if user wants to save changes
			if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitSceneEditor"))
			{
				save();
				_leftWindow->setActiveScreen("main");
				unload();
			}
			else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitSceneEditor"))
			{
				_leftWindow->setActiveScreen("main");
				unload();
			}
		}
	}
}

void SceneEditor::_updateCamera()
{
	if (_isLoaded)
	{
		// Camera looking
		if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
		{
			if (_fe3d.misc_isMouseInsideViewport())
			{
				_fe3d.camera_enableFirstPersonView(_fe3d.camera_getMouseSensitivity());
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
			if (_fe3d.misc_isMouseInsideWindow())
			{
				_fe3d.guiEntity_show("@@cursor");
			}
		}

		// Camera movement
		if (!_gui->getGlobalScreen()->isFocused())
		{
			// X movement
			if (_fe3d.input_getKeyDown(Input::KEY_A))
			{
				_fe3d.camera_translateFollowX(-_customCameraSpeed);
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_D))
			{
				_fe3d.camera_translateFollowX(_customCameraSpeed);
			}

			// Y movement
			if (_fe3d.input_getKeyDown(Input::KEY_SPACE))
			{
				_fe3d.camera_translate(vec3(0.0f, _customCameraSpeed / 50.0f, 0.0f));
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT))
			{
				_fe3d.camera_translate(vec3(0.0f, -(_customCameraSpeed / 50.0f), 0.0f));
			}

			// Z movement
			if (_fe3d.input_getKeyDown(Input::KEY_W))
			{
				_fe3d.camera_translateFollowZ(_customCameraSpeed);
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_S))
			{
				_fe3d.camera_translateFollowZ(-_customCameraSpeed);
			}
		}
	}
}