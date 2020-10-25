#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateModelEditingLighting()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("modelEditorMenuLighting");

	// GUI management
	if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("isSpecular")->isHovered())
		{
			_fe3d.gameEntity_setSpecularLighted(_currentModelID, !_fe3d.gameEntity_isSpecularLighted(_currentModelID));
		}
		else if (screen->getButton("specularFactor")->isHovered())
		{
			_gui.getGlobalScreen()->addValueForm("specularFactor", "Specular factor (0-256)",
				_fe3d.gameEntity_getSpecularFactor(_currentModelID), vec2(0.0f, 0.1f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("specularIntensity")->isHovered())
		{
			_gui.getGlobalScreen()->addValueForm("specularIntensity", "Specular intensity (%)",
				_fe3d.gameEntity_getSpecularIntensity(_currentModelID) * 100.0f, vec2(0.0f, 0.1f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("modelLightness")->isHovered())
		{
			_gui.getGlobalScreen()->addValueForm("modelLightness", "Model lightness (%)",
				_fe3d.gameEntity_getLightness(_currentModelID) * 100.0f, vec2(0.0f, 0.1f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("isShadowed")->isHovered())
		{
			_fe3d.gameEntity_setShadowed(_currentModelID, !_fe3d.gameEntity_isShadowed(_currentModelID));
		}
		else if (screen->getButton("isReflectiveSurface")->isHovered())
		{
			_fe3d.gameEntity_setSceneReflective(_currentModelID, !_fe3d.gameEntity_isSceneReflective(_currentModelID));
		}
		else if (screen->getButton("back")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
		}
	}

	// Update GUI button contents
	auto specularID = screen->getButton("isSpecular")->getTextfield()->getEntityID();
	auto isSpecular = _fe3d.gameEntity_isSpecularLighted(_currentModelID);
	auto shadowedID = screen->getButton("isShadowed")->getTextfield()->getEntityID();
	auto isShadowed = _fe3d.gameEntity_isShadowed(_currentModelID);
	auto reflectiveID = screen->getButton("isReflectiveSurface")->getTextfield()->getEntityID();
	auto isReflective = _fe3d.gameEntity_isSceneReflective(_currentModelID);
	_fe3d.textEntity_setTextContent(specularID, isSpecular ? "Specular: ON" : "Specular: OFF");
	_fe3d.textEntity_setTextContent(shadowedID, isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	_fe3d.textEntity_setTextContent(reflectiveID, isReflective ? "Reflective: ON" : "Reflective: OFF");

	// Update specular factor
	float factor = _fe3d.gameEntity_getSpecularFactor(_currentModelID);
	if (_gui.getGlobalScreen()->checkValueForm("specularFactor", factor))
	{
		factor = std::clamp(factor, 0.0f, 256.0f);
		_fe3d.gameEntity_setSpecularFactor(_currentModelID, factor);
	}

	// Update specular intensity
	float intensity = _fe3d.gameEntity_getSpecularIntensity(_currentModelID);
	if (_gui.getGlobalScreen()->checkValueForm("specularIntensity", intensity))
	{
		intensity /= 100.0f;
		_fe3d.gameEntity_setSpecularIntensity(_currentModelID, intensity);
	}

	// Update lightness
	float lightness = _fe3d.gameEntity_getLightness(_currentModelID);
	if (_gui.getGlobalScreen()->checkValueForm("modelLightness", lightness))
	{
		lightness /= 100.0f;
		_fe3d.gameEntity_setLightness(_currentModelID, lightness);
	}

	// Update reflective button hoverability
	screen->getButton("isReflectiveSurface")->setHoverable(false);
	bool hoverable = true;
	for (auto& entityID : _fe3d.gameEntity_getAllIDs())
	{
		// If model is reflective
		if (_fe3d.gameEntity_isSceneReflective(entityID))
		{
			// If current model is reflective, it's allowed to change
			if (entityID != _currentModelID)
			{
				hoverable = false;
			}
		}
	}
	screen->getButton("isReflectiveSurface")->setHoverable(hoverable);
	
	// Update specular buttons hoverability
	screen->getButton("specularFactor")->setHoverable(_fe3d.gameEntity_isSpecularLighted(_currentModelID));
	screen->getButton("specularIntensity")->setHoverable(_fe3d.gameEntity_isSpecularLighted(_currentModelID));
}