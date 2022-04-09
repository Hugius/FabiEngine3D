#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WaterEditor::_updateLightingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "waterEditorMenuLighting")
	{
		const auto color = _fe3d->water_getColor(_currentWaterId);
		const auto isReflective = _fe3d->water_isReflective(_currentWaterId);
		const auto isRefractive = _fe3d->water_isRefractive(_currentWaterId);
		const auto isSpecular = _fe3d->water_isSpecular(_currentWaterId);
		const auto isEdged = _fe3d->water_isEdged(_currentWaterId);
		const auto specularShininess = _fe3d->water_getSpecularShininess(_currentWaterId);
		const auto specularIntensity = _fe3d->water_getSpecularIntensity(_currentWaterId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "R", (color.r * COLOR_MULTIPLIER), fvec2(-0.25f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "G", (color.g * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "B", (color.b * COLOR_MULTIPLIER), fvec2(0.25f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflective")->isHovered())
		{
			_fe3d->water_setReflective(_currentWaterId, !isReflective);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isRefractive")->isHovered())
		{
			_fe3d->water_setRefractive(_currentWaterId, !isRefractive);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			_fe3d->water_setSpecular(_currentWaterId, !isSpecular);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEdged")->isHovered())
		{
			_fe3d->water_setEdged(_currentWaterId, !isEdged);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularShininess", "Specular Shininess", specularShininess, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setColor(_currentWaterId, fvec3((content / COLOR_MULTIPLIER), color.g, color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setColor(_currentWaterId, fvec3(color.r, (content / COLOR_MULTIPLIER), color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setColor(_currentWaterId, fvec3(color.r, color.g, (content / COLOR_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "specularShininess") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setSpecularShininess(_currentWaterId, content);
		}
		if((_gui->getOverlay()->getValueFormId() == "specularIntensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseSignedInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->water_setSpecularIntensity(_currentWaterId, (content / 100.0f));
		}

		screen->getButton("isReflective")->setTextContent(isReflective ? "Reflective: ON" : "Reflective: OFF");
		screen->getButton("isRefractive")->setTextContent(isRefractive ? "Refractive: ON" : "Refractive: OFF");
		screen->getButton("isSpecular")->setTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
		screen->getButton("isEdged")->setTextContent(isEdged ? "Edged: ON" : "Edged: OFF");
	}
}