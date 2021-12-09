#include "top_viewport_controller.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

using std::ofstream;

using TVPC = TopViewportController;

TopViewportController::TopViewportController(FabiEngine3D& fe3d,
											 EngineGuiManager& gui,
											 SettingsEditor& settingsEditor,
											 SkyEditor& skyEditor,
											 TerrainEditor& terrainEditor,
											 WaterEditor& waterEditor,
											 ModelEditor& modelEditor,
											 BillboardEditor& billboardEditor,
											 MeshAnimationEditor& meshAnimationEditor,
											 AudioEditor& audioEditor,
											 WorldEditor& worldEditor,
											 ScriptEditor& scriptEditor)
	:
	BaseViewportController(fe3d, gui),
	_settingsEditor(settingsEditor),
	_skyEditor(skyEditor),
	_terrainEditor(terrainEditor),
	_waterEditor(waterEditor),
	_modelEditor(modelEditor),
	_billboardEditor(billboardEditor),
	_meshAnimationEditor(meshAnimationEditor),
	_audioEditor(audioEditor),
	_worldEditor(worldEditor),
	_scriptEditor(scriptEditor)
{

}

void TopViewportController::initialize()
{
	// Project window
	_gui.getViewport("top")->createWindow("projectWindow", fvec2(-0.25f, 0.0f), fvec2(0.9875f, 1.5f), TVPC::FRAME_COLOR);
	auto projectWindow = _gui.getViewport("top")->getWindow("projectWindow");

	// Execution window
	_gui.getViewport("top")->createWindow("executionWindow", fvec2(0.125f, 0.0f), fvec2(0.4875f, 1.5f), TVPC::FRAME_COLOR);
	auto executionWindow = _gui.getViewport("top")->getWindow("executionWindow");

	// Miscellaneous window
	_gui.getViewport("top")->createWindow("miscellaneousWindow", fvec2(0.375f, 0.0f), fvec2(0.4875f, 1.5f), TVPC::FRAME_COLOR);
	auto miscellaneousWindow = _gui.getViewport("top")->getWindow("miscellaneousWindow");

	// Project screen
	projectWindow->createScreen("main");
	projectWindow->setActiveScreen("main");
	projectWindow->getScreen("main")->createButton("newProject", fvec2(-0.767f, 0.0f), fvec2(0.15f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "NEW", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	projectWindow->getScreen("main")->createButton("loadProject", fvec2(-0.384f, 0.0f), fvec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "LOAD", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	projectWindow->getScreen("main")->createButton("saveProject", fvec2(0.0f, 0.0f), fvec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "SAVE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	projectWindow->getScreen("main")->createButton("deleteProject", fvec2(0.384f, 0.0f), fvec2(0.3f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "DELETE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	projectWindow->getScreen("main")->createButton("quitEngine", fvec2(0.767f, 0.0f), fvec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "QUIT", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);

	// Execution screen
	executionWindow->createScreen("main");
	executionWindow->setActiveScreen("main");
	executionWindow->getScreen("main")->createButton("start", fvec2(-0.73f, 0.0f), fvec2(0.2f, 1.75f), "start.png", fvec3(2.0f), true, true, true);
	executionWindow->getScreen("main")->createButton("pause", fvec2(-0.36f, 0.0f), fvec2(0.2f, 1.75f), "pause.png", fvec3(2.0f), true, true, true);
	executionWindow->getScreen("main")->createButton("restart", fvec2(0.0f, 0.0f), fvec2(0.2f, 1.75f), "restart.png", fvec3(2.0f), true, true, true);
	executionWindow->getScreen("main")->createButton("stop", fvec2(0.36f, 0.0f), fvec2(0.2f, 1.75f), "stop.png", fvec3(2.0f), true, true, true);
	executionWindow->getScreen("main")->createButton("debug", fvec2(0.73f, 0.0f), fvec2(0.2f, 1.75f), "debug.png", fvec3(2.0f), true, true, true);

	// Miscellaneous screen
	miscellaneousWindow->createScreen("main");
	miscellaneousWindow->setActiveScreen("main");
	miscellaneousWindow->getScreen("main")->createButton("uncache", fvec2(-0.5875f, 0.0f), fvec2(0.55f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "UNCACHE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	miscellaneousWindow->getScreen("main")->createButton("export", fvec2(0.075f, 0.0f), fvec2(0.5f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "EXPORT", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	miscellaneousWindow->getScreen("main")->createButton("docs", fvec2(0.6625f, 0.0f), fvec2(0.4f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "DOCS", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
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
	auto topScreen = _gui.getViewport("top")->getWindow("projectWindow")->getActiveScreen();
	auto leftScreen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if(topScreen->getButton("newProject")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("newProjectID", "Create Project", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingProject = true;
		}
		else if(topScreen->getButton("loadProject")->isHovered())
		{
			if(_prepareProjectChoosing("Load Project"))
			{
				_isLoadingProject = true;
			}
		}
		else if(topScreen->getButton("saveProject")->isHovered())
		{
			_saveCurrentProject();
		}
		else if(topScreen->getButton("deleteProject")->isHovered())
		{
			if(_prepareProjectChoosing("Delete Project"))
			{
				_isDeletingProject = true;
			}
		}
		else if(topScreen->getButton("quitEngine")->isHovered())
		{
			// Check if currently in editor (except for world editor)
			if((_currentProjectID != "") && (leftScreen->getID() != "main") && (leftScreen->getID() != "worldEditorMenuMain"))
			{
				_gui.getGlobalScreen()->createAnswerForm("quit", "Save Changes?", fvec2(0.0f, 0.25f));
			}
			else
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
	if(_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && (leftScreen->getID() == "main") && !_gui.getGlobalScreen()->isFocused())
	{
		// Check if script execution not started
		if(!_scriptEditor.getScriptExecutor().isStarted())
		{
			_fe3d.application_stop();
		}
	}

	// Update answer forms
	if(_gui.getGlobalScreen()->isAnswerFormConfirmed("quit"))
	{
		_saveCurrentProject();
		_fe3d.application_stop();
	}
	if(_gui.getGlobalScreen()->isAnswerFormDenied("quit"))
	{
		_fe3d.application_stop();
	}

	// Update buttons hoverability
	topScreen->getButton("newProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
	topScreen->getButton("loadProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
	topScreen->getButton("saveProject")->setHoverable(!_currentProjectID.empty() && !_scriptEditor.getScriptExecutor().isStarted());
	topScreen->getButton("deleteProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
}

void TopViewportController::_updateGameScreenManagement()
{
	// Temporary values
	auto screen = _gui.getViewport("top")->getWindow("executionWindow")->getActiveScreen();

	// Check if currently any project loaded
	if(_currentProjectID.empty())
	{
		screen->getButton("start")->setHoverable(false);
		screen->getButton("pause")->setHoverable(false);
		screen->getButton("restart")->setHoverable(false);
		screen->getButton("stop")->setHoverable(false);
		screen->getButton("debug")->setHoverable(false);
	}
	else
	{
		// Check if LMB pressed
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if(screen->getButton("start")->isHovered())
			{
				// Resume game or load game
				if(_scriptEditor.getScriptExecutor().isStarted())
				{
					_scriptEditor.getScriptExecutor().resume();
				}
				else
				{
					_scriptEditor.loadScriptFiles(true);
					_scriptEditor.getScriptExecutor().load();
				}
			}
			else if(screen->getButton("pause")->isHovered())
			{
				_scriptEditor.getScriptExecutor().pause();
			}
			else if(screen->getButton("restart")->isHovered())
			{
				_scriptEditor.getScriptExecutor().unload();
				_scriptEditor.loadScriptFiles(true);
				_scriptEditor.getScriptExecutor().load();
			}
			else if(screen->getButton("stop")->isHovered())
			{
				_scriptEditor.getScriptExecutor().unload();
			}
			else if(screen->getButton("debug")->isHovered())
			{
				_scriptEditor.getScriptExecutor().resume();
				_scriptEditor.getScriptExecutor().update(true);
				_scriptEditor.getScriptExecutor().pause();
			}
		}

		// Update buttons hoverability
		static bool wasInMainMenu = false;
		bool isInMainMenu = (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "main");
		screen->getButton("start")->setHoverable(isInMainMenu && !_scriptEditor.getScriptExecutor().isScriptEmpty() && !isScriptRunning());
		screen->getButton("pause")->setHoverable(isInMainMenu && isScriptRunning() && !_fe3d.server_isRunning());
		screen->getButton("restart")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());
		screen->getButton("stop")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());
		screen->getButton("debug")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());

		// Reload script files every second or if user came into menu
		bool cameIntoMenu = (!wasInMainMenu && isInMainMenu);
		if(cameIntoMenu || (isInMainMenu && !isScriptStarted() && _fe3d.misc_checkInterval(Config::UPDATES_PER_SECOND)))
		{
			_scriptEditor.loadScriptFiles(false);
		}
		wasInMainMenu = isInMainMenu;

		// Check if user wants to pause the running game
		if(_scriptEditor.getScriptExecutor().isRunning())
		{
			// Check if ESCAPE pressed
			if(_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if(_fe3d.server_isRunning()) // Server application cannot be paused, only on or off
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
	auto screen = _gui.getViewport("top")->getWindow("miscellaneousWindow")->getActiveScreen();

	// Button management
	if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("uncache")->isHovered())
	{
		// Get the chosen file name
		const auto rootDirectoryPath = Tools::getRootDirectoryPath();
		const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\");

		// Validate target directory
		if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
		{
			Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
			return;
		}

		// Validate chosen file
		const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "");
		if(filePath.empty())
		{
			return;
		}

		// Validate directory of file
		if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
		   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
		{
			Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
			return;
		}

		// Clear the cache of selected file
		const string newFilePath = filePath.substr(rootDirectoryPath.size());
		_fe3d.misc_clearMeshCache(newFilePath);
		_fe3d.misc_clearFontCache(newFilePath);
		_fe3d.misc_clearTextureCache2D(newFilePath);
		_fe3d.misc_clearBitmapCache(newFilePath);
		_fe3d.misc_clearAudioCache(newFilePath);
	}
	else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("export")->isHovered())
	{
		// Validate chosen directory
		const string chosenDirectoryPath = Tools::chooseExplorerDirectory("");
		if(chosenDirectoryPath.empty())
		{
			return;
		}

		// Compose important paths
		const string rootDirectoryPath = Tools::getRootDirectoryPath();
		const string exportDirectoryPath = string(chosenDirectoryPath + "\\" + _currentProjectID + "\\");

		// Check if project already exported
		if(Tools::isDirectoryExisting(exportDirectoryPath))
		{
			Logger::throwWarning("Project already exported to that location!");
		}
		else
		{
			// Create application directory
			Tools::createDirectory(exportDirectoryPath);

			// Copy directories
			Tools::copyDirectory(string(rootDirectoryPath + "binaries"), string(exportDirectoryPath + "binaries"));
			Tools::copyDirectory(string(rootDirectoryPath + "engine"), string(exportDirectoryPath + "engine"));
			Tools::copyDirectory(string(rootDirectoryPath + "projects\\" + _currentProjectID), exportDirectoryPath);

			// Rename executable
			auto oldPath = string(exportDirectoryPath + "binaries\\fe3d.exe");
			auto newPath = string(exportDirectoryPath + "binaries\\" + _currentProjectID + ".exe");
			Tools::renameFile(oldPath, newPath);

			// Create configuration file
			auto file = ofstream(exportDirectoryPath + "config.fe3d");
			file << "window_size = 0.75" << endl;
			file << "window_fullscreen      = false" << endl;
			file << "window_borderless      = false" << endl;
			file << "window_title           = MyGame";
			file.close();
		}
	}
	else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("docs")->isHovered())
	{
		ShellExecute(0, 0, "https://github.com/ConsolePeasant92/FabiEngine3D/blob/master/README.md", 0, 0, SW_SHOW);
	}

	// Update buttons hoverability
	screen->getButton("uncache")->setHoverable(!_currentProjectID.empty() && !_scriptEditor.getScriptExecutor().isStarted());
	screen->getButton("export")->setHoverable(!_currentProjectID.empty());
}

void TopViewportController::_saveCurrentProject()
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("TopViewportController::_saveCurrentProject");
	}

	// Save everything
	_settingsEditor.saveSettingsToFile();
	_skyEditor.saveSkyEntitiesToFile();
	_terrainEditor.saveTerrainEntitiesToFile();
	_waterEditor.saveWaterEntitiesToFile();
	_modelEditor.saveModelEntitiesToFile();
	_billboardEditor.saveBillboardEntitiesToFile();
	_meshAnimationEditor.saveAnimationsToFile();
	_audioEditor.saveAudioEntitiesToFile();
	_worldEditor.saveEditorWorldToFile();
	_scriptEditor.saveScriptFiles();

	// Logging
	Logger::throwInfo("Project \"" + _currentProjectID + "\" saved!");
}