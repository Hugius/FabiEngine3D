#include "top_viewport_controller.hpp"

#include <filesystem>
#include <direct.h>

bool TopViewportController::isScriptRunning()
{
	if (_currentProjectName == "")
	{
		return false;
	}
	else
	{
		return _scriptEditor.getScriptExecutor()->isRunning();
	}
}

void TopViewportController::_updateMiscellaneous()
{
	bool hoverable = (_currentProjectName == "") ? false : !_scriptEditor.getScriptExecutor()->isInitialized();

	// Project menus
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("modelEditor")->setHoverable(hoverable);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("worldEditor")->setHoverable(hoverable);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("billboardEditor")->setHoverable(hoverable);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("sceneEditor")->setHoverable(hoverable);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("animationEditor")->setHoverable(hoverable);
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("scriptEditor")->setHoverable(hoverable);

	// Settings menu can be loaded without project
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("settingsEditor")->setHoverable(hoverable || (_currentProjectName == ""));
}

void TopViewportController::_updateProjectCreation()
{
	if (_creatingProject)
	{
		string projectName;

		if (_gui->getGlobalScreen()->checkValueForm("newProjectName", projectName))
		{
			// Get directory path for the new project
			string newDirectoryPath = _fe3d.misc_getRootDirectory() + "User\\projects\\" + projectName;

			// Check if project already exists
			if (_fe3d.misc_isFileExisting(newDirectoryPath) && _fe3d.misc_isDirectory(newDirectoryPath)) // Project is existent
			{
				Logger::getInst().throwWarning("Project \"" + projectName + "\"" + " already exists!");
			}
			else // Project is non-existent
			{
				// Create new project directory & subfolders
				auto temp1 = _mkdir(newDirectoryPath.c_str());
				auto temp2 = _mkdir((newDirectoryPath + "\\Data").c_str());
				auto temp3 = _mkdir((newDirectoryPath + "\\Scenes").c_str());

				// Load current project
				_currentProjectName = projectName;
				_loadCurrentProject();

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
		string clickedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("projectList");

		// Check if user clicked a project name
		if (clickedButtonID != "" && _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			// Load current project
			_currentProjectName = clickedButtonID;
			_loadCurrentProject();

			// Logging
			_fe3d.logger_throwInfo("Existing project \"" + _currentProjectName + "\" loaded!");

			// Miscellaneous
			_loadingProject = false;
			_gui->getGlobalScreen()->removeChoiceForm("projectList");
		}
		else if (_gui->getGlobalScreen()->isChoiceFormCancelled("projectList"))
		{
			_loadingProject = false;
			_gui->getGlobalScreen()->removeChoiceForm("projectList");
		}
	}
}

void TopViewportController::_updateProjectDeletion()
{
	if (_deletingProject)
	{
		static string chosenButtonID = "";
		string clickedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("projectList");

		// Check if user clicked a project name
		if (clickedButtonID != "" && _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			_gui->getGlobalScreen()->addAnswerForm("deleteProject", "Are you sure?", vec2(0.0f, 0.25f));
			chosenButtonID = clickedButtonID;
			_gui->getGlobalScreen()->removeChoiceForm("projectList");
		}
		else if (_gui->getGlobalScreen()->isChoiceFormCancelled("projectList"))
		{
			_deletingProject = false;
			_gui->getGlobalScreen()->removeChoiceForm("projectList");
		}

		// Check if user is sure to delete
		if (_gui->getGlobalScreen()->isAnswerFormConfirmed("deleteProject"))
		{
			// Check if deleting currently opened project
			if (chosenButtonID == _currentProjectName)
			{
				// Unload current project
				_currentProjectName = "";
				_loadCurrentProject();
			}

			// Deleting project folder
			std::filesystem::remove_all(_fe3d.misc_getRootDirectory() + "User\\projects\\" + chosenButtonID);

			// Logging
			_fe3d.logger_throwInfo("Existing project \"" + chosenButtonID + "\" deleted!");

			// Miscellaneous
			_deletingProject = false;
			_fe3d.misc_setWindowTitle("FabiEngine3D");
			chosenButtonID = "";
		}
		else if (_gui->getGlobalScreen()->isAnswerFormCancelled("deleteProject"))
		{
			_deletingProject = false;
			chosenButtonID = "";
		}
	}
}

void TopViewportController::_prepareProjectChoosing()
{
	// Get new path
	string userDirectoryPath = _fe3d.misc_getRootDirectory() + "User\\projects\\";

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
		_gui->getGlobalScreen()->addChoiceForm("projectList", "Select project", vec2(0.0f), projectNames);
	}
	else
	{
		_fe3d.logger_throwError("\"User\\projects\\\" folder does not exist anymore!");
	}
}