#include "top_viewport_controller.hpp"

#include <fstream>
#include <filesystem>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>

void TopViewportController::initialize()
{
	// Top-viewport: projectWindow
	_gui->getViewport("topViewport")->addWindow("projectWindow", vec2(-0.25f, 0.0f), vec2(0.9825f, 1.5f), vec3(0.25f));
	_gui->getViewport("topViewport")->getWindow("projectWindow")->addScreen("mainScreen");
	_gui->getViewport("topViewport")->getWindow("projectWindow")->setActiveScreen("mainScreen");
	_gui->getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("newProject", vec2(-0.767f, 0.0f), vec2(0.3f, 1.25f), _buttonColor, _buttonHoverColor, "New project", _textColor, _textHoverColor);
	_gui->getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("loadProject", vec2(-0.384, 0.0f), vec2(0.3f, 1.25f), _buttonColor, _buttonHoverColor, "Load project", _textColor, _textHoverColor);
	_gui->getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("saveProject", vec2(0.0f, 0.0f), vec2(0.3f, 1.25f), _buttonColor, _buttonHoverColor, "Save project", _textColor, _textHoverColor);
	_gui->getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("openDocs", vec2(0.384, 0.0f), vec2(0.3f, 1.25f), _buttonColor, _buttonHoverColor, "Open docs", _textColor, _textHoverColor);
	_gui->getViewport("topViewport")->getWindow("projectWindow")->getScreen("mainScreen")->addButton("quitEngine", vec2(0.767f, 0.0f), vec2(0.3f, 1.25f), _buttonColor, _buttonHoverColor, "Quit engine", _textColor, _textHoverColor);

	// Top-viewport: gameWindow
	_gui->getViewport("topViewport")->addWindow("gameWindow", vec2(0.25f, 0.0f), vec2(0.9825f, 1.5f), vec3(0.25f));
	_gui->getViewport("topViewport")->getWindow("gameWindow")->addScreen("mainScreen");
	_gui->getViewport("topViewport")->getWindow("gameWindow")->setActiveScreen("mainScreen");
}

void TopViewportController::update(float delta)
{
	auto vp = _gui->getViewport("topViewport");

	// Getting hovered button
	string hoveredItemID = vp->getWindow("projectWindow")->getActiveScreen()->getHoveredItemID();

	// Check if LMB pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (hoveredItemID == "newProject")
		{
			_initializeProjectCreation();
		}
		else if (hoveredItemID == "loadProject")
		{
			_initializeProjectLoading();
		}
		else if (hoveredItemID == "saveProject")
		{
			_initializeProjectSaving();
		}
		else if (hoveredItemID == "openDocs")
		{
			_initializeDocsOpening();
		}
		else if (hoveredItemID == "quitEngine")
		{
			_initializeEngineQuitting();
		}
	}

	// Update specific processes
	_updateProjectCreation();
	_updateProjectLoading();
	_updateProjectSaving();
	_updateDocsOpening();
	_updateEngineQuitting();

	// Update button hoverability
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->getButton("modelEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->getButton("worldEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->getButton("placingEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->getButton("lightingEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("leftViewport")->getWindow("mainWindow")->getScreen("mainScreen")->getButton("scriptEditor")->setHoverable(_currentProjectName != "");
}

void TopViewportController::_initializeProjectCreation()
{
	if (!_creatingProject)
	{
		_gui->getGlobalScreen()->addTextfield("newProjectName", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Enter project name:", vec3(1.0f));
		_gui->getGlobalScreen()->addWriteField("newProjectName", vec2(0.0f, 0.0f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f));
		_gui->getGlobalScreen()->getWriteField("newProjectName")->setActive(true);
		_gui->setFocus(true);
		_creatingProject = true;
	}
}

void TopViewportController::_initializeProjectLoading()
{
	_loadingProject = true;
	_gui->getGlobalScreen()->addTextfield("projectList", vec2(0.0f, 0.45f), vec2(0.3f, 0.1f), "Select project:", vec3(1.0f));
	_gui->getGlobalScreen()->addScrollingList("projectList", vec2(0.0f, 0.0f), vec2(0.5, 0.75f), vec3(0.3f), _buttonColor, _buttonHoverColor, _textColor, _textHoverColor, 0.1f, 5);

	// Get new path
	string userDirectoryPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\";
	int endOfNameIndex = 0;

	// Get all project names
	for (const auto& entry : std::filesystem::directory_iterator(userDirectoryPath))
	{
		string projectName = string(entry.path().u8string());
		projectName.erase(0, userDirectoryPath.size());
		_gui->getGlobalScreen()->getScrollingList("projectList")->addButton(projectName, projectName);
	}
}

void TopViewportController::_initializeProjectSaving()
{
	_savingProject = true;
}

void TopViewportController::_initializeDocsOpening()
{
	_openingDocs = true;
}

void TopViewportController::_initializeEngineQuitting()
{
	_quittingEngine = true;
}

void TopViewportController::_updateProjectCreation()
{
	if (_creatingProject)
	{
		// Check if pressed ESCAPE or ENTER
		if (_gui->getGlobalScreen()->getWriteField("newProjectName")->cancelledInput() ||
			_gui->getGlobalScreen()->getWriteField("newProjectName")->confirmedInput())
		{
			// Extract new name
			string projectName = _gui->getGlobalScreen()->getWriteField("newProjectName")->getTextContent();

			// Create new project
			if (_gui->getGlobalScreen()->getWriteField("newProjectName")->confirmedInput())
			{
				// Get directory path for the new project
				string newDirectoryPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + projectName;

				// Check if project already exists
				struct stat info;
				stat(newDirectoryPath.c_str(), &info);
				if (info.st_mode & S_IFDIR) // Project already exists
				{
					Logger::getInst().throwWarning("Project \"" + projectName + "\"" + " already exists!");
				}
				else // Project non-existent
				{
					// Create new directory
					_mkdir(newDirectoryPath.c_str());

					// Create new models file
					std::ofstream file;
					file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + projectName + "\\models.fe3d");
					file << "test";
					file.close();

					// Apply to current project
					_currentProjectName = projectName;
				}
			}

			// Cleanup
			_creatingProject = false;
			_gui->setFocus(false);
			_gui->getGlobalScreen()->deleteTextfield("newProjectName");
			_gui->getGlobalScreen()->deleteWriteField("newProjectName");
		}
	}
}

void TopViewportController::_updateProjectLoading()
{
	if (_loadingProject)
	{
		
	}
}

void TopViewportController::_updateProjectSaving()
{
	if (_savingProject)
	{

	}
}

void TopViewportController::_updateDocsOpening()
{
	if (_openingDocs)
	{

	}
}

void TopViewportController::_updateEngineQuitting()
{
	if (_quittingEngine)
	{
		_fe3d.engine_stop();
	}
}