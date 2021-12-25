#include "model_editor.hpp"

void ModelEditor::_updateLightingMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "modelEditorMenuLighting")
	{
		// Temporary values
		auto isSpecular = _fe3d.model_isSpecular(_currentModelID, _currentPartID);
		auto isReflective = _fe3d.model_isReflective(_currentModelID, _currentPartID);
		auto reflectionType = _fe3d.model_getReflectionType(_currentModelID, _currentPartID);
		auto reflectivity = _fe3d.model_getReflectivity(_currentModelID, _currentPartID);
		auto specularShininess = _fe3d.model_getSpecularShininess(_currentModelID, _currentPartID);
		auto specularIntensity = _fe3d.model_getSpecularIntensity(_currentModelID, _currentPartID);
		auto lightness = _fe3d.model_getLightness(_currentModelID, _currentPartID);
		auto color = _fe3d.model_getColor(_currentModelID, _currentPartID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			for(const auto& partID : _fe3d.model_getPartIDs(_currentModelID))
			{
				_fe3d.model_setTransparency(_currentModelID, partID, 1.0f);
			}
			_currentPartID = "";
			_fe3d.text_setVisible(_gui.getOverlay()->getTextField("partID")->getEntityID(), false);
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getOverlay()->createValueForm("colorR", "R", color.r * 255.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getOverlay()->createValueForm("colorG", "G", color.g * 255.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getOverlay()->createValueForm("colorB", "B", color.b * 255.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui.getOverlay()->createValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			isSpecular = !isSpecular;
			_fe3d.model_setSpecular(_currentModelID, _currentPartID, isSpecular);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui.getOverlay()->createValueForm("specularShininess", "Specular Shininess", specularShininess, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui.getOverlay()->createValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflective")->isHovered())
		{
			isReflective = !isReflective;
			_fe3d.model_setReflective(_currentModelID, _currentPartID, isReflective);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectionType")->isHovered())
		{
			if(reflectionType == ReflectionType::CUBE)
			{
				reflectionType = ReflectionType::PLANAR;
			}
			else
			{
				reflectionType = ReflectionType::CUBE;
			}
			_fe3d.model_setReflectionType(_currentModelID, _currentPartID, reflectionType);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectivity")->isHovered())
		{
			_gui.getOverlay()->createValueForm("reflectivity", "Reflectivity", (reflectivity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d.model_setColor(_currentModelID, _currentPartID, color);
		}
		if(_gui.getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d.model_setColor(_currentModelID, _currentPartID, color);
		}
		if(_gui.getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d.model_setColor(_currentModelID, _currentPartID, color);
		}
		if(_gui.getOverlay()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d.model_setLightness(_currentModelID, _currentPartID, lightness);
		}
		if(_gui.getOverlay()->checkValueForm("specularShininess", specularShininess))
		{
			_fe3d.model_setSpecularShininess(_currentModelID, _currentPartID, specularShininess);
		}
		if(_gui.getOverlay()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d.model_setSpecularIntensity(_currentModelID, _currentPartID, specularIntensity);
		}
		if(_gui.getOverlay()->checkValueForm("reflectivity", reflectivity))
		{
			reflectivity /= 100.0f;
			_fe3d.model_setReflectivity(_currentModelID, _currentPartID, reflectivity);
		}

		// Update buttons hoverability
		screen->getButton("specularShininess")->setHoverable(isSpecular);
		screen->getButton("specularIntensity")->setHoverable(isSpecular);
		screen->getButton("reflectionType")->setHoverable(isReflective);
		screen->getButton("reflectivity")->setHoverable(isReflective);

		// Update button text contents
		screen->getButton("isSpecular")->changeTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
		screen->getButton("isReflective")->changeTextContent(isReflective ? "Reflective: ON" : "Reflective: OFF");
		if(isReflective)
		{
			if(reflectionType == ReflectionType::CUBE)
			{
				screen->getButton("reflectionType")->changeTextContent("Type: CUBE");
			}
			else
			{
				screen->getButton("reflectionType")->changeTextContent("Type: PLANAR");
			}
		}
		else
		{
			screen->getButton("reflectionType")->changeTextContent("Type: NONE");
		}
	}
}