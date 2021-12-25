#include "terrain_editor.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

void TerrainEditor::_updateLightingMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "terrainEditorMenuLighting")
	{
		bool isSpecular = _fe3d.terrain_isSpecular(_currentTerrainID);
		float specularShininess = _fe3d.terrain_getSpecularShininess(_currentTerrainID);
		float specularIntensity = _fe3d.terrain_getSpecularIntensity(_currentTerrainID);
		float lightness = _fe3d.terrain_getLightness(_currentTerrainID);

		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			isSpecular = !isSpecular;
			_fe3d.terrain_setSpecular(_currentTerrainID, isSpecular);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui.getOverlay()->createValueForm("specularShininess", "Specular Shininess", specularShininess, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui.getOverlay()->createValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui.getOverlay()->createValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui.getOverlay()->checkValueForm("specularShininess", specularShininess))
		{
			_fe3d.terrain_setSpecularShininess(_currentTerrainID, specularShininess);
		}
		if(_gui.getOverlay()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d.terrain_setSpecularIntensity(_currentTerrainID, specularIntensity);
		}
		if(_gui.getOverlay()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d.terrain_setLightness(_currentTerrainID, lightness);
		}

		screen->getButton("specularShininess")->setHoverable(isSpecular);
		screen->getButton("specularIntensity")->setHoverable(isSpecular);

		screen->getButton("isSpecular")->changeTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
	}
}