#include "text3d_editor.hpp"
#include "tools.hpp"

void Text3dEditor::_updateLightingMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text3dEditorMenuLighting")
	{
		const auto lightness = _fe3d->text3d_getLightness(_currentText3dId);
		const auto isBright = _fe3d->text3d_isBright(_currentText3dId);
		const auto isReflected = _fe3d->text3d_isReflected(_currentText3dId);
		const auto isRefracted = _fe3d->text3d_isRefracted(_currentText3dId);
		const auto isShadowed = _fe3d->text3d_isShadowed(_currentText3dId);
		const auto color = _fe3d->text3d_getColor(_currentText3dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * LIGHTNESS_FACTOR), VALUE_FORM_POSITION, 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			_fe3d->text3d_setBright(_currentText3dId, !isBright);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			_fe3d->text3d_setShadowed(_currentText3dId, !isShadowed);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			_fe3d->text3d_setReflected(_currentText3dId, !isReflected);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isRefracted")->isHovered())
		{
			_fe3d->text3d_setRefracted(_currentText3dId, !isRefracted);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->text3d_setColor(_currentText3dId, fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->text3d_setColor(_currentText3dId, fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->text3d_setColor(_currentText3dId, fvec3(color.r, color.g, (value / COLOR_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->text3d_setLightness(_currentText3dId, (value / LIGHTNESS_FACTOR));
		}

		screen->getButton("isBright")->setTextContent(isBright ? "Bright: ON" : "Bright: OFF");
		screen->getButton("isReflected")->setTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isRefracted")->setTextContent(isRefracted ? "Refracted: ON" : "Refracted: OFF");
		screen->getButton("isShadowed")->setTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	}
}