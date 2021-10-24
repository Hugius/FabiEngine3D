#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TerrainEditor::_updateDiffuseMapMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "terrainEditorMenuDiffuseMap")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = Tools::getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");

			// Validate target directory
			if (!Tools::isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
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
			_fe3d.terrainEntity_setDiffuseMap(_currentTerrainID, newFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.terrainEntity_setDiffuseMap(_currentTerrainID, "");
		}

		// Update buttons hoverability
		screen->getButton("clearMaps")->setHoverable(_fe3d.terrainEntity_hasDiffuseMap(_currentTerrainID));
	}
}