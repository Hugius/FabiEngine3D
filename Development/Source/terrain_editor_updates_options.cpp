#include "terrain_editor.hpp"

void TerrainEditor::_updateOptionsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "terrainEditorMenuOptions")
	{
		// Temporary values
		auto uvRepeat = _fe3d.terrainEntity_getUvRepeat(_currentTerrainID);
		auto blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(_currentTerrainID);
		auto blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(_currentTerrainID);
		auto blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(_currentTerrainID);
		auto hasBlendMap = _fe3d.terrainEntity_hasBlendMap(_currentTerrainID);
		auto hasDiffuseMap = _fe3d.terrainEntity_hasDiffuseMap(_currentTerrainID);
		auto hasNormalMap = _fe3d.terrainEntity_hasNormalMap(_currentTerrainID);
		auto hasDiffuseMapR = _fe3d.terrainEntity_hasDiffuseMapR(_currentTerrainID);
		auto hasDiffuseMapG = _fe3d.terrainEntity_hasDiffuseMapG(_currentTerrainID);
		auto hasDiffuseMapB = _fe3d.terrainEntity_hasDiffuseMapB(_currentTerrainID);
		auto hasNormalMapR = _fe3d.terrainEntity_hasNormalMapR(_currentTerrainID);
		auto hasNormalMapG = _fe3d.terrainEntity_hasNormalMapG(_currentTerrainID);
		auto hasNormalMapB = _fe3d.terrainEntity_hasNormalMapB(_currentTerrainID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("uvRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("uvRepeat", "UV Repeat", uvRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("redRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("redRepeat", "Red Repeat", blendRepeatR, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("greenRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("greenRepeat", "Green Repeat", blendRepeatG, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blueRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("blueRepeat", "Blue Repeat", blendRepeatB, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat))
		{
			_fe3d.terrainEntity_setUvRepeat(_currentTerrainID, uvRepeat);
		}
		if (_gui.getGlobalScreen()->checkValueForm("redRepeat", blendRepeatR))
		{
			_fe3d.terrainEntity_setBlendRepeatR(_currentTerrainID, blendRepeatR);
		}
		if (_gui.getGlobalScreen()->checkValueForm("greenRepeat", blendRepeatG))
		{
			_fe3d.terrainEntity_setBlendRepeatG(_currentTerrainID, blendRepeatG);
		}
		if (_gui.getGlobalScreen()->checkValueForm("blueRepeat", blendRepeatB))
		{
			_fe3d.terrainEntity_setBlendRepeatB(_currentTerrainID, blendRepeatB);
		}

		// Update buttons hoverability
		screen->getButton("uvRepeat")->setHoverable(hasDiffuseMap || hasDiffuseMapR || hasDiffuseMapG || hasDiffuseMapB);
		screen->getButton("redRepeat")->setHoverable(hasDiffuseMapR || hasNormalMapR);
		screen->getButton("greenRepeat")->setHoverable(hasDiffuseMapG || hasNormalMapG);
		screen->getButton("blueRepeat")->setHoverable(hasDiffuseMapB || hasNormalMapB);
	}
}