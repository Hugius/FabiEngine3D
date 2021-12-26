#include "bottom_viewport_controller.hpp"

using BVPC = BottomViewportController;

BottomViewportController::BottomViewportController(FabiEngine3D& fe3d, GuiManager& gui,
												   TopViewportController& topViewportController, ScriptEditor& scriptEditor)
	:
	BaseViewportController(fe3d, gui),
	_topViewportController(topViewportController),
	_scriptEditor(scriptEditor)
{

}

void BottomViewportController::initialize()
{
	_gui.getViewport("bottom")->createWindow("statistics", fvec2(-0.25f, 0.0f), fvec2(0.9875f, 1.875f), BVPC::FRAME_COLOR);
	auto statisticsWindow = _gui.getViewport("bottom")->getWindow("statistics");

	statisticsWindow->createScreen("main");
	statisticsWindow->setActiveScreen("main");
	auto statisticsScreen = statisticsWindow->getScreen("main");

	_gui.getViewport("bottom")->createWindow("console", fvec2(0.25f, 0.0f), fvec2(0.9875f, 1.875f), BVPC::FRAME_COLOR);
	auto consoleWindow = _gui.getViewport("bottom")->getWindow("console");

	consoleWindow->createScreen("main");
	consoleWindow->setActiveScreen("main");
	auto consoleScreen = consoleWindow->getScreen("main");

	statisticsScreen->createTextField("fps", fvec2(-1.0f, 0.85f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("cpuModel", fvec2(-1.0f, 0.7f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("gpuModel", fvec2(-1.0f, 0.55f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("openglVersion", fvec2(-1.0f, 0.4f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("cameraPositionYawPitch", fvec2(-1.0f, 0.25f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("cursorPosition", fvec2(-1.0f, 0.1f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("triangleCount", fvec2(-1.0f, -0.05f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("modelEntityCount", fvec2(-1.0f, -0.2f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("billboardEntityCount", fvec2(-1.0f, -0.35f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("aabbEntityCount", fvec2(-1.0f, -0.5f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("lightEntityCount", fvec2(-1.0f, -0.65f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("reflectionEntityCount", fvec2(-1.0f, -0.8f), fvec2(0.0f), "", fvec3(1.0f), false);
	statisticsScreen->createTextField("imageEntityCount", fvec2(-1.0f, -0.95f), fvec2(0.0f), "", fvec3(1.0f), false);

	auto updateStatistics = _fe3d.misc_getUpdateProfilingStatistics();
	int uCounter = 1;
	for(const auto& [key, value] : updateStatistics)
	{
		statisticsScreen->createTextField(key, fvec2(-0.075f, 1.0f - (static_cast<float>(uCounter) * 0.15f)), fvec2(0.0f, 0.15f), "", fvec3(1.0f), false);
		uCounter++;
	}

	auto renderStatistics = _fe3d.misc_getRenderProfilingStatistics();
	int rCounter = 1;
	for(const auto& [key, value] : renderStatistics)
	{
		statisticsScreen->createTextField(key, fvec2(0.475f, 1.0f - (static_cast<float>(rCounter) * 0.15f)), fvec2(0.0f, 0.15f), "", fvec3(1.0f), false);
		rCounter++;
	}
}

void BottomViewportController::update()
{
	_updateStatistics();

	_updateConsole();
}