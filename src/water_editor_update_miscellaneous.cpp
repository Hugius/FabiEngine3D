#include "water_editor.hpp"

void WaterEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "waterEditorMenuMiscellaneous")
	{
		auto speed = _fe3d.water_getSpeed(_currentWaterID);
		auto transparency = _fe3d.water_getTransparency(_currentWaterID);
		auto waveHeight = _fe3d.water_getWaveHeight(_currentWaterID);
		auto quality = _fe3d.water_getQuality(_currentWaterID);

		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("waveHeight")->isHovered())
		{
			_gui.getOverlay()->createValueForm("waveHeight", "Wave Height", (waveHeight * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui.getOverlay()->createValueForm("speedX", "X", speed.x * 100000.0f, fvec2(-0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getOverlay()->createValueForm("speedZ", "Z", speed.y * 100000.0f, fvec2(0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transparency")->isHovered())
		{
			_gui.getOverlay()->createValueForm("transparency", "Transparency", (transparency * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
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

			_fe3d.water_setQuality(_currentWaterID, quality);
		}

		if(_gui.getOverlay()->checkValueForm("speedX", speed.x))
		{
			speed.x /= 100000.0f;
			_fe3d.water_setSpeed(_currentWaterID, speed);
		}
		if(_gui.getOverlay()->checkValueForm("speedZ", speed.y))
		{
			speed.y /= 100000.0f;
			_fe3d.water_setSpeed(_currentWaterID, speed);
		}
		if(_gui.getOverlay()->checkValueForm("transparency", transparency))
		{
			transparency /= 100.0f;
			_fe3d.water_setTransparency(_currentWaterID, transparency);
		}
		if(_gui.getOverlay()->checkValueForm("waveHeight", waveHeight))
		{
			waveHeight /= 100.0f;
			_fe3d.water_setWaveHeight(_currentWaterID, waveHeight);
		}

		screen->getButton("waveHeight")->setHoverable(_fe3d.water_hasDisplacementMap(_currentWaterID));
		screen->getButton("speed")->setHoverable(_fe3d.water_hasDudvMap(_currentWaterID) || _fe3d.water_hasDisplacementMap(_currentWaterID));

		screen->getButton("quality")->changeTextContent("Quality: " + to_string(static_cast<int>(quality) + 1));
	}
}