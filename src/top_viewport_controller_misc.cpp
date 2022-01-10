#include "top_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

using TVPC = TopViewportController;

void TopViewportController::initialize()
{
	_gui->getViewport("top")->createWindow("projectWindow", fvec2(-0.25f, 0.0f), fvec2(0.9875f, 1.5f), TVPC::FRAME_COLOR);
	auto projectWindow = _gui->getViewport("top")->getWindow("projectWindow");

	_gui->getViewport("top")->createWindow("executionWindow", fvec2(0.125f, 0.0f), fvec2(0.4875f, 1.5f), TVPC::FRAME_COLOR);
	auto executionWindow = _gui->getViewport("top")->getWindow("executionWindow");

	_gui->getViewport("top")->createWindow("miscellaneousWindow", fvec2(0.375f, 0.0f), fvec2(0.4875f, 1.5f), TVPC::FRAME_COLOR);
	auto miscellaneousWindow = _gui->getViewport("top")->getWindow("miscellaneousWindow");

	projectWindow->createScreen("main");
	projectWindow->setActiveScreen("main");
	projectWindow->getScreen("main")->createButton("newProject", fvec2(-0.767f, 0.0f), fvec2(0.15f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "NEW", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("loadProject", fvec2(-0.384f, 0.0f), fvec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "LOAD", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("saveProject", fvec2(0.0f, 0.0f), fvec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "SAVE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("deleteProject", fvec2(0.384f, 0.0f), fvec2(0.3f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "DELETE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("quitEngine", fvec2(0.767f, 0.0f), fvec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "QUIT", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true);

	executionWindow->createScreen("main");
	executionWindow->setActiveScreen("main");
	executionWindow->getScreen("main")->createButton("start", fvec2(-0.73f, 0.0f), fvec2(0.2f, 1.75f), "start.tga", fvec3(2.0f), true);
	executionWindow->getScreen("main")->createButton("pause", fvec2(-0.36f, 0.0f), fvec2(0.2f, 1.75f), "pause.tga", fvec3(2.0f), true);
	executionWindow->getScreen("main")->createButton("restart", fvec2(0.0f, 0.0f), fvec2(0.2f, 1.75f), "restart.tga", fvec3(2.0f), true);
	executionWindow->getScreen("main")->createButton("stop", fvec2(0.36f, 0.0f), fvec2(0.2f, 1.75f), "stop.tga", fvec3(2.0f), true);
	executionWindow->getScreen("main")->createButton("debug", fvec2(0.73f, 0.0f), fvec2(0.2f, 1.75f), "debug.tga", fvec3(2.0f), true);

	miscellaneousWindow->createScreen("main");
	miscellaneousWindow->setActiveScreen("main");
	miscellaneousWindow->getScreen("main")->createButton("uncache", fvec2(-0.5875f, 0.0f), fvec2(0.55f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "UNCACHE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true);
	miscellaneousWindow->getScreen("main")->createButton("export", fvec2(0.075f, 0.0f), fvec2(0.5f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "EXPORT", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true);
	miscellaneousWindow->getScreen("main")->createButton("docs", fvec2(0.6625f, 0.0f), fvec2(0.4f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "DOCS", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true);
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
		return _scriptExecutor->isStarted();
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
		return _scriptExecutor->isRunning();
	}
}

void TopViewportController::_updateMiscellaneous()
{
	auto screen = _gui->getViewport("left")->getWindow("main")->getScreen("main");
	bool isHoverable = (_currentProjectID.empty()) ? false : !_scriptExecutor->isStarted();

	screen->getButton("skyEditor")->setHoverable(isHoverable);
	screen->getButton("terrainEditor")->setHoverable(isHoverable);
	screen->getButton("waterEditor")->setHoverable(isHoverable);
	screen->getButton("modelEditor")->setHoverable(isHoverable);
	screen->getButton("billboardEditor")->setHoverable(isHoverable);
	screen->getButton("quadEditor")->setHoverable(isHoverable);
	screen->getButton("animation2dEditor")->setHoverable(isHoverable);
	screen->getButton("animation3dEditor")->setHoverable(isHoverable);
	screen->getButton("soundEditor")->setHoverable(isHoverable);
	screen->getButton("worldEditor")->setHoverable(isHoverable);
	screen->getButton("scriptEditor")->setHoverable(isHoverable);
}

const bool TopViewportController::_prepareProjectChoosing(const string& title) const
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const string projectDirectoryPath = (rootPath + "projects\\");

	if(!Tools::isDirectoryExisting(projectDirectoryPath))
	{
		Logger::throwWarning("Directory `projects\\` is missing!");
		return false;
	}

	auto projectIDs = Tools::getDirectoriesFromDirectory(projectDirectoryPath);

	_gui->getOverlay()->createChoiceForm("projectList", title, fvec2(0.0f, 0.1f), projectIDs);

	return true;
}

void TopViewportController::_applyProjectChange()
{
	if(_currentProjectID.empty())
	{
		_fe3d->misc_setWindowTitle("FabiEngine3D");
	}
	else
	{
		_fe3d->misc_setWindowTitle("FabiEngine3D - " + _currentProjectID);
	}

	_gui->getViewport("left")->getWindow("main")->setActiveScreen("main");

	if(_skyEditor->isLoaded())
	{
		_skyEditor->unload();
	}

	if(_terrainEditor->isLoaded())
	{
		_terrainEditor->unload();
	}

	if(_waterEditor->isLoaded())
	{
		_waterEditor->unload();
	}

	if(_modelEditor->isLoaded())
	{
		_modelEditor->unload();
	}

	if(_billboardEditor->isLoaded())
	{
		_billboardEditor->unload();
	}

	if(_quadEditor->isLoaded())
	{
		_quadEditor->unload();
	}

	if(_animation2dEditor->isLoaded())
	{
		_animation2dEditor->unload();
	}

	if(_animation3dEditor->isLoaded())
	{
		_animation3dEditor->unload();
	}

	if(_soundEditor->isLoaded())
	{
		_soundEditor->unload();
	}

	if(_worldEditor->isLoaded())
	{
		_worldEditor->unload();
	}

	if(_scriptEditor->isLoaded())
	{
		_scriptEditor->unload();
	}

	_skyEditor->setCurrentProjectID(_currentProjectID);
	_terrainEditor->setCurrentProjectID(_currentProjectID);
	_waterEditor->setCurrentProjectID(_currentProjectID);
	_modelEditor->setCurrentProjectID(_currentProjectID);
	_billboardEditor->setCurrentProjectID(_currentProjectID);
	_quadEditor->setCurrentProjectID(_currentProjectID);
	_animation2dEditor->setCurrentProjectID(_currentProjectID);
	_animation3dEditor->setCurrentProjectID(_currentProjectID);
	_soundEditor->setCurrentProjectID(_currentProjectID);
	_worldEditor->setCurrentProjectID(_currentProjectID);
	_scriptEditor->setCurrentProjectID(_currentProjectID);
}

const bool TopViewportController::isProjectCorrupted(const string& projectDirectoryPath) const
{
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

	if(!Tools::isFileExisting(projectDirectoryPath + "data\\animation3d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\animation2d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\billboard.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\model.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\quad.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\settings.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\sky.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\sound.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\terrain.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\water.fe3d"))
	{
		return true;
	}

	return false;
}

void TopViewportController::_saveCurrentProject()
{
	if(_currentProjectID.empty())
	{
		Logger::throwError("TopViewportController::_saveCurrentProject");
	}

	_skyEditor->saveToFile();
	_terrainEditor->saveToFile();
	_waterEditor->saveToFile();
	_modelEditor->saveToFile();
	_billboardEditor->saveToFile();
	_quadEditor->saveToFile();
	_animation2dEditor->saveToFile();
	_animation3dEditor->saveToFile();
	_soundEditor->saveToFile();
	_worldEditor->saveEditorWorldToFile();
	_scriptEditor->saveScriptFiles();

	Logger::throwInfo("Project \"" + _currentProjectID + "\" saved!");
}

void TopViewportController::inject(shared_ptr<SkyEditor> skyEditor)
{
	_skyEditor = skyEditor;
}

void TopViewportController::inject(shared_ptr<TerrainEditor> terrainEditor)
{
	_terrainEditor = terrainEditor;
}

void TopViewportController::inject(shared_ptr<WaterEditor> waterEditor)
{
	_waterEditor = waterEditor;
}

void TopViewportController::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

void TopViewportController::inject(shared_ptr<BillboardEditor> billboardEditor)
{
	_billboardEditor = billboardEditor;
}

void TopViewportController::inject(shared_ptr<QuadEditor> quadEditor)
{
	_quadEditor = quadEditor;
}

void TopViewportController::inject(shared_ptr<Animation2dEditor> animation2dEditor)
{
	_animation2dEditor = animation2dEditor;
}

void TopViewportController::inject(shared_ptr<Animation3dEditor> animation3dEditor)
{
	_animation3dEditor = animation3dEditor;
}

void TopViewportController::inject(shared_ptr<SoundEditor> soundEditor)
{
	_soundEditor = soundEditor;
}

void TopViewportController::inject(shared_ptr<WorldEditor> worldEditor)
{
	_worldEditor = worldEditor;
}

void TopViewportController::inject(shared_ptr<ScriptEditor> scriptEditor)
{
	_scriptEditor = scriptEditor;
}

void TopViewportController::inject(shared_ptr<ScriptExecutor> scriptExecutor)
{
	_scriptExecutor = scriptExecutor;
}