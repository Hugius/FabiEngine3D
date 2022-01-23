#include "text3d_editor.hpp"
#include "logger.hpp"

void Text3dEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "text3dEditorMenuMiscellaneous")
	{
		auto size = _fe3d->text3d_getSize(_currentTextID);
		auto isFacingX = _fe3d->text3d_isFacingCameraX(_currentTextID);
		auto isFacingY = _fe3d->text3d_isFacingCameraY(_currentTextID);
		auto opacity = _fe3d->text3d_getOpacity(_currentTextID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");
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
			_fe3d->text3d_setFacingCameraX(_currentTextID, isFacingX);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFacingY")->isHovered())
		{
			isFacingY = !isFacingY;
			_fe3d->text3d_setFacingCameraY(_currentTextID, isFacingY);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("sizeX", size.x, {0.0f}))
		{
			size.x /= 100.0f;
			_fe3d->text3d_setSize(_currentTextID, size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeY", size.y, {0.0f}))
		{
			size.y /= 100.0f;
			_fe3d->text3d_setSize(_currentTextID, size);
		}
		if(_gui->getOverlay()->checkValueForm("opacity", opacity, {0.0f}))
		{
			opacity /= 100.0f;
			_fe3d->text3d_setOpacity(_currentTextID, opacity);
		}

		screen->getButton("isFacingX")->changeTextContent(isFacingX ? "Facing X: ON" : "Facing X: OFF");
		screen->getButton("isFacingY")->changeTextContent(isFacingY ? "Facing Y: ON" : "Facing Y: OFF");

		auto rotation = _fe3d->text3d_getRotation(_currentTextID);
		if(!isFacingX)
		{
			rotation.x = 0.0f;
			rotation.z = 0.0f;
		}
		if(!isFacingY)
		{
			rotation.y = 0.0f;
		}
		_fe3d->text3d_setRotation(_currentTextID, rotation);
	}
}