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
		auto specularFactor = _fe3d.modelEntity_getSpecularFactor(_currentModelID);
		auto specularIntensity = _fe3d.modelEntity_getSpecularIntensity(_currentModelID);
		auto lightness = _fe3d.modelEntity_getLightness(_currentModelID);
		auto isBright = _fe3d.modelEntity_isBright(_currentModelID);

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
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularFactor")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("specularFactor", "Specular Factor", specularFactor, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", (lightness * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			isBright = !isBright;
			_fe3d.modelEntity_setBright(_currentModelID, isBright);
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
		if (_gui.getGlobalScreen()->checkValueForm("specularFactor", specularFactor))
		{
			specularFactor = min(256.0f, specularFactor);
			_fe3d.modelEntity_setSpecularFactor(_currentModelID, specularFactor);
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
		screen->getButton("specularFactor")->setHoverable(_fe3d.modelEntity_isSpecularLighted(_currentModelID));
		screen->getButton("specularIntensity")->setHoverable(_fe3d.modelEntity_isSpecularLighted(_currentModelID));
		screen->getButton("reflectionType")->setHoverable(_fe3d.modelEntity_hasReflectionMap(_currentModelID));
		screen->getButton("reflectivity")->setHoverable(_fe3d.modelEntity_hasReflectionMap(_currentModelID));

		// Update button text contents
		screen->getButton("isSpecular")->changeTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
		screen->getButton("isBright")->changeTextContent(isBright ? "Bright: ON" : "Bright: OFF");
		if (_fe3d.modelEntity_hasReflectionMap(_currentModelID))
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