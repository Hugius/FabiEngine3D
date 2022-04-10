#include "terrain_editor.hpp"
#include "tools.hpp"

void TerrainEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "terrainEditorMenuMiscellaneous")
	{
		const auto maxHeight = _fe3d->terrain_getMaxHeight(_currentTerrainId);
		const auto textureRepeat = _fe3d->terrain_getTextureRepeat(_currentTerrainId);
		const auto redTextureRepeat = _fe3d->terrain_getRedTextureRepeat(_currentTerrainId);
		const auto greenTextureRepeat = _fe3d->terrain_getGreenTextureRepeat(_currentTerrainId);
		const auto blueTextureRepeat = _fe3d->terrain_getBlueTextureRepeat(_currentTerrainId);

		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("maxHeight")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxHeight", "Max Height", maxHeight, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("redTextureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("redTextureRepeat", "Red Texture Repeat", redTextureRepeat, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("greenTextureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("greenTextureRepeat", "Green Texture Repeat", greenTextureRepeat, fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("blueTextureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("blueTextureRepeat", "Blue Texture Repeat", blueTextureRepeat, fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "maxHeight") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->terrain_setMaxHeight(_currentTerrainId, content);
		}
		if((_gui->getOverlay()->getValueFormId() == "textureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<unsigned int>(max(0, Tools::parseInteger(_gui->getOverlay()->getValueFormContent())));

			_fe3d->terrain_setTextureRepeat(_currentTerrainId, content);
		}
		if((_gui->getOverlay()->getValueFormId() == "redTextureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<unsigned int>(max(0, Tools::parseInteger(_gui->getOverlay()->getValueFormContent())));

			_fe3d->terrain_setRedTextureRepeat(_currentTerrainId, content);
		}
		if((_gui->getOverlay()->getValueFormId() == "greenTextureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<unsigned int>(max(0, Tools::parseInteger(_gui->getOverlay()->getValueFormContent())));

			_fe3d->terrain_setGreenTextureRepeat(_currentTerrainId, content);
		}
		if((_gui->getOverlay()->getValueFormId() == "blueTextureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<unsigned int>(max(0, Tools::parseInteger(_gui->getOverlay()->getValueFormContent())));

			_fe3d->terrain_setBlueTextureRepeat(_currentTerrainId, content);
		}
	}
}