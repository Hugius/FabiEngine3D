#include "top_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

void TopViewportController::initialize()
{
	_gui->getTopViewport()->createWindow("projectWindow", fvec2(-0.25f, 0.0f), fvec2(0.9875f, 1.5f), FRAME_COLOR);
	auto projectWindow = _gui->getTopViewport()->getWindow("projectWindow");

	_gui->getTopViewport()->createWindow("executionWindow", fvec2(0.125f, 0.0f), fvec2(0.4875f, 1.5f), FRAME_COLOR);
	auto executionWindow = _gui->getTopViewport()->getWindow("executionWindow");

	_gui->getTopViewport()->createWindow("miscellaneousWindow", fvec2(0.375f, 0.0f), fvec2(0.4875f, 1.5f), FRAME_COLOR);
	auto miscellaneousWindow = _gui->getTopViewport()->getWindow("miscellaneousWindow");

	projectWindow->createScreen("main");
	projectWindow->setActiveScreen("main");
	projectWindow->getScreen("main")->createButton("newProject", fvec2(-0.767f, 0.0f), fvec2(0.15f, 1.25f), BUTTON_COLOR, BUTTON_HOVER_COLOR, "NEW", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("loadProject", fvec2(-0.384f, 0.0f), fvec2(0.2f, 1.25f), BUTTON_COLOR, BUTTON_HOVER_COLOR, "LOAD", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("saveProject", fvec2(0.0f, 0.0f), fvec2(0.2f, 1.25f), BUTTON_COLOR, BUTTON_HOVER_COLOR, "SAVE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("deleteProject", fvec2(0.384f, 0.0f), fvec2(0.3f, 1.25f), BUTTON_COLOR, BUTTON_HOVER_COLOR, "DELETE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("quitEngine", fvec2(0.767f, 0.0f), fvec2(0.2f, 1.25f), BUTTON_COLOR, BUTTON_HOVER_COLOR, "QUIT", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	executionWindow->createScreen("main");
	executionWindow->setActiveScreen("main");
	executionWindow->getScreen("main")->createButton("start", fvec2(-0.73f, 0.0f), fvec2(0.2f, 1.75f), "start.tga", fvec3(2.0f), true);
	executionWindow->getScreen("main")->createButton("pause", fvec2(-0.36f, 0.0f), fvec2(0.2f, 1.75f), "pause.tga", fvec3(2.0f), true);
	executionWindow->getScreen("main")->createButton("restart", fvec2(0.0f, 0.0f), fvec2(0.2f, 1.75f), "restart.tga", fvec3(2.0f), true);
	executionWindow->getScreen("main")->createButton("stop", fvec2(0.36f, 0.0f), fvec2(0.2f, 1.75f), "stop.tga", fvec3(2.0f), true);
	executionWindow->getScreen("main")->createButton("debug", fvec2(0.73f, 0.0f), fvec2(0.2f, 1.75f), "debug.tga", fvec3(2.0f), true);

	miscellaneousWindow->createScreen("main");
	miscellaneousWindow->setActiveScreen("main");
	miscellaneousWindow->getScreen("main")->createButton("uncache", fvec2(-0.5875f, 0.0f), fvec2(0.55f, 1.25f), BUTTON_COLOR, BUTTON_HOVER_COLOR, "UNCACHE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	miscellaneousWindow->getScreen("main")->createButton("export", fvec2(0.075f, 0.0f), fvec2(0.5f, 1.25f), BUTTON_COLOR, BUTTON_HOVER_COLOR, "EXPORT", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	miscellaneousWindow->getScreen("main")->createButton("documentation", fvec2(0.6625f, 0.0f), fvec2(0.4f, 1.25f), BUTTON_COLOR, BUTTON_HOVER_COLOR, "DOCS", TEXT_COLOR, TEXT_HOVER_COLOR, true);
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
	if(_currentProjectId.empty())
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
	if(_currentProjectId.empty())
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
	auto screen = _gui->getLeftViewport()->getWindow("main")->getScreen("main");
	bool isHoverable = (_currentProjectId.empty()) ? false : !_scriptExecutor->isStarted();

	screen->getButton("skyEditor")->setHoverable(isHoverable);
	screen->getButton("terrainEditor")->setHoverable(isHoverable);
	screen->getButton("waterEditor")->setHoverable(isHoverable);
	screen->getButton("modelEditor")->setHoverable(isHoverable);
	screen->getButton("quad3dEditor")->setHoverable(isHoverable);
	screen->getButton("text3dEditor")->setHoverable(isHoverable);
	screen->getButton("quad2dEditor")->setHoverable(isHoverable);
	screen->getButton("text2dEditor")->setHoverable(isHoverable);
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
		Logger::throwWarning("Directory `projects\\` not existing");
		return false;
	}

	auto projectIds = Tools::getDirectoriesFromDirectory(projectDirectoryPath);

	_gui->getOverlay()->createChoiceForm("projectList", title, fvec2(0.0f, 0.1f), projectIds);

	return true;
}

void TopViewportController::_applyProjectChange()
{
	if(_currentProjectId.empty())
	{
		_fe3d->misc_setWindowTitle("FabiEngine3D");
	}
	else
	{
		_fe3d->misc_setWindowTitle("FabiEngine3D - " + _currentProjectId);
	}

	_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");

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

	if(_quad3dEditor->isLoaded())
	{
		_quad3dEditor->unload();
	}

	if(_text3dEditor->isLoaded())
	{
		_text3dEditor->unload();
	}

	if(_quad2dEditor->isLoaded())
	{
		_quad2dEditor->unload();
	}

	if(_text2dEditor->isLoaded())
	{
		_text2dEditor->unload();
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

	_skyEditor->setCurrentProjectId(_currentProjectId);
	_terrainEditor->setCurrentProjectId(_currentProjectId);
	_waterEditor->setCurrentProjectId(_currentProjectId);
	_modelEditor->setCurrentProjectId(_currentProjectId);
	_quad3dEditor->setCurrentProjectId(_currentProjectId);
	_text3dEditor->setCurrentProjectId(_currentProjectId);
	_quad2dEditor->setCurrentProjectId(_currentProjectId);
	_text2dEditor->setCurrentProjectId(_currentProjectId);
	_animation2dEditor->setCurrentProjectId(_currentProjectId);
	_animation3dEditor->setCurrentProjectId(_currentProjectId);
	_soundEditor->setCurrentProjectId(_currentProjectId);
	_worldEditor->setCurrentProjectId(_currentProjectId);
	_scriptEditor->setCurrentProjectId(_currentProjectId);
}

const bool TopViewportController::validateProject(const string& projectDirectoryPath) const
{
	if(!Tools::isDirectoryExisting(projectDirectoryPath) ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\audio\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\model\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\model\\diffuse_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\model\\emission_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\model\\normal_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\model\\reflection_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\model\\specular_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\quad2d\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\quad2d\\diffuse_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\quad3d\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\quad3d\\diffuse_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\quad3d\\emission_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\sky\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\sky\\cube_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\terrain\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\terrain\\blend_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\terrain\\diffuse_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\terrain\\height_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\text2d\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\text2d\\font_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\text3d\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\text3d\\font_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\water\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\water\\displacement_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\water\\dudv_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\entity\\water\\normal_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\misc\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\image\\misc\\flare_map\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "assets\\mesh\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "data\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "saves\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "scripts\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "worlds\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "worlds\\custom\\") ||
	   !Tools::isDirectoryExisting(projectDirectoryPath + "worlds\\editor\\"))
	{
		return true;
	}

	if(!Tools::isFileExisting(projectDirectoryPath + "data\\animation2d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\animation3d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\model.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\quad2d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\quad3d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\settings.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\sky.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\sound.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\terrain.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\text2d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\text3d.fe3d") ||
	   !Tools::isFileExisting(projectDirectoryPath + "data\\water.fe3d"))
	{
		return true;
	}

	return false;
}

void TopViewportController::_saveCurrentProject()
{
	if(_currentProjectId.empty())
	{
		abort();
	}

	_skyEditor->saveToFile();
	_terrainEditor->saveToFile();
	_waterEditor->saveToFile();
	_modelEditor->saveToFile();
	_quad3dEditor->saveToFile();
	_text3dEditor->saveToFile();
	_quad2dEditor->saveToFile();
	_text2dEditor->saveToFile();
	_animation2dEditor->saveToFile();
	_animation3dEditor->saveToFile();
	_soundEditor->saveToFile();
	_worldEditor->saveEditorWorldToFile();
	_scriptEditor->saveScriptFiles();

	Logger::throwInfo("Project \"" + _currentProjectId + "\" saved");
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

void TopViewportController::inject(shared_ptr<Quad3dEditor> quad3dEditor)
{
	_quad3dEditor = quad3dEditor;
}

void TopViewportController::inject(shared_ptr<Text3dEditor> text3dEditor)
{
	_text3dEditor = text3dEditor;
}

void TopViewportController::inject(shared_ptr<Quad2dEditor> quad2dEditor)
{
	_quad2dEditor = quad2dEditor;
}

void TopViewportController::inject(shared_ptr<Text2dEditor> text2dEditor)
{
	_text2dEditor = text2dEditor;
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

void TopViewportController::inject(shared_ptr<Script> script)
{
	_script = script;
}

void TopViewportController::inject(shared_ptr<ScriptExecutor> scriptExecutor)
{
	_scriptExecutor = scriptExecutor;
}