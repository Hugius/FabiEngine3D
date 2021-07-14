#include "top_viewport_controller.hpp"
#include "logger.hpp"

#include <filesystem>
#include <fstream>

bool TopViewportController::isScriptStarted()
{
	if (_currentProjectID == "")
	{
		return false;
	}
	else
	{
		return _scriptEditor.getScriptExecutor().isStarted();
	}
}

bool TopViewportController::isScriptRunning()
{
	if (_currentProjectID == "")
	{
		return false;
	}
	else
	{
		return _scriptEditor.getScriptExecutor().isRunning();
	}
}

void TopViewportController::_updateMiscellaneous()
{
	bool hoverable = (_currentProjectID == "") ? false : !_scriptEditor.getScriptExecutor().isStarted();

	// Project menus hoverability
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("environmentEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("modelEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("billboardEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("sceneEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("animationEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("audioEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("scriptEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("settingsEditor")->setHoverable(hoverable);
}

void TopViewportController::_updateProjectCreating()
{
	if (_creatingProject)
	{
		// Temporary values
		string newProjectID;

		// Check if value changed
		if (_gui.getGlobalScreen()->checkValueForm("newProjectID", newProjectID))
		{
			// Get directory path for the new project
			string newProjectDirectoryPath = _fe3d.misc_getRootDirectory() + "projects\\" + newProjectID;

			// Check if project already exists
			if (_fe3d.misc_isDirectoryExisting(newProjectDirectoryPath))
			{
				Logger::throwWarning("Project \"" + newProjectID + "\"" + " already exists!");
			}
			else if (newProjectID.find_first_not_of(" ") == string::npos)
			{
				Logger::throwWarning("New project name cannot contain any spaces!");
			}
			else if (isupper(newProjectID.front()))
			{
				Logger::throwWarning("New project name cannot start with capital!");
			}
			else // Project is non-existent
			{
				// Generate new project directory
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath);

				// Generate project subfolders
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\data");
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\saves");
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\scenes");
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\scenes\\custom");
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\scenes\\editor");
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\scripts");

				// Create new empty project files
				auto file = std::ofstream(string(newProjectDirectoryPath + "\\data\\animation.fe3d"));
				file.close();
				file = std::ofstream(string(newProjectDirectoryPath + "\\data\\audio.fe3d"));
				file.close();
				file = std::ofstream(string(newProjectDirectoryPath + "\\data\\billboard.fe3d"));
				file.close();
				file = std::ofstream(string(newProjectDirectoryPath + "\\data\\model.fe3d"));
				file.close();
				file = std::ofstream(string(newProjectDirectoryPath + "\\data\\sky.fe3d"));
				file.close();
				file = std::ofstream(string(newProjectDirectoryPath + "\\data\\terrain.fe3d"));
				file.close();
				file = std::ofstream(string(newProjectDirectoryPath + "\\data\\water.fe3d"));
				file.close();
				file = std::ofstream(string(newProjectDirectoryPath + "\\settings.fe3d"));
				file.close();

				// Load current project
				_currentProjectID = newProjectID;
				_applyProjectChange();

				// Create default settings
				_settingsEditor.loadDefaultSettings();
				_settingsEditor.saveSettingsToFile();

				// Logging
				Logger::throwInfo("New project \"" + _currentProjectID + "\" created!");

				// Miscellaneous
				_creatingProject = false;
			}
		}
	}
}

void TopViewportController::_prepareProjectLoading()
{
	// Get new path
	string userDirectoryPath = _fe3d.misc_getRootDirectory() + "projects\\";

	// Check if projects directory exists
	if (_fe3d.misc_isDirectoryExisting(userDirectoryPath))
	{
		// Get all project names
		vector<string> projectIDs;
		for (const auto& entry : std::filesystem::directory_iterator(userDirectoryPath))
		{
			// Extract project name
			string projectPath = string(entry.path().u8string());
			if (_fe3d.misc_isDirectoryExisting(projectPath))
			{
				string projectID = projectPath;
				projectID.erase(0, userDirectoryPath.size());
				projectIDs.push_back(projectID);
			}
		}

		// Add buttons
		_gui.getGlobalScreen()->addChoiceForm("projectList", "Select Project", Vec2(0.0f, 0.1f), projectIDs);
	}
	else
	{
		Logger::throwError("Projects folder is missing!");
	}
}

void TopViewportController::_updateProjectLoading()
{
	if (_loadingProject)
	{
		string clickedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("projectList");

		// Check if user clicked a project name
		if (clickedButtonID != "" && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (_isProjectCorrupted(clickedButtonID))
			{
				Logger::throwWarning("Cannot load project: corrupted files/folders!");
			}
			else
			{
				// Load current project
				_currentProjectID = clickedButtonID;
				_applyProjectChange();

				// Load settings for this project
				_settingsEditor.loadSettingsFromFile();

				// Preload all big assets of this project
				vector<string> texturePaths;
				auto skyTextures = _environmentEditor.getAllSkyTexturePathsFromFile();
				auto terrainTextures = _environmentEditor.getAllTerrainTexturePathsFromFile();
				auto waterTextures = _environmentEditor.getAllWaterTexturePathsFromFile();
				auto modelTextures = _modelEditor.getAllTexturePathsFromFile(); // This function already pre-caches all mesh files
				auto billboardTextures = _billboardEditor.getAllTexturePathsFromFile();
				auto audioPaths = _audioEditor.getAllAudioPathsFromFile();
				texturePaths.insert(texturePaths.end(), terrainTextures.begin(), terrainTextures.end());
				texturePaths.insert(texturePaths.end(), waterTextures.begin(), waterTextures.end());
				texturePaths.insert(texturePaths.end(), modelTextures.begin(), modelTextures.end());
				texturePaths.insert(texturePaths.end(), billboardTextures.begin(), billboardTextures.end());
				_fe3d.misc_cacheTexturesMultiThreaded2D(texturePaths); // Pre-cache 2D texture files
				_fe3d.misc_cacheTexturesMultiThreaded3D(skyTextures); // Pre-cache 3D texture files
				_fe3d.misc_cacheAudioMultiThreaded(audioPaths); // Pre-cache audio files

				// Logging
				Logger::throwInfo("Existing project \"" + _currentProjectID + "\" loaded!");

				// Miscellaneous
				_loadingProject = false;
				_gui.getGlobalScreen()->deleteChoiceForm("projectList");
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("projectList"))
		{
			_loadingProject = false;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}
	}
}

void TopViewportController::_updateProjectDeleting()
{
	if (_deletingProject)
	{
		static string chosenButtonID = "";
		string clickedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("projectList");

		// Check if user clicked a project name
		if (clickedButtonID != "" && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_gui.getGlobalScreen()->addAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
			chosenButtonID = clickedButtonID;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("projectList"))
		{
			_deletingProject = false;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}

		// Check if user is sure to delete
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Check if deleting currently opened project
			if (chosenButtonID == _currentProjectID)
			{
				// Unload current project
				_currentProjectID = "";
				_applyProjectChange();
			}

			// Check if project folder is still existing
			string directoryPath = (_fe3d.misc_getRootDirectory() + "projects\\" + chosenButtonID);
			if (_fe3d.misc_isDirectoryExisting(directoryPath))
			{
				// Deleting project folder
				std::filesystem::remove_all(directoryPath);

				// Logging
				Logger::throwInfo("Existing project \"" + chosenButtonID + "\" deleted!");

				// Miscellaneous
				_deletingProject = false;
				chosenButtonID = "";
			}
			else
			{
				Logger::throwWarning("Project \"" + chosenButtonID + "\" was already deleted!");
			}
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_deletingProject = false;
			chosenButtonID = "";
		}
	}
}

void TopViewportController::_applyProjectChange()
{
	// Change window title
	if (_currentProjectID == "")
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D");
	}
	else
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D - " + _currentProjectID);
	}

	// Go back to main menu
	_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");

	// Unload environment editor
	if (_environmentEditor.isLoaded())
	{
		_environmentEditor.unload();
	}

	// Unload model editor
	if (_modelEditor.isLoaded())
	{
		_modelEditor.unload();
	}

	// Unload animation editor
	if (_animationEditor.isLoaded())
	{
		_animationEditor.unload();
	}

	// Unload billboard editor
	if (_billboardEditor.isLoaded())
	{
		_billboardEditor.unload();
	}

	// Unload audio editor
	if (_audioEditor.isLoaded())
	{
		_audioEditor.unload();
	}

	// Unload scene editor
	if (_sceneEditor.isLoaded())
	{
		_sceneEditor.unload();
	}

	// Unload script editor
	if (_scriptEditor.isLoaded())
	{
		_scriptEditor.unload();
	}

	// Unload settings editor
	if (_settingsEditor.isLoaded())
	{
		_settingsEditor.unload();
	}

	// Pass loaded project name
	_environmentEditor.setCurrentProjectID(_currentProjectID);
	_modelEditor.setCurrentProjectID(_currentProjectID);
	_animationEditor.setCurrentProjectID(_currentProjectID);
	_billboardEditor.setCurrentProjectID(_currentProjectID);
	_audioEditor.setCurrentProjectID(_currentProjectID);
	_sceneEditor.setCurrentProjectID(_currentProjectID);
	_scriptEditor.setCurrentProjectID(_currentProjectID);
	_settingsEditor.setCurrentProjectID(_currentProjectID);
}

bool TopViewportController::_isProjectCorrupted(const string& projectID)
{
	// Compose full directory path
	string projectDirectoryPath = _fe3d.misc_getRootDirectory() + "projects\\" + projectID;

	// Check if all default directories are still existing
	if (!_fe3d.misc_isDirectoryExisting(projectDirectoryPath) ||
		!_fe3d.misc_isDirectoryExisting(projectDirectoryPath + "\\data") ||
		!_fe3d.misc_isDirectoryExisting(projectDirectoryPath + "\\saves") ||
		!_fe3d.misc_isDirectoryExisting(projectDirectoryPath + "\\scenes") ||
		!_fe3d.misc_isDirectoryExisting(projectDirectoryPath + "\\scenes\\custom") ||
		!_fe3d.misc_isDirectoryExisting(projectDirectoryPath + "\\scenes\\editor") ||
		!_fe3d.misc_isDirectoryExisting(projectDirectoryPath + "\\scripts"))
	{
		return true;
	}

	// Check if all default files are still existing
	if (!_fe3d.misc_isFileExisting(projectDirectoryPath + "\\data\\animation.fe3d") ||
		!_fe3d.misc_isFileExisting(projectDirectoryPath + "\\data\\audio.fe3d") ||
		!_fe3d.misc_isFileExisting(projectDirectoryPath + "\\data\\billboard.fe3d") ||
		!_fe3d.misc_isFileExisting(projectDirectoryPath + "\\data\\model.fe3d") ||
		!_fe3d.misc_isFileExisting(projectDirectoryPath + "\\data\\sky.fe3d") ||
		!_fe3d.misc_isFileExisting(projectDirectoryPath + "\\data\\terrain.fe3d") ||
		!_fe3d.misc_isFileExisting(projectDirectoryPath + "\\data\\water.fe3d") ||
		!_fe3d.misc_isFileExisting(projectDirectoryPath + "\\settings.fe3d"))
	{
		return true;
	}

	return false;
}