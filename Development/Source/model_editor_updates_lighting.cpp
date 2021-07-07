#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateModelEditingLighting()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "modelEditorMenuLighting")
	{
		// Temporary values
		auto isSpecular = _fe3d.modelEntity_isSpecularLighted(_currentModelID);
		auto isSkyReflective = _fe3d.modelEntity_isSkyReflective(_currentModelID);
		auto isSceneReflective = _fe3d.modelEntity_isSceneReflective(_currentModelID);
		auto specularFactor = _fe3d.modelEntity_getSpecularFactor(_currentModelID);
		auto specularIntensity = _fe3d.modelEntity_getSpecularIntensity(_currentModelID);
		auto lightness = _fe3d.modelEntity_getLightness(_currentModelID);
		auto isBloomed = _fe3d.modelEntity_isBloomed(_currentModelID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			}
			else if (screen->getButton("isSpecular")->isHovered())
			{
				isSpecular = !isSpecular;
				_fe3d.modelEntity_setSpecularLighted(_currentModelID, isSpecular);
			}
			else if (screen->getButton("specularFactor")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("specularFactor", "Spec Factor", specularFactor, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("specularIntensity")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("specularIntensity", "Spec Intensity", specularIntensity * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("lightness", "Lightness", lightness * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("reflectionType")->isHovered())
			{
				if (isSceneReflective)
				{
					_fe3d.modelEntity_setSceneReflective(_currentModelID, false);
				}
				else if (isSkyReflective)
				{
					_fe3d.modelEntity_setSkyReflective(_currentModelID, false);
					_fe3d.modelEntity_setSceneReflective(_currentModelID, true);
				}
				else
				{
					_fe3d.modelEntity_setSkyReflective(_currentModelID, true);
				}
			}
			else if (screen->getButton("isBloomed")->isHovered())
			{
				isBloomed = !isBloomed;
				_fe3d.modelEntity_setBloomed(_currentModelID, isBloomed);
			}
		}

		// Button text contents
		screen->getButton("isSpecular")->changeTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
		screen->getButton("reflectionType")->changeTextContent(isSkyReflective ? "Reflect: SKY" : isSceneReflective ? "Reflect: SCENE" : "Reflect: OFF");
		screen->getButton("isBloomed")->changeTextContent(isBloomed ? "Bloomed: ON" : "Bloomed: OFF");

		// Update specular factor
		if (_gui.getGlobalScreen()->checkValueForm("specularFactor", specularFactor))
		{
			specularFactor = std::clamp(specularFactor, 0.0f, 256.0f);
			_fe3d.modelEntity_setSpecularFactor(_currentModelID, specularFactor);
		}

		// Update specular intensity
		if (_gui.getGlobalScreen()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d.modelEntity_setSpecularIntensity(_currentModelID, specularIntensity);
		}

		// Update lightness
		if (_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d.modelEntity_setLightness(_currentModelID, lightness);
		}

		// Update buttons hoverability
		screen->getButton("specularFactor")->setHoverable(_fe3d.modelEntity_isSpecularLighted(_currentModelID));
		screen->getButton("specularIntensity")->setHoverable(_fe3d.modelEntity_isSpecularLighted(_currentModelID));
	}
}