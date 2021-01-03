#include "top_viewport_controller.hpp"

#include <filesystem>
#include <direct.h>

#define SCRIPT_EXECUTOR _scriptEditor.getScriptExecutor(false)

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
			string newDirectoryPath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + newProjectName;

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
				// Create new project directory & subfolders
				auto temp1 = _mkdir(newDirectoryPath.c_str());
				auto temp2 = _mkdir((newDirectoryPath + "\\data").c_str());
				auto temp3 = _mkdir((newDirectoryPath + "\\scenes").c_str());
				auto temp4 = _mkdir((newDirectoryPath + "\\scripts").c_str());

				// Create settings file
				_settingsEditor.setCurrentProjectName(newProjectName);
				_settingsEditor.save(true);

				// Load current project
				_currentProjectName = newProjectName;
				_updateProjectChange();

				// Load settings for this project
				_settingsEditor.load();

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
			_updateProjectChange();

			// Load settings for this project
			_settingsEditor.load();

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
			if (chosenButtonID == _currentProjectName)
			{
				// Unload current project
				_currentProjectName = "";
				_updateProjectChange();
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
		_gui.getGlobalScreen()->addChoiceForm("projectList", "Select project", Vec2(0.0f), projectNames);
	}
	else
	{
		_fe3d.logger_throwError("User folder is corrupted!");
	}
}