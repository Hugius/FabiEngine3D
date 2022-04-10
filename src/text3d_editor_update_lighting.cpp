#include "text3d_editor.hpp"
#include "tools.hpp"

void Text3dEditor::_updateLightingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text3dEditorMenuLighting")
	{
		const auto lightness = _fe3d->text3d_getLightness(_currentTextId);
		const auto isBright = _fe3d->text3d_isBright(_currentTextId);
		const auto isReflected = _fe3d->text3d_isReflected(_currentTextId);
		const auto isShadowed = _fe3d->text3d_isShadowed(_currentTextId);
		const auto color = _fe3d->text3d_getColor(_currentTextId);

		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			_fe3d->text3d_setBright(_currentTextId, !isBright);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			_fe3d->text3d_setShadowed(_currentTextId, !isShadowed);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			_fe3d->text3d_setReflected(_currentTextId, !isReflected);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->text3d_setColor(_currentTextId, fvec3((content / COLOR_MULTIPLIER), color.g, color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->text3d_setColor(_currentTextId, fvec3(color.r, (content / COLOR_MULTIPLIER), color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->text3d_setColor(_currentTextId, fvec3(color.r, color.g, (content / COLOR_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->text3d_setLightness(_currentTextId, (content / 100.0f));
		}

		screen->getButton("isBright")->setTextContent(isBright ? "Bright: ON" : "Bright: OFF");
		screen->getButton("isReflected")->setTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isShadowed")->setTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	}
}