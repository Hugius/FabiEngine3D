#include "scene_editor.hpp"

void SceneEditor::update()
{
	// Model updates
	_updateModelScreen();
	_updateModelPlacingScreen();
	_updateModelChoosingScreen();
	_updateModelPlacing();
	_updateModelEditing();

	// Billboard updates
	_updateBillboardScreen();
	_updateBilboardPlacing();
	_updateBillboardEditing();

	// Light updates
	_updateLightScreen();
	_updateAmbientLightScreen();
	_updateDirectionalLightScreen();
	_updatePointLightScreen();
	_updateLightPlacing();
	_updateLightEditing();

	// Miscellaneous
	_updateManagementScreen();
	_updateCamera();
	_updateMiscellaneous();
}

void SceneEditor::_updateManagementScreen()
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
				else if (screen->getButton("sceneEditorMenuLighting")->isHovered()) // Light button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuLighting");
				}
				else if (screen->getButton("setSpeed")->isHovered()) // Set speed button
				{
					_gui->getGlobalScreen()->addValueForm("setSpeed", "Camera speed", _customCameraSpeed, vec2(0.0f), vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_gui->getGlobalScreen()->addAnswerForm("exitSceneEditor", "Save changes?", vec2(0.0f, 0.25f));
				}
			}

			// Setting camera speed
			_gui->getGlobalScreen()->checkValueForm("setSpeed", _customCameraSpeed, {});

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
				_fe3d.gfx_enableMotionBlur();
				_fe3d.camera_enableFirstPersonView(10.0f);
				_fe3d.camera_disableLookat();
				_fe3d.misc_hideCursor();
			}
		}
		else
		{
			_fe3d.gfx_disableMotionBlur();
			_fe3d.camera_disableFirstPersonView();
			_fe3d.misc_showCursor();
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
