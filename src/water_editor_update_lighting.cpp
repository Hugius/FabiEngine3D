#include "water_editor.hpp"
#include "logger.hpp"

void WaterEditor::_updateLightingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "waterEditorMenuLighting")
	{
		auto color = _fe3d->water_getColor(_currentWaterId);
		bool isReflective = _fe3d->water_isReflective(_currentWaterId);
		bool isRefractive = _fe3d->water_isRefractive(_currentWaterId);
		bool isSpecular = _fe3d->water_isSpecular(_currentWaterId);
		bool isEdged = _fe3d->water_isEdged(_currentWaterId);
		auto specularShininess = _fe3d->water_getSpecularShininess(_currentWaterId);
		auto specularIntensity = _fe3d->water_getSpecularIntensity(_currentWaterId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isReflective")->isHovered())
		{
			isReflective = !isReflective;
			_fe3d->water_setReflective(_currentWaterId, isReflective);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isRefractive")->isHovered())
		{
			isRefractive = !isRefractive;
			_fe3d->water_setRefractive(_currentWaterId, isRefractive);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			isSpecular = !isSpecular;
			_fe3d->water_setSpecular(_currentWaterId, isSpecular);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isEdged")->isHovered())
		{
			isEdged = !isEdged;
			_fe3d->water_setEdged(_currentWaterId, isEdged);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularShininess", "Specular Shininess", specularShininess, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("colorR", color.r))
		{
			color.r /= 255.0f;
			_fe3d->water_setColor(_currentWaterId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("colorG", color.g))
		{
			color.g /= 255.0f;
			_fe3d->water_setColor(_currentWaterId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("colorB", color.b))
		{
			color.b /= 255.0f;
			_fe3d->water_setColor(_currentWaterId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("specularShininess", specularShininess))
		{
			_fe3d->water_setSpecularShininess(_currentWaterId, specularShininess);
		}
		//if(_gui->getOverlay()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d->water_setSpecularIntensity(_currentWaterId, specularIntensity);
		}

		screen->getButton("isReflective")->setTextContent(isReflective ? "Reflective: ON" : "Reflective: OFF");
		screen->getButton("isRefractive")->setTextContent(isRefractive ? "Refractive: ON" : "Refractive: OFF");
		screen->getButton("isSpecular")->setTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
		screen->getButton("isEdged")->setTextContent(isEdged ? "Edged: ON" : "Edged: OFF");
	}
}