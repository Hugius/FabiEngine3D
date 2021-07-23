#include "top_viewport_controller.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>

TopViewportController::TopViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui,
	EnvironmentEditor& environmentEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor,
	SceneEditor& sceneEditor, AnimationEditor& animationEditor, ScriptEditor& scriptEditor, 
	AudioEditor& audioEditor, SettingsEditor& settingsEditor) :
	BaseViewportController(fe3d, gui),
	_environmentEditor(environmentEditor),
	_modelEditor(modelEditor),
	_animationEditor(animationEditor),
	_billboardEditor(billboardEditor),
	_audioEditor(audioEditor),
	_sceneEditor(sceneEditor),
	_scriptEditor(scriptEditor),
	_settingsEditor(settingsEditor)
{

}

void TopViewportController::initialize()
{
	// Top-viewport windows
	_gui.getViewport("top")->addWindow("projectWindow", Vec2(-0.25f, 0.0f), Vec2(0.9875f, 1.5f), TVPC::FRAME_COLOR);
	_gui.getViewport("top")->addWindow("runWindow", Vec2(0.125f, 0.0f), Vec2(0.4875f, 1.5f), TVPC::FRAME_COLOR);
	_gui.getViewport("top")->addWindow("miscWindow", Vec2(0.375f, 0.0f), Vec2(0.4875f, 1.5f), TVPC::FRAME_COLOR);
	_projectWindow = _gui.getViewport("top")->getWindow("projectWindow");
	_gameWindow = _gui.getViewport("top")->getWindow("runWindow");
	_miscWindow = _gui.getViewport("top")->getWindow("miscWindow");
	
	// Top-viewport: projectWindow
	_projectWindow->addScreen("main");
	_projectWindow->setActiveScreen("main");
	auto screen = _projectWindow->getScreen("main");
	screen->addButton("newProject", Vec2(-0.767f, 0.0f), Vec2(0.15f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "NEW", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR);
	screen->addButton("loadProject", Vec2(-0.384f, 0.0f), Vec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "LOAD", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR);
	screen->addButton("saveProject", Vec2(0.0f, 0.0f), Vec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "SAVE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR);
	screen->addButton("deleteProject", Vec2(0.384f, 0.0f), Vec2(0.3f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "DELETE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR);
	screen->addButton("quitEngine", Vec2(0.767f, 0.0f), Vec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "QUIT", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR);

	// Top-viewport: gameWindow
	_gameWindow->addScreen("main");
	_gameWindow->setActiveScreen("main");
	screen = _gameWindow->getScreen("main");
	screen->addButton("play", Vec2(-0.73f, 0.0f), Vec2(0.2f, 1.75f), "play.png", Vec3(2.0f));
	screen->addButton("pause", Vec2(-0.36f, 0.0f), Vec2(0.2f, 1.75f), "pause.png", Vec3(2.0f));
	screen->addButton("restart", Vec2(0.0f, 0.0f), Vec2(0.2f, 1.75f), "restart.png", Vec3(2.0f));
	screen->addButton("stop", Vec2(0.36f, 0.0f), Vec2(0.2f, 1.75f), "stop.png", Vec3(2.0f));
	screen->addButton("debug", Vec2(0.73f, 0.0f), Vec2(0.2f, 1.75f), "debug.png", Vec3(2.0f));

	// Top-viewport: miscWindow
	_miscWindow->addScreen("main");
	_miscWindow->setActiveScreen("main");
	screen = _miscWindow->getScreen("main");
	screen->addButton("uncache", Vec2(-0.55f, 0.0f), Vec2(0.49f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "UNCACHE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR);
	screen->addButton("documentation", Vec2(0.35f, 0.0f), Vec2(0.91f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "DOCUMENTATION", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR);
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
	auto topScreen = _projectWindow->getActiveScreen();
	auto leftScreen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (topScreen->getID() == "main")
	{
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (topScreen->getButton("newProject")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("newProjectID", "Enter Project Name", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
				_creatingProject = true;
			}
			else if (topScreen->getButton("loadProject")->isHovered())
			{
				_prepareProjectLoading();
				_loadingProject = true;
			}
			else if (topScreen->getButton("saveProject")->isHovered())
			{
				_saveCurrentProject();
			}
			else if (topScreen->getButton("deleteProject")->isHovered())
			{
				_prepareProjectLoading();
				_deletingProject = true;
			}
			else if (topScreen->getButton("quitEngine")->isHovered())
			{
				// Check if currently in an editor (except for: scene editor & environment editor)
				if (_currentProjectID != "" && leftScreen->getID() != "main" && 
					leftScreen->getID() != "sceneEditorMenuMain" && leftScreen->getID() != "environmentEditorMenuMain")
				{
					_gui.getGlobalScreen()->addAnswerForm("quit", "Save Changes?", Vec2(0.0f, 0.25f));
				}
				else // Otherwise, just stop the engine
				{
					_fe3d.application_stop();
				}
			}
		}

		// Update specific processes
		_updateProjectCreating();
		_updateProjectLoading();
		_updateProjectDeleting();

		// Quitting with ESCAPE
		if (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && leftScreen->getID() == "main")
		{
			// Check if script execution not started
			if (!_scriptEditor.getScriptExecutor().isStarted())
			{
				_fe3d.application_stop();
			}
		}

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("quit"))
		{
			_saveCurrentProject();
			_fe3d.application_stop();
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("quit"))
		{
			_fe3d.application_stop();
		}

		// Button hoverabilities
		topScreen->getButton("saveProject")->setHoverable(_currentProjectID != "");
	}
}

void TopViewportController::_updateGameScreenManagement()
{
	// Temporary values
	auto projectScreen = _projectWindow->getActiveScreen();
	auto gameScreen = _gameWindow->getScreen("main");
	auto miscScreen = _miscWindow->getScreen("main");

	// Check if currently a project is loaded
	if (_currentProjectID == "")
	{
		gameScreen->getButton("play")->setHoverable(false);
		gameScreen->getButton("pause")->setHoverable(false);
		gameScreen->getButton("restart")->setHoverable(false);
		gameScreen->getButton("stop")->setHoverable(false);
		gameScreen->getButton("debug")->setHoverable(false);
	}
	else
	{
		// Check if LMB pressed
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (gameScreen->getButton("play")->isHovered())
			{
				// Resume game or load game
				if (_scriptEditor.getScriptExecutor().isStarted())
				{
					_scriptEditor.getScriptExecutor().resume();
				}
				else
				{
					_scriptEditor.loadScriptFiles();
					_scriptEditor.getScriptExecutor().load();
				}
			}
			else if (gameScreen->getButton("pause")->isHovered())
			{
				_scriptEditor.getScriptExecutor().pause();
			}
			else if (gameScreen->getButton("restart")->isHovered())
			{
				_scriptEditor.getScriptExecutor().unload();
				_scriptEditor.loadScriptFiles();
				_scriptEditor.getScriptExecutor().load();
			}
			else if (gameScreen->getButton("stop")->isHovered())
			{
				_scriptEditor.getScriptExecutor().unload();
			}
			else if (gameScreen->getButton("debug")->isHovered())
			{
				_scriptEditor.getScriptExecutor().resume();
				_scriptEditor.getScriptExecutor().update(true);
				_scriptEditor.getScriptExecutor().pause();
			}
		}

		// Update game buttons hoverability
		static bool wasInMainMenu = false;
		bool isInMainMenu = (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "main");
		gameScreen->getButton("play")->setHoverable(isInMainMenu && !_scriptEditor.getScriptExecutor().isScriptEmpty() && !isScriptRunning());
		gameScreen->getButton("pause")->setHoverable(isInMainMenu && isScriptRunning() && !_fe3d.networkServer_isRunning());
		gameScreen->getButton("restart")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());
		gameScreen->getButton("stop")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());
		gameScreen->getButton("debug")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());

		// Reload script files every second or if user came into menu
		bool cameIntoMenu = (!wasInMainMenu && isInMainMenu);
		if (cameIntoMenu || (isInMainMenu && !isScriptStarted() && _fe3d.misc_checkInterval(Config::UPDATES_PER_SECOND)))
		{
			_scriptEditor.loadScriptFiles(false);
		}
		wasInMainMenu = isInMainMenu;

		// Update other buttons hoverability
		projectScreen->getButton("newProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
		projectScreen->getButton("loadProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
		projectScreen->getButton("saveProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
		projectScreen->getButton("deleteProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
		miscScreen->getButton("uncache")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());

		// Check if user wants to pause the running game
		if (_scriptEditor.getScriptExecutor().isRunning())
		{
			// Check if user pressed ESCAPE
			if (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (_fe3d.networkServer_isRunning()) // Server application cannot be paused, only on or off
				{
					_scriptEditor.getScriptExecutor().unload();
				}
				else // Non-server application can be paused
				{
					_scriptEditor.getScriptExecutor().pause();
				}
			}
		}

		// Executing game script (if possible)
		_scriptEditor.getScriptExecutor().update(false);
	}
}

void TopViewportController::_updateMiscScreenManagement()
{
	// Temporary values
	auto screen = _miscWindow->getScreen("main");

	// Check if LMB pressed
	if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		// Check if button is hovered
		if (screen->getButton("uncache")->isHovered())
		{
			// Get the chosen filename
			const string rootDirectory = _fe3d.misc_getRootDirectory();
			const string targetDirectory = string("game_assets\\");
			const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "");

			// Check if user did not cancel
			if (filePath != "")
			{
				// Check if user did not switch directory
				if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
					filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
				{
					// Make path relative
					const string newFilePath = filePath.substr(rootDirectory.size());

					// Clear the cache of selected file
					_fe3d.misc_clearMeshCache(newFilePath);
					_fe3d.misc_clearFontCache(newFilePath);
					_fe3d.misc_clearTextureCache2D(newFilePath);
					_fe3d.misc_clearBitmapCache(newFilePath);
					_fe3d.misc_clearAudioChunkCache(newFilePath);
					_fe3d.misc_clearAudioMusicCache(newFilePath);
				}
				else
				{
					Logger::throwWarning("Invalid filepath, directory switching not allowed!");
				}
			}
		}
		else if (screen->getButton("documentation")->isHovered())
		{
			ShellExecute(0, 0, "https://github.com/ConsolePeasant92/FabiEngine3D/blob/master/README.md", 0, 0, SW_SHOW);
		}
	}
}

void TopViewportController::_saveCurrentProject()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("TopViewportController::_saveCurrentProject() ---> no current project loaded!");
	}

	// Save everything
	_environmentEditor.saveSkyEntitiesToFile();
	_environmentEditor.saveTerrainEntitiesToFile();
	_environmentEditor.saveWaterEntitiesToFile();
	_modelEditor.saveModelEntitiesToFile();
	_animationEditor.saveAnimationsToFile();
	_billboardEditor.saveBillboardEntitiesToFile();
	_audioEditor.saveAudioEntitiesToFile();
	_sceneEditor.saveEditorSceneToFile();
	_scriptEditor.saveScriptFiles();
	_settingsEditor.saveSettingsToFile();

	// Logging
	Logger::throwInfo("Project \"" + _currentProjectID + "\" saved!");
}