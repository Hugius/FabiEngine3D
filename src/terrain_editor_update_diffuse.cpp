#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TerrainEditor::_updateDiffuseMapMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "terrainEditorMenuDiffuseMap")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("TerrainEditor::_updateDiffuseMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "BMP");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string newFilePath = filePath.substr(rootPath.size());
			_fe3d.misc_clearImageCache(newFilePath);
			_fe3d.terrain_setDiffuseMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("redDiffuseMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("TerrainEditor::_updateDiffuseMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "BMP");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string newFilePath = filePath.substr(rootPath.size());
			_fe3d.misc_clearImageCache(newFilePath);
			_fe3d.terrain_setRedDiffuseMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("greenDiffuseMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("TerrainEditor::_updateDiffuseMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "BMP");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string newFilePath = filePath.substr(rootPath.size());
			_fe3d.misc_clearImageCache(newFilePath);
			_fe3d.terrain_setGreenDiffuseMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blueDiffuseMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("TerrainEditor::_updateDiffuseMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "BMP");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string newFilePath = filePath.substr(rootPath.size());
			_fe3d.misc_clearImageCache(newFilePath);
			_fe3d.terrain_setBlueDiffuseMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.terrain_setDiffuseMap(_currentTerrainID, "");
			_fe3d.terrain_setRedDiffuseMap(_currentTerrainID, "");
			_fe3d.terrain_setGreenDiffuseMap(_currentTerrainID, "");
			_fe3d.terrain_setBlueDiffuseMap(_currentTerrainID, "");
		}

		screen->getButton("redDiffuseMap")->setHoverable(_fe3d.terrain_hasBlendMap(_currentTerrainID));
		screen->getButton("greenDiffuseMap")->setHoverable(_fe3d.terrain_hasBlendMap(_currentTerrainID));
		screen->getButton("blueDiffuseMap")->setHoverable(_fe3d.terrain_hasBlendMap(_currentTerrainID));
		screen->getButton("clearMaps")->setHoverable(
			_fe3d.terrain_hasDiffuseMap(_currentTerrainID) ||
			_fe3d.terrain_hasRedDiffuseMap(_currentTerrainID) ||
			_fe3d.terrain_hasGreenDiffuseMap(_currentTerrainID) ||
			_fe3d.terrain_hasBlueDiffuseMap(_currentTerrainID));
	}
}