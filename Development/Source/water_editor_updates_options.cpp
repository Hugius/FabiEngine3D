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
		auto specularShininess = _fe3d.waterEntity_getSpecularShininess(_currentWaterID);
		auto specularIntensity = _fe3d.waterEntity_getSpecularIntensity(_currentWaterID);
		auto waveHeight = _fe3d.waterEntity_getWaveHeight(_currentWaterID);
		auto quality = _fe3d.waterEntity_getQuality(_currentWaterID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
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
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularShininess")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("specularShininess", "Specular Shininess", specularShininess, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularIntensity")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("specularIntensity", "Specular Intensity", (specularIntensity * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("waveHeight")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("waveHeight", "Wave Height Factor", (waveHeight * 100.0f), Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quality")->isHovered())
		{
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
		}

		// Update value forms
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
		if (_gui.getGlobalScreen()->checkValueForm("specularShininess", specularShininess))
		{
			specularShininess = min(256.0f, specularShininess);
			_fe3d.waterEntity_setSpecularShininess(_currentWaterID, specularShininess);
		}
		if (_gui.getGlobalScreen()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d.waterEntity_setSpecularIntensity(_currentWaterID, specularIntensity);
		}
		if (_gui.getGlobalScreen()->checkValueForm("waveHeight", waveHeight))
		{
			waveHeight /= 100.0f;
			_fe3d.waterEntity_setWaveHeight(_currentWaterID, waveHeight);
		}

		// Update water quality
		_fe3d.waterEntity_setQuality(_currentWaterID, quality);

		// Update buttons hoverability
		screen->getButton("specularShininess")->setHoverable(_fe3d.waterEntity_isSpecularLighted(_currentWaterID));
		screen->getButton("specularIntensity")->setHoverable(_fe3d.waterEntity_isSpecularLighted(_currentWaterID));
		screen->getButton("waveHeight")->setHoverable(_fe3d.waterEntity_isWaving(_currentWaterID));

		// Update button text contents
		screen->getButton("quality")->changeTextContent("Quality: " + to_string(static_cast<int>(quality) + 1));
	}
}