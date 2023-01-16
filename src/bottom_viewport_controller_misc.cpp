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
	_gui->getBottomViewport()->createWindow("console", fvec2(0.25f, 0.0f), fvec2(0.9875f, 1.875f), FRAME_COLOR);

	const auto statisticsWindow = _gui->getBottomViewport()->getWindow("statistics");
	const auto consoleWindow = _gui->getBottomViewport()->getWindow("console");

	statisticsWindow->createScreen("main");
	statisticsWindow->setActiveScreen("main");
	statisticsWindow->getScreen("main")->createTextField("fps", fvec2(-1.0f, 0.85f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsWindow->getScreen("main")->createTextField("cpu", fvec2(-1.0f, 0.7f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsWindow->getScreen("main")->createTextField("gpu", fvec2(-1.0f, 0.55f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsWindow->getScreen("main")->createTextField("openglVersion", fvec2(-1.0f, 0.4f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsWindow->getScreen("main")->createTextField("cameraPosition", fvec2(-1.0f, 0.25f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsWindow->getScreen("main")->createTextField("cameraYaw", fvec2(-1.0f, 0.1f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsWindow->getScreen("main")->createTextField("cameraPitch", fvec2(-1.0f, -0.05f), CHAR_SIZE, "", fvec3(1.0f), false);
	statisticsWindow->getScreen("main")->createTextField("triangles", fvec2(-1.0f, -0.2f), CHAR_SIZE, "", fvec3(1.0f), false);

	int uCounter = 1;
	int rCounter = 1;

	for(const auto & [key, deltaTime] : _fe3d->misc_getUpdateDeltaTimes())
	{
		statisticsWindow->getScreen("main")->createTextField(key, fvec2(0.0f, 1.0f - (static_cast<float>(uCounter) * 0.15f)), CHAR_SIZE, "", fvec3(1.0f), false);

		uCounter++;
	}

	for(const auto & [key, deltaTime] : _fe3d->misc_getRenderDeltaTimes())
	{
		statisticsWindow->getScreen("main")->createTextField(key, fvec2(0.4475f, 1.0f - (static_cast<float>(rCounter) * 0.15f)), CHAR_SIZE, "", fvec3(1.0f), false);

		rCounter++;
	}

	consoleWindow->createScreen("main");
	consoleWindow->setActiveScreen("main");
}

void BottomViewportController::update()
{
	_updateStatistics();
	_updateConsole();
}