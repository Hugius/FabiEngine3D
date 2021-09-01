#include "top_viewport_controller.hpp"
#include "logger.hpp"

#include <filesystem>
#include <fstream>

using std::ofstream;
using std::filesystem::directory_iterator;
using std::filesystem::remove_all;

bool TopViewportController::isScriptStarted()
{
	if (_currentProjectID.empty())
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
	if (_currentProjectID.empty())
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
	bool hoverable = (_currentProjectID.empty()) ? false : !_scriptEditor.getScriptExecutor().isStarted();

	// Update buttons hoverability
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("skyEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("terrainEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("waterEditor")->setHoverable(hoverable);
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
	if (_isCreatingProject)
	{
		// Temporary values
		string newProjectID;

		// Check if user filled in a new ID
		if (_gui.getGlobalScreen()->checkValueForm("newProjectID", newProjectID))
		{
			// Temporary values
			const string projectDirectoryPath = (_fe3d.misc_getRootDirectory() + "projects\\");
			const string newProjectDirectoryPath = (projectDirectoryPath + newProjectID);

			// Check if projects directory exists
			if (!_fe3d.misc_isDirectoryExisting(projectDirectoryPath))
			{
				Logger::throwWarning("Directory `projects\\` is missing!");
				return;
			}

			if (newProjectID.find(' ') != string::npos) // ID contains spaces
			{
				Logger::throwWarning("New project name cannot contain any spaces!");
				return;
			}
			else if (_fe3d.misc_isDirectoryExisting(newProjectDirectoryPath)) // Project already exists
			{
				Logger::throwWarning("Project \"" + newProjectID + "\"" + " already exists!");
				return;
			}
			else if (std::any_of(newProjectID.begin(), newProjectID.end(), isupper)) // ID contains capitals
			{
				Logger::throwWarning("New project name cannot contain any capitals!");
				return;
			}
			else // Project is non-existent
			{
				// Generate new project directory
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath);

				// Generate project subdirectories
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\data");
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\saves");
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\scenes");
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\scenes\\custom");
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\scenes\\editor");
				_fe3d.misc_createNewDirectory(newProjectDirectoryPath + "\\scripts");

				// Create new empty project files
				auto file = ofstream(string(newProjectDirectoryPath + "\\data\\animation.fe3d"));
				file.close();
				file = ofstream(string(newProjectDirectoryPath + "\\data\\audio.fe3d"));
				file.close();
				file = ofstream(string(newProjectDirectoryPath + "\\data\\billboard.fe3d"));
				file.close();
				file = ofstream(string(newProjectDirectoryPath + "\\data\\model.fe3d"));
				file.close();
				file = ofstream(string(newProjectDirectoryPath + "\\data\\sky.fe3d"));
				file.close();
				file = ofstream(string(newProjectDirectoryPath + "\\data\\terrain.fe3d"));
				file.close();
				file = ofstream(string(newProjectDirectoryPath + "\\data\\water.fe3d"));
				file.close();
				file = ofstream(string(newProjectDirectoryPath + "\\settings.fe3d"));
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
				_isCreatingProject = false;
			}
		}
	}
}

bool TopViewportController::_prepareProjectChoosing(const string& title)
{
	// Temporary values
	const string projectDirectoryPath = (_fe3d.misc_getRootDirectory() + "projects\\");

	// Check if projects directory exists
	if (!_fe3d.misc_isDirectoryExisting(projectDirectoryPath))
	{
		Logger::throwWarning("Directory `projects\\` is missing!");
		return false;
	}

	// Get all project names
	vector<string> projectIDs;
	for (const auto& entry : directory_iterator(projectDirectoryPath))
	{
		// Extract project ID
		string projectPath = string(entry.path().u8string());
		if (_fe3d.misc_isDirectoryExisting(projectPath))
		{
			string projectID = projectPath;
			projectID.erase(0, projectDirectoryPath.size());
			projectIDs.push_back(projectID);
		}
	}

	// Add buttons
	_gui.getGlobalScreen()->createChoiceForm("projectList", title, Vec2(0.0f, 0.1f), projectIDs);

	return true;
}

void TopViewportController::_updateProjectLoading()
{
	if (_isLoadingProject)
	{
		// Temporary values
		const string clickedButtonID = _gui.getGlobalScreen()->checkChoiceForm("projectList");
		const string projectDirectoryPath = _fe3d.misc_getRootDirectory() + "projects\\" + clickedButtonID;

		// Check if user clicked a project ID
		if (clickedButtonID != "" && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			// Check if project is corrupted
			if (isProjectCorrupted(projectDirectoryPath))
			{
				Logger::throwWarning("Cannot load project: missing files/directories!");
				return;
			}

			// Load current project
			_currentProjectID = clickedButtonID;
			_applyProjectChange();

			// Load settings for this project
			_settingsEditor.loadSettingsFromFile();

			// Gather all file paths
			auto skyTexturePaths = _skyEditor.getAllTexturePathsFromFile();
			auto terrainTexturePaths = _terrainEditor.getAllTerrainTexturePathsFromFile();
			auto waterTexturePaths = _waterEditor.getAllWaterTexturePathsFromFile();
			auto modelTexturePaths = _modelEditor.getAllTexturePathsFromFile(); // This function already pre-caches all mesh files
			auto billboardTexturePaths = _billboardEditor.getAllTexturePathsFromFile();
			auto billboardFontPaths = _billboardEditor.getAllFontPathsFromFile();
			auto audioPaths = _audioEditor.getAllAudioPathsFromFile();

			// Cache 2D textures
			vector<string> texturePaths2D;
			texturePaths2D.insert(texturePaths2D.end(), terrainTexturePaths.begin(), terrainTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), waterTexturePaths.begin(), waterTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), modelTexturePaths.begin(), modelTexturePaths.end());
			texturePaths2D.insert(texturePaths2D.end(), billboardTexturePaths.begin(), billboardTexturePaths.end());
			_fe3d.misc_cacheTexturesMultiThreaded2D(texturePaths2D);

			// Cache 3D textures	
			_fe3d.misc_cacheTexturesMultiThreaded3D(skyTexturePaths);

			// Cache fonts
			_fe3d.misc_cacheFontsMultiThreaded(billboardFontPaths);

			// Cache audio
			_fe3d.misc_cacheAudioMultiThreaded(audioPaths);

			// Logging
			Logger::throwInfo("Existing project \"" + _currentProjectID + "\" loaded!");

			// Miscellaneous
			_isLoadingProject = false;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("projectList"))
		{
			_isLoadingProject = false;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}
	}
}

void TopViewportController::_updateProjectDeleting()
{
	if (_isDeletingProject)
	{
		// Temporary values
		static string chosenButtonID = "";
		string clickedButtonID = _gui.getGlobalScreen()->checkChoiceForm("projectList");

		// Check if user clicked a project ID
		if (clickedButtonID != "" && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
			chosenButtonID = clickedButtonID;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("projectList"))
		{
			_isDeletingProject = false;
			_gui.getGlobalScreen()->deleteChoiceForm("projectList");
		}

		// Update answer forms
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Check if deleting currently opened project
			if (chosenButtonID == _currentProjectID)
			{
				// Unload current project
				_currentProjectID = "";
				_applyProjectChange();
			}

			// Check if project directory is still existing
			const string directoryPath = (_fe3d.misc_getRootDirectory() + "projects\\" + chosenButtonID);
			if (!_fe3d.misc_isDirectoryExisting(directoryPath))
			{
				Logger::throwWarning("Cannot delete project: missing directory!");
				return;
			}

			// Delete project directory
			remove_all(directoryPath);

			// Logging
			Logger::throwInfo("Existing project \"" + chosenButtonID + "\" deleted!");

			// Miscellaneous
			_isDeletingProject = false;
			chosenButtonID = "";
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isDeletingProject = false;
			chosenButtonID = "";
		}
	}
}

void TopViewportController::_applyProjectChange()
{
	// Change window title
	if (_currentProjectID.empty())
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D");
	}
	else
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D - " + _currentProjectID);
	}

	// Go back to main menu
	_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");

	// Unload sky editor
	if (_skyEditor.isLoaded())
	{
		_skyEditor.unload();
	}

	// Unload terrain editor
	if (_terrainEditor.isLoaded())
	{
		_terrainEditor.unload();
	}

	// Unload water editor
	if (_waterEditor.isLoaded())
	{
		_waterEditor.unload();
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

	// Pass loaded project ID
	_skyEditor.setCurrentProjectID(_currentProjectID);
	_terrainEditor.setCurrentProjectID(_currentProjectID);
	_waterEditor.setCurrentProjectID(_currentProjectID);
	_modelEditor.setCurrentProjectID(_currentProjectID);
	_animationEditor.setCurrentProjectID(_currentProjectID);
	_billboardEditor.setCurrentProjectID(_currentProjectID);
	_audioEditor.setCurrentProjectID(_currentProjectID);
	_sceneEditor.setCurrentProjectID(_currentProjectID);
	_scriptEditor.setCurrentProjectID(_currentProjectID);
	_settingsEditor.setCurrentProjectID(_currentProjectID);
}

bool TopViewportController::isProjectCorrupted(const string& projectDirectoryPath)
{
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