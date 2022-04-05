#include "quad3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad3dEditor::_updateLightingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuLighting")
	{
		const auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(_currentQuadId);
		const auto lightness = _fe3d->quad3d_getLightness(_currentQuadId);
		const auto isBright = _fe3d->quad3d_isBright(_currentQuadId);
		const auto isReflected = _fe3d->quad3d_isReflected(_currentQuadId);
		const auto isShadowed = _fe3d->quad3d_isShadowed(_currentQuadId);
		const auto color = _fe3d->quad3d_getColor(_currentQuadId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("emissionIntensity", "Emission Intensity", (emissionIntensity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			_fe3d->quad3d_setBright(_currentQuadId, !isBright);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			_fe3d->quad3d_setShadowed(_currentQuadId, !isShadowed);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			_fe3d->quad3d_setReflected(_currentQuadId, !isReflected);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->quad3d_setColor(_currentQuadId, (static_cast<float>(content) / 255.0f));

			_gui->getOverlay()->openValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->quad3d_setColor(_currentQuadId, (static_cast<float>(content) / 255.0f));

			_gui->getOverlay()->openValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), 5, false, true, false);
		}
		if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->quad3d_setColor(_currentQuadId, (static_cast<float>(content) / 255.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->quad3d_setLightness(_currentQuadId, (static_cast<float>(content) / 100.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "emissionIntensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent());

			_fe3d->quad3d_setEmissionIntensity(_currentQuadId, (static_cast<float>(content) / 100.0f));
		}

		screen->getButton("isBright")->setTextContent(isBright ? "Bright: ON" : "Bright: OFF");
		screen->getButton("isReflected")->setTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isShadowed")->setTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	}
}