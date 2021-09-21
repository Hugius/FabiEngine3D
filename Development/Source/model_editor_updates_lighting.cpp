#include "model_editor.hpp"

void ModelEditor::_updateLightingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "modelEditorMenuLighting")
	{
		// Temporary values
		auto isSpecular = _fe3d.modelEntity_isSpecularLighted(_currentModelID);
		auto reflectionType = _fe3d.modelEntity_getReflectionType(_currentModelID);
		auto reflectivity = _fe3d.modelEntity_getReflectivity(_currentModelID);
		auto specularShininess = _fe3d.modelEntity_getSpecularShininess(_currentModelID);
		auto specularIntensity = _fe3d.modelEntity_getSpecularIntensity(_currentModelID);
		auto lightness = _fe3d.modelEntity_getLightness(_currentModelID);
		auto hasReflectionMap = _fe3d.modelEntity_hasReflectionMap(_currentModelID, "");
		auto isSpecularLighted = _fe3d.modelEntity_isSpecularLighted(_currentModelID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			isSpecular = !isSpecular;
			_fe3d.modelEntity_setSpecularLighted(_currentModelID, isSpecular);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("specularShininess", "Specular Shininess", specularShininess, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", (lightness * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectionType")->isHovered())
		{
			if (reflectionType == ReflectionType::CUBE)
			{
				reflectionType = ReflectionType::PLANAR;
			}
			else
			{
				reflectionType = ReflectionType::CUBE;
			}
			_fe3d.modelEntity_setReflectionType(_currentModelID, reflectionType);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectivity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("reflectivity", "Reflectivity", (reflectivity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("specularShininess", specularShininess))
		{
			specularShininess = min(256.0f, specularShininess);
			_fe3d.modelEntity_setSpecularShininess(_currentModelID, specularShininess);
		}
		if (_gui.getGlobalScreen()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d.modelEntity_setSpecularIntensity(_currentModelID, specularIntensity);
		}
		if (_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d.modelEntity_setLightness(_currentModelID, lightness);
		}
		if (_gui.getGlobalScreen()->checkValueForm("reflectivity", reflectivity))
		{
			reflectivity /= 100.0f;
			_fe3d.modelEntity_setReflectivity(_currentModelID, reflectivity);
		}

		// Update buttons hoverability
		screen->getButton("specularShininess")->setHoverable(isSpecularLighted);
		screen->getButton("specularIntensity")->setHoverable(isSpecularLighted);
		screen->getButton("reflectionType")->setHoverable(hasReflectionMap);
		screen->getButton("reflectivity")->setHoverable(hasReflectionMap);

		// Update button text contents
		screen->getButton("isSpecular")->changeTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
		if (hasReflectionMap)
		{
			if (reflectionType == ReflectionType::CUBE)
			{
				screen->getButton("reflectionType")->changeTextContent("Reflect: CUBE");
			}
			else
			{
				screen->getButton("reflectionType")->changeTextContent("Reflect: PLANAR");
			}
		}
		else
		{
			screen->getButton("reflectionType")->changeTextContent("Reflect: OFF");
		}
	}
}