#include "water_editor.hpp"

void WaterEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "waterEditorMenuMiscellaneous")
	{
		auto size = _fe3d->water_getSize(_currentWaterId);
		auto speed = _fe3d->water_getSpeed(_currentWaterId);
		auto opacity = _fe3d->water_getOpacity(_currentWaterId);
		auto waveHeight = _fe3d->water_getWaveHeight(_currentWaterId);
		auto quality = _fe3d->water_getQuality(_currentWaterId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->createValueForm("size", "Size", size, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("waveHeight")->isHovered())
		{
			_gui->getOverlay()->createValueForm("waveHeight", "Wave Height", (waveHeight * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui->getOverlay()->createValueForm("speedX", "X", speed.x * 100000.0f, fvec2(-0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("speedZ", "Z", speed.y * 100000.0f, fvec2(0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			_gui->getOverlay()->createValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			switch(quality)
			{
				case WaterQuality::SKY:
				{
					quality = WaterQuality::SKY_TERRAIN;
					break;
				}
				case WaterQuality::SKY_TERRAIN:
				{
					quality = WaterQuality::SKY_TERRAIN_MODEL;
					break;
				}
				case WaterQuality::SKY_TERRAIN_MODEL:
				{
					quality = WaterQuality::SKY_TERRAIN_MODEL_QUAD3D;
					break;
				}
				case WaterQuality::SKY_TERRAIN_MODEL_QUAD3D:
				{
					quality = WaterQuality::SKY_TERRAIN_MODEL_QUAD3D_TEXT3D;
					break;
				}
				case WaterQuality::SKY_TERRAIN_MODEL_QUAD3D_TEXT3D:
				{
					quality = WaterQuality::SKY;
					break;
				}
			}

			_fe3d->water_setQuality(_currentWaterId, quality);
		}

		if(_gui->getOverlay()->checkValueForm("size", size, {0.0f}))
		{
			_fe3d->water_setSize(_currentWaterId, size);
		}
		if(_gui->getOverlay()->checkValueForm("speedX", speed.x))
		{
			speed.x /= 100000.0f;
			_fe3d->water_setSpeed(_currentWaterId, speed);
		}
		if(_gui->getOverlay()->checkValueForm("speedZ", speed.y))
		{
			speed.y /= 100000.0f;
			_fe3d->water_setSpeed(_currentWaterId, speed);
		}
		if(_gui->getOverlay()->checkValueForm("opacity", opacity))
		{
			opacity /= 100.0f;
			_fe3d->water_setOpacity(_currentWaterId, opacity);
		}
		if(_gui->getOverlay()->checkValueForm("waveHeight", waveHeight))
		{
			waveHeight /= 100.0f;
			_fe3d->water_setWaveHeight(_currentWaterId, waveHeight);
		}

		screen->getButton("waveHeight")->setHoverable(_fe3d->water_hasDisplacementMap(_currentWaterId));
		screen->getButton("speed")->setHoverable(_fe3d->water_hasDudvMap(_currentWaterId) || _fe3d->water_hasDisplacementMap(_currentWaterId));

		screen->getButton("quality")->changeTextContent("Quality: " + to_string(static_cast<int>(quality) + 1));
	}
}