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
		const auto reflectionType = (isPartSelected ? _fe3d->model_getReflectionType(_currentModelId, _currentPartId) : ReflectionType::CUBE);
		const auto reflectivity = (isPartSelected ? _fe3d->model_getReflectivity(_currentModelId, _currentPartId) : 0.0f);
		const auto specularShininess = (isPartSelected ? _fe3d->model_getSpecularShininess(_currentModelId, _currentPartId) : 0.0f);
		const auto specularIntensity = (isPartSelected ? _fe3d->model_getSpecularIntensity(_currentModelId, _currentPartId) : 0.0f);
		const auto lightness = (isPartSelected ? _fe3d->model_getLightness(_currentModelId, _currentPartId) : 0.0f);
		const auto color = (isPartSelected ? _fe3d->model_getColor(_currentModelId, _currentPartId) : fvec3(0.0f));
		const auto isBright = (isPartSelected ? _fe3d->model_isBright(_currentModelId, _currentPartId) : false);
		const auto isShadowed = (isNoPartSelected ? _fe3d->model_isShadowed(_currentModelId) : false);
		const auto isReflected = (isNoPartSelected ? _fe3d->model_isReflected(_currentModelId) : false);
		const auto emissionIntensity = (isPartSelected ? _fe3d->model_getEmissionIntensity(_currentModelId, _currentPartId) : 0.0f);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			_fe3d->model_setSpecular(_currentModelId, _currentPartId, !isSpecular);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularShininess", "Specular Shininess", specularShininess, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isReflective")->isHovered())
		{
			_fe3d->model_setReflective(_currentModelId, _currentPartId, !isReflective);
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
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("reflectivity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("reflectivity", "Reflectivity", (reflectivity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("emissionIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("emissionIntensity", "Emission Intensity", (emissionIntensity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setColor(_currentModelId, _currentPartId, fvec3((value / COLOR_MULTIPLIER), color.g, color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setColor(_currentModelId, _currentPartId, fvec3(color.r, (value / COLOR_MULTIPLIER), color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setColor(_currentModelId, _currentPartId, fvec3(color.r, color.g, (value / COLOR_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setLightness(_currentModelId, _currentPartId, (value / 100.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "specularShininess") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setSpecularShininess(_currentModelId, _currentPartId, value);
		}
		if((_gui->getOverlay()->getValueFormId() == "specularIntensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setSpecularIntensity(_currentModelId, _currentPartId, (value / 100.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "reflectivity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setReflectivity(_currentModelId, _currentPartId, (value / 100.0f));
		}
		if((_gui->getOverlay()->getValueFormId() == "emissionIntensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setEmissionIntensity(_currentModelId, _currentPartId, (value / 100.0f));
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