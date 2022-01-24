#include "quad3d_editor.hpp"
#include "logger.hpp"

void Quad3dEditor::_updateLightingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuLighting")
	{
		auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(_currentQuadId);
		auto lightness = _fe3d->quad3d_getLightness(_currentQuadId);
		auto isBright = _fe3d->quad3d_isBright(_currentQuadId);
		auto isReflected = _fe3d->quad3d_isReflected(_currentQuadId);
		auto isShadowed = _fe3d->quad3d_isShadowed(_currentQuadId);
		auto color = _fe3d->quad3d_getColor(_currentQuadId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");
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
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionIntensity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("emissionIntensity", "Emission Intensity", (emissionIntensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			isBright = !isBright;
			_fe3d->quad3d_setBright(_currentQuadId, isBright);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			isShadowed = !isShadowed;
			_fe3d->quad3d_setShadowed(_currentQuadId, isShadowed);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			isReflected = !isReflected;
			_fe3d->quad3d_setReflected(_currentQuadId, isReflected);
		}

		if(_gui->getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d->quad3d_setColor(_currentQuadId, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d->quad3d_setColor(_currentQuadId, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d->quad3d_setColor(_currentQuadId, color);
		}
		if(_gui->getOverlay()->checkValueForm("lightness", lightness, {}))
		{
			lightness /= 100.0f;
			_fe3d->quad3d_setLightness(_currentQuadId, lightness);
		}
		if(_gui->getOverlay()->checkValueForm("emissionIntensity", emissionIntensity, {}))
		{
			emissionIntensity /= 100.0f;
			_fe3d->quad3d_setEmissionIntensity(_currentQuadId, emissionIntensity);
		}

		screen->getButton("isBright")->changeTextContent(isBright ? "Bright: ON" : "Bright: OFF");
		screen->getButton("isReflected")->changeTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isShadowed")->changeTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	}
}