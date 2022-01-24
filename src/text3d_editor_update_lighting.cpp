#include "text3d_editor.hpp"
#include "logger.hpp"

void Text3dEditor::_updateLightingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text3dEditorMenuLighting")
	{
		auto lightness = _fe3d->text3d_getLightness(_currentTextID);
		auto isBright = _fe3d->text3d_isBright(_currentTextID);
		auto isReflected = _fe3d->text3d_isReflected(_currentTextID);
		auto isShadowed = _fe3d->text3d_isShadowed(_currentTextID);
		auto color = _fe3d->text3d_getColor(_currentTextID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->createValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->createValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			isBright = !isBright;
			_fe3d->text3d_setBright(_currentTextID, isBright);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			isShadowed = !isShadowed;
			_fe3d->text3d_setShadowed(_currentTextID, isShadowed);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			isReflected = !isReflected;
			_fe3d->text3d_setReflected(_currentTextID, isReflected);
		}

		if(_gui->getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d->text3d_setColor(_currentTextID, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d->text3d_setColor(_currentTextID, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d->text3d_setColor(_currentTextID, color);
		}
		if(_gui->getOverlay()->checkValueForm("lightness", lightness, {}))
		{
			lightness /= 100.0f;
			_fe3d->text3d_setLightness(_currentTextID, lightness);
		}

		screen->getButton("isBright")->changeTextContent(isBright ? "Bright: ON" : "Bright: OFF");
		screen->getButton("isReflected")->changeTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isShadowed")->changeTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	}
}