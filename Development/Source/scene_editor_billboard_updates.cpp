#include "scene_editor.hpp"

void SceneEditor::_updateMainBillboardMenu()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuBillboard")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuBillboard");

			// GUI management
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Back button
				if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuMain");
				}
			}
		}
	}
}