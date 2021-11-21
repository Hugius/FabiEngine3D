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
		auto hasDiffuseMapR = _fe3d.terrain_hasDiffuseMapR(_currentTerrainID);
		auto hasDiffuseMapG = _fe3d.terrain_hasDiffuseMapG(_currentTerrainID);
		auto hasDiffuseMapB = _fe3d.terrain_hasDiffuseMapB(_currentTerrainID);
		auto hasNormalMapR = _fe3d.terrain_hasNormalMapR(_currentTerrainID);
		auto hasNormalMapG = _fe3d.terrain_hasNormalMapG(_currentTerrainID);
		auto hasNormalMapB = _fe3d.terrain_hasNormalMapB(_currentTerrainID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("redRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("redRepeat", "Red Repeat", redRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("greenRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("greenRepeat", "Green Repeat", greenRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blueRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("blueRepeat", "Blue Repeat", blueRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("textureRepeat", textureRepeat))
		{
			_fe3d.terrain_setTextureRepeat(_currentTerrainID, textureRepeat);
		}
		if(_gui.getGlobalScreen()->checkValueForm("redRepeat", redRepeat))
		{
			_fe3d.terrain_setRedRepeat(_currentTerrainID, redRepeat);
		}
		if(_gui.getGlobalScreen()->checkValueForm("greenRepeat", greenRepeat))
		{
			_fe3d.terrain_setGreenRepeat(_currentTerrainID, greenRepeat);
		}
		if(_gui.getGlobalScreen()->checkValueForm("blueRepeat", blueRepeat))
		{
			_fe3d.terrain_setBlueRepeat(_currentTerrainID, blueRepeat);
		}

		// Update buttons hoverability
		screen->getButton("textureRepeat")->setHoverable(hasDiffuseMap || hasNormalMap);
		screen->getButton("redRepeat")->setHoverable(hasDiffuseMapR || hasNormalMapR);
		screen->getButton("greenRepeat")->setHoverable(hasDiffuseMapG || hasNormalMapG);
		screen->getButton("blueRepeat")->setHoverable(hasDiffuseMapB || hasNormalMapB);
	}
}