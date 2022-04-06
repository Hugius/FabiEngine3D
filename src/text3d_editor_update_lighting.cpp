#include "text3d_editor.hpp"
#include "logger.hpp"

void Text3dEditor::_updateLightingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text3dEditorMenuLighting")
	{
		auto lightness = _fe3d->text3d_getLightness(_currentTextId);
		auto isBright = _fe3d->text3d_isBright(_currentTextId);
		auto isReflected = _fe3d->text3d_isReflected(_currentTextId);
		auto isShadowed = _fe3d->text3d_isShadowed(_currentTextId);
		auto color = _fe3d->text3d_getColor(_currentTextId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			isBright = !isBright;
			_fe3d->text3d_setBright(_currentTextId, isBright);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			isShadowed = !isShadowed;
			_fe3d->text3d_setShadowed(_currentTextId, isShadowed);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			isReflected = !isReflected;
			_fe3d->text3d_setReflected(_currentTextId, isReflected);
		}

		if(_gui->getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d->text3d_setColor(_currentTextId, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d->text3d_setColor(_currentTextId, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d->text3d_setColor(_currentTextId, color);
		}
		if(_gui->getOverlay()->checkValueForm("lightness", lightness, {}))
		{
			lightness /= 100.0f;
			_fe3d->text3d_setLightness(_currentTextId, lightness);
		}

		screen->getButton("isBright")->setTextContent(isBright ? "Bright: ON" : "Bright: OFF");
		screen->getButton("isReflected")->setTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isShadowed")->setTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	}
}