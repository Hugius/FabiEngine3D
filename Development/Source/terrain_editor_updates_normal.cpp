#include "terrain_editor.hpp"
#include "logger.hpp"

void TerrainEditor::_updateNormalMapMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "terrainEditorMenuNormalMap")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
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
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMapR")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
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
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMapG")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
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
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMapB")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
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

		// Update buttons hoverability
		screen->getButton("normalMapR")->setHoverable(_fe3d.terrainEntity_hasBlendMap(_currentTerrainID));
		screen->getButton("normalMapG")->setHoverable(_fe3d.terrainEntity_hasBlendMap(_currentTerrainID));
		screen->getButton("normalMapB")->setHoverable(_fe3d.terrainEntity_hasBlendMap(_currentTerrainID));
	}
}