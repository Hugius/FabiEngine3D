#include "top_viewport_controller.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>

TopViewportController::TopViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, ModelEditor& modelEditor) :
	ViewportController(fe3d, gui),
	_modelEditor(modelEditor)
	
{

}

TopViewportController::~TopViewportController()
{
	_saveCurrentProject();
}

void TopViewportController::initialize()
{
	// Top-viewport: projectWindow
	_gui->getViewport("top")->addWindow("projectWindow", vec2(-0.25f, 0.0f), vec2(0.9825f, 1.5f), vec3(0.25f));
	_gui->getViewport("top")->getWindow("projectWindow")->addScreen("main");
	_gui->getViewport("top")->getWindow("projectWindow")->setActiveScreen("main");
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("newProject", vec2(-0.767f, 0.0f), vec2(0.3f, 1.25f), _buttonColor, _buttonHoverColor, "New project", _textColor, _textHoverColor);
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("loadProject", vec2(-0.384, 0.0f), vec2(0.3f, 1.25f), _buttonColor, _buttonHoverColor, "Load project", _textColor, _textHoverColor);
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("saveProject", vec2(0.0f, 0.0f), vec2(0.3f, 1.25f), _buttonColor, _buttonHoverColor, "Save project", _textColor, _textHoverColor);
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("openDocs", vec2(0.384, 0.0f), vec2(0.3f, 1.25f), _buttonColor, _buttonHoverColor, "Open docs", _textColor, _textHoverColor);
	_gui->getViewport("top")->getWindow("projectWindow")->getScreen("main")->addButton("quitEngine", vec2(0.767f, 0.0f), vec2(0.3f, 1.25f), _buttonColor, _buttonHoverColor, "Quit engine", _textColor, _textHoverColor);

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
		_gui->getGlobalScreen()->addTextfield("newProjectName", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Enter project name:", vec3(1.0f));
		_gui->getGlobalScreen()->addWriteField("newProjectName", vec2(0.0f, 0.0f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f));
		_gui->getGlobalScreen()->getWriteField("newProjectName")->setActive(true);
		_gui->setFocus(true);
		_creatingProject = true;
	}
}

void TopViewportController::_initializeProjectLoading()
{
	if (!_creatingProject && !_loadingProject)
	{
		_gui->getGlobalScreen()->addTextfield("projectList", vec2(0.0f, 0.45f), vec2(0.3f, 0.1f), "Select project:", vec3(1.0f));
		_gui->getGlobalScreen()->addScrollingList("projectList", vec2(0.0f, 0.0f), vec2(0.5, 0.75f), vec3(0.3f), _buttonColor, _buttonHoverColor, _textColor, _textHoverColor, vec2(0.1f, 0.25f));
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
					file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + projectName + "\\models.fe3d");;
					file.close();

					// Apply to current project
					_currentProjectName = projectName;

					// Go back to main editor screen
					_gui->getViewport("left")->getWindow("main")->setActiveScreen("main");

					// Unload model editor
					if (_modelEditor.isLoaded())
					{
						_modelEditor.unload();
					}
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
						_modelEditor.unload();
					}

					// Load models file
					std::ifstream file;
					file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\models.fe3d");
					string line;

					// Read model data
					while (std::getline(file, line))
					{
						string modelName, objName, diffuseName, lightName, reflectionName;
						float width, height, depth;
						std::istringstream iss(line);
						
						// Extract from file
						iss >> modelName >> objName >> diffuseName >> lightName >> reflectionName >> width >> height >> depth;
						objName        = (objName == "-") ? "" : objName;
						diffuseName    = (diffuseName == "-") ? "" : diffuseName;
						lightName      = (lightName == "-") ? "" : lightName;
						reflectionName = (reflectionName == "-") ? "" : reflectionName;

						// Add new model
						_modelEditor.addModel(modelName, objName, diffuseName, lightName, reflectionName, vec3(width, height, depth));
					}

					// Close file
					file.close();
				}
			}
		}

		// Cleaning up
		if (_fe3d.input_getKeyDown(Input::KEY_ESCAPE) || loaded)
		{
			_gui->getGlobalScreen()->deleteTextfield("projectList");
			_gui->getGlobalScreen()->deleteScrollingList("projectList");
			_gui->setFocus(false);
			_loadingProject = false;
			return;
		}
	}
}

void TopViewportController::_saveCurrentProject()
{
	if (_currentProjectName != "")
	{
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\models.fe3d");

		// Write model data into file
		for (auto& modelName : _modelEditor.getModelNames())
		{
			// Check if 3D entity exists
			if (_fe3d.gameEntity_isExisting(modelName))
			{
				auto objName = _fe3d.gameEntity_getObjName(modelName);
				auto diffuseMapName = _fe3d.gameEntity_getDiffuseMapName(modelName);
				diffuseMapName = (diffuseMapName == "") ? "-" : diffuseMapName;
				auto lightMapName = _fe3d.gameEntity_getLightMapName(modelName);
				lightMapName = (lightMapName == "") ? "-" : lightMapName;
				auto reflectionMapName = _fe3d.gameEntity_getReflectionMapName(modelName);
				reflectionMapName = (reflectionMapName == "") ? "-" : reflectionMapName;
				auto modelSize = _fe3d.gameEntity_getSize(modelName);

				// 1 model -> 1 line in file
				file << modelName << " " << objName << " " << diffuseMapName << " " << lightMapName << " " << reflectionMapName << " " <<
					std::to_string(modelSize.x) << " " << std::to_string(modelSize.y) << " " << std::to_string(modelSize.z) << "\n";
			}
			else
			{
				file << modelName << " -  -  -  -  0  0  0\n";
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Current project saved!");
	}
}