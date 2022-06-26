#include "model_editor.hpp"
#include "tools.hpp"

void ModelEditor::_updateLightingMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuLighting")
	{
		const auto isPartSelected = (!_fe3d->model_isMultiParted(_currentModelId) || !_currentPartId.empty());
		const auto isNoPartSelected = (!_fe3d->model_isMultiParted(_currentModelId) || _currentPartId.empty());
		const auto isSpecular = (isPartSelected ? _fe3d->model_isSpecular(_currentModelId, _currentPartId) : false);
		const auto isReflective = (isPartSelected ? _fe3d->model_isReflective(_currentModelId, _currentPartId) : false);
		const auto isRefractive = (isPartSelected ? _fe3d->model_isRefractive(_currentModelId, _currentPartId) : false);
		const auto reflectionType = (isPartSelected ? _fe3d->model_getReflectionType(_currentModelId, _currentPartId) : ReflectionType::CUBE);
		const auto refractionType = (isPartSelected ? _fe3d->model_getRefractionType(_currentModelId, _currentPartId) : RefractionType::CUBE);
		const auto reflectivity = (isPartSelected ? _fe3d->model_getReflectivity(_currentModelId, _currentPartId) : 0.0f);
		const auto refractivity = (isPartSelected ? _fe3d->model_getRefractivity(_currentModelId, _currentPartId) : 0.0f);
		const auto specularShininess = (isPartSelected ? _fe3d->model_getSpecularShininess(_currentModelId, _currentPartId) : 0.0f);
		const auto specularIntensity = (isPartSelected ? _fe3d->model_getSpecularIntensity(_currentModelId, _currentPartId) : 0.0f);
		const auto lightness = (isPartSelected ? _fe3d->model_getLightness(_currentModelId, _currentPartId) : 0.0f);
		const auto color = (isPartSelected ? _fe3d->model_getColor(_currentModelId, _currentPartId) : fvec3(0.0f));
		const auto isBright = (isPartSelected ? _fe3d->model_isBright(_currentModelId, _currentPartId) : false);
		const auto isShadowed = (isNoPartSelected ? _fe3d->model_isShadowed(_currentModelId) : false);
		const auto isReflected = (isNoPartSelected ? _fe3d->model_isReflected(_currentModelId) : false);
		const auto isRefracted = (isNoPartSelected ? _fe3d->model_isRefracted(_currentModelId) : false);
		const auto emissionIntensity = (isPartSelected ? _fe3d->model_getEmissionIntensity(_currentModelId, _currentPartId) : 0.0f);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * LIGHTNESS_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			_fe3d->model_setSpecular(_currentModelId, _currentPartId, !isSpecular);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularShininess", "Specular Shininess", specularShininess, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularIntensity", "Specular Intensity", (specularIntensity * SPECULAR_INTENSITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isReflective")->isHovered())
		{
			_fe3d->model_setReflective(_currentModelId, _currentPartId, !isReflective);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isRefractive")->isHovered())
		{
			_fe3d->model_setRefractive(_currentModelId, _currentPartId, !isRefractive);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			_fe3d->model_setBright(_currentModelId, _currentPartId, !isBright);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			_fe3d->model_setShadowed(_currentModelId, !isShadowed);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			_fe3d->model_setReflected(_currentModelId, !isReflected);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isRefracted")->isHovered())
		{
			_fe3d->model_setRefracted(_currentModelId, !isRefracted);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("reflectionType")->isHovered())
		{
			switch(reflectionType)
			{
				case ReflectionType::CUBE:
				{
					_fe3d->model_setReflectionType(_currentModelId, _currentPartId, ReflectionType::PLANAR);

					break;
				}
				case ReflectionType::PLANAR:
				{
					_fe3d->model_setReflectionType(_currentModelId, _currentPartId, ReflectionType::CUBE);

					break;
				}
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("refractionType")->isHovered())
		{
			switch(refractionType)
			{
				case RefractionType::CUBE:
				{
					_fe3d->model_setRefractionType(_currentModelId, _currentPartId, RefractionType::PLANAR);

					break;
				}
				case RefractionType::PLANAR:
				{
					_fe3d->model_setRefractionType(_currentModelId, _currentPartId, RefractionType::CUBE);

					break;
				}
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("reflectivity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("reflectivity", "Reflectivity", (reflectivity * REFLECTIVITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("refractivity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("refractivity", "Refractivity", (refractivity * REFRACTIVITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("emissionIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("emissionIntensity", "Emission Intensity", (emissionIntensity * EMISSION_INTENSITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setColor(_currentModelId, _currentPartId, fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setColor(_currentModelId, _currentPartId, fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setColor(_currentModelId, _currentPartId, fvec3(color.r, color.g, (value / COLOR_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setLightness(_currentModelId, _currentPartId, (value / LIGHTNESS_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "specularShininess") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setSpecularShininess(_currentModelId, _currentPartId, value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "specularIntensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setSpecularIntensity(_currentModelId, _currentPartId, (value / SPECULAR_INTENSITY_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "reflectivity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setReflectivity(_currentModelId, _currentPartId, (value / REFLECTIVITY_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "refractivity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setRefractivity(_currentModelId, _currentPartId, (value / REFRACTIVITY_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "emissionIntensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setEmissionIntensity(_currentModelId, _currentPartId, (value / EMISSION_INTENSITY_FACTOR));
		}

		screen->getButton("color")->setHoverable(isPartSelected, true);
		screen->getButton("lightness")->setHoverable(isPartSelected, true);
		screen->getButton("isSpecular")->setHoverable(isPartSelected, true);
		screen->getButton("specularShininess")->setHoverable(isPartSelected, true);
		screen->getButton("specularIntensity")->setHoverable(isPartSelected, true);
		screen->getButton("isReflective")->setHoverable(isPartSelected, true);
		screen->getButton("isRefractive")->setHoverable(isPartSelected, true);
		screen->getButton("reflectionType")->setHoverable(isPartSelected, true);
		screen->getButton("refractionType")->setHoverable(isPartSelected, true);
		screen->getButton("reflectivity")->setHoverable(isPartSelected, true);
		screen->getButton("refractivity")->setHoverable(isPartSelected, true);
		screen->getButton("isBright")->setHoverable(isPartSelected, true);
		screen->getButton("isShadowed")->setHoverable(isNoPartSelected, true);
		screen->getButton("isReflected")->setHoverable(isNoPartSelected, true);
		screen->getButton("isRefracted")->setHoverable(isNoPartSelected, true);
		screen->getButton("emissionIntensity")->setHoverable(isPartSelected, true);
		screen->getButton("isBright")->setTextContent(isBright ? "Bright: ON" : "Bright: OFF");
		screen->getButton("isShadowed")->setTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
		screen->getButton("isReflected")->setTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isRefracted")->setTextContent(isRefracted ? "Refracted: ON" : "Refracted: OFF");
		screen->getButton("isSpecular")->setTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
		screen->getButton("isReflective")->setTextContent(isReflective ? "Reflective: ON" : "Reflective: OFF");
		screen->getButton("isRefractive")->setTextContent(isRefractive ? "Refractive: ON" : "Refractive: OFF");

		switch(reflectionType)
		{
			case ReflectionType::CUBE:
			{
				screen->getButton("reflectionType")->setTextContent("Reflection: CUBE");

				break;
			}
			case ReflectionType::PLANAR:
			{
				screen->getButton("reflectionType")->setTextContent("Reflection: PLANAR");

				break;
			}
		}

		switch(refractionType)
		{
			case RefractionType::CUBE:
			{
				screen->getButton("refractionType")->setTextContent("Refraction: CUBE");

				break;
			}
			case RefractionType::PLANAR:
			{
				screen->getButton("refractionType")->setTextContent("Refraction: PLANAR");

				break;
			}
		}
	}
}