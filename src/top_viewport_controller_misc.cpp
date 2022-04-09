#define LEFT_TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * LCW), CH)
#define RIGHT_TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * RCW), CH)

#include "top_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

void TopViewportController::initialize()
{
	_gui->getTopViewport()->createWindow("projectWindow", fvec2(-0.25f, 0.0f), fvec2(0.9875f, 1.5f), FRAME_COLOR);
	_gui->getTopViewport()->createWindow("executionWindow", fvec2(0.125f, 0.0f), fvec2(0.4875f, 1.5f), FRAME_COLOR);
	_gui->getTopViewport()->createWindow("miscellaneousWindow", fvec2(0.375f, 0.0f), fvec2(0.4875f, 1.5f), FRAME_COLOR);

	auto projectWindow = _gui->getTopViewport()->getWindow("projectWindow");
	auto executionWindow = _gui->getTopViewport()->getWindow("executionWindow");
	auto miscellaneousWindow = _gui->getTopViewport()->getWindow("miscellaneousWindow");

	auto positions = Mathematics::calculateDistributedPositions(4, LEFT_TEXT_SIZE("CREATE").x, true);
	projectWindow->createScreen("main");
	projectWindow->getScreen("main")->createButton("createProject", fvec2(positions[0], 0.0f), LEFT_TEXT_SIZE("CREATE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "CREATE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("loadProject", fvec2(positions[1], 0.0f), LEFT_TEXT_SIZE("LOAD"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "LOAD", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("deleteProject", fvec2(positions[2], 0.0f), LEFT_TEXT_SIZE("DELETE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "DELETE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("quitEngine", fvec2(positions[3], 0.0f), LEFT_TEXT_SIZE("QUIT"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "QUIT", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->setActiveScreen("main");

	positions = Mathematics::calculateDistributedPositions(5, 0.2f, true);
	executionWindow->createScreen("main");
	executionWindow->getScreen("main")->createButton("start", fvec2(positions[0], 0.0f), fvec2(0.2f, 1.75f), "start.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	executionWindow->getScreen("main")->createButton("pause", fvec2(positions[1], 0.0f), fvec2(0.2f, 1.75f), "pause.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	executionWindow->getScreen("main")->createButton("restart", fvec2(positions[2], 0.0f), fvec2(0.2f, 1.75f), "restart.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	executionWindow->getScreen("main")->createButton("stop", fvec2(positions[3], 0.0f), fvec2(0.2f, 1.75f), "stop.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	executionWindow->getScreen("main")->createButton("debug", fvec2(positions[4], 0.0f), fvec2(0.2f, 1.75f), "debug.tga", fvec3(1.0f), fvec3(0.25f), "", fvec3(0.0f), fvec3(0.0f), true);
	executionWindow->setActiveScreen("main");

	positions = Mathematics::calculateDistributedPositions(3, RIGHT_TEXT_SIZE("UNCACHE").x, true);
	miscellaneousWindow->createScreen("main");
	miscellaneousWindow->getScreen("main")->createButton("uncache", fvec2(positions[0], 0.0f), RIGHT_TEXT_SIZE("UNCACHE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "UNCACHE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	miscellaneousWindow->getScreen("main")->createButton("export", fvec2(positions[1], 0.0f), RIGHT_TEXT_SIZE("EXPORT"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "EXPORT", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	miscellaneousWindow->getScreen("main")->createButton("documentation", fvec2(positions[2], 0.0f), RIGHT_TEXT_SIZE("DOCS"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "DOCS", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	miscellaneousWindow->setActiveScreen("main");
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
	bool isHoverable = (_currentProjectId.empty() ? false : !_scriptExecutor->isStarted());

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

void TopViewportController::_setProject(const string & value)
{
	_currentProjectId = value;

	if(_currentProjectId.empty())
	{
		_fe3d->misc_setWindowTitle("FabiEngine3D");
	}
	else
	{
		_fe3d->misc_setWindowTitle("FabiEngine3D - " + _currentProjectId);
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
	_customWorldBuilder->setCurrentProjectId(_currentProjectId);
	_scriptEditor->setCurrentProjectId(_currentProjectId);
	_scriptExecutor->setCurrentProjectId(_currentProjectId);

	_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
}

const bool TopViewportController::isProjectCorrupted(const string & projectDirectoryPath) const
{
	vector<string> directoryPaths;
	vector<string> filePaths;

	directoryPaths.push_back(projectDirectoryPath);
	directoryPaths.push_back(projectDirectoryPath + "assets\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\audio\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\model\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\model\\diffuse_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\model\\emission_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\model\\normal_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\model\\reflection_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\model\\specular_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\quad2d\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\quad2d\\diffuse_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\quad3d\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\quad3d\\diffuse_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\quad3d\\emission_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\sky\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\sky\\cube_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\terrain\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\terrain\\blend_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\terrain\\diffuse_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\terrain\\height_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\terrain\\normal_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\text2d\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\text2d\\font_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\text3d\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\text3d\\font_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\water\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\water\\displacement_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\water\\dudv_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\entity\\water\\normal_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\misc\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\misc\\flare_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\mesh\\");
	directoryPaths.push_back(projectDirectoryPath + "data\\");
	directoryPaths.push_back(projectDirectoryPath + "saves\\");
	directoryPaths.push_back(projectDirectoryPath + "scripts\\");
	directoryPaths.push_back(projectDirectoryPath + "worlds\\");
	directoryPaths.push_back(projectDirectoryPath + "worlds\\custom\\");
	directoryPaths.push_back(projectDirectoryPath + "worlds\\editor\\");

	filePaths.push_back(projectDirectoryPath + "data\\animation2d.fe3d");
	filePaths.push_back(projectDirectoryPath + "data\\animation3d.fe3d");
	filePaths.push_back(projectDirectoryPath + "data\\model.fe3d");
	filePaths.push_back(projectDirectoryPath + "data\\quad2d.fe3d");
	filePaths.push_back(projectDirectoryPath + "data\\quad3d.fe3d");
	filePaths.push_back(projectDirectoryPath + "data\\sky.fe3d");
	filePaths.push_back(projectDirectoryPath + "data\\sound.fe3d");
	filePaths.push_back(projectDirectoryPath + "data\\terrain.fe3d");
	filePaths.push_back(projectDirectoryPath + "data\\text2d.fe3d");
	filePaths.push_back(projectDirectoryPath + "data\\text3d.fe3d");
	filePaths.push_back(projectDirectoryPath + "data\\water.fe3d");

	for(const auto & path : directoryPaths)
	{
		if(!Tools::isDirectoryExisting(path))
		{
			Logger::throwWarning("Project corrupted: directory `" + path + "` does not exist");

			return true;
		}
	}

	for(const auto & path : filePaths)
	{
		if(!Tools::isFileExisting(path))
		{
			Logger::throwWarning("Project corrupted: file `" + path + "` does not exist");

			return true;
		}
	}

	return false;
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

void TopViewportController::inject(shared_ptr<CustomWorldBuilder> customWorldBuilder)
{
	_customWorldBuilder = customWorldBuilder;
}

void TopViewportController::inject(shared_ptr<Script> script)
{
	_script = script;
}

void TopViewportController::inject(shared_ptr<ScriptExecutor> scriptExecutor)
{
	_scriptExecutor = scriptExecutor;
}