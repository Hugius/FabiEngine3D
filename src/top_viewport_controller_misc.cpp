#define LEFT_TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * LCW), LCH)
#define RIGHT_TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * RCW), RCH)

#include "top_viewport_controller.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>

using std::ofstream;

void TopViewportController::initialize()
{
	_gui->getTopViewport()->createWindow("projectWindow", fvec2(-0.25f, 0.0f), fvec2(0.9875f, 1.5f), FRAME_COLOR);
	_gui->getTopViewport()->createWindow("executionWindow", fvec2(0.125f, 0.0f), fvec2(0.4875f, 1.5f), FRAME_COLOR);
	_gui->getTopViewport()->createWindow("extraWindow", fvec2(0.375f, 0.0f), fvec2(0.4875f, 1.5f), FRAME_COLOR);

	const auto projectWindow = _gui->getTopViewport()->getWindow("projectWindow");
	const auto executionWindow = _gui->getTopViewport()->getWindow("executionWindow");
	const auto extraWindow = _gui->getTopViewport()->getWindow("extraWindow");
	const auto projectPositions = Mathematics::calculateDistributedPositions(4, LEFT_TEXT_SIZE("CREATE").x, true);
	const auto executionPositions = Mathematics::calculateDistributedPositions(4, ROUND_BUTTON_SIZE.x, true);
	const auto extraPositions = Mathematics::calculateDistributedPositions(3, RIGHT_TEXT_SIZE("UNCACHE").x, true);

	projectWindow->createScreen("main");
	projectWindow->getScreen("main")->createButton("createProject", fvec2(projectPositions[0], 0.0f), LEFT_TEXT_SIZE("CREATE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "CREATE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("loadProject", fvec2(projectPositions[1], 0.0f), LEFT_TEXT_SIZE("LOAD"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "LOAD", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("deleteProject", fvec2(projectPositions[2], 0.0f), LEFT_TEXT_SIZE("DELETE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "DELETE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->getScreen("main")->createButton("closeWindow", fvec2(projectPositions[3], 0.0f), LEFT_TEXT_SIZE("CLOSE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "CLOSE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	projectWindow->setActiveScreen("main");

	executionWindow->createScreen("main");
	executionWindow->getScreen("main")->createButton("start", fvec2(executionPositions[0], 0.0f), ROUND_BUTTON_SIZE, "start.tga", ROUND_BUTTON_COLOR, ROUND_BUTTON_HOVER_COLOR, "", fvec3(0.0f), fvec3(0.0f), true);
	executionWindow->getScreen("main")->createButton("debug", fvec2(executionPositions[1], 0.0f), ROUND_BUTTON_SIZE, "debug.tga", ROUND_BUTTON_COLOR, ROUND_BUTTON_HOVER_COLOR, "", fvec3(0.0f), fvec3(0.0f), true);
	executionWindow->getScreen("main")->createButton("restart", fvec2(executionPositions[2], 0.0f), ROUND_BUTTON_SIZE, "restart.tga", ROUND_BUTTON_COLOR, ROUND_BUTTON_HOVER_COLOR, "", fvec3(0.0f), fvec3(0.0f), true);
	executionWindow->getScreen("main")->createButton("stop", fvec2(executionPositions[3], 0.0f), ROUND_BUTTON_SIZE, "stop.tga", ROUND_BUTTON_COLOR, ROUND_BUTTON_HOVER_COLOR, "", fvec3(0.0f), fvec3(0.0f), true);
	executionWindow->setActiveScreen("main");

	extraWindow->createScreen("main");
	extraWindow->getScreen("main")->createButton("uncache", fvec2(extraPositions[0], 0.0f), RIGHT_TEXT_SIZE("UNCACHE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "UNCACHE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	extraWindow->getScreen("main")->createButton("export", fvec2(extraPositions[1], 0.0f), RIGHT_TEXT_SIZE("EXPORT"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "EXPORT", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	extraWindow->getScreen("main")->createButton("documentation", fvec2(extraPositions[2], 0.0f), RIGHT_TEXT_SIZE("DOCS"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "DOCS", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	extraWindow->setActiveScreen("main");
}

void TopViewportController::update()
{
	_updateApplicationScreenManagement();
	_updateProjectScreenManagement();
	_updateExtraScreenManagement();
	_updateMiscellaneous();
}

void TopViewportController::_updateMiscellaneous()
{
	const auto leftScreen = _gui->getLeftViewport()->getWindow("main")->getScreen("main");
	const auto rightScreen = _gui->getRightViewport()->getWindow("main")->getScreen("main");
	const auto isHoverable = (_currentProjectId.empty() ? false : !_scriptExecutor->isStarted());

	leftScreen->getButton("skyEditor")->setHoverable(isHoverable, true);
	leftScreen->getButton("terrainEditor")->setHoverable(isHoverable, true);
	leftScreen->getButton("waterEditor")->setHoverable(isHoverable, true);
	leftScreen->getButton("modelEditor")->setHoverable(isHoverable, true);
	leftScreen->getButton("quad3dEditor")->setHoverable(isHoverable, true);
	leftScreen->getButton("quad2dEditor")->setHoverable(isHoverable, true);
	leftScreen->getButton("text3dEditor")->setHoverable(isHoverable, true);
	leftScreen->getButton("text2dEditor")->setHoverable(isHoverable, true);

	rightScreen->getButton("animation3dEditor")->setHoverable(isHoverable, true);
	rightScreen->getButton("animation2dEditor")->setHoverable(isHoverable, true);
	rightScreen->getButton("aabbEditor")->setHoverable(isHoverable, true);
	rightScreen->getButton("pointlightEditor")->setHoverable(isHoverable, true);
	rightScreen->getButton("spotlightEditor")->setHoverable(isHoverable, true);
	rightScreen->getButton("captorEditor")->setHoverable(isHoverable, true);
	rightScreen->getButton("sound3dEditor")->setHoverable(isHoverable, true);
	rightScreen->getButton("sound2dEditor")->setHoverable(isHoverable, true);
	rightScreen->getButton("worldEditor")->setHoverable(isHoverable, true);
	rightScreen->getButton("scriptEditor")->setHoverable(isHoverable, true);
}

void TopViewportController::_setProject(const string & projectId)
{
	_currentProjectId = projectId;

	_skyEditor->setCurrentProjectId(_currentProjectId);
	_terrainEditor->setCurrentProjectId(_currentProjectId);
	_waterEditor->setCurrentProjectId(_currentProjectId);
	_modelEditor->setCurrentProjectId(_currentProjectId);
	_quad3dEditor->setCurrentProjectId(_currentProjectId);
	_quad2dEditor->setCurrentProjectId(_currentProjectId);
	_text3dEditor->setCurrentProjectId(_currentProjectId);
	_text2dEditor->setCurrentProjectId(_currentProjectId);
	_animation3dEditor->setCurrentProjectId(_currentProjectId);
	_animation2dEditor->setCurrentProjectId(_currentProjectId);
	_aabbEditor->setCurrentProjectId(_currentProjectId);
	_pointlightEditor->setCurrentProjectId(_currentProjectId);
	_spotlightEditor->setCurrentProjectId(_currentProjectId);
	_captorEditor->setCurrentProjectId(_currentProjectId);
	_sound3dEditor->setCurrentProjectId(_currentProjectId);
	_sound2dEditor->setCurrentProjectId(_currentProjectId);
	_worldEditor->setCurrentProjectId(_currentProjectId);
	_customWorldBuilder->setCurrentProjectId(_currentProjectId);
	_scriptEditor->setCurrentProjectId(_currentProjectId);
	_scriptExecutor->setCurrentProjectId(_currentProjectId);
}

const bool TopViewportController::isProjectCorrupted(const string & projectDirectoryPath) const
{
	vector<string> directoryPaths = {};
	vector<string> filePaths = {};

	directoryPaths.push_back(projectDirectoryPath);
	directoryPaths.push_back(projectDirectoryPath + "assets\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\audio\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\miscellaneous\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\miscellaneous\\flare_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\model\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\model\\diffuse_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\model\\emission_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\model\\normal_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\model\\reflection_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\model\\refraction_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\model\\specular_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\quad2d\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\quad2d\\diffuse_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\quad3d\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\quad3d\\diffuse_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\quad3d\\emission_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\sky\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\sky\\cube_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\terrain\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\terrain\\blend_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\terrain\\diffuse_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\terrain\\height_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\terrain\\normal_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\text2d\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\text2d\\font_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\text3d\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\text3d\\font_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\water\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\water\\dudv_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\water\\height_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\image\\water\\normal_map\\");
	directoryPaths.push_back(projectDirectoryPath + "assets\\mesh\\");
	directoryPaths.push_back(projectDirectoryPath + "domain\\");
	directoryPaths.push_back(projectDirectoryPath + "saves\\");
	directoryPaths.push_back(projectDirectoryPath + "scripts\\");
	directoryPaths.push_back(projectDirectoryPath + "worlds\\");
	directoryPaths.push_back(projectDirectoryPath + "worlds\\custom\\");
	directoryPaths.push_back(projectDirectoryPath + "worlds\\editor\\");

	filePaths.push_back(projectDirectoryPath + "domain\\aabb.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\animation2d.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\animation3d.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\captor.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\model.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\pointlight.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\quad2d.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\quad3d.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\sky.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\sound2d.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\sound3d.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\spotlight.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\terrain.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\text2d.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\text3d.fe3d");
	filePaths.push_back(projectDirectoryPath + "domain\\water.fe3d");

	for(const auto & path : directoryPaths)
	{
		if(!Tools::isDirectoryExisting(path))
		{
			Logger::throwWarning("Project corrupted: directory `" + path.substr(projectDirectoryPath.size()) + "` does not exist");

			return true;
		}
	}

	for(const auto & path : filePaths)
	{
		if(!Tools::isFileExisting(path))
		{
			Logger::throwWarning("Project corrupted: file `" + path.substr(projectDirectoryPath.size()) + "` does not exist");

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

void TopViewportController::inject(shared_ptr<Sound3dEditor> sound3dEditor)
{
	_sound3dEditor = sound3dEditor;
}

void TopViewportController::inject(shared_ptr<Quad2dEditor> quad2dEditor)
{
	_quad2dEditor = quad2dEditor;
}

void TopViewportController::inject(shared_ptr<Text2dEditor> text2dEditor)
{
	_text2dEditor = text2dEditor;
}

void TopViewportController::inject(shared_ptr<PointlightEditor> pointlightEditor)
{
	_pointlightEditor = pointlightEditor;
}

void TopViewportController::inject(shared_ptr<SpotlightEditor> spotlightEditor)
{
	_spotlightEditor = spotlightEditor;
}

void TopViewportController::inject(shared_ptr<Animation2dEditor> animation2dEditor)
{
	_animation2dEditor = animation2dEditor;
}

void TopViewportController::inject(shared_ptr<Animation3dEditor> animation3dEditor)
{
	_animation3dEditor = animation3dEditor;
}

void TopViewportController::inject(shared_ptr<AabbEditor> aabbEditor)
{
	_aabbEditor = aabbEditor;
}

void TopViewportController::inject(shared_ptr<Sound2dEditor> sound2dEditor)
{
	_sound2dEditor = sound2dEditor;
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

void TopViewportController::inject(shared_ptr<CaptorEditor> captorEditor)
{
	_captorEditor = captorEditor;
}