#include "billboard_editor.hpp"
#include "logger.hpp"

void BillboardEditor::_updateMeshMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "billboardEditorMenuMesh")
	{
		// Temporary values
		auto size = _fe3d.billboardEntity_getSize(_currentBillboardID);
		auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(_currentBillboardID);
		auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(_currentBillboardID);
		auto isReflected = _fe3d.billboardEntity_isReflected(_currentBillboardID);
		auto isShadowed = _fe3d.billboardEntity_isShadowed(_currentBillboardID);
		auto isBright = _fe3d.billboardEntity_isBright(_currentBillboardID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("sizeX", "X", (size.x * 100.0f), Vec2(-0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("sizeY", "Y", (size.y * 100.0f), Vec2(0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
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
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			isShadowed = !isShadowed;
			_fe3d.billboardEntity_setShadowed(_currentBillboardID, isShadowed);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			isReflected = !isReflected;
			_fe3d.billboardEntity_setReflected(_currentBillboardID, isReflected);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			isBright = !isBright;
			_fe3d.billboardEntity_setBright(_currentBillboardID, isBright);
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("sizeX", size.x, { 0.0f }))
		{
			size.x /= 100.0f;
			_fe3d.billboardEntity_setSize(_currentBillboardID, size);
		}
		if (_gui.getGlobalScreen()->checkValueForm("sizeY", size.y, { 0.0f }))
		{
			size.y /= 100.0f;
			_fe3d.billboardEntity_setSize(_currentBillboardID, size);
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
		screen->getButton("isBright")->changeTextContent(isBright ? "Bright: ON" : "Bright : OFF");
		screen->getButton("isReflected")->changeTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isShadowed")->changeTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	}
}