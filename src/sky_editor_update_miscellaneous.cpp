#include "sky_editor.hpp"
#include "tools.hpp"

void SkyEditor::_updateMiscellaneousMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "skyEditorMenuMiscellaneous")
	{
		const auto rotation = _fe3d->sky_getRotation(_currentSkyId);
		const auto lightness = _fe3d->sky_getLightness(_currentSkyId);
		const auto color = _fe3d->sky_getColor(_currentSkyId);
		const auto rotationOrder = _fe3d->sky_getRotationOrder(_currentSkyId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("skyEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
		{
			_gui->getOverlay()->openValueForm("rotationX", "X", rotation.x, fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("rotationY", "Y", rotation.y, fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("rotationZ", "Z", rotation.z, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rotationOrder")->isHovered())
		{
			switch(rotationOrder)
			{
				case DirectionOrderType::XYZ:
				{
					_fe3d->sky_setRotationOrder(_currentSkyId, DirectionOrderType::XZY);

					break;
				}
				case DirectionOrderType::XZY:
				{
					_fe3d->sky_setRotationOrder(_currentSkyId, DirectionOrderType::YXZ);

					break;
				}
				case DirectionOrderType::YXZ:
				{
					_fe3d->sky_setRotationOrder(_currentSkyId, DirectionOrderType::YZX);

					break;
				}
				case DirectionOrderType::YZX:
				{
					_fe3d->sky_setRotationOrder(_currentSkyId, DirectionOrderType::ZXY);

					break;
				}
				case DirectionOrderType::ZXY:
				{
					_fe3d->sky_setRotationOrder(_currentSkyId, DirectionOrderType::ZYX);

					break;
				}
				case DirectionOrderType::ZYX:
				{
					_fe3d->sky_setRotationOrder(_currentSkyId, DirectionOrderType::XYZ);

					break;
				}
			}
		}

		if((_gui->getOverlay()->getValueFormId() == "rotationX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->sky_setRotation(_currentSkyId, fvec3(content, rotation.y, rotation.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "rotationY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->sky_setRotation(_currentSkyId, fvec3(rotation.x, content, rotation.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "rotationZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->sky_setRotation(_currentSkyId, fvec3(rotation.x, rotation.y, content));
		}
		if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->sky_setLightness(_currentSkyId, (content / 100.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->sky_setColor(_currentSkyId, fvec3((content / COLOR_MULTIPLIER), color.g, color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->sky_setColor(_currentSkyId, fvec3(color.r, (content / COLOR_MULTIPLIER), color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->sky_setColor(_currentSkyId, fvec3(color.r, color.g, (content / COLOR_MULTIPLIER)));
		}

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