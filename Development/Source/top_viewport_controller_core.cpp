#include "top_viewport_controller.hpp"

#include <fstream>
#include <sstream>

#define SCRIPT_EXECUTOR _scriptEditor.getScriptExecutor()

TopViewportController::TopViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, 
	ModelEditor& modelEditor, WorldEditor& worldEditor, BillboardEditor& billboardEditor, SceneEditor& sceneEditor, ScriptEditor& scriptEditor) :
	ViewportController(fe3d, gui),
	_modelEditor(modelEditor),
	_worldEditor(worldEditor),
	_billboardEditor(billboardEditor),
	_sceneEditor(sceneEditor),
	_scriptEditor(scriptEditor)
{

}

void TopViewportController::initialize()
{
	// Top-viewport windows
	_gui->getViewport("top")->addWindow("projectWindow", vec2(-0.25f, 0.0f), vec2(0.9825f, 1.5f), TVPC::frameColor);
	_gui->getViewport("top")->addWindow("gameWindow", vec2(0.25f, 0.0f), vec2(0.9825f, 1.5f), vec3(0.25f));
	_projectWindow = _gui->getViewport("top")->getWindow("projectWindow");
	_gameWindow = _gui->getViewport("top")->getWindow("gameWindow");
	
	// Top-viewport: projectWindow
	_projectWindow->addScreen("main");
	_projectWindow->setActiveScreen("main");
	auto screen = _projectWindow->getScreen("main");
	screen->addButton("newProject", vec2(-0.767f, 0.0f), vec2(0.15f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "NEW", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("loadProject", vec2(-0.384, 0.0f), vec2(0.2f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "LOAD", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("saveProject", vec2(0.0f, 0.0f), vec2(0.2f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "SAVE", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("deleteProject", vec2(0.384, 0.0f), vec2(0.3f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "DELETE", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("quitEngine", vec2(0.767f, 0.0f), vec2(0.2f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "QUIT", TVPC::textColor, TVPC::textHoverColor);

	// Top-viewport: gameWindow
	_gameWindow->addScreen("main");
	_gameWindow->setActiveScreen("main");
	screen = _gameWindow->getScreen("main");
	screen->addButton("play", vec2(-0.85f, 0.0f), vec2(0.1f, 1.75f), "play.png", vec3(2.0f));
	screen->addButton("pause", vec2(-0.65f, 0.0f), vec2(0.1f, 1.75f), "pause.png", vec3(2.0f));
	screen->addButton("restart", vec2(-0.45f, 0.0f), vec2(0.1f, 1.75f), "restart.png", vec3(2.0f));
	screen->addButton("stop", vec2(-0.25f, 0.0f), vec2(0.1f, 1.75f), "stop.png", vec3(2.0f));
}

void TopViewportController::update()
{
	_updateProjectManagement();
	_updateGameManagement();
	_updateMiscellaneous();
}

void TopViewportController::_updateProjectManagement()
{
	auto projectScreen = _projectWindow->getScreen("main");

	// Check if LMB pressed
	if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if (projectScreen->getButton("newProject")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("newProjectName", "Enter project name", "", vec2(0.0f), vec2(0.5f, 0.1f));
			_creatingProject = true;
		}
		else if (projectScreen->getButton("loadProject")->isHovered())
		{
			_prepareProjectChoosing();
			_loadingProject = true;
		}
		else if (projectScreen->getButton("saveProject")->isHovered())
		{
			_saveCurrentProject();
		}
		else if (projectScreen->getButton("deleteProject")->isHovered())
		{
			_prepareProjectChoosing();
			_deletingProject = true;
		}
		else if (projectScreen->getButton("quitEngine")->isHovered())
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

	// Update save button hoverability
	bool scriptRunning = (_currentProjectName == "") ? false : SCRIPT_EXECUTOR.isInitialized();
	projectScreen->getButton("newProject")->setHoverable(!scriptRunning);
	projectScreen->getButton("loadProject")->setHoverable(!scriptRunning);
	projectScreen->getButton("saveProject")->setHoverable(!scriptRunning && _currentProjectName != "");
	projectScreen->getButton("deleteProject")->setHoverable(!scriptRunning);
	projectScreen->getButton("quitEngine")->setHoverable(!scriptRunning);

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

void TopViewportController::_updateGameManagement()
{
	auto gameScreen = _gameWindow->getScreen("main");

	// Check if currently a project is loaded
	if (_currentProjectName == "")
	{
		gameScreen->getButton("play")->setHoverable(false);
		gameScreen->getButton("pause")->setHoverable(false);
		gameScreen->getButton("restart")->setHoverable(false);
		gameScreen->getButton("stop")->setHoverable(false);
	}
	else
	{
		// Check if LMB pressed
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (gameScreen->getButton("play")->isHovered())
			{
				// Unpause game or load game
				if (SCRIPT_EXECUTOR.isInitialized())
				{
					SCRIPT_EXECUTOR.unpause();
				}
				else
				{
					// Load all assets before executing script
					SCRIPT_EXECUTOR.load();
					_sceneEditor.loadScene(false);
				}
			}
			else if (gameScreen->getButton("pause")->isHovered())
			{
				// Pause script execution
				SCRIPT_EXECUTOR.pause();
			}
			else if (gameScreen->getButton("restart")->isHovered())
			{
				// Unload
				SCRIPT_EXECUTOR.unload();
				_sceneEditor.unloadScene();

				// Load again
				SCRIPT_EXECUTOR.load();
				_sceneEditor.loadScene(false);
			}
			else if (gameScreen->getButton("stop")->isHovered())
			{
				// Reset everything and load main menu again
				SCRIPT_EXECUTOR.unload();
				_sceneEditor.unloadScene();
				_fe3d.skyEntity_select("@@defaultSky");
			}
		}

		// Game buttons hoverability
		bool isInMainMenu = (_gui->getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "main");
		gameScreen->getButton("play")->setHoverable(isInMainMenu && !SCRIPT_EXECUTOR.isScriptEmpty() && !SCRIPT_EXECUTOR.isRunning());
		gameScreen->getButton("pause")->setHoverable(isInMainMenu && SCRIPT_EXECUTOR.isRunning());
		gameScreen->getButton("restart")->setHoverable(isInMainMenu && SCRIPT_EXECUTOR.isInitialized());
		gameScreen->getButton("stop")->setHoverable(isInMainMenu && SCRIPT_EXECUTOR.isInitialized());

		// Check if player wants to pause the running game
		if (SCRIPT_EXECUTOR.isRunning())
		{
			if (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				SCRIPT_EXECUTOR.pause();
			}
		}

		// Executing game script (if possible)
		SCRIPT_EXECUTOR.update();
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
	_sceneEditor.save();
	_scriptEditor.save();

	// Logging
	_fe3d.logger_throwInfo("Project \"" + _currentProjectName + "\" saved!");
}

void TopViewportController::_loadCurrentProject()
{
	// Change window title
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

	// Pass loaded project name
	_modelEditor.setCurrentProjectName(_currentProjectName);
	_worldEditor.setCurrentProjectName(_currentProjectName);
	_billboardEditor.setCurrentProjectName(_currentProjectName);
	_sceneEditor.setCurrentProjectName(_currentProjectName);
	_scriptEditor.setCurrentProjectName(_currentProjectName);
}