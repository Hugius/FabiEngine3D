#include "model_editor.hpp"

void ModelEditor::_updateLightingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuLighting")
	{
		const auto isPartSelected = (!_fe3d->model_isMultiParted(_currentModelId) || !_currentPartId.empty());
		const auto isNoPartSelected = (!_fe3d->model_isMultiParted(_currentModelId) || _currentPartId.empty());

		auto isSpecular = (isPartSelected ? _fe3d->model_isSpecular(_currentModelId, _currentPartId) : false);
		auto isReflective = (isPartSelected ? _fe3d->model_isReflective(_currentModelId, _currentPartId) : false);
		auto reflectionType = (isPartSelected ? _fe3d->model_getReflectionType(_currentModelId, _currentPartId) : ReflectionType::CUBE);
		auto reflectivity = (isPartSelected ? _fe3d->model_getReflectivity(_currentModelId, _currentPartId) : 0.0f);
		auto specularShininess = (isPartSelected ? _fe3d->model_getSpecularShininess(_currentModelId, _currentPartId) : 0.0f);
		auto specularIntensity = (isPartSelected ? _fe3d->model_getSpecularIntensity(_currentModelId, _currentPartId) : 0.0f);
		auto lightness = (isPartSelected ? _fe3d->model_getLightness(_currentModelId, _currentPartId) : 0.0f);
		auto color = (isPartSelected ? _fe3d->model_getColor(_currentModelId, _currentPartId) : fvec3(0.0f));
		auto isBright = (isPartSelected ? _fe3d->model_isBright(_currentModelId, _currentPartId) : false);
		auto isShadowed = (isNoPartSelected ? _fe3d->model_isShadowed(_currentModelId) : false);
		auto isReflected = (isNoPartSelected ? _fe3d->model_isReflected(_currentModelId) : false);
		auto emissionIntensity = (isPartSelected ? _fe3d->model_getEmissionIntensity(_currentModelId, _currentPartId) : 0.0f);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			isSpecular = !isSpecular;
			_fe3d->model_setSpecular(_currentModelId, _currentPartId, isSpecular);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularShininess", "Specular Shininess", specularShininess, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflective")->isHovered())
		{
			isReflective = !isReflective;
			_fe3d->model_setReflective(_currentModelId, _currentPartId, isReflective);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			isBright = !isBright;
			_fe3d->model_setBright(_currentModelId, _currentPartId, isBright);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			isShadowed = !isShadowed;
			_fe3d->model_setShadowed(_currentModelId, isShadowed);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			isReflected = !isReflected;
			_fe3d->model_setReflected(_currentModelId, isReflected);
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

			_fe3d->model_setReflectionType(_currentModelId, _currentPartId, reflectionType);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectivity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("reflectivity", "Reflectivity", (reflectivity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("emissionIntensity", "Emission Intensity", (emissionIntensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d->model_setColor(_currentModelId, _currentPartId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d->model_setColor(_currentModelId, _currentPartId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d->model_setColor(_currentModelId, _currentPartId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d->model_setLightness(_currentModelId, _currentPartId, lightness);
		}
		//if(_gui->getOverlay()->checkValueForm("specularShininess", specularShininess))
		{
			_fe3d->model_setSpecularShininess(_currentModelId, _currentPartId, specularShininess);
		}
		//if(_gui->getOverlay()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d->model_setSpecularIntensity(_currentModelId, _currentPartId, specularIntensity);
		}
		//if(_gui->getOverlay()->checkValueForm("reflectivity", reflectivity))
		{
			reflectivity /= 100.0f;
			_fe3d->model_setReflectivity(_currentModelId, _currentPartId, reflectivity);
		}
		//if(_gui->getOverlay()->checkValueForm("emissionIntensity", emissionIntensity))
		{
			emissionIntensity /= 100.0f;
			_fe3d->model_setEmissionIntensity(_currentModelId, _currentPartId, emissionIntensity);
		}

		screen->getButton("color")->setHoverable(isPartSelected);
		screen->getButton("lightness")->setHoverable(isPartSelected);
		screen->getButton("isSpecular")->setHoverable(isPartSelected);
		screen->getButton("specularShininess")->setHoverable(isPartSelected);
		screen->getButton("specularIntensity")->setHoverable(isPartSelected);
		screen->getButton("isReflective")->setHoverable(isPartSelected);
		screen->getButton("reflectionType")->setHoverable(isPartSelected);
		screen->getButton("reflectivity")->setHoverable(isPartSelected);
		screen->getButton("isBright")->setHoverable(isPartSelected);
		screen->getButton("isShadowed")->setHoverable(isNoPartSelected);
		screen->getButton("isReflected")->setHoverable(isNoPartSelected);
		screen->getButton("emissionIntensity")->setHoverable(isPartSelected);

		screen->getButton("isBright")->setTextContent(isBright ? "Bright: ON" : "Bright: OFF");
		screen->getButton("isShadowed")->setTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
		screen->getButton("isReflected")->setTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isSpecular")->setTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
		screen->getButton("isReflective")->setTextContent(isReflective ? "Reflective: ON" : "Reflective: OFF");
		switch(reflectionType)
		{
			case ReflectionType::CUBE:
			{
				screen->getButton("reflectionType")->setTextContent("Type: CUBE");
				break;
			}
			case ReflectionType::PLANAR:
			{
				screen->getButton("reflectionType")->setTextContent("Type: PLANAR");
				break;
			}
		}
	}
}