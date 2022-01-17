#include "billboard_editor.hpp"
#include "logger.hpp"

void Quad3dEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "quad3dEditorMenuMiscellaneous")
	{
		auto size = _fe3d->quad3d_getSize(_currentQuad3dID);
		auto isFacingX = _fe3d->quad3d_isFacingCameraX(_currentQuad3dID);
		auto isFacingY = _fe3d->quad3d_isFacingCameraY(_currentQuad3dID);
		auto transparency = _fe3d->quad3d_getTransparency(_currentQuad3dID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");
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
			_fe3d->quad3d_setFacingCameraX(_currentQuad3dID, isFacingX);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFacingY")->isHovered())
		{
			isFacingY = !isFacingY;
			_fe3d->quad3d_setFacingCameraY(_currentQuad3dID, isFacingY);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transparency")->isHovered())
		{
			_gui->getOverlay()->createValueForm("transparency", "Transparency", (transparency * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("sizeX", size.x, {0.0f}))
		{
			size.x /= 100.0f;
			_fe3d->quad3d_setSize(_currentQuad3dID, size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeY", size.y, {0.0f}))
		{
			size.y /= 100.0f;
			_fe3d->quad3d_setSize(_currentQuad3dID, size);
		}
		if(_gui->getOverlay()->checkValueForm("transparency", transparency, {0.0f}))
		{
			transparency /= 100.0f;
			_fe3d->quad3d_setTransparency(_currentQuad3dID, transparency);
		}

		screen->getButton("isFacingX")->changeTextContent(isFacingX ? "Facing X: ON" : "Facing X: OFF");
		screen->getButton("isFacingY")->changeTextContent(isFacingY ? "Facing Y: ON" : "Facing Y: OFF");

		auto rotation = _fe3d->quad3d_getRotation(_currentQuad3dID);
		if(!isFacingX)
		{
			rotation.x = 0.0f;
			rotation.z = 0.0f;
		}
		if(!isFacingY)
		{
			rotation.y = 0.0f;
		}
		_fe3d->quad3d_setRotation(_currentQuad3dID, rotation);
	}
}