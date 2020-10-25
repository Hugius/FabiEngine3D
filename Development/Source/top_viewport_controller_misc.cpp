#include "top_viewport_controller.hpp"

#include <filesystem>
#include <direct.h>

#define SCRIPT_EXECUTOR _scriptEditor.getScriptExecutor()

bool TopViewportController::isScriptRunning()
{
	if (_currentProjectName == "")
	{
		return false;
	}
	else
	{
		return SCRIPT_EXECUTOR.isRunning();
	}
}

void TopViewportController::_updateMiscellaneous()
{
	bool hoverable = (_currentProjectName == "") ? false : !SCRIPT_EXECUTOR.isInitialized();

	// Project menus
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("modelEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("worldEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("billboardEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("sceneEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("animationEditor")->setHoverable(hoverable);
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("scriptEditor")->setHoverable(hoverable);

	// Settings menu can be loaded without project
	_gui.getViewport("left")->getWindow("main")->getScreen("main")->getButton("settingsEditor")->setHoverable(hoverable || (_currentProjectName == ""));
}

void TopViewportController::_updateProjectCreation()
{
	if (_creatingProject)
	{
		string projectName;

		if (_gui.getGlobalScreen()->checkValueForm("newProjectName", projectName))
		{
			// Get directory path for the new project
			string newDirectoryPath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + projectName;

			// Check if project already exists
			if (_fe3d.misc_isFileExisting(newDirectoryPath) && _fe3d.misc_isDirectory(newDirectoryPath))
			{
				Logger::throwWarning("Project \"" + projectName + "\"" + " already exists!");
			}
			else // Project is non-existent
			{
				// Create new project directory & subfolders
				auto temp1 = _mkdir(newDirectoryPath.c_str());
				auto temp2 = _mkdir((newDirectoryPath + "\\data").c_str());
				auto temp3 = _mkdir((newDirectoryPath + "\\scenes").c_str());
				auto temp4 = _mkdir((newDirectoryPath + "\\scripts").c_str());

				// Load current project
				_currentProjectName = projectName;
				_updateCurrentProject();

				// Logging
				_fe3d.logger_throwInfo("New project \"" + _currentProjectName + "\" created!");

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
			_currentProjectName = clickedButtonID;
			_updateCurrentProject();

			// Logging
			_fe3d.logger_throwInfo("Existing project \"" + _currentProjectName + "\" loaded!");

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
			_gui.getGlobalScreen()->addAnswerForm("deleteProject", "Are you sure?", vec2(0.0f, 0.25f));
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
			if (chosenButtonID == _currentProjectName)
			{
				// Unload current project
				_currentProjectName = "";
				_updateCurrentProject();
			}

			// Check if project folder is still existing
			string directoryPath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + chosenButtonID;
			if (_fe3d.misc_isFileExisting(directoryPath) && _fe3d.misc_isDirectory(directoryPath))
			{
				// Deleting project folder
				std::filesystem::remove_all(directoryPath);

				// Logging
				_fe3d.logger_throwInfo("Existing project \"" + chosenButtonID + "\" deleted!");

				// Miscellaneous
				_deletingProject = false;
				_fe3d.misc_setWindowTitle("FabiEngine3D");
				chosenButtonID = "";
			}
			else
			{
				_fe3d.logger_throwWarning("Project \"" + chosenButtonID + "\" is corrupted!");
			}
		}
		else if (_gui.getGlobalScreen()->isAnswerFormCancelled("deleteProject"))
		{
			_deletingProject = false;
			chosenButtonID = "";
		}
	}
}

void TopViewportController::_prepareProjectChoosing()
{
	// Get new path
	string userDirectoryPath = _fe3d.misc_getRootDirectory() + "user\\projects\\";

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
		_gui.getGlobalScreen()->addChoiceForm("projectList", "Select project", vec2(0.0f), projectNames);
	}
	else
	{
		_fe3d.logger_throwError("User folder is corrupted!");
	}
}