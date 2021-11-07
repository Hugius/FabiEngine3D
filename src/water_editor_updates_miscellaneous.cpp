#include "water_editor.hpp"

void WaterEditor::_updateMiscellaneousMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "waterEditorMenuMiscellaneous")
	{
		// Temporary values
		auto speed = _fe3d.waterEntity_getSpeed(_currentWaterID);
		auto transparency = _fe3d.waterEntity_getTransparency(_currentWaterID);
		auto waveHeight = _fe3d.waterEntity_getWaveHeight(_currentWaterID);
		auto quality = _fe3d.waterEntity_getQuality(_currentWaterID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("waveHeight")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("waveHeight", "Wave Height", (waveHeight * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("speedX", "X", speed.x * 100000.0f, Vec2(-0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("speedZ", "Z", speed.y * 100000.0f, Vec2(0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transparency")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("transparency", "Transparency", (transparency * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			// Change water quality
			if(quality == WaterQuality::SKY)
			{
				quality = WaterQuality::SKY_TERRAIN;
			}
			else if(quality == WaterQuality::SKY_TERRAIN)
			{
				quality = WaterQuality::SKY_TERRAIN_MODELS;
			}
			else if(quality == WaterQuality::SKY_TERRAIN_MODELS)
			{
				quality = WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS;
			}
			else
			{
				quality = WaterQuality::SKY;
			}

			// Update water quality
			_fe3d.waterEntity_setQuality(_currentWaterID, quality);
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("speedX", speed.x))
		{
			speed.x /= 100000.0f;
			_fe3d.waterEntity_setSpeed(_currentWaterID, speed);
		}
		if(_gui.getGlobalScreen()->checkValueForm("speedZ", speed.y))
		{
			speed.y /= 100000.0f;
			_fe3d.waterEntity_setSpeed(_currentWaterID, speed);
		}
		if(_gui.getGlobalScreen()->checkValueForm("transparency", transparency))
		{
			transparency /= 100.0f;
			_fe3d.waterEntity_setTransparency(_currentWaterID, transparency);
		}
		if(_gui.getGlobalScreen()->checkValueForm("waveHeight", waveHeight))
		{
			waveHeight /= 100.0f;
			_fe3d.waterEntity_setWaveHeight(_currentWaterID, waveHeight);
		}

		// Update buttons hoverability
		screen->getButton("waveHeight")->setHoverable(_fe3d.waterEntity_hasDisplacementMap(_currentWaterID));
		screen->getButton("speed")->setHoverable(_fe3d.waterEntity_hasDudvMap(_currentWaterID) || _fe3d.waterEntity_hasDisplacementMap(_currentWaterID));

		// Update button text contents
		screen->getButton("quality")->changeTextContent("Quality: " + to_string(static_cast<int>(quality) + 1));
	}
}