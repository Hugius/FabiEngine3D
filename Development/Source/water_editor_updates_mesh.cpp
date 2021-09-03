#include "water_editor.hpp"

void WaterEditor::_updateMeshMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "waterEditorMenuMesh")
	{
		// Temporary values
		float uvRepeat = _fe3d.waterEntity_getUvRepeat(_currentWaterID);
		float waterSize = _fe3d.waterEntity_getSize(_currentWaterID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
				return;
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("size", "Size", waterSize, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("uvRepeat")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("uvRepeat", "UV Repeat", uvRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("size", waterSize, { 0.0f }))
		{
			_fe3d.waterEntity_setSize(_currentWaterID, waterSize);
		}
		if (_gui.getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat))
		{
			_fe3d.waterEntity_setUvRepeat(_currentWaterID, uvRepeat);
		}
	}
}