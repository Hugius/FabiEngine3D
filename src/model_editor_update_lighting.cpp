#include "model_editor.hpp"

void ModelEditor::_updateLightingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "modelEditorMenuLighting")
	{
		const auto isPartSelected = (!_fe3d->model_isMultiParted(_currentModelID) || !_currentPartID.empty());

		auto isSpecular = (isPartSelected ? _fe3d->model_isSpecular(_currentModelID, _currentPartID) : false);
		auto isReflective = (isPartSelected ? _fe3d->model_isReflective(_currentModelID, _currentPartID) : false);
		auto reflectionType = (isPartSelected ? _fe3d->model_getReflectionType(_currentModelID, _currentPartID) : ReflectionType::CUBE);
		auto reflectivity = (isPartSelected ? _fe3d->model_getReflectivity(_currentModelID, _currentPartID) : 0.0f);
		auto specularShininess = (isPartSelected ? _fe3d->model_getSpecularShininess(_currentModelID, _currentPartID) : 0.0f);
		auto specularIntensity = (isPartSelected ? _fe3d->model_getSpecularIntensity(_currentModelID, _currentPartID) : 0.0f);
		auto lightness = (isPartSelected ? _fe3d->model_getLightness(_currentModelID, _currentPartID) : 0.0f);
		auto color = (isPartSelected ? _fe3d->model_getColor(_currentModelID, _currentPartID) : fvec3(0.0f));

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
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
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			isSpecular = !isSpecular;
			_fe3d->model_setSpecular(_currentModelID, _currentPartID, isSpecular);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui->getOverlay()->createValueForm("specularShininess", "Specular Shininess", specularShininess, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflective")->isHovered())
		{
			isReflective = !isReflective;
			_fe3d->model_setReflective(_currentModelID, _currentPartID, isReflective);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectionType")->isHovered())
		{
			if(reflectionType == ReflectionType::CUBE)
			{
				reflectionType = ReflectionType::PLANAR;
			}
			else
			{
				reflectionType = ReflectionType::CUBE;
			}
			_fe3d->model_setReflectionType(_currentModelID, _currentPartID, reflectionType);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectivity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("reflectivity", "Reflectivity", (reflectivity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d->model_setColor(_currentModelID, _currentPartID, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d->model_setColor(_currentModelID, _currentPartID, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d->model_setColor(_currentModelID, _currentPartID, color);
		}
		if(_gui->getOverlay()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d->model_setLightness(_currentModelID, _currentPartID, lightness);
		}
		if(_gui->getOverlay()->checkValueForm("specularShininess", specularShininess))
		{
			_fe3d->model_setSpecularShininess(_currentModelID, _currentPartID, specularShininess);
		}
		if(_gui->getOverlay()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d->model_setSpecularIntensity(_currentModelID, _currentPartID, specularIntensity);
		}
		if(_gui->getOverlay()->checkValueForm("reflectivity", reflectivity))
		{
			reflectivity /= 100.0f;
			_fe3d->model_setReflectivity(_currentModelID, _currentPartID, reflectivity);
		}

		screen->getButton("color")->setHoverable(isPartSelected);
		screen->getButton("lightness")->setHoverable(isPartSelected);
		screen->getButton("isSpecular")->setHoverable(isPartSelected);
		screen->getButton("specularShininess")->setHoverable(isPartSelected && isSpecular);
		screen->getButton("specularIntensity")->setHoverable(isPartSelected && isSpecular);
		screen->getButton("isReflective")->setHoverable(isPartSelected);
		screen->getButton("reflectionType")->setHoverable(isPartSelected && isReflective);
		screen->getButton("reflectivity")->setHoverable(isPartSelected && isReflective);

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