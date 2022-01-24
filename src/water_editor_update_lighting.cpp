#include "water_editor.hpp"
#include "logger.hpp"

void WaterEditor::_updateLightingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "waterEditorMenuLighting")
	{
		auto color = _fe3d->water_getColor(_currentWaterID);
		bool isReflective = _fe3d->water_isReflective(_currentWaterID);
		bool isRefractive = _fe3d->water_isRefractive(_currentWaterID);
		bool isSpecular = _fe3d->water_isSpecular(_currentWaterID);
		auto specularShininess = _fe3d->water_getSpecularShininess(_currentWaterID);
		auto specularIntensity = _fe3d->water_getSpecularIntensity(_currentWaterID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->createValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflective")->isHovered())
		{
			isReflective = !isReflective;
			_fe3d->water_setReflective(_currentWaterID, isReflective);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isRefractive")->isHovered())
		{
			isRefractive = !isRefractive;
			_fe3d->water_setRefractive(_currentWaterID, isRefractive);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			isSpecular = !isSpecular;
			_fe3d->water_setSpecular(_currentWaterID, isSpecular);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui->getOverlay()->createValueForm("specularShininess", "Specular Shininess", specularShininess, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("colorR", color.r))
		{
			color.r /= 255.0f;
			_fe3d->water_setColor(_currentWaterID, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorG", color.g))
		{
			color.g /= 255.0f;
			_fe3d->water_setColor(_currentWaterID, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorB", color.b))
		{
			color.b /= 255.0f;
			_fe3d->water_setColor(_currentWaterID, color);
		}
		if(_gui->getOverlay()->checkValueForm("specularShininess", specularShininess))
		{
			_fe3d->water_setSpecularShininess(_currentWaterID, specularShininess);
		}
		if(_gui->getOverlay()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d->water_setSpecularIntensity(_currentWaterID, specularIntensity);
		}

		screen->getButton("specularShininess")->setHoverable(isSpecular);
		screen->getButton("specularIntensity")->setHoverable(isSpecular);

		screen->getButton("isReflective")->changeTextContent(isReflective ? "Reflective: ON" : "Reflective: OFF");
		screen->getButton("isRefractive")->changeTextContent(isRefractive ? "Refractive: ON" : "Refractive: OFF");
		screen->getButton("isSpecular")->changeTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
	}
}