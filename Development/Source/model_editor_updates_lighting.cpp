#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateLightingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "modelEditorMenuLighting")
	{
		// Temporary values
		auto isSpecular = _fe3d.modelEntity_isSpecularLighted(_currentModelID);
		auto reflectionType = _fe3d.modelEntity_getReflectionType(_currentModelID);
		auto specularFactor = _fe3d.modelEntity_getSpecularFactor(_currentModelID);
		auto specularIntensity = _fe3d.modelEntity_getSpecularIntensity(_currentModelID);
		auto lightness = _fe3d.modelEntity_getLightness(_currentModelID);
		auto isBright = _fe3d.modelEntity_isBright(_currentModelID);

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
				_gui.getGlobalScreen()->addValueForm("specularFactor", "Spec Factor", specularFactor, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("specularIntensity")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("specularIntensity", "Spec Intensity", specularIntensity * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("lightness", "Lightness", lightness * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("reflectionType")->isHovered())
			{
				if (reflectionType == ReflectionType::SKY)
				{
					reflectionType = ReflectionType::SCENE;
				}
				else
				{
					reflectionType = ReflectionType::SKY;
				}
				_fe3d.modelEntity_setReflectionType(_currentModelID, reflectionType);
			}
			else if (screen->getButton("isBright")->isHovered())
			{
				isBright = !isBright;
				_fe3d.modelEntity_setBright(_currentModelID, isBright);
			}
		}

		// Button text contents
		screen->getButton("isSpecular")->changeTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
		screen->getButton("reflectionType")->changeTextContent((reflectionType == ReflectionType::SKY) ? "Reflect: SKY" : "Reflect: SCENE");
		screen->getButton("isBright")->changeTextContent(isBright ? "Bright: ON" : "Bright: OFF");

		// Update specular factor
		if (_gui.getGlobalScreen()->hasValueFormChanged("specularFactor", specularFactor))
		{
			specularFactor = std::clamp(specularFactor, 0.0f, 256.0f);
			_fe3d.modelEntity_setSpecularFactor(_currentModelID, specularFactor);
		}

		// Update specular intensity
		if (_gui.getGlobalScreen()->hasValueFormChanged("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d.modelEntity_setSpecularIntensity(_currentModelID, specularIntensity);
		}

		// Update lightness
		if (_gui.getGlobalScreen()->hasValueFormChanged("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d.modelEntity_setLightness(_currentModelID, lightness);
		}

		// Update buttons hoverability
		screen->getButton("specularFactor")->setHoverable(_fe3d.modelEntity_isSpecularLighted(_currentModelID));
		screen->getButton("specularIntensity")->setHoverable(_fe3d.modelEntity_isSpecularLighted(_currentModelID));
		screen->getButton("reflectionType")->setHoverable(_fe3d.modelEntity_hasReflectionMap(_currentModelID));
	}
}