#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateModelEditingLighting()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "modelEditorMenuLighting")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			}
			else if (screen->getButton("isSpecular")->isHovered())
			{
				_fe3d.gameEntity_setSpecularLighted(_currentModelID, !_fe3d.gameEntity_isSpecularLighted(_currentModelID));
			}
			else if (screen->getButton("specularFactor")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("specularFactor", "Spec factor",
					_fe3d.gameEntity_getSpecularFactor(_currentModelID), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("specularIntensity")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("specularIntensity", "Spec intensity",
					_fe3d.gameEntity_getSpecularIntensity(_currentModelID) * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("lightness", "Lightness",
					_fe3d.gameEntity_getLightness(_currentModelID) * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("isShadowed")->isHovered())
			{
				_fe3d.gameEntity_setShadowed(_currentModelID, !_fe3d.gameEntity_isShadowed(_currentModelID));
			}
			else if (screen->getButton("reflectionType")->isHovered())
			{
				if (_fe3d.gameEntity_isSceneReflective(_currentModelID))
				{
					_fe3d.gameEntity_setSceneReflective(_currentModelID, false);
				}
				else if (_fe3d.gameEntity_isSkyReflective(_currentModelID))
				{
					_fe3d.gameEntity_setSkyReflective(_currentModelID, false);
					_fe3d.gameEntity_setSceneReflective(_currentModelID, true);
				}
				else
				{
					_fe3d.gameEntity_setSkyReflective(_currentModelID, true);
				}
			}
		}

		// Update GUI button contents
		auto specularID = screen->getButton("isSpecular")->getTextfield()->getEntityID();
		auto isSpecular = _fe3d.gameEntity_isSpecularLighted(_currentModelID);
		auto shadowedID = screen->getButton("isShadowed")->getTextfield()->getEntityID();
		auto isShadowed = _fe3d.gameEntity_isShadowed(_currentModelID);
		auto reflectiveID = screen->getButton("reflectionType")->getTextfield()->getEntityID();
		auto isSkyReflective = _fe3d.gameEntity_isSkyReflective(_currentModelID);
		auto isSceneReflective = _fe3d.gameEntity_isSceneReflective(_currentModelID);
		_fe3d.textEntity_setTextContent(specularID, isSpecular ? "Specular: ON" : "Specular: OFF");
		_fe3d.textEntity_setTextContent(shadowedID, isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
		_fe3d.textEntity_setTextContent(reflectiveID, isSkyReflective ? "Reflection: sky" : isSceneReflective ? "Reflection: scene" : "Reflective: OFF");

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
		if (_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d.gameEntity_setLightness(_currentModelID, lightness);
		}

		// Update buttons hoverability
		screen->getButton("specularFactor")->setHoverable(_fe3d.gameEntity_isSpecularLighted(_currentModelID));
		screen->getButton("specularIntensity")->setHoverable(_fe3d.gameEntity_isSpecularLighted(_currentModelID));
	}
}