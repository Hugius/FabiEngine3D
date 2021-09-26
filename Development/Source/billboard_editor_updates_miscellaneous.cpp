#include "billboard_editor.hpp"
#include "logger.hpp"

void BillboardEditor::_updateMiscellaneousMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "billboardEditorMenuMiscellaneous")
	{
		// Temporary values
		auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(_currentBillboardID);
		auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(_currentBillboardID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("facingX")->isHovered())
		{
			isFacingX = !isFacingX;
			_fe3d.billboardEntity_setCameraFacingX(_currentBillboardID, isFacingX);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("facingY")->isHovered())
		{
			isFacingY = !isFacingY;
			_fe3d.billboardEntity_setCameraFacingY(_currentBillboardID, isFacingY);
		}

		// Reset rotations if not facing camera
		Vec3 rotation = _fe3d.billboardEntity_getRotation(_currentBillboardID);
		if (!isFacingX)
		{
			rotation.x = 0.0f;
			rotation.z = 0.0f;
		}
		if (!isFacingY)
		{
			rotation.y = 0.0f;
		}
		_fe3d.billboardEntity_setRotation(_currentBillboardID, rotation);

		// Update button text contents
		screen->getButton("facingX")->changeTextContent(isFacingX ? "Facing X: ON" : "Facing X: OFF");
		screen->getButton("facingY")->changeTextContent(isFacingY ? "Facing Y: ON" : "Facing Y: OFF");
	}
}