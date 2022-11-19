#include "terrain_editor.hpp"
#include "tools.hpp"

void TerrainEditor::_updateMiscellaneousMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "terrainEditorMenuMiscellaneous")
	{
		const auto maxHeight = _fe3d->terrain_getMaxHeight(_currentTerrainId);
		const auto textureRepeat = _fe3d->terrain_getTextureRepeat(_currentTerrainId);
		const auto redTextureRepeat = _fe3d->terrain_getRedTextureRepeat(_currentTerrainId);
		const auto greenTextureRepeat = _fe3d->terrain_getGreenTextureRepeat(_currentTerrainId);
		const auto blueTextureRepeat = _fe3d->terrain_getBlueTextureRepeat(_currentTerrainId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("maxHeight")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxHeight", "Max Height", maxHeight, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("textureRepeat", "Texture Repeat", textureRepeat, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("redTextureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("redTextureRepeat", "Red Texture Repeat", redTextureRepeat, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("greenTextureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("greenTextureRepeat", "Green Texture Repeat", greenTextureRepeat, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("blueTextureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("blueTextureRepeat", "Blue Texture Repeat", blueTextureRepeat, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "maxHeight") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->terrain_setMaxHeight(_currentTerrainId, value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "textureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->terrain_setTextureRepeat(_currentTerrainId, value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "redTextureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->terrain_setRedTextureRepeat(_currentTerrainId, value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "greenTextureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->terrain_setGreenTextureRepeat(_currentTerrainId, value);
		}
		else if((_gui->getOverlay()->getValueFormId() == "blueTextureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->terrain_setBlueTextureRepeat(_currentTerrainId, value);
		}
	}
}