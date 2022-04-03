#include "quad3d_editor.hpp"
#include "logger.hpp"

void Quad3dEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuMiscellaneous")
	{
		auto size = _fe3d->quad3d_getSize(_currentQuadId);
		auto isFacingCameraHorizontally = _fe3d->quad3d_isFacingCameraHorizontally(_currentQuadId);
		auto isFacingCameraVertically = _fe3d->quad3d_isFacingCameraVertically(_currentQuadId);
		auto opacity = _fe3d->quad3d_getOpacity(_currentQuadId);
		auto minTextureAlpha = _fe3d->quad3d_getMinTextureAlpha(_currentQuadId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			//_gui->getOverlay()->openValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			//_gui->getOverlay()->openValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFacingCameraHorizontally")->isHovered())
		{
			isFacingCameraHorizontally = !isFacingCameraHorizontally;
			_fe3d->quad3d_setFacingCameraHorizontally(_currentQuadId, isFacingCameraHorizontally);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFacingCameraVertically")->isHovered())
		{
			isFacingCameraVertically = !isFacingCameraVertically;
			_fe3d->quad3d_setFacingCameraVertically(_currentQuadId, isFacingCameraVertically);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			//_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("minTextureAlpha")->isHovered())
		{
			//_gui->getOverlay()->openValueForm("minTextureAlpha", "Min Texture Alpha", (minTextureAlpha * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("sizeX", size.x))
		{
			size.x /= 100.0f;
			_fe3d->quad3d_setSize(_currentQuadId, size);
		}
		//if(_gui->getOverlay()->checkValueForm("sizeY", size.y))
		{
			size.y /= 100.0f;
			_fe3d->quad3d_setSize(_currentQuadId, size);
		}
		//if(_gui->getOverlay()->checkValueForm("opacity", opacity))
		{
			opacity /= 100.0f;
			_fe3d->quad3d_setOpacity(_currentQuadId, opacity);
		}
		//if(_gui->getOverlay()->checkValueForm("minTextureAlpha", minTextureAlpha))
		{
			minTextureAlpha /= 100.0f;
			_fe3d->quad3d_setMinTextureAlpha(_currentQuadId, minTextureAlpha);
		}

		screen->getButton("isFacingCameraHorizontally")->setTextContent(isFacingCameraHorizontally ? "Facing X: ON" : "Facing X: OFF");
		screen->getButton("isFacingCameraVertically")->setTextContent(isFacingCameraVertically ? "Facing Y: ON" : "Facing Y: OFF");

		auto rotation = _fe3d->quad3d_getRotation(_currentQuadId);
		if(!isFacingCameraHorizontally)
		{
			rotation.x = 0.0f;
			rotation.z = 0.0f;
		}
		if(!isFacingCameraVertically)
		{
			rotation.y = 0.0f;
		}
		_fe3d->quad3d_setRotation(_currentQuadId, rotation);
	}
}