#include "water_editor.hpp"

using std::max;

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
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("size", "Size", waterSize, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("uvRepeat")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("uvRepeat", "UV Repeat", uvRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Update size changes
		if (_gui.getGlobalScreen()->checkValueForm("size", waterSize, { 0.0f }))
		{
			waterSize = max(0.0f, waterSize);
			_fe3d.waterEntity_setSize(_currentWaterID, waterSize);
		}

		// Update uvRepeat changes
		_gui.getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat);
		_fe3d.waterEntity_setUvRepeat(_currentWaterID, uvRepeat);
	}
}