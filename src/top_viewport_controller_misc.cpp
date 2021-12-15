#include "top_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

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
											 Animation3dEditor& animation3dEditor,
											 Animation2dEditor& animation2dEditor,
											 SoundEditor& soundEditor,
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
	_animation3dEditor(animation3dEditor),
	_animation2dEditor(animation2dEditor),
	_soundEditor(soundEditor),
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

const bool TopViewportController::isScriptStarted() const
{
	if(_currentProjectID.empty())
	{
		return false;
	}
	else
	{
		return _scriptEditor.getScriptExecutor().isStarted();
	}
}

const bool TopViewportController::isScriptRunning() const
{
	if(_currentProjectID.empty())
	{
		return false;
	}
	else
	{
		return _scriptEditor.getScriptExecutor().isRunning();
	}
}

void TopViewportController::_updateMiscellaneous()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("main");
	bool isHoverable = (_currentProjectID.empty()) ? false : !_scriptEditor.getScriptExecutor().isStarted();

	// Update buttons hoverability
	screen->getButton("settingsEditor")->setHoverable(isHoverable);
	screen->getButton("skyEditor")->setHoverable(isHoverable);
	screen->getButton("terrainEditor")->setHoverable(isHoverable);
	screen->getButton("waterEditor")->setHoverable(isHoverable);
	screen->getButton("modelEditor")->setHoverable(isHoverable);
	screen->getButton("billboardEditor")->setHoverable(isHoverable);
	screen->getButton("worldEditor")->setHoverable(isHoverable);
	screen->getButton("animation3dEditor")->setHoverable(isHoverable);
	screen->getButton("animation2dEditor")->setHoverable(isHoverable);
	screen->getButton("soundEditor")->setHoverable(isHoverable);
	screen->getButton("scriptEditor")->setHoverable(isHoverable);
}

const bool TopViewportController::_prepareProjectChoosing(const string& title) const
{
	// Temporary values
	const string projectDirectoryPath = (Tools::getRootDirectoryPath() + "projects\\");

	// Check if game directory exists
	if(!Tools::isDirectoryExisting(projectDirectoryPath))
	{
		Logger::throwWarning("Directory `projects\\` is missing!");
		return false;
	}

	// Get all project names
	auto projectIDs = Tools::getDirectoriesFromDirectory(projectDirectoryPath);

	// Add buttons
	_gui.getGlobalScreen()->createChoiceForm("projectList", title, fvec2(0.0f, 0.1f), projectIDs);

	return true;
}

void TopViewportController::_applyProjectChange()
{
	// Change window title
	if(_currentProjectID.empty())
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D");
	}
	else
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D - " + _currentProjectID);
	}

	// Go back to main menu
	_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");

	// Unload settings editor
	if(_settingsEditor.isLoaded())
	{
		_settingsEditor.unload();
	}

	// Unload sky editor
	if(_skyEditor.isLoaded())
	{
		_skyEditor.unload();
	}

	// Unload terrain editor
	if(_terrainEditor.isLoaded())
	{
		_terrainEditor.unload();
	}

	// Unload water editor
	if(_waterEditor.isLoaded())
	{
		_waterEditor.unload();
	}

	// Unload model editor
	if(_modelEditor.isLoaded())
	{
		_modelEditor.unload();
	}

	// Unload billboard editor
	if(_billboardEditor.isLoaded())
	{
		_billboardEditor.unload();
	}

	// Unload animation3D editor
	if(_animation3dEditor.isLoaded())
	{
		_animation3dEditor.unload();
	}

	// Unload animation2D editor
	if(_animation2dEditor.isLoaded())
	{
		_animation2dEditor.unload();
	}

	// Unload audio editor
	if(_soundEditor.isLoaded())
	{
		_soundEditor.unload();
	}

	// Unload world editor
	if(_worldEditor.isLoaded())
	{
		_worldEditor.unload();
	}

	// Unload script editor
	if(_scriptEditor.isLoaded())
	{
		_scriptEditor.unload();
	}

	// Pass loaded project ID
	_settingsEditor.setCurrentProjectID(_currentProjectID);
	_skyEditor.setCurrentProjectID(_currentProjectID);
	_terrainEditor.setCurrentProjectID(_currentProjectID);
	_waterEditor.setCurrentProjectID(_currentProjectID);
	_modelEditor.setCurrentProjectID(_currentProjectID);
	_billboardEditor.setCurrentProjectID(_currentProjectID);
	_animation3dEditor.setCurrentProjectID(_currentProjectID);
	_animation2dEditor.setCurrentProjectID(_currentProjectID);
	_soundEditor.setCurrentProjectID(_currentProjectID);
	_worldEditor.setCurrentProjectID(_currentProjectID);
	_scriptEditor.setCurrentProjectID(_currentProjectID);
}

const bool TopViewportController::isProjectCorrupted(const string& projectDirectoryPath) const
{
	// Check if all default directories are still existing
	if(!Tools::isDirectoryExisting(projectDirectoryPath) ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "data") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "saves") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "worlds") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "worlds\\custom") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "worlds\\editor") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "scripts"))
	{
		return true;
	}

	// Check if all default files are still existing
	if(!Tools::isFileExisting(projectDirectoryPath + "data\\animation3d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\animation2d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\sound.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\billboard.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\model.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\settings.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\sky.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\terrain.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\water.fe3d"))
	{
		return true;
	}

	return false;
}

void TopViewportController::_saveCurrentProject()
{
	// Validate project ID
	if(_currentProjectID.empty())
	{
		Logger::throwError("TopViewportController::_saveCurrentProject");
	}

	// Save everything
	_settingsEditor.saveSettingsToFile();
	_skyEditor.saveToFile();
	_terrainEditor.saveToFile();
	_waterEditor.saveToFile();
	_modelEditor.saveToFile();
	_billboardEditor.saveToFile();
	_animation3dEditor.saveToFile();
	_animation2dEditor.saveToFile();
	_soundEditor.saveToFile();
	_worldEditor.saveEditorWorldToFile();
	_scriptEditor.saveScriptFiles();

	// Logging
	Logger::throwInfo("Project \"" + _currentProjectID + "\" saved!");
}