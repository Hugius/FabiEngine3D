#include "terrain_editor.hpp"

void TerrainEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "terrainEditorMenuMiscellaneous")
	{
		auto maxHeight = _fe3d->terrain_getMaxHeight(_currentTerrainId);
		auto textureRepeat = _fe3d->terrain_getTextureRepeat(_currentTerrainId);
		auto redTextureRepeat = _fe3d->terrain_getRedTextureRepeat(_currentTerrainId);
		auto greenTextureRepeat = _fe3d->terrain_getGreenTextureRepeat(_currentTerrainId);
		auto blueTextureRepeat = _fe3d->terrain_getBlueTextureRepeat(_currentTerrainId);
		auto hasBlendMap = _fe3d->terrain_hasBlendMap(_currentTerrainId);
		auto hasDiffuseMap = _fe3d->terrain_hasDiffuseMap(_currentTerrainId);
		auto hasNormalMap = _fe3d->terrain_hasNormalMap(_currentTerrainId);
		auto hasRedDiffuseMap = _fe3d->terrain_hasRedDiffuseMap(_currentTerrainId);
		auto hasGreenDiffuseMap = _fe3d->terrain_hasGreenDiffuseMap(_currentTerrainId);
		auto hasBlueDiffuseMap = _fe3d->terrain_hasBlueDiffuseMap(_currentTerrainId);
		auto hasRedNormalMap = _fe3d->terrain_hasRedNormalMap(_currentTerrainId);
		auto hasGreenNormalMap = _fe3d->terrain_hasGreenNormalMap(_currentTerrainId);
		auto hasBlueNormalMap = _fe3d->terrain_hasBlueNormalMap(_currentTerrainId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxHeight")->isHovered())
		{
			_gui->getOverlay()->createValueForm("maxHeight", "Max Height", maxHeight, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui->getOverlay()->createValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("redTextureRepeat")->isHovered())
		{
			_gui->getOverlay()->createValueForm("redTextureRepeat", "Red Repeat", redTextureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("greenTextureRepeat")->isHovered())
		{
			_gui->getOverlay()->createValueForm("greenTextureRepeat", "Green Repeat", greenTextureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blueTextureRepeat")->isHovered())
		{
			_gui->getOverlay()->createValueForm("blueTextureRepeat", "Blue Repeat", blueTextureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("maxHeight", maxHeight))
		{
			_fe3d->terrain_setMaxHeight(_currentTerrainId, maxHeight);
		}
		if(_gui->getOverlay()->checkValueForm("textureRepeat", textureRepeat))
		{
			_fe3d->terrain_setTextureRepeat(_currentTerrainId, textureRepeat);
		}
		if(_gui->getOverlay()->checkValueForm("redTextureRepeat", redTextureRepeat))
		{
			_fe3d->terrain_setRedTextureRepeat(_currentTerrainId, redTextureRepeat);
		}
		if(_gui->getOverlay()->checkValueForm("greenTextureRepeat", greenTextureRepeat))
		{
			_fe3d->terrain_setGreenTextureRepeat(_currentTerrainId, greenTextureRepeat);
		}
		if(_gui->getOverlay()->checkValueForm("blueTextureRepeat", blueTextureRepeat))
		{
			_fe3d->terrain_setBlueTextureRepeat(_currentTerrainId, blueTextureRepeat);
		}
	}
}