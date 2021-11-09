#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TerrainEditor::_updateBlendMapMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "terrainEditorMenuBlendMap")
	{
		// Temporary values
		auto hasBlendMap = _fe3d.terrainEntity_hasBlendMap(_currentTerrainID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blendMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string(_currentProjectID + "\\assets\\textures\\blend_maps\\");

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

			// Set blend map
			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setBlendMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("redMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string(_currentProjectID + "\\assets\\textures\\diffuse_maps\\");

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

			// Set diffuse map
			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setDiffuseMapR(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("greenMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string(_currentProjectID + "\\assets\\textures\\diffuse_maps\\");

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

			// Set diffuse map
			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setDiffuseMapG(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blueMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string(_currentProjectID + "\\assets\\textures\\diffuse_maps\\");

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

			// Set diffuse map
			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.terrainEntity_setDiffuseMapB(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
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