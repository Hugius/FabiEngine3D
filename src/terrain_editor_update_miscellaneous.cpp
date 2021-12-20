#include "terrain_editor.hpp"

void TerrainEditor::_updateMiscellaneousMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "terrainEditorMenuMiscellaneous")
	{
		// Temporary values
		auto textureRepeat = _fe3d.terrain_getTextureRepeat(_currentTerrainID);
		auto redRepeat = _fe3d.terrain_getRedRepeat(_currentTerrainID);
		auto greenRepeat = _fe3d.terrain_getGreenRepeat(_currentTerrainID);
		auto blueRepeat = _fe3d.terrain_getBlueRepeat(_currentTerrainID);
		auto hasBlendMap = _fe3d.terrain_hasBlendMap(_currentTerrainID);
		auto hasDiffuseMap = _fe3d.terrain_hasDiffuseMap(_currentTerrainID);
		auto hasNormalMap = _fe3d.terrain_hasNormalMap(_currentTerrainID);
		auto hasRedDiffuseMap = _fe3d.terrain_hasRedDiffuseMap(_currentTerrainID);
		auto hasGreenDiffuseMap = _fe3d.terrain_hasGreenDiffuseMap(_currentTerrainID);
		auto hasBlueDiffuseMap = _fe3d.terrain_hasBlueDiffuseMap(_currentTerrainID);
		auto hasRedNormalMap = _fe3d.terrain_hasRedNormalMap(_currentTerrainID);
		auto hasGreenNormalMap = _fe3d.terrain_hasGreenNormalMap(_currentTerrainID);
		auto hasBlueNormalMap = _fe3d.terrain_hasBlueNormalMap(_currentTerrainID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui.getOverlay()->createValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("redRepeat")->isHovered())
		{
			_gui.getOverlay()->createValueForm("redRepeat", "Red Repeat", redRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("greenRepeat")->isHovered())
		{
			_gui.getOverlay()->createValueForm("greenRepeat", "Green Repeat", greenRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blueRepeat")->isHovered())
		{
			_gui.getOverlay()->createValueForm("blueRepeat", "Blue Repeat", blueRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getOverlay()->checkValueForm("textureRepeat", textureRepeat))
		{
			_fe3d.terrain_setTextureRepeat(_currentTerrainID, textureRepeat);
		}
		if(_gui.getOverlay()->checkValueForm("redRepeat", redRepeat))
		{
			_fe3d.terrain_setRedRepeat(_currentTerrainID, redRepeat);
		}
		if(_gui.getOverlay()->checkValueForm("greenRepeat", greenRepeat))
		{
			_fe3d.terrain_setGreenRepeat(_currentTerrainID, greenRepeat);
		}
		if(_gui.getOverlay()->checkValueForm("blueRepeat", blueRepeat))
		{
			_fe3d.terrain_setBlueRepeat(_currentTerrainID, blueRepeat);
		}

		// Update buttons hoverability
		screen->getButton("textureRepeat")->setHoverable(hasDiffuseMap || hasNormalMap);
		screen->getButton("redRepeat")->setHoverable(hasRedDiffuseMap || hasRedNormalMap);
		screen->getButton("greenRepeat")->setHoverable(hasGreenDiffuseMap || hasGreenNormalMap);
		screen->getButton("blueRepeat")->setHoverable(hasBlueDiffuseMap || hasBlueNormalMap);
	}
}