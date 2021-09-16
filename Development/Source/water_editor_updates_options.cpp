#include "water_editor.hpp"

void WaterEditor::_updateOptionsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "waterEditorMenuOptions")
	{
		// Temporary values
		auto color = _fe3d.waterEntity_getColor(_currentWaterID);
		auto speed = _fe3d.waterEntity_getSpeed(_currentWaterID);
		auto transparency = _fe3d.waterEntity_getTransparency(_currentWaterID);
		auto waveHeight = _fe3d.waterEntity_getWaveHeight(_currentWaterID);
		auto quality = _fe3d.waterEntity_getQuality(_currentWaterID);
		float uvRepeat = _fe3d.waterEntity_getUvRepeat(_currentWaterID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("uvRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("uvRepeat", "UV Repeat", uvRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("waveHeight")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("waveHeight", "Wave Height", (waveHeight * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("speed")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("speedX", "X", speed.x * 100000.0f, Vec2(-0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("speedZ", "Z", speed.y * 100000.0f, Vec2(0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transparency")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("transparency", "Transparency", (transparency * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("colorR", "R", color.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorG", "G", color.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorB", "B", color.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
			// Change water quality
			if (quality == WaterQuality::SKY)
			{
				quality = WaterQuality::SKY_TERRAIN;
			}
			else if (quality == WaterQuality::SKY_TERRAIN)
			{
				quality = WaterQuality::SKY_TERRAIN_MODELS;
			}
			else if (quality == WaterQuality::SKY_TERRAIN_MODELS)
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
		if (_gui.getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat))
		{
			_fe3d.waterEntity_setUvRepeat(_currentWaterID, uvRepeat);
		}
		if (_gui.getGlobalScreen()->checkValueForm("speedX", speed.x))
		{
			speed.x /= 100000.0f;
			_fe3d.waterEntity_setSpeed(_currentWaterID, speed);
		}
		if (_gui.getGlobalScreen()->checkValueForm("speedZ", speed.y))
		{
			speed.y /= 100000.0f;
			_fe3d.waterEntity_setSpeed(_currentWaterID, speed);
		}
		if (_gui.getGlobalScreen()->checkValueForm("transparency", transparency))
		{
			transparency /= 100.0f;
			_fe3d.waterEntity_setTransparency(_currentWaterID, transparency);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorR", color.r))
		{
			color.r /= 255.0f;
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorG", color.g))
		{
			color.g /= 255.0f;
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorB", color.b))
		{
			color.b /= 255.0f;
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}
		if (_gui.getGlobalScreen()->checkValueForm("waveHeight", waveHeight))
		{
			waveHeight /= 100.0f;
			_fe3d.waterEntity_setWaveHeight(_currentWaterID, waveHeight);
		}

		// Update buttons hoverability
		screen->getButton("uvRepeat")->setHoverable(
			_fe3d.waterEntity_hasDudvMap(_currentWaterID) ||
			_fe3d.waterEntity_hasNormalMap(_currentWaterID) ||
			_fe3d.waterEntity_hasDisplacementMap(_currentWaterID));
		screen->getButton("waveHeight")->setHoverable(_fe3d.waterEntity_isWaving(_currentWaterID));
		screen->getButton("speed")->setHoverable(_fe3d.waterEntity_isRippling(_currentWaterID) || _fe3d.waterEntity_isWaving(_currentWaterID));

		// Update button text contents
		screen->getButton("quality")->changeTextContent("Quality: " + to_string(static_cast<int>(quality) + 1));
	}
}