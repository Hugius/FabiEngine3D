#include "water_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WaterEditor::_updateTexturingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "waterEditorMenuTexturing")
	{
		// Temporary values
		auto hasDudvMap = _fe3d.waterEntity_hasDudvMap(_currentWaterID);
		auto hasNormalMap = _fe3d.waterEntity_hasNormalMap(_currentWaterID);
		auto hasDisplacementMap = _fe3d.waterEntity_hasDisplacementMap(_currentWaterID);
		auto textureRepeat = _fe3d.waterEntity_getTextureRepeat(_currentWaterID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("dudvMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game_assets\\textures\\dudv_maps\\");

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

			// Set DUDV map
			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.waterEntity_setDudvMap(_currentWaterID, newFilePath);
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
			_fe3d.waterEntity_setNormalMap(_currentWaterID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("displaceMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game_assets\\textures\\displacement_maps\\");

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

			// Set displacement map
			const string newFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache2D(newFilePath);
			_fe3d.waterEntity_setDisplacementMap(_currentWaterID, newFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.waterEntity_setDudvMap(_currentWaterID, "");
			_fe3d.waterEntity_setNormalMap(_currentWaterID, "");
			_fe3d.waterEntity_setDisplacementMap(_currentWaterID, "");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("textureRepeat", "Texture Repeat", textureRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("textureRepeat", textureRepeat))
		{
			_fe3d.waterEntity_setTextureRepeat(_currentWaterID, textureRepeat);
		}

		// Update buttons hoverability
		screen->getButton("clearMaps")->setHoverable(hasDudvMap || hasNormalMap || hasDisplacementMap);
		screen->getButton("textureRepeat")->setHoverable(hasDudvMap || hasNormalMap || hasDisplacementMap);
	}
}