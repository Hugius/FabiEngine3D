#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TerrainEditor::_updateDiffuseMapMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "terrainEditorMenuDiffuseTexturing")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(_currentProjectId.empty())
			{
				Logger::throwError("TerrainEditor::_updateDiffuseMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectId + "\\assets\\image\\entity\\terrain\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
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

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->terrain_setDiffuseMap(_currentTerrainID, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("redDiffuseMap")->isHovered())
		{
			if(_currentProjectId.empty())
			{
				Logger::throwError("TerrainEditor::_updateDiffuseMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectId + "\\assets\\image\\entity\\terrain\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
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

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->terrain_setRedDiffuseMap(_currentTerrainID, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("greenDiffuseMap")->isHovered())
		{
			if(_currentProjectId.empty())
			{
				Logger::throwError("TerrainEditor::_updateDiffuseMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectId + "\\assets\\image\\entity\\terrain\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
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

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->terrain_setGreenDiffuseMap(_currentTerrainID, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blueDiffuseMap")->isHovered())
		{
			if(_currentProjectId.empty())
			{
				Logger::throwError("TerrainEditor::_updateDiffuseMapMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectId + "\\assets\\image\\entity\\terrain\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
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

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->terrain_setBlueDiffuseMap(_currentTerrainID, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d->terrain_setDiffuseMap(_currentTerrainID, "");
			_fe3d->terrain_setRedDiffuseMap(_currentTerrainID, "");
			_fe3d->terrain_setGreenDiffuseMap(_currentTerrainID, "");
			_fe3d->terrain_setBlueDiffuseMap(_currentTerrainID, "");
		}

		screen->getButton("redDiffuseMap")->setHoverable(_fe3d->terrain_hasBlendMap(_currentTerrainID));
		screen->getButton("greenDiffuseMap")->setHoverable(_fe3d->terrain_hasBlendMap(_currentTerrainID));
		screen->getButton("blueDiffuseMap")->setHoverable(_fe3d->terrain_hasBlendMap(_currentTerrainID));
		screen->getButton("clearMaps")->setHoverable(
			_fe3d->terrain_hasDiffuseMap(_currentTerrainID) ||
			_fe3d->terrain_hasRedDiffuseMap(_currentTerrainID) ||
			_fe3d->terrain_hasGreenDiffuseMap(_currentTerrainID) ||
			_fe3d->terrain_hasBlueDiffuseMap(_currentTerrainID));
	}
}