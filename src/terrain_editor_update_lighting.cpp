#include "terrain_editor.hpp"

#include <algorithm>
#include "tools.hpp"

using std::clamp;

void TerrainEditor::_updateLightingMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "terrainEditorMenuLighting")
	{
		const auto isSpecular = _fe3d->terrain_isSpecular(_currentTerrainId);
		const auto specularShininess = _fe3d->terrain_getSpecularShininess(_currentTerrainId);
		const auto specularIntensity = _fe3d->terrain_getSpecularIntensity(_currentTerrainId);
		const auto lightness = _fe3d->terrain_getLightness(_currentTerrainId);
		const auto color = _fe3d->terrain_getColor(_currentTerrainId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isSpecular")->isHovered())
		{
			_fe3d->terrain_setSpecular(_currentTerrainId, !isSpecular);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularShininess", "Specular Shininess", specularShininess, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("specularIntensity", "Specular Intensity", (specularIntensity * SPECULAR_INTENSITY_FACTOR), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * LIGHTNESS_FACTOR), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_FACTOR), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_FACTOR), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_FACTOR), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "specularShininess") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->terrain_setSpecularShininess(_currentTerrainId, value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "specularIntensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->terrain_setSpecularIntensity(_currentTerrainId, (value / SPECULAR_INTENSITY_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->terrain_setLightness(_currentTerrainId, (value / LIGHTNESS_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->terrain_setColor(_currentTerrainId, fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->terrain_setColor(_currentTerrainId, fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->terrain_setColor(_currentTerrainId, fvec3(color.r, color.g, (value / COLOR_FACTOR)));
		}

		screen->getButton("isSpecular")->setTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
	}
}