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