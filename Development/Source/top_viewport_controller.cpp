#include "top_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>

TopViewportController::TopViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, 
	ModelEditor& modelEditor, WorldEditor& worldEditor, BillboardEditor& billboardEditor, EntityPlacer& entityPlacer) :
	ViewportController(fe3d, gui),
	_modelEditor(modelEditor),
	_worldEditor(worldEditor),
	_billboardEditor(billboardEditor),
	_entityPlacer(entityPlacer)
{

}

void TopViewportController::initialize()
{
	// Top-viewport: projectWindow
	_gui->getViewport("top")->addWindow("projectWindow", vec2(-0.25f, 0.0f), vec2(0.9825f, 1.5f), vec3(0.25f));
	_gui->getViewport("top")->getWindow("projectWindow")->addScreen("main");
	_gui->getViewport("top")->getWindow("projectWindow")->setActiveScreen("main");
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("newProject", vec2(-0.767f, 0.0f), vec2(0.3f, 1.25f), _gui->topVpButtonColor, _gui->topVpButtonHoverColor, "New project", _gui->topVpTextColor, _gui->topVpTextHoverColor);
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("loadProject", vec2(-0.384, 0.0f), vec2(0.3f, 1.25f), _gui->topVpButtonColor, _gui->topVpButtonHoverColor, "Load project", _gui->topVpTextColor, _gui->topVpTextHoverColor);
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("saveProject", vec2(0.0f, 0.0f), vec2(0.3f, 1.25f), _gui->topVpButtonColor, _gui->topVpButtonHoverColor, "Save project", _gui->topVpTextColor, _gui->topVpTextHoverColor);
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("deleteProject", vec2(0.384, 0.0f), vec2(0.3f, 1.25f), _gui->topVpButtonColor, _gui->topVpButtonHoverColor, "Delete project", _gui->topVpTextColor, _gui->topVpTextHoverColor);
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("quitEngine", vec2(0.767f, 0.0f), vec2(0.3f, 1.25f), _gui->topVpButtonColor, _gui->topVpButtonHoverColor, "Quit engine", _gui->topVpTextColor, _gui->topVpTextHoverColor);

	// Top-viewport: gameWindow
	_gui->getViewport("top")->addWindow("gameWindow", vec2(0.25f, 0.0f), vec2(0.9825f, 1.5f), vec3(0.25f));
	_gui->getViewport("top")->getWindow("gameWindow")->addScreen("main");
	_gui->getViewport("top")->getWindow("gameWindow")->setActiveScreen("main");
}

void TopViewportController::update()
{
	auto projectWindow = _gui->getViewport("top")->getWindow("projectWindow");
	auto mainScreen = projectWindow->getScreen("main");

	// Check if LMB pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (mainScreen->getButton("newProject")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("newProjectName", "Enter project name", "", vec2(0.0f), vec2(0.5f, 0.1f));
			_creatingProject = true;
		}
		else if (mainScreen->getButton("loadProject")->isHovered())
		{
			_initializeProjectChoosing();
			_loadingProject = true;
		}
		else if (mainScreen->getButton("saveProject")->isHovered())
		{
			_saveCurrentProject();
		}
		else if (mainScreen->getButton("deleteProject")->isHovered())
		{
			_initializeProjectChoosing();
			_deletingProject = true;
		}
		else if (mainScreen->getButton("quitEngine")->isHovered())
		{
			if (_currentProjectName != "") // A project must be loaded
			{
				_gui->getGlobalScreen()->addAnswerForm("exitEngine", "Save changes?", vec2(0.0f, 0.25f));
			}
			else // Otherwise, just exit the engine
			{
				_fe3d.engine_stop();
			}
		}
	}

	// Update specific processes
	_updateProjectCreation();
	_updateProjectLoading();
	_updateProjectDeletion();

	// Update button hoverability
	mainScreen->getButton("saveProject")->setHoverable(_currentProjectName != "");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("modelEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("worldEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("billboardEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("entityPlacer")->setHoverable(_currentProjectName != "");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("scriptEditor")->setHoverable(_currentProjectName != "");

	// Check if user wants to save changes
	if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitEngine"))
	{
		_saveCurrentProject();
		_fe3d.engine_stop();
	}
	else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitEngine"))
	{
		_fe3d.engine_stop();
	}
}

void TopViewportController::_initializeProjectChoosing()
{
	// Get new path
	string userDirectoryPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\";

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
		_fe3d.logger_throwError("\"User\\Projects\\\" folder does not exist anymore!");
	}
}

void TopViewportController::_updateProjectCreation()
{
	if (_creatingProject)
	{
		string projectName;

		if (_gui->getGlobalScreen()->checkValueForm("newProjectName", projectName))
		{
			// Get directory path for the new project
			string newDirectoryPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + projectName;

			// Check if project already exists
			if (_fe3d.misc_isFileExisting(newDirectoryPath) && _fe3d.misc_isDirectory(newDirectoryPath)) // Project is existent
			{
				Logger::getInst().throwWarning("Project \"" + projectName + "\"" + " already exists!");
			}
			else // Project is non-existent
			{
				// Create new directory
				_mkdir(newDirectoryPath.c_str());

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
			std::filesystem::remove_all(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + chosenButtonID);

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

void TopViewportController::_saveCurrentProject()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to save as empty project!");
	}

	// Save everything
	_modelEditor.save();
	_worldEditor.save();
	_billboardEditor.save();
	_entityPlacer.save();

	// Logging
	_fe3d.logger_throwInfo("Project \"" + _currentProjectName + "\" saved!");
}

void TopViewportController::_loadCurrentProject()
{
	if (_currentProjectName == "")
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D");
	}
	else
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D - " + _currentProjectName);
	}

	// Go back to main editor screen
	_gui->getViewport("left")->getWindow("main")->setActiveScreen("main");

	// Unload model editor
	if (_modelEditor.isLoaded())
	{
		_modelEditor.unload();
	}

	// Unload world editor
	if (_worldEditor.isLoaded())
	{
		_worldEditor.unload();
	}

	// Unload billboard editor
	if (_billboardEditor.isLoaded())
	{
		_billboardEditor.unload();
	}

	// Unload entity placer
	if (_entityPlacer.isLoaded())
	{
		_entityPlacer.unload();
	}

	// Pass loaded project name
	_modelEditor.setCurrentProjectName(_currentProjectName);
	_worldEditor.setCurrentProjectName(_currentProjectName);
	_billboardEditor.setCurrentProjectName(_currentProjectName);
	_entityPlacer.setCurrentProjectName(_currentProjectName);
}