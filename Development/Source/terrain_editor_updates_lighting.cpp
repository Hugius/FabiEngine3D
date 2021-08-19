#include "terrain_editor.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

void TerrainEditor::_updateLightingSettingsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "terrainEditorMenuLighting")
	{
		// Temporary values
		bool isSpecular = _fe3d.terrainEntity_isSpecularLighted(_currentTerrainID);
		float specularFactor = _fe3d.terrainEntity_getSpecularLightingFactor(_currentTerrainID);
		float specularIntensity = _fe3d.terrainEntity_getSpecularLightingIntensity(_currentTerrainID);
		float lightness = _fe3d.terrainEntity_getLightness(_currentTerrainID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
				return;
			}
			else if (screen->getButton("normalMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\normal_maps\\");

				// Validate target directory
				if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
				{
					Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
					return;
				}

				// Validate chosen file
				const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
				if (filePath.empty())
				{
					return;
				}

				// Validate directory of file
				if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
					filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
				{
					Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
					return;
				}

				// Set normal map
				const string newFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(newFilePath);
				_fe3d.terrainEntity_setNormalMap(_currentTerrainID, newFilePath);
			}
			else if (screen->getButton("normalMapR")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\normal_maps\\");

				// Validate target directory
				if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
				{
					Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
					return;
				}

				// Validate chosen file
				const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
				if (filePath.empty())
				{
					return;
				}

				// Validate directory of file
				if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
					filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
				{
					Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
					return;
				}

				// Set normal map
				const string newFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(newFilePath);
				_fe3d.terrainEntity_setNormalMapR(_currentTerrainID, newFilePath);
			}
			else if (screen->getButton("normalMapG")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\normal_maps\\");

				// Validate target directory
				if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
				{
					Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
					return;
				}

				// Validate chosen file
				const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
				if (filePath.empty())
				{
					return;
				}

				// Validate directory of file
				if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
					filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
				{
					Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
					return;
				}

				// Set normal map
				const string newFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(newFilePath);
				_fe3d.terrainEntity_setNormalMapG(_currentTerrainID, newFilePath);
			}
			else if (screen->getButton("normalMapB")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\normal_maps\\");

				// Validate target directory
				if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
				{
					Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
					return;
				}

				// Validate chosen file
				const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
				if (filePath.empty())
				{
					return;
				}

				// Validate directory of file
				if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
					filePath.substr(rootDirectory.size(), targetDirectory.size()) != targetDirectory)
				{
					Logger::throwWarning("File cannot be outside of `" + targetDirectory + "`!");
					return;
				}

				// Set normal map
				const string newFilePath = filePath.substr(rootDirectory.size());
				_fe3d.misc_clearTextureCache2D(newFilePath);
				_fe3d.terrainEntity_setNormalMapB(_currentTerrainID, newFilePath);
			}
			else if (screen->getButton("isSpecular")->isHovered())
			{
				isSpecular = !isSpecular;
				_fe3d.terrainEntity_setSpecularLighted(_currentTerrainID, isSpecular);
			}
			else if (screen->getButton("specularFactor")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("specularFactor", "Specular Factor", specularFactor, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("specularIntensity")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("specularIntensity", "Specular Intensity", specularIntensity * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", lightness * 100.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("specularFactor", specularFactor))
		{
			specularFactor = clamp(specularFactor, 0.0f, 256.0f);
			_fe3d.terrainEntity_setSpecularLightingFactor(_currentTerrainID, specularFactor);
		}
		if (_gui.getGlobalScreen()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity = max(0.0f, specularIntensity / 100.0f);
			_fe3d.terrainEntity_setSpecularLightingIntensity(_currentTerrainID, specularIntensity);
		}
		if (_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness = max(0.0f, lightness / 100.0f);
			_fe3d.terrainEntity_setLightness(_currentTerrainID, lightness);
		}

		// Update buttons hoverability
		screen->getButton("specularFactor")->setHoverable(isSpecular);
		screen->getButton("specularIntensity")->setHoverable(isSpecular);

		// Update button text contents
		screen->getButton("isSpecular")->changeTextContent(isSpecular ? "Specular: ON" : "Specular: OFF");
	}
}