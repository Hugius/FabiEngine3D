#include "scene_editor.hpp"

void SceneEditor::_updateMainSettingsMenu()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuSettings")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuSettings");

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("setSpeed")->isHovered()) // Set speed button
				{
					_gui->getGlobalScreen()->addValueForm("setSpeed", "Camera speed", _customCameraSpeed, vec2(0.0f), vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuMain");
				}
			}

			// Setting camera speed
			_gui->getGlobalScreen()->checkValueForm("setSpeed", _customCameraSpeed, {});
		}
	}
}