#include "water_editor.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void WaterEditor::_updateOptionsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "waterEditorMenuOptions")
	{
		// Temporary values
		auto color = _fe3d.waterEntity_getColor(_currentWaterID);
		auto speed = _fe3d.waterEntity_getSpeed(_currentWaterID);
		auto transparency = _fe3d.waterEntity_getTransparency(_currentWaterID);
		auto specularFactor = _fe3d.waterEntity_getSpecularLightingFactor(_currentWaterID);
		auto specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity(_currentWaterID);
		auto waveHeight = _fe3d.waterEntity_getWaveHeight(_currentWaterID);
		auto quality = _fe3d.waterEntity_getQuality(_currentWaterID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			}
			else if (screen->getButton("speed")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("speedX", "X", speed.x * 100000.0f, Vec2(-0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("speedZ", "Z", speed.y * 100000.0f, Vec2(0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("transparency")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("transparency", "Transparency", transparency * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("colorR", "R", color.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("colorG", "G", color.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("colorB", "B", color.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("specularFactor")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("specularFactor", "Specular Factor", specularFactor, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("specularIntensity")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("specularIntensity", "Specular Intensity", specularIntensity * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("waveHeight")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("waveHeight", "Wave Height Factor", waveHeight * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("quality")->isHovered())
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
		}

		// Check if speed X value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("speedX", speed.x))
		{
			speed.x /= 100000.0f;
			_fe3d.waterEntity_setSpeed(_currentWaterID, speed);
		}

		// Check if speed Z value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("speedZ", speed.y))
		{
			speed.y /= 100000.0f;
			_fe3d.waterEntity_setSpeed(_currentWaterID, speed);
		}

		// Check if transparency value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("transparency", transparency))
		{
			transparency = clamp(transparency / 100.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setTransparency(_currentWaterID, transparency);
		}

		// Check if color R value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("colorR", color.r))
		{
			color.r = clamp(color.r / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}

		// Check if color G value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("colorG", color.g))
		{
			color.g = clamp(color.g / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}

		// Check if color B value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("colorB", color.b))
		{
			color.b = clamp(color.b / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}

		// Check if specular factor value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("specularFactor", specularFactor))
		{
			specularFactor = clamp(specularFactor, 0.0f, 256.0f);
			_fe3d.waterEntity_setSpecularLightingFactor(_currentWaterID, specularFactor);
		}

		// Check if specular intensity value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity = max(0.0f, specularIntensity / 100.0f);
			_fe3d.waterEntity_setSpecularLightingIntensity(_currentWaterID, specularIntensity);
		}

		// Check if wave height value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("waveHeight", waveHeight))
		{
			waveHeight = max(0.0f, waveHeight / 100.0f);
			_fe3d.waterEntity_setWaveHeight(_currentWaterID, waveHeight);
		}

		// Update water quality
		_fe3d.waterEntity_setQuality(_currentWaterID, quality);

		// Button hoverabilities
		screen->getButton("specularFactor")->setHoverable(_fe3d.waterEntity_isSpecularLighted(_currentWaterID));
		screen->getButton("specularIntensity")->setHoverable(_fe3d.waterEntity_isSpecularLighted(_currentWaterID));
		screen->getButton("waveHeight")->setHoverable(_fe3d.waterEntity_isWaving(_currentWaterID));

		// Button text contents
		screen->getButton("quality")->changeTextContent("Quality: " + to_string(static_cast<int>(quality) + 1));
	}
}