#include "environment_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void EnvironmentEditor::_updateWaterMenuEffects()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "environmentEditorMenuWaterEffects")
	{
		// Temporary values
		float uvRepeat = _fe3d.waterEntity_getUvRepeat(_currentWaterID);
		bool isReflective = _fe3d.waterEntity_isReflective(_currentWaterID);
		bool isRefractive = _fe3d.waterEntity_isRefractive(_currentWaterID);
		bool isWaving = _fe3d.waterEntity_isWaving(_currentWaterID);
		bool isRippling = _fe3d.waterEntity_isRippling(_currentWaterID);
		bool isSpecularLighted = _fe3d.waterEntity_isSpecularLighted(_currentWaterID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuWaterChoice");
			}
			else if (screen->getButton("uvRepeat")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("uvRepeat", "UV Repeat", uvRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("dudvMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\dudv_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.waterEntity_setDudvMap(_currentWaterID, newFilePath);
					}
					else
					{
						Logger::throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("normalMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\normal_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.waterEntity_setNormalMap(_currentWaterID, newFilePath);
					}
					else
					{
						Logger::throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("displaceMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\displacement_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.waterEntity_setDisplacementMap(_currentWaterID, newFilePath);
					}
					else
					{
						Logger::throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("isReflective")->isHovered())
			{
				isReflective = !isReflective;
				_fe3d.waterEntity_setReflective(_currentWaterID, isReflective);
			}
			else if (screen->getButton("isRefractive")->isHovered())
			{
				isRefractive = !isRefractive;
				_fe3d.waterEntity_setRefractive(_currentWaterID, isRefractive);
			}
			else if (screen->getButton("isWaving")->isHovered())
			{
				isWaving = !isWaving;
				_fe3d.waterEntity_setWaving(_currentWaterID, isWaving);
			}
			else if (screen->getButton("isRippling")->isHovered())
			{
				isRippling = !isRippling;
				_fe3d.waterEntity_setRippling(_currentWaterID, isRippling);
			}
			else if (screen->getButton("isSpecular")->isHovered())
			{
				isSpecularLighted = !isSpecularLighted;
				_fe3d.waterEntity_setSpecularLighted(_currentWaterID, isSpecularLighted);
			}
		}

		// Button hoverabilities
		string displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath(_currentWaterID);
		string dudvMapPath = _fe3d.waterEntity_getDudvMapPath(_currentWaterID);
		string normalMapPath = _fe3d.waterEntity_getNormalMapPath(_currentWaterID);
		screen->getButton("isWaving")->setHoverable(displacementMapPath != "");
		screen->getButton("isRippling")->setHoverable(dudvMapPath != "");
		screen->getButton("isSpecular")->setHoverable(normalMapPath != "");

		// Button text contents
		screen->getButton("isReflective")->changeTextContent(isReflective ? "Reflective: ON" : "Reflective: OFF");
		screen->getButton("isRefractive")->changeTextContent(isRefractive ? "Refractive: ON" : "Refractive: OFF");
		screen->getButton("isWaving")->changeTextContent(isWaving ? "Waving: ON" : "Waving: OFF");
		screen->getButton("isRippling")->changeTextContent(isRippling ? "Rippling: ON" : "Rippling: OFF");
		screen->getButton("isSpecular")->changeTextContent(isSpecularLighted ? "Specular: ON" : "Specular: OFF");

		// Update uvRepeat changes
		_gui.getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat);
		_fe3d.waterEntity_setUvRepeat(_currentWaterID, uvRepeat);
	}
}

void EnvironmentEditor::_updateWaterMenuOptions()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "environmentEditorMenuWaterOptions")
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
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuWaterChoice");
			}
			else if (screen->getButton("speed")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("speedX", "X", speed.x * 100000.0f, Vec2(-0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("speedZ", "Z", speed.y * 100000.0f, Vec2(0.15f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("transparency")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("transparency", "Transparency", transparency * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("colorR", "R", color.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorG", "G", color.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorB", "B", color.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("specularFactor")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("specularFactor", "Specular Factor", specularFactor, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("specularIntensity")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("specularIntensity", "Specular Intensity", specularIntensity * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("waveHeight")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("waveHeight", "Wave Height Factor", waveHeight * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
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
			transparency = std::clamp(transparency / 100.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setTransparency(_currentWaterID, transparency);
		}

		// Check if color R value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("colorR", color.r))
		{
			color.r = std::clamp(color.r / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}

		// Check if color G value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("colorG", color.g))
		{
			color.g = std::clamp(color.g / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}

		// Check if color B value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("colorB", color.b))
		{
			color.b = std::clamp(color.b / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}

		// Check if specular factor value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("specularFactor", specularFactor))
		{
			specularFactor = std::clamp(specularFactor, 0.0f, 256.0f);
			_fe3d.waterEntity_setSpecularLightingFactor(_currentWaterID, specularFactor);
		}

		// Check if specular intensity value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity = std::max(0.0f, specularIntensity / 100.0f);
			_fe3d.waterEntity_setSpecularLightingIntensity(_currentWaterID, specularIntensity);
		}

		// Check if wave height value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("waveHeight", waveHeight))
		{
			waveHeight = std::max(0.0f, waveHeight / 100.0f);
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