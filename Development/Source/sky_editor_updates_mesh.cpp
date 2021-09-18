#include "sky_editor.hpp"
#include "logger.hpp"

void SkyEditor::_updateMeshMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "skyEditorMenuMesh")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rightMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\cube_maps\\");

			// Validate target directory
			if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
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
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapRight(_currentSkyID, finalFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("leftMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\cube_maps\\");

			// Validate target directory
			if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
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
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapLeft(_currentSkyID, finalFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("topMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\cube_maps\\");

			// Validate target directory
			if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
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
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapTop(_currentSkyID, finalFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("bottomMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\cube_maps\\");

			// Validate target directory
			if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
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
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapBottom(_currentSkyID, finalFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("frontMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\cube_maps\\");

			// Validate target directory
			if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
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
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapFront(_currentSkyID, finalFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("backMap")->isHovered())
		{
			// Get the chosen filename
			const auto rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\textures\\cube_maps\\");

			// Validate target directory
			if (!_fe3d.misc_isDirectoryExisting(rootDirectory + targetDirectory))
			{
				Logger::throwWarning("Directory `" + targetDirectory + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = _fe3d.misc_getWinExplorerFilename(string(rootDirectory + targetDirectory), "PNG");
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
			const string finalFilePath = filePath.substr(rootDirectory.size());
			_fe3d.misc_clearTextureCache3D(_fe3d.skyEntity_getDiffuseMapPaths(_currentSkyID));
			_fe3d.skyEntity_setDiffuseMapBack(_currentSkyID, finalFilePath);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
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