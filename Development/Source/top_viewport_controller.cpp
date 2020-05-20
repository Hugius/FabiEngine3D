#include "top_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>

TopViewportController::TopViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, ModelEditor& modelEditor, WorldEditor& worldEditor) :
	ViewportController(fe3d, gui),
	_modelEditor(modelEditor),
	_worldEditor(worldEditor)
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
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("openDocs", vec2(0.384, 0.0f), vec2(0.3f, 1.25f), _gui->topVpButtonColor, _gui->topVpButtonHoverColor, "Open docs", _gui->topVpTextColor, _gui->topVpTextHoverColor);
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("quitEngine", vec2(0.767f, 0.0f), vec2(0.3f, 1.25f), _gui->topVpButtonColor, _gui->topVpButtonHoverColor, "Quit engine", _gui->topVpTextColor, _gui->topVpTextHoverColor);

	// Top-viewport: gameWindow
	_gui->getViewport("top")->addWindow("gameWindow", vec2(0.25f, 0.0f), vec2(0.9825f, 1.5f), vec3(0.25f));
	_gui->getViewport("top")->getWindow("gameWindow")->addScreen("main");
	_gui->getViewport("top")->getWindow("gameWindow")->setActiveScreen("main");
}

void TopViewportController::update(float delta)
{
	auto projectWindow = _gui->getViewport("top")->getWindow("projectWindow");

	// Check if LMB pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (projectWindow->getScreen("main")->getButton("newProject")->isHovered())
		{
			_initializeProjectCreation();
		}
		else if (projectWindow->getScreen("main")->getButton("loadProject")->isHovered())
		{
			_initializeProjectLoading();
		}
		else if (projectWindow->getScreen("main")->getButton("saveProject")->isHovered())
		{
			_saveCurrentProject();
		}
		else if (projectWindow->getScreen("main")->getButton("openDocs")->isHovered())
		{
			
		}
		else if (projectWindow->getScreen("main")->getButton("quitEngine")->isHovered())
		{
			_fe3d.engine_stop();
		}
	}

	// Update specific processes
	_updateProjectCreation();
	_updateProjectLoading();

	// Update button hoverability
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("modelEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("worldEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("placingEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("lightingEditor")->setHoverable(_currentProjectName != "");
	_gui->getViewport("left")->getWindow("main")->getScreen("main")->getButton("scriptEditor")->setHoverable(_currentProjectName != "");
}

void TopViewportController::_initializeProjectCreation()
{
	if (!_creatingProject && !_loadingProject)
	{
		_gui->getGlobalScreen()->addTextfield("newProjectName", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Enter project name", vec3(1.0f));
		_gui->getGlobalScreen()->addWriteField("newProjectName", vec2(0.0f, 0.0f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f));
		_gui->getGlobalScreen()->getWriteField("newProjectName")->setActive(true);
		_gui->getGlobalScreen()->addButton("done", vec2(-0.15f, -0.2f), vec2(0.15f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));
		_gui->getGlobalScreen()->addButton("cancel", vec2(0.15f, -0.2f), vec2(0.15f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "Cancel", vec3(1.0f), vec3(0.0f));
		_gui->setFocus(true);
		_creatingProject = true;
	}
}

void TopViewportController::_initializeProjectLoading()
{
	if (!_creatingProject && !_loadingProject)
	{
		_gui->getGlobalScreen()->addTextfield("projectList", vec2(0.0f, 0.45f), vec2(0.3f, 0.1f), "Select project", vec3(1.0f));
		_gui->getGlobalScreen()->addScrollingList("projectList", vec2(0.0f, 0.0f), vec2(0.5, 0.75f), vec3(0.3f), _gui->topVpButtonColor, _gui->topVpButtonHoverColor, _gui->topVpTextColor, _gui->topVpTextHoverColor, vec2(0.1f, 0.25f));
		_gui->getGlobalScreen()->addButton("cancel", vec2(0.0f, -0.45f), vec2(0.15f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "Cancel", vec3(1.0f), vec3(0.0f));
		_gui->setFocus(true);
		_loadingProject = true;

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
}

void TopViewportController::_updateProjectCreation()
{
	if (_creatingProject)
	{
		bool done = _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && _gui->getGlobalScreen()->getButton("done")->isHovered();
		bool cancelled = _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && _gui->getGlobalScreen()->getButton("cancel")->isHovered();
		bool entered = _gui->getGlobalScreen()->getWriteField("newProjectName")->confirmedInput();
		bool escaped = _gui->getGlobalScreen()->getWriteField("newProjectName")->cancelledInput();
		bool cleanup = false;

		// Check if user confirmed or cancelled
		if (done || entered || cancelled || escaped)
		{
			// Extract new name
			string projectName = _gui->getGlobalScreen()->getWriteField("newProjectName")->getTextContent();

			// Create new project
			if (done || entered)
			{
				// Projectname must be valid
				if (projectName != "")
				{
					cleanup = true;

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
						file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + projectName + "\\models.fe3d");;
						file.close();

						// Apply to current project
						_currentProjectName = projectName;

						// Go back to main editor screen
						_gui->getViewport("left")->getWindow("main")->setActiveScreen("main");

						// Unload model editor
						if (_modelEditor.isLoaded())
						{
							_modelEditor.unloadProject();
						}

						// Unload world editor
						if (_worldEditor.isLoaded())
						{
							_worldEditor.unloadProject();
						}
					}
				}
			}
			else
			{
				cleanup = true;
			}

			// Cleanup
			if (cleanup)
			{
				_creatingProject = false;
				_gui->setFocus(false);
				_gui->getGlobalScreen()->deleteTextfield("newProjectName");
				_gui->getGlobalScreen()->deleteWriteField("newProjectName");
				_gui->getGlobalScreen()->deleteButton("done");
				_gui->getGlobalScreen()->deleteButton("cancel");
			}
		}
	}
}

void TopViewportController::_updateProjectLoading()
{
	if (_loadingProject)
	{
		bool loaded = false;

		// Check if project must be loaded
		for (auto& button : _gui->getGlobalScreen()->getScrollingList("projectList")->getButtons())
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (button->isHovered())
				{
					// Change active project
					_currentProjectName = button->getID();
					_fe3d.misc_setWindowTitle("FabiEngine3D - " + _currentProjectName);
					loaded = true;

					// Go back to main editor screen
					_gui->getViewport("left")->getWindow("main")->setActiveScreen("main");

					// Unload model editor
					if (_modelEditor.isLoaded())
					{
						_modelEditor.unloadProject();
					}

					// Unload world editor
					if (_worldEditor.isLoaded())
					{
						_worldEditor.unloadProject();
					}

					// Give new project name
					_modelEditor.setCurrentProjectName(_currentProjectName);
				}
			}
		}

		// Cleaning up
		if (loaded || _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && _gui->getGlobalScreen()->getButton("cancel")->isHovered())
		{
			_gui->getGlobalScreen()->deleteTextfield("projectList");
			_gui->getGlobalScreen()->deleteScrollingList("projectList");
			_gui->getGlobalScreen()->deleteButton("cancel");
			_gui->setFocus(false);
			_loadingProject = false;
			return;
		}
	}
}

void TopViewportController::_saveCurrentProject()
{
	_modelEditor.saveProject();
}