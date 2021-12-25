#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TerrainEditor::_updateBlendMapMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "terrainEditorMenuBlendMap")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("blendMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("TerrainEditor::_updateBlendMapMenu");
			}

			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\texture\\blend_map\\");

			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "PNG");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clear2dTextureCache(newFilePath);
			_fe3d.terrain_setBlendMap(_currentTerrainID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.terrain_setBlendMap(_currentTerrainID, "");
		}

		screen->getButton("clearMaps")->setHoverable(_fe3d.terrain_hasBlendMap(_currentTerrainID));
	}
}