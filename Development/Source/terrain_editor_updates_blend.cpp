#include "terrain_editor.hpp"
#include "logger.hpp"

void TerrainEditor::_updateBlendMapMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "terrainEditorMenuBlendMap")
	{
		// Temporary values
		auto hasBlendMap = _fe3d.terrainEntity_hasBlendMap(_currentTerrainID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blendMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\blend_maps\\");

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

			// Set blend map
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setBlendMap(_currentTerrainID, newFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("redMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");

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

			// Set diffuse map
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setDiffuseMapR(_currentTerrainID, newFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("greenMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");

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

			// Set diffuse map
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setDiffuseMapG(_currentTerrainID, newFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blueMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");

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

			// Set diffuse map
			const string newFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setDiffuseMapB(_currentTerrainID, newFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.terrainEntity_setBlendMap(_currentTerrainID, "");
			_fe3d.terrainEntity_setDiffuseMapR(_currentTerrainID, "");
			_fe3d.terrainEntity_setDiffuseMapG(_currentTerrainID, "");
			_fe3d.terrainEntity_setDiffuseMapB(_currentTerrainID, "");
		}

		// Update buttons hoverability
		screen->getButton("redMap")->setHoverable(hasBlendMap);
		screen->getButton("greenMap")->setHoverable(hasBlendMap);
		screen->getButton("blueMap")->setHoverable(hasBlendMap);
		screen->getButton("clearMaps")->setHoverable(
			_fe3d.terrainEntity_hasBlendMap(_currentTerrainID) ||
			_fe3d.terrainEntity_hasDiffuseMapR(_currentTerrainID) ||
			_fe3d.terrainEntity_hasDiffuseMapG(_currentTerrainID) ||
			_fe3d.terrainEntity_hasDiffuseMapB(_currentTerrainID));
	}
}