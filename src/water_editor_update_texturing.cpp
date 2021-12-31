#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WaterEditor::_updateTexturingMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "waterEditorMenuTexturing")
	{
		auto hasDudvMap = _fe3d.water_hasDudvMap(_currentWaterID);
		auto hasNormalMap = _fe3d.water_hasNormalMap(_currentWaterID);
		auto hasDisplacementMap = _fe3d.water_hasDisplacementMap(_currentWaterID);
		auto textureRepeat = _fe3d.water_getTextureRepeat(_currentWaterID);

		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("dudvMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("WaterEditor::_updateTexturingMenu");
			}

			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\dudv_map\\");

			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "BMP");
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
			_fe3d.water_setDudvMap(_currentWaterID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("WaterEditor::_updateTexturingMenu");
			}

			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\normal_map\\");

			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "BMP");
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
			_fe3d.water_setNormalMap(_currentWaterID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("displaceMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("WaterEditor::_updateTexturingMenu");
			}

			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\displacement_map\\");

			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "BMP");
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
			_fe3d.water_setDisplacementMap(_currentWaterID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.water_setDudvMap(_currentWaterID, "");
			_fe3d.water_setNormalMap(_currentWaterID, "");
			_fe3d.water_setDisplacementMap(_currentWaterID, "");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui.getOverlay()->createValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui.getOverlay()->checkValueForm("textureRepeat", textureRepeat))
		{
			_fe3d.water_setTextureRepeat(_currentWaterID, textureRepeat);
		}

		screen->getButton("clearMaps")->setHoverable(hasDudvMap || hasNormalMap || hasDisplacementMap);
		screen->getButton("textureRepeat")->setHoverable(hasDudvMap || hasNormalMap || hasDisplacementMap);
	}
}