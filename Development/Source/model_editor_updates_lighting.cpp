#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateModelEditingLighting()
{
	auto screen = _leftWindow->getScreen("modelEditorMenuLighting");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("isSpecular")->isHovered())
		{
			_fe3d.gameEntity_setSpecularLighted(_currentModelName, !_fe3d.gameEntity_isSpecularLighted(_currentModelName));
		}
		else if (screen->getButton("specularFactor")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("specularFactor", "Specular factor (0-256)",
				_fe3d.gameEntity_getSpecularFactor(_currentModelName), vec2(0.0f, 0.1f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("specularIntensity")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("specularIntensity", "Specular intensity (%)",
				_fe3d.gameEntity_getSpecularIntensity(_currentModelName) * 100.0f, vec2(0.0f, 0.1f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("modelLightness")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("modelLightness", "Model lightness (%)",
				_fe3d.gameEntity_getLightness(_currentModelName) * 100.0f, vec2(0.0f, 0.1f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("isShadowed")->isHovered())
		{
			_fe3d.gameEntity_setShadowed(_currentModelName, !_fe3d.gameEntity_isShadowed(_currentModelName));
		}
		else if (screen->getButton("isReflectiveSurface")->isHovered())
		{
			_fe3d.gameEntity_setSceneReflective(_currentModelName, !_fe3d.gameEntity_isSceneReflective(_currentModelName));
		}
		else if (screen->getButton("back")->isHovered())
		{
			_leftWindow->setActiveScreen("modelEditorMenuChoice");
		}
	}

	// Update GUI button contents
	auto specularID = screen->getButton("isSpecular")->getTextfield()->getEntityID();
	auto isSpecular = _fe3d.gameEntity_isSpecularLighted(_currentModelName);
	auto shadowedID = screen->getButton("isShadowed")->getTextfield()->getEntityID();
	auto isShadowed = _fe3d.gameEntity_isShadowed(_currentModelName);
	auto reflectiveID = screen->getButton("isReflectiveSurface")->getTextfield()->getEntityID();
	auto isReflective = _fe3d.gameEntity_isSceneReflective(_currentModelName);
	_fe3d.textEntity_setTextContent(specularID, isSpecular ? "Specular: ON" : "Specular: OFF");
	_fe3d.textEntity_setTextContent(shadowedID, isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	_fe3d.textEntity_setTextContent(reflectiveID, isReflective ? "Reflective: ON" : "Reflective: OFF");

	// Update specular factor
	float factor = _fe3d.gameEntity_getSpecularFactor(_currentModelName);
	if (_gui->getGlobalScreen()->checkValueForm("specularFactor", factor))
	{
		factor = std::clamp(factor, 0.0f, 256.0f);
		_fe3d.gameEntity_setSpecularFactor(_currentModelName, factor);
	}

	// Update specular intensity
	float intensity = _fe3d.gameEntity_getSpecularIntensity(_currentModelName);
	if (_gui->getGlobalScreen()->checkValueForm("specularIntensity", intensity))
	{
		intensity = std::clamp(intensity / 100.0f, 0.0f, 1.0f);
		_fe3d.gameEntity_setSpecularIntensity(_currentModelName, intensity);
	}

	// Update lightness
	float lightness = _fe3d.gameEntity_getLightness(_currentModelName);
	if (_gui->getGlobalScreen()->checkValueForm("modelLightness", lightness))
	{
		lightness = std::clamp(lightness / 100.0f, 0.0f, 1.0f);
		_fe3d.gameEntity_setLightness(_currentModelName, lightness);
	}

	// Update specular buttons hoverability
	screen->getButton("specularFactor")->setHoverable(_fe3d.gameEntity_isSpecularLighted(_currentModelName));
	screen->getButton("specularIntensity")->setHoverable(_fe3d.gameEntity_isSpecularLighted(_currentModelName));
}