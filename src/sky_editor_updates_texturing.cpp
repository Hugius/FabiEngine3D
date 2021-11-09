#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void SkyEditor::_updateTexturingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "skyEditorMenuTexturing")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rightMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game\\" + _currentProjectID + "\\assets\\textures\\cube_maps\\");

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
			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapRight(_currentSkyID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("leftMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game\\" + _currentProjectID + "\\assets\\textures\\cube_maps\\");

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
			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapLeft(_currentSkyID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("topMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game\\" + _currentProjectID + "\\assets\\textures\\cube_maps\\");

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
			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapTop(_currentSkyID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("bottomMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game\\" + _currentProjectID + "\\assets\\textures\\cube_maps\\");

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
			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapBottom(_currentSkyID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("frontMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game\\" + _currentProjectID + "\\assets\\textures\\cube_maps\\");

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
			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapFront(_currentSkyID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("backMap")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("game\\" + _currentProjectID + "\\assets\\textures\\cube_maps\\");

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
			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapBack(_currentSkyID, finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d.skyEntity_setDiffuseMaps(_currentSkyID, { "","","","","","" });
		}

		// Update buttons hoverability
		screen->getButton("clearMaps")->setHoverable(
			_fe3d.skyEntity_hasDiffuseMapRight(_currentSkyID) ||
			_fe3d.skyEntity_hasDiffuseMapLeft(_currentSkyID) ||
			_fe3d.skyEntity_hasDiffuseMapTop(_currentSkyID) ||
			_fe3d.skyEntity_hasDiffuseMapBottom(_currentSkyID) ||
			_fe3d.skyEntity_hasDiffuseMapFront(_currentSkyID) ||
			_fe3d.skyEntity_hasDiffuseMapBack(_currentSkyID));
	}
}