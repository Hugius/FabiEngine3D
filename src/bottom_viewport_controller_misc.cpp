#include "bottom_viewport_controller.hpp"

void BottomViewportController::inject(shared_ptr<ScriptExecutor> scriptExecutor)
{
	_scriptExecutor = scriptExecutor;
}

void BottomViewportController::inject(shared_ptr<ScriptEditor> scriptEditor)
{
	_scriptEditor = scriptEditor;
}

void BottomViewportController::initialize()
{
	_gui->getBottomViewport()->createWindow("statistics", fvec2(-0.25f, 0.0f), fvec2(0.9875f, 1.875f), FRAME_COLOR);
	auto statisticsWindow = _gui->getBottomViewport()->getWindow("statistics");

	statisticsWindow->createScreen("main");
	statisticsWindow->setActiveScreen("main");
	auto statisticsScreen = statisticsWindow->getScreen("main");

	_gui->getBottomViewport()->createWindow("console", fvec2(0.25f, 0.0f), fvec2(0.9875f, 1.875f), FRAME_COLOR);
	auto consoleWindow = _gui->getBottomViewport()->getWindow("console");

	consoleWindow->createScreen("main");
	consoleWindow->setActiveScreen("main");
	auto consoleScreen = consoleWindow->getScreen("main");

	statisticsScreen->createTextField("fps", fvec2(-1.0f, 0.85f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsScreen->createTextField("cpu", fvec2(-1.0f, 0.7f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsScreen->createTextField("gpu", fvec2(-1.0f, 0.55f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsScreen->createTextField("openglVersion", fvec2(-1.0f, 0.4f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsScreen->createTextField("cameraPosition", fvec2(-1.0f, 0.25f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsScreen->createTextField("cameraYaw", fvec2(-1.0f, 0.1f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsScreen->createTextField("cameraPitch", fvec2(-1.0f, -0.05f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsScreen->createTextField("raycastDirection", fvec2(-1.0f, -0.2f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsScreen->createTextField("triangles", fvec2(-1.0f, -0.35f), CHAR_SIZE, "", fvec3(1.0f), false);

	int uCounter = 1;
	for(const auto & [key, deltaTime] : _fe3d->misc_getUpdateDeltaTimes())
	{
		statisticsScreen->createTextField(key, fvec2(0.0f, 1.0f - (static_cast<float>(uCounter) * 0.15f)), CHAR_SIZE, "", fvec3(1.0f), false);
		uCounter++;
	}

	int rCounter = 1;
	for(const auto & [key, deltaTime] : _fe3d->misc_getRenderDeltaTimes())
	{
		statisticsScreen->createTextField(key, fvec2(0.45f, 1.0f - (static_cast<float>(rCounter) * 0.15f)), CHAR_SIZE, "", fvec3(1.0f), false);
		rCounter++;
	}
}

void BottomViewportController::update()
{
	_updateStatistics();
	_updateConsole();
}