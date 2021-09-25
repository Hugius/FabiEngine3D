#include "water_editor.hpp"
#include "logger.hpp"

void WaterEditor::_updateLightingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "waterEditorMenuLighting")
	{
		// Temporary values
		bool isReflective = _fe3d.waterEntity_isReflective(_currentWaterID);
		bool isRefractive = _fe3d.waterEntity_isRefractive(_currentWaterID);
		bool isSpecular = _fe3d.waterEntity_isSpecular(_currentWaterID);
		auto specularShininess = _fe3d.waterEntity_getSpecularShininess(_currentWaterID);
		auto specularIntensity = _fe3d.waterEntity_getSpecularIntensity(_currentWaterID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflective")->isHovered())
		{
			isReflective = !isReflective;
			_fe3d.waterEntity_setReflective(_currentWaterID, isReflective);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isRefractive")->isHovered())
		{
			isRefractive = !isRefractive;
			_fe3d.waterEntity_setRefractive(_currentWaterID, isRefractive);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			isSpecular = !isSpecular;
			_fe3d.waterEntity_setSpecular(_currentWaterID, isSpecular);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("specularShininess", "Specular Shininess", specularShininess, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("specularShininess", specularShininess))
		{
			specularShininess = min(256.0f, specularShininess);
			_fe3d.waterEntity_setSpecularShininess(_currentWaterID, specularShininess);
		}
		if (_gui.getGlobalScreen()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d.waterEntity_setSpecularIntensity(_currentWaterID, specularIntensity);
		}

		// Update buttons hoverability
		screen->getButton("specularShininess")->setHoverable(_fe3d.waterEntity_isSpecular(_currentWaterID));
		screen->getButton("specularIntensity")->setHoverable(_fe3d.waterEntity_isSpecular(_currentWaterID));

		// Update button text contents
		screen->getButton("isReflective")->changeTextContent(isReflective ? "Reflective: ON" : "Reflective: OFF");
		screen->getButton("isRefractive")->changeTextContent(isRefractive ? "Refractive: ON" : "Refractive: OFF");
		screen->getButton("isSpecular")->changeTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
	}
}