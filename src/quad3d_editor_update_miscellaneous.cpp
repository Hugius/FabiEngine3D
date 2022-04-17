#include "quad3d_editor.hpp"
#include "tools.hpp"

void Quad3dEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuMiscellaneous")
	{
		const auto size = _fe3d->quad3d_getSize(_currentQuadId);
		const auto isFacingCameraHorizontally = _fe3d->quad3d_isFacingCameraHorizontally(_currentQuadId);
		const auto isFacingCameraVertically = _fe3d->quad3d_isFacingCameraVertically(_currentQuadId);
		const auto opacity = _fe3d->quad3d_getOpacity(_currentQuadId);
		const auto minTextureAlpha = _fe3d->quad3d_getMinTextureAlpha(_currentQuadId);

		if((_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKey::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.15f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.15f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("isFacingCameraHorizontally")->isHovered())
		{
			_fe3d->quad3d_setFacingCameraHorizontally(_currentQuadId, !isFacingCameraHorizontally);

			if(isFacingCameraHorizontally)
			{
				auto rotation = _fe3d->quad3d_getRotation(_currentQuadId);

				_fe3d->quad3d_setRotation(_currentQuadId, fvec3(0.0f, rotation.y, 0.0f));
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("isFacingCameraVertically")->isHovered())
		{
			_fe3d->quad3d_setFacingCameraVertically(_currentQuadId, !isFacingCameraVertically);

			if(isFacingCameraVertically)
			{
				auto rotation = _fe3d->quad3d_getRotation(_currentQuadId);

				_fe3d->quad3d_setRotation(_currentQuadId, fvec3(rotation.x, 0.0f, rotation.z));
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButton::BUTTON_LEFT) && screen->getButton("minTextureAlpha")->isHovered())
		{
			_gui->getOverlay()->openValueForm("minTextureAlpha", "Min Texture Alpha", (minTextureAlpha * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "sizeX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->quad3d_setSize(_currentQuadId, fvec2((content / 100.0f), size.y));
		}
		if((_gui->getOverlay()->getValueFormId() == "sizeY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->quad3d_setSize(_currentQuadId, fvec2(size.x, (content / 100.0f)));
		}
		if((_gui->getOverlay()->getValueFormId() == "opacity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->quad3d_setOpacity(_currentQuadId, (content / 100.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "minTextureAlpha") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->quad3d_setMinTextureAlpha(_currentQuadId, (content / 100.0f));
		}

		screen->getButton("isFacingCameraHorizontally")->setTextContent(isFacingCameraHorizontally ? "Facing X: ON" : "Facing X: OFF");
		screen->getButton("isFacingCameraVertically")->setTextContent(isFacingCameraVertically ? "Facing Y: ON" : "Facing Y: OFF");
	}
}