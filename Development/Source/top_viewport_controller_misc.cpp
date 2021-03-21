#include "top_viewport_controller.hpp"

#include <filesystem>
#include <direct.h>
#include <fstream>  

#define SCRIPT_EXECUTOR _scriptEditor.getScriptExecutor(false)

bool TopViewportController::isScriptRunning()
{
	if (_currentProjectID == "")
	{
		return false;
	}
	else
	{
		return SCRIPT_EXECUTOR.isRunning();
	}
}

const string& TopViewportController::getCurrentProjectName()
{
	return _currentProjectID;
}

void TopViewportController::_updateMiscellaneous()
{
	bool hoverable = (_currentProjectID == "") ? false : !SCRIPT_EXECUTOR.isInitialized();

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

void TopViewportController::_updateProjectCreation()
{
	if (_creatingProject)
	{
		// Temporary values
		string newProjectName;

		// Check if value changed
		if (_gui.getGlobalScreen()->checkValueForm("newProjectName", newProjectName))
		{
			// Get directory path for the new project
			string newDirectoryPath = _fe3d.misc_getRootDirectory() + "projects\\" + newProjectName;

			// Check if project already exists
			if (_fe3d.misc_isFileExisting(newDirectoryPath) && _fe3d.misc_isDirectory(newDirectoryPath))
			{
				_fe3d.logger_throwWarning("Project \"" + newProjectName + "\"" + " already exists!");
			}
			else if (newProjectName.find_first_not_of(" ") == string::npos)
			{
				_fe3d.logger_throwWarning("New project name cannot contain any spaces!");
			}
			else if (isupper(newProjectName.front()))
			{
				_fe3d.logger_throwWarning("New project name cannot start with capital!");
			}
			else // Project is non-existent
			{
				// Generate new project directory
				auto temp = _mkdir(newDirectoryPath.c_str());

				// Generate project subfolders
				temp = _mkdir((newDirectoryPath + "\\data").c_str());
				temp = _mkdir((newDirectoryPath + "\\saves").c_str());
				temp = _mkdir((newDirectoryPath + "\\scenes").c_str());
				temp = _mkdir((newDirectoryPath + "\\scenes\\custom").c_str());
				temp = _mkdir((newDirectoryPath + "\\scenes\\editor").c_str());
				temp = _mkdir((newDirectoryPath + "\\scripts").c_str());

				// Create new empty project files
				auto file = std::ofstream(string(newDirectoryPath + "\\data\\animation.fe3d"));
				file.close();
				file = std::ofstream(string(newDirectoryPath + "\\data\\audio.fe3d"));
				file.close();
				file = std::ofstream(string(newDirectoryPath + "\\data\\billboard.fe3d"));
				file.close();
				file = std::ofstream(string(newDirectoryPath + "\\data\\model.fe3d"));
				file.close();
				file = std::ofstream(string(newDirectoryPath + "\\data\\sky.fe3d"));
				file.close();
				file = std::ofstream(string(newDirectoryPath + "\\data\\terrain.fe3d"));
				file.close();
				file = std::ofstream(string(newDirectoryPath + "\\data\\water.fe3d"));
				file.close();

				// Create settings file
				_settingsEditor.setCurrentProjectID(newProjectName);
				_settingsEditor.save(true);

				// Load current project
				_currentProjectID = newProjectName;
				_applyProjectChange();

				// Load settings for this project
				_settingsEditor.loadSettings();

				// Logging
				_fe3d.logger_throwInfo("New project \"" + _currentProjectID + "\" created!");

				// Miscellaneous
				_creatingProject = false;
			}
		}
	}
}

void TopViewportController::_updateProjectLoading()
{
	if (_loadingProject)
	{
		string clickedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("projectList");

		// Check if user clicked a project name
		if (clickedButtonID != "" && _fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			// Load current project
			_currentProjectID = clickedButtonID;
			_applyProjectChange();

			// Load settings for this project
			_settingsEditor.loadSettings();

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
			_fe3d.logger_throwInfo("Existing project \"" + _currentProjectID + "\" loaded!");

			// Miscellaneous
			_loadingProject = false;
			_gui.getGlobalScreen()->removeChoiceForm("projectList");
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("projectList"))
		{
			_loadingProject = false;
			_gui.getGlobalScreen()->removeChoiceForm("projectList");
		}
	}
}

void TopViewportController::_updateProjectDeletion()
{
	if (_deletingProject)
	{
		static string chosenButtonID = "";
		string clickedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("projectList");

		// Check if user clicked a project name
		if (clickedButtonID != "" && _fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_gui.getGlobalScreen()->addAnswerForm("deleteProject", "Are you sure?", Vec2(0.0f, 0.25f));
			chosenButtonID = clickedButtonID;
			_gui.getGlobalScreen()->removeChoiceForm("projectList");
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("projectList"))
		{
			_deletingProject = false;
			_gui.getGlobalScreen()->removeChoiceForm("projectList");
		}

		// Check if user is sure to delete
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("deleteProject"))
		{
			// Check if deleting currently opened project
			if (chosenButtonID == _currentProjectID)
			{
				// Unload current project
				_currentProjectID = "";
				_applyProjectChange();
			}

			// Check if project folder is still existing
			string directoryPath = _fe3d.misc_getRootDirectory() + "projects\\" + chosenButtonID;
			if (_fe3d.misc_isFileExisting(directoryPath) && _fe3d.misc_isDirectory(directoryPath))
			{
				// Deleting project folder
				std::filesystem::remove_all(directoryPath);

				// Logging
				_fe3d.logger_throwInfo("Existing project \"" + chosenButtonID + "\" deleted!");

				// Miscellaneous
				_deletingProject = false;
				chosenButtonID = "";
			}
			else
			{
				_fe3d.logger_throwWarning("Project \"" + chosenButtonID + "\" was already deleted!");
			}
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("deleteProject"))
		{
			_deletingProject = false;
			chosenButtonID = "";
		}
	}
}

void TopViewportController::_prepareProjectChoosing()
{
	// Get new path
	string userDirectoryPath = _fe3d.misc_getRootDirectory() + "projects\\";

	// Check if projects directory exists
	if (_fe3d.misc_isDirectory(userDirectoryPath))
	{
		// Get all project names
		vector<string> projectNames;
		for (const auto& entry : std::filesystem::directory_iterator(userDirectoryPath))
		{
			string projectName = string(entry.path().u8string());
			projectName.erase(0, userDirectoryPath.size());
			projectNames.push_back(projectName);
		}

		// Add buttons
		_gui.getGlobalScreen()->addChoiceForm("projectList", "Select project", Vec2(0.0f), projectNames);
	}
	else
	{
		_fe3d.logger_throwError("Projects folder is missing!");
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

	// Unload script editor (loaded by default)
	_scriptEditor.unload();

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