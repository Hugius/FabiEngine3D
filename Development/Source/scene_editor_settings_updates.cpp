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
				if (screen->getButton("graphics")->isHovered()) // Set speed button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuSettingsGraphics");
				}
				else if (screen->getButton("setSpeed")->isHovered()) // Set speed button
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

void SceneEditor::_updateGraphicsSettingsMenu()
{
	if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuSettingsGraphics")
	{
		auto screen = _leftWindow->getScreen("sceneEditorMenuSettingsGraphics");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("shadows")->isHovered())
			{
				
			}
			else if (screen->getButton("motionblur")->isHovered())
			{

			}
			else if (screen->getButton("dof")->isHovered())
			{

			}
			else if (screen->getButton("fog")->isHovered())
			{

			}
			else if (screen->getButton("lensflare")->isHovered())
			{

			}
			else if (screen->getButton("skyHdr")->isHovered())
			{

			}
			else if (screen->getButton("back")->isHovered()) // Back button
			{
				_leftWindow->setActiveScreen("sceneEditorMenuSettings");
			}
		}
	}
}

void SceneEditor::_updateShadowGraphicsSettingsMenu()
{
	if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuSettingsGraphicsShadows")
	{
		auto screen = _leftWindow->getScreen("sceneEditorMenuSettingsGraphicsShadows");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("shadows")->isHovered())
			{

			}
			else if (screen->getButton("back")->isHovered()) // Back button
			{
				_leftWindow->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
		}
	}
}