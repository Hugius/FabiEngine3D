#include "top_viewport_controller.hpp"

#include <fstream>
#include <sstream>

#define SCRIPT_EXECUTOR _scriptEditor.getScriptExecutor(false)

TopViewportController::TopViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui,
	EnvironmentEditor& environmentEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor,
	SceneEditor& sceneEditor, AnimationEditor& animationEditor, ScriptEditor& scriptEditor, 
	AudioEditor& audioEditor, SettingsEditor& settingsEditor) :
	ViewportController(fe3d, gui),
	_modelEditor(modelEditor),
	_environmentEditor(environmentEditor),
	_billboardEditor(billboardEditor),
	_sceneEditor(sceneEditor),
	_animationEditor(animationEditor),
	_scriptEditor(scriptEditor),
	_audioEditor(audioEditor),
	_settingsEditor(settingsEditor)
{

}

void TopViewportController::initialize()
{
	// Top-viewport windows
	_gui.getViewport("top")->addWindow("projectWindow", Vec2(-0.25f, 0.0f), Vec2(0.9875f, 1.5f), TVPC::frameColor);
	_gui.getViewport("top")->addWindow("gameWindow", Vec2(0.125f, 0.0f), Vec2(0.4875f, 1.5f), Vec3(0.25f));
	_gui.getViewport("top")->addWindow("miscWindow", Vec2(0.375f, 0.0f), Vec2(0.4875f, 1.5f), Vec3(0.25f));
	_projectWindow = _gui.getViewport("top")->getWindow("projectWindow");
	_gameWindow = _gui.getViewport("top")->getWindow("gameWindow");
	_miscWindow = _gui.getViewport("top")->getWindow("miscWindow");
	
	// Top-viewport: projectWindow
	_projectWindow->addScreen("main");
	_projectWindow->setActiveScreen("main");
	auto screen = _projectWindow->getScreen("main");
	screen->addButton("newProject", Vec2(-0.767f, 0.0f), Vec2(0.15f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "NEW", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("loadProject", Vec2(-0.384f, 0.0f), Vec2(0.2f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "LOAD", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("saveProject", Vec2(0.0f, 0.0f), Vec2(0.2f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "SAVE", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("deleteProject", Vec2(0.384f, 0.0f), Vec2(0.3f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "DELETE", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("quitEngine", Vec2(0.767f, 0.0f), Vec2(0.2f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "QUIT", TVPC::textColor, TVPC::textHoverColor);

	// Top-viewport: gameWindow
	_gameWindow->addScreen("main");
	_gameWindow->setActiveScreen("main");
	screen = _gameWindow->getScreen("main");
	screen->addButton("play", Vec2(-0.6f, 0.0f), Vec2(0.2f, 1.75f), "play.png", Vec3(2.0f));
	screen->addButton("pause", Vec2(-0.2f, 0.0f), Vec2(0.2f, 1.75f), "pause.png", Vec3(2.0f));
	screen->addButton("restart", Vec2(0.2f, 0.0f), Vec2(0.2f, 1.75f), "restart.png", Vec3(2.0f));
	screen->addButton("stop", Vec2(0.6f, 0.0f), Vec2(0.2f, 1.75f), "stop.png", Vec3(2.0f));

	// Top-viewport: miscWindow
	_miscWindow->addScreen("main");
	_miscWindow->setActiveScreen("main");
	screen = _miscWindow->getScreen("main");
	screen->addButton("uncache", Vec2(0.0f, 0.0f), Vec2(0.5f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "UNCACHE", TVPC::textColor, TVPC::textHoverColor);
}

void TopViewportController::update()
{
	_updateProjectScreenManagement();
	_updateGameScreenManagement();
	_updateMiscScreenManagement();
	_updateMiscellaneous();
}

void TopViewportController::_updateProjectScreenManagement()
{
	// Temporary values
	auto screen = _projectWindow->getActiveScreen();

	// GUI management
	if (screen->getID() == "main")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("newProject")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("newProjectName", "Enter project name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
				_creatingProject = true;
			}
			else if (screen->getButton("loadProject")->isHovered())
			{
				_prepareProjectChoosing();
				_loadingProject = true;
			}
			else if (screen->getButton("saveProject")->isHovered())
			{
				_saveCurrentProject();
			}
			else if (screen->getButton("deleteProject")->isHovered())
			{
				_prepareProjectChoosing();
				_deletingProject = true;
			}
			else if (screen->getButton("quitEngine")->isHovered())
			{
				// Check if currently in an editor
				if (_currentProjectName != "" && _gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() != "main")
				{
					_gui.getGlobalScreen()->addAnswerForm("exitEngine", "Save changes?", Vec2(0.0f, 0.25f));
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

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitEngine"))
		{
			_saveCurrentProject();
			_fe3d.engine_stop();
		}
		else if (_gui.getGlobalScreen()->isAnswerFormCancelled("exitEngine"))
		{
			_fe3d.engine_stop();
		}

		// Buttons hoverability
		screen->getButton("saveProject")->setHoverable(_currentProjectName != "");
	}
}

void TopViewportController::_updateGameScreenManagement()
{
	// Temporary values
	auto projectScreen = _projectWindow->getActiveScreen();
	auto gameScreen = _gameWindow->getScreen("main");
	auto miscScreen = _miscWindow->getScreen("main");

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
					_scriptEditor.getScriptExecutor(true).load();
				}
			}
			else if (gameScreen->getButton("pause")->isHovered())
			{
				SCRIPT_EXECUTOR.pause();
			}
			else if (gameScreen->getButton("restart")->isHovered())
			{
				SCRIPT_EXECUTOR.unload();
				_scriptEditor.getScriptExecutor(true).load();
			}
			else if (gameScreen->getButton("stop")->isHovered())
			{
				SCRIPT_EXECUTOR.unload();
			}
		}

		// Update game buttons hoverability
		bool isInMainMenu = (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "main");
		gameScreen->getButton("play")->setHoverable(isInMainMenu && !SCRIPT_EXECUTOR.isScriptEmpty() && !SCRIPT_EXECUTOR.isRunning());
		gameScreen->getButton("pause")->setHoverable(isInMainMenu && SCRIPT_EXECUTOR.isRunning());
		gameScreen->getButton("restart")->setHoverable(isInMainMenu && SCRIPT_EXECUTOR.isInitialized());
		gameScreen->getButton("stop")->setHoverable(isInMainMenu && SCRIPT_EXECUTOR.isInitialized());

		// Update other buttons hoverability
		if (SCRIPT_EXECUTOR.isInitialized())
		{
			projectScreen->getButton("newProject")->setHoverable(false);
			projectScreen->getButton("loadProject")->setHoverable(false);
			projectScreen->getButton("saveProject")->setHoverable(false);
			projectScreen->getButton("deleteProject")->setHoverable(false);
			miscScreen->getButton("uncache")->setHoverable(false);
		}
		else
		{
			projectScreen->getButton("newProject")->setHoverable(true);
			projectScreen->getButton("loadProject")->setHoverable(true);
			projectScreen->getButton("saveProject")->setHoverable(true);
			projectScreen->getButton("deleteProject")->setHoverable(true);
			miscScreen->getButton("uncache")->setHoverable(true);
		}
		std::cout << "wtf";
		// Check if user wants to pause the running game
		if (SCRIPT_EXECUTOR.isRunning())
		{
			// Check if user pressed ESCAPE
			if (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				SCRIPT_EXECUTOR.pause();
			}
		}

		// Executing game script (if possible)
		SCRIPT_EXECUTOR.update();
	}
}

void TopViewportController::_updateMiscScreenManagement()
{
	// Temporary values
	auto screen = _miscWindow->getScreen("main");

	// Check if LMB pressed
	if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("uncache")->isHovered())
		{
			// Get the chosen filename
			const string rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("user\\assets\\");
			const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "");

			// Check if user did not cancel
			if (filePath != "")
			{
				// Make path relative
				const string newFilePath = filePath.substr(rootDirectory.size());

				// Clear the cache of selected file
				_fe3d.misc_clearOBJCache(newFilePath);
				_fe3d.misc_clearFontCache(newFilePath);
				_fe3d.misc_clearTextureCache(newFilePath);
				_fe3d.misc_clearHeightMapCache(newFilePath);
				_fe3d.misc_clearAudioChunkCache(newFilePath);
				_fe3d.misc_clearAudioMusicCache(newFilePath);
			}
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
	_environmentEditor.save();
	_modelEditor.saveGameEntitiesToFile();
	_billboardEditor.saveBillboardEntitiesToFile();
	_sceneEditor.saveSceneToFile();
	_animationEditor.saveAnimationsToFile();
	_scriptEditor.saveScriptsToFile();
	_audioEditor.saveAudioEntitiesToFile();

	// Logging
	_fe3d.logger_throwInfo("Project \"" + _currentProjectName + "\" saved!");
}

void TopViewportController::_updateProjectChange()
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

	// Unload animation editor
	if (_animationEditor.isLoaded())
	{
		_animationEditor.unload();
	}

	// Unload script editor (loaded by default)
	_scriptEditor.unload();

	// Unload audio editor
	if (_audioEditor.isLoaded())
	{
		_audioEditor.unload();
	}

	// Pass loaded project name
	_environmentEditor.setCurrentProjectName(_currentProjectName);
	_modelEditor.setCurrentProjectName(_currentProjectName);
	_billboardEditor.setCurrentProjectName(_currentProjectName);
	_sceneEditor.setCurrentProjectName(_currentProjectName);
	_animationEditor.setCurrentProjectName(_currentProjectName);
	_scriptEditor.setCurrentProjectName(_currentProjectName);
	_audioEditor.setCurrentProjectName(_currentProjectName);
	_settingsEditor.setCurrentProjectName(_currentProjectName);
}