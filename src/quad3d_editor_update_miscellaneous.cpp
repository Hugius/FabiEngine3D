#include "quad3d_editor.hpp"
#include "tools.hpp"

void Quad3dEditor::_updateMiscellaneousMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuMiscellaneous")
	{
		const auto size = _fe3d->quad3d_getSize(_currentQuad3dId);
		const auto isFacingCameraHorizontally = _fe3d->quad3d_isFacingCameraHorizontally(_currentQuad3dId);
		const auto isFacingCameraVertically = _fe3d->quad3d_isFacingCameraVertically(_currentQuad3dId);
		const auto isHorizontallyFlipped = _fe3d->quad3d_isHorizontallyFlipped(_currentQuad3dId);
		const auto isVerticallyFlipped = _fe3d->quad3d_isVerticallyFlipped(_currentQuad3dId);
		const auto opacity = _fe3d->quad3d_getOpacity(_currentQuad3dId);
		const auto minTextureAlpha = _fe3d->quad3d_getMinTextureAlpha(_currentQuad3dId);
		const auto rotationOrder = _fe3d->quad3d_getRotationOrder(_currentQuad3dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sizeX", "X", (size.x * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isFacingCameraHorizontally")->isHovered())
		{
			_fe3d->quad3d_setFacingCameraHorizontally(_currentQuad3dId, !isFacingCameraHorizontally);

			if(isFacingCameraHorizontally)
			{
				auto rotation = _fe3d->quad3d_getRotation(_currentQuad3dId);

				_fe3d->quad3d_setRotation(_currentQuad3dId, fvec3(0.0f, rotation.y, 0.0f));
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isFacingCameraVertically")->isHovered())
		{
			_fe3d->quad3d_setFacingCameraVertically(_currentQuad3dId, !isFacingCameraVertically);

			if(isFacingCameraVertically)
			{
				auto rotation = _fe3d->quad3d_getRotation(_currentQuad3dId);

				_fe3d->quad3d_setRotation(_currentQuad3dId, fvec3(rotation.x, 0.0f, rotation.z));
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isHorizontallyFlipped")->isHovered())
		{
			_fe3d->quad3d_setHorizontallyFlipped(_currentQuad3dId, !isHorizontallyFlipped);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isVerticallyFlipped")->isHovered())
		{
			_fe3d->quad3d_setVerticallyFlipped(_currentQuad3dId, !isVerticallyFlipped);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("minTextureAlpha")->isHovered())
		{
			_gui->getOverlay()->openValueForm("minTextureAlpha", "Min Texture Alpha", (minTextureAlpha * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rotationOrder")->isHovered())
		{
			switch(rotationOrder)
			{
				case DirectionOrderType::XYZ:
				{
					_fe3d->quad3d_setRotationOrder(_currentQuad3dId, DirectionOrderType::XZY);

					break;
				}
				case DirectionOrderType::XZY:
				{
					_fe3d->quad3d_setRotationOrder(_currentQuad3dId, DirectionOrderType::YXZ);

					break;
				}
				case DirectionOrderType::YXZ:
				{
					_fe3d->quad3d_setRotationOrder(_currentQuad3dId, DirectionOrderType::YZX);

					break;
				}
				case DirectionOrderType::YZX:
				{
					_fe3d->quad3d_setRotationOrder(_currentQuad3dId, DirectionOrderType::ZXY);

					break;
				}
				case DirectionOrderType::ZXY:
				{
					_fe3d->quad3d_setRotationOrder(_currentQuad3dId, DirectionOrderType::ZYX);

					break;
				}
				case DirectionOrderType::ZYX:
				{
					_fe3d->quad3d_setRotationOrder(_currentQuad3dId, DirectionOrderType::XYZ);

					break;
				}
			}
		}

		if((_gui->getOverlay()->getValueFormId() == "sizeX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad3d_setSize(_currentQuad3dId, fvec2((value / 100.0f), size.y));
		}
		if((_gui->getOverlay()->getValueFormId() == "sizeY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad3d_setSize(_currentQuad3dId, fvec2(size.x, (value / 100.0f)));
		}
		if((_gui->getOverlay()->getValueFormId() == "opacity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad3d_setOpacity(_currentQuad3dId, (value / 100.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "minTextureAlpha") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad3d_setMinTextureAlpha(_currentQuad3dId, (value / 100.0f));
		}

		screen->getButton("isFacingCameraHorizontally")->setTextContent(isFacingCameraHorizontally ? "Facing X: ON" : "Facing X: OFF");
		screen->getButton("isFacingCameraVertically")->setTextContent(isFacingCameraVertically ? "Facing Y: ON" : "Facing Y: OFF");
		screen->getButton("isHorizontallyFlipped")->setTextContent(isHorizontallyFlipped ? "Flipped X: ON" : "Flipped X: OFF");
		screen->getButton("isVerticallyFlipped")->setTextContent(isVerticallyFlipped ? "Flipped Y: ON" : "Flipped Y: OFF");

		switch(rotationOrder)
		{
			case DirectionOrderType::XYZ:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: X Y Z");

				break;
			}
			case DirectionOrderType::XZY:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: X Z Y");

				break;
			}
			case DirectionOrderType::YXZ:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: Y X Z");

				break;
			}
			case DirectionOrderType::YZX:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: Y Z X");

				break;
			}
			case DirectionOrderType::ZXY:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: Z X Y");

				break;
			}
			case DirectionOrderType::ZYX:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: Z Y X");

				break;
			}
		}
	}
}