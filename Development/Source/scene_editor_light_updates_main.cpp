#include "scene_editor.hpp"

void SceneEditor::_updateLightMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuLight")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				return;
			}
			else if (screen->getButton("place")->isHovered())
			{
				// Deactivate everything
				_deactivateModel();
				_deactivateBillboard();
				_deactivateSound();

				// Set new preview light
				_isPlacingLight = true;
				_fe3d.modelEntity_setPosition(PREVIEW_LAMP_ID, Vec3(0.0f));
				_fe3d.modelEntity_setVisible(PREVIEW_LAMP_ID, true);
				_fe3d.lightEntity_setPosition(PREVIEW_LAMP_ID, Vec3(0.0f));
				_fe3d.lightEntity_setVisible(PREVIEW_LAMP_ID, true);
				_fe3d.misc_centerCursor();

				// Add position value forms for placing without terrain
				if (_fe3d.terrainEntity_getSelectedID().empty())
				{
					_gui.getGlobalScreen()->createValueForm("positionX", "X", 0.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->createValueForm("positionY", "Y", 0.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
					_gui.getGlobalScreen()->createValueForm("positionZ", "Z", 0.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				}
			}
		}
	}
}