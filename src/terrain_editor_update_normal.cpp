#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TerrainEditor::_updateNormalMapMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "terrainEditorMenuNormalMap")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("TerrainEditor::_updateNormalMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\normal_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "BMP");
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
			_fe3d.terrain_setNormalMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("redNormalMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("TerrainEditor::_updateNormalMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\normal_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "BMP");
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
			_fe3d.terrain_setRedNormalMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("greenNormalMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("TerrainEditor::_updateNormalMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\normal_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "BMP");
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
			_fe3d.terrain_setGreenNormalMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blueNormalMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("TerrainEditor::_updateNormalMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\normal_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "BMP");
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
			_fe3d.terrain_setBlueNormalMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.terrain_setNormalMap(_currentTerrainID, "");
			_fe3d.terrain_setRedNormalMap(_currentTerrainID, "");
			_fe3d.terrain_setGreenNormalMap(_currentTerrainID, "");
			_fe3d.terrain_setBlueNormalMap(_currentTerrainID, "");
		}

		screen->getButton("redNormalMap")->setHoverable(_fe3d.terrain_hasBlendMap(_currentTerrainID));
		screen->getButton("greenNormalMap")->setHoverable(_fe3d.terrain_hasBlendMap(_currentTerrainID));
		screen->getButton("blueNormalMap")->setHoverable(_fe3d.terrain_hasBlendMap(_currentTerrainID));
		screen->getButton("clearMaps")->setHoverable(
			_fe3d.terrain_hasNormalMap(_currentTerrainID) ||
			_fe3d.terrain_hasRedNormalMap(_currentTerrainID) ||
			_fe3d.terrain_hasGreenNormalMap(_currentTerrainID) ||
			_fe3d.terrain_hasBlueNormalMap(_currentTerrainID));
	}
}