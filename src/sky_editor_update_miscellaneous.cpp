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
			_gui->getOverlay()->openValueForm("rotationX", "X", rotation.x, VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("rotationY", "Y", rotation.y, VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("rotationZ", "Z", rotation.z, VALUE_FORM_POSITION, 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * LIGHTNESS_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
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
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sky_setRotation(_currentSkyId, fvec3(value, rotation.y, rotation.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "rotationY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sky_setRotation(_currentSkyId, fvec3(rotation.x, value, rotation.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "rotationZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sky_setRotation(_currentSkyId, fvec3(rotation.x, rotation.y, value));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sky_setLightness(_currentSkyId, (value / 100.0f));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sky_setColor(_currentSkyId, fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sky_setColor(_currentSkyId, fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sky_setColor(_currentSkyId, fvec3(color.r, color.g, (value / COLOR_FACTOR)));
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