#include "billboard_editor.hpp"
#include "logger.hpp"

void BillboardEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "billboardEditorMenuMiscellaneous")
	{
		auto size = _fe3d->billboard_getSize(_currentBillboardID);
		auto isFacingX = _fe3d->billboard_isFacingCameraX(_currentBillboardID);
		auto isFacingY = _fe3d->billboard_isFacingCameraY(_currentBillboardID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->createValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFacingX")->isHovered())
		{
			isFacingX = !isFacingX;
			_fe3d->billboard_setFacingCameraX(_currentBillboardID, isFacingX);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFacingY")->isHovered())
		{
			isFacingY = !isFacingY;
			_fe3d->billboard_setFacingCameraY(_currentBillboardID, isFacingY);
		}

		if(_gui->getOverlay()->checkValueForm("sizeX", size.x, {0.0f}))
		{
			size.x /= 100.0f;
			_fe3d->billboard_setSize(_currentBillboardID, size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeY", size.y, {0.0f}))
		{
			size.y /= 100.0f;
			_fe3d->billboard_setSize(_currentBillboardID, size);
		}

		fvec3 rotation = _fe3d->billboard_getRotation(_currentBillboardID);
		if(!isFacingX)
		{
			rotation.x = 0.0f;
			rotation.z = 0.0f;
		}
		if(!isFacingY)
		{
			rotation.y = 0.0f;
		}
		_fe3d->billboard_setRotation(_currentBillboardID, rotation);

		screen->getButton("isFacingX")->changeTextContent(isFacingX ? "Facing X: ON" : "Facing X: OFF");
		screen->getButton("isFacingY")->changeTextContent(isFacingY ? "Facing Y: ON" : "Facing Y: OFF");
	}
}