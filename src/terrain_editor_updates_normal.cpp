#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TerrainEditor::_updateNormalMapMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "terrainEditorMenuNormalMap")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game_assets\\textures\\normal_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			// Set normal map
			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setNormalMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("redMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game_assets\\textures\\normal_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			// Set normal map
			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setNormalMapR(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("greenMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game_assets\\textures\\normal_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			// Set normal map
			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setNormalMapG(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blueMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game_assets\\textures\\normal_maps\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			// Set normal map
			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setNormalMapB(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.terrainEntity_setNormalMap(_currentTerrainID, "");
			_fe3d.terrainEntity_setNormalMapR(_currentTerrainID, "");
			_fe3d.terrainEntity_setNormalMapG(_currentTerrainID, "");
			_fe3d.terrainEntity_setNormalMapB(_currentTerrainID, "");
		}

		// Update buttons hoverability
		screen->getButton("redMap")->setHoverable(_fe3d.terrainEntity_hasBlendMap(_currentTerrainID));
		screen->getButton("greenMap")->setHoverable(_fe3d.terrainEntity_hasBlendMap(_currentTerrainID));
		screen->getButton("blueMap")->setHoverable(_fe3d.terrainEntity_hasBlendMap(_currentTerrainID));
		screen->getButton("clearMaps")->setHoverable(
			_fe3d.terrainEntity_hasNormalMap(_currentTerrainID) ||
			_fe3d.terrainEntity_hasNormalMapR(_currentTerrainID) ||
			_fe3d.terrainEntity_hasNormalMapG(_currentTerrainID) ||
			_fe3d.terrainEntity_hasNormalMapB(_currentTerrainID));
	}
}