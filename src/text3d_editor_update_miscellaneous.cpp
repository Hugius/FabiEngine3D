#include "text3d_editor.hpp"
#include "tools.hpp"

void Text3dEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text3dEditorMenuMiscellaneous")
	{
		const auto size = _fe3d->text3d_getSize(_currentTextId);
		const auto isFacingCameraHorizontally = _fe3d->text3d_isFacingCameraHorizontally(_currentTextId);
		const auto isFacingCameraVertically = _fe3d->text3d_isFacingCameraVertically(_currentTextId);
		const auto opacity = _fe3d->text3d_getOpacity(_currentTextId);
		const auto minTextureAlpha = _fe3d->text3d_getMinTextureAlpha(_currentTextId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.15f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.15f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFacingCameraHorizontally")->isHovered())
		{
			_fe3d->text3d_setFacingCameraHorizontally(_currentTextId, !isFacingCameraHorizontally);

			if(isFacingCameraHorizontally)
			{
				auto rotation = _fe3d->text3d_getRotation(_currentTextId);

				_fe3d->text3d_setRotation(_currentTextId, fvec3(0.0f, rotation.y, 0.0f));
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFacingCameraVertically")->isHovered())
		{
			_fe3d->text3d_setFacingCameraVertically(_currentTextId, !isFacingCameraVertically);

			if(isFacingCameraVertically)
			{
				auto rotation = _fe3d->text3d_getRotation(_currentTextId);

				_fe3d->text3d_setRotation(_currentTextId, fvec3(rotation.x, 0.0f, rotation.z));
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("minTextureAlpha")->isHovered())
		{
			_gui->getOverlay()->openValueForm("minTextureAlpha", "Min Texture Alpha", (minTextureAlpha * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "sizeX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->text3d_setSize(_currentTextId, fvec2((content / 100.0f), size.y));
		}
		if((_gui->getOverlay()->getValueFormId() == "sizeY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->text3d_setSize(_currentTextId, fvec2(size.x, (content / 100.0f)));
		}
		if((_gui->getOverlay()->getValueFormId() == "opacity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->text3d_setOpacity(_currentTextId, (content / 100.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "minTextureAlpha") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->text3d_setMinTextureAlpha(_currentTextId, (content / 100.0f));
		}

		screen->getButton("isFacingCameraHorizontally")->setTextContent(isFacingCameraHorizontally ? "Facing X: ON" : "Facing X: OFF");
		screen->getButton("isFacingCameraVertically")->setTextContent(isFacingCameraVertically ? "Facing Y: ON" : "Facing Y: OFF");
	}
}