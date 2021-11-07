#include "terrain_editor.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

void TerrainEditor::_updateLightingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "terrainEditorMenuLighting")
	{
		// Temporary values
		bool isSpecular = _fe3d.terrainEntity_isSpecular(_currentTerrainID);
		float specularShininess = _fe3d.terrainEntity_getSpecularShininess(_currentTerrainID);
		float specularIntensity = _fe3d.terrainEntity_getSpecularIntensity(_currentTerrainID);
		float lightness = _fe3d.terrainEntity_getLightness(_currentTerrainID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			isSpecular = !isSpecular;
			_fe3d.terrainEntity_setSpecular(_currentTerrainID, isSpecular);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("specularShininess", "Specular Shininess", specularShininess, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", (lightness * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("specularShininess", specularShininess))
		{
			specularShininess = min(256.0f, specularShininess);
			_fe3d.terrainEntity_setSpecularShininess(_currentTerrainID, specularShininess);
		}
		if(_gui.getGlobalScreen()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d.terrainEntity_setSpecularIntensity(_currentTerrainID, specularIntensity);
		}
		if(_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d.terrainEntity_setLightness(_currentTerrainID, lightness);
		}

		// Update buttons hoverability
		screen->getButton("specularShininess")->setHoverable(isSpecular);
		screen->getButton("specularIntensity")->setHoverable(isSpecular);

		// Update button text contents
		screen->getButton("isSpecular")->changeTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
	}
}