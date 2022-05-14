#include "bottom_viewport_controller.hpp"

using BVPC = BottomViewportController;

void BottomViewportController::_updateStatistics()
{
	const auto statisticsScreen = _gui->getBottomViewport()->getWindow("statistics")->getScreen("main");
	const auto consoleScreen = _gui->getBottomViewport()->getWindow("statistics")->getScreen("main");

	static vector<float> fpsList = {};

	if((_fe3d->misc_getPassedUpdateCount() % _fe3d->misc_getUpdateCountPerSecond()) == 0)
	{
		sort(fpsList.begin(), fpsList.end());

		const auto fps = (fpsList.empty() ? 0.0f : fpsList[_fe3d->misc_getUpdateCountPerSecond() / 2]);
		const auto text = ("FPS: " + to_string(static_cast<int>(fps)));

		statisticsScreen->getTextField("fps")->setTextContent(text);

		fpsList.clear();
	}
	else
	{
		fpsList.push_back(1000.0f / _fe3d->misc_getTotalDeltaTime());
	}

	if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / STATISTICS_UPDATE_DIVIDER)) == 0)
	{
		const auto text = ("CPU: " + _fe3d->misc_getCpuName());

		statisticsScreen->getTextField("cpu")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / STATISTICS_UPDATE_DIVIDER)) == 0)
	{
		const auto text = ("GPU: " + _fe3d->misc_getGpuName());

		statisticsScreen->getTextField("gpu")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / STATISTICS_UPDATE_DIVIDER)) == 0)
	{
		const auto text = ("OpenGL Version: " + _fe3d->misc_getOpenglVersion());

		statisticsScreen->getTextField("openglVersion")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / STATISTICS_UPDATE_DIVIDER)) == 0)
	{
		const auto text = ("Camera Position: " +
						   to_string(static_cast<int>(_fe3d->camera_getPosition().x)) + " " +
						   to_string(static_cast<int>(_fe3d->camera_getPosition().y)) + " " +
						   to_string(static_cast<int>(_fe3d->camera_getPosition().z)));

		statisticsScreen->getTextField("cameraPosition")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / STATISTICS_UPDATE_DIVIDER)) == 0)
	{
		const auto text = ("Camera Yaw: " + to_string(static_cast<int>(_fe3d->camera_getYaw())));

		statisticsScreen->getTextField("cameraYaw")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / STATISTICS_UPDATE_DIVIDER)) == 0)
	{
		const auto text = ("Camera Pitch: " + to_string(static_cast<int>(_fe3d->camera_getPitch())));

		statisticsScreen->getTextField("cameraPitch")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / STATISTICS_UPDATE_DIVIDER)) == 0)
	{
		const auto text = ("Raycast Direction: " +
						   to_string(static_cast<int>(_fe3d->raycast_getCursorRayDirection().x * 100.0f)) + "% " +
						   to_string(static_cast<int>(_fe3d->raycast_getCursorRayDirection().y * 100.0f)) + "% " +
						   to_string(static_cast<int>(_fe3d->raycast_getCursorRayDirection().z * 100.0f)) + "% ");

		statisticsScreen->getTextField("raycastDirection")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / STATISTICS_UPDATE_DIVIDER)) == 0)
	{
		const auto text = ("Triangles: " + to_string(static_cast<int>(_fe3d->misc_getTriangleCount())));

		statisticsScreen->getTextField("triangles")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() % _fe3d->misc_getUpdateCountPerSecond()) == 0)
	{
		auto deltaTimes = _fe3d->misc_getUpdateDeltaTimes();
		float totalDeltaTime = 0.0f;

		for(auto & [key, deltaTime] : deltaTimes)
		{
			totalDeltaTime += deltaTime;
		}

		for(const auto & [key, deltaTime] : deltaTimes)
		{
			const auto percentage = ((totalDeltaTime == 0.0f) ? 0 : static_cast<int>((deltaTime / totalDeltaTime) * 100.0f));
			const auto text = (key + ": " + to_string(percentage) + "%");

			statisticsScreen->getTextField(key)->setTextContent(text);
		}
	}

	if((_fe3d->misc_getPassedUpdateCount() % _fe3d->misc_getUpdateCountPerSecond()) == 0)
	{
		auto deltaTimes = _fe3d->misc_getRenderDeltaTimes();
		float totalDeltaTime = 0.0f;

		for(auto & [key, deltaTime] : deltaTimes)
		{
			totalDeltaTime += deltaTime;
		}

		for(const auto & [key, deltaTime] : deltaTimes)
		{
			const auto percentage = ((totalDeltaTime == 0.0f) ? 0 : static_cast<int>((deltaTime / totalDeltaTime) * 100.0f));
			const auto text = (key + ": " + to_string(percentage) + "%");

			statisticsScreen->getTextField(key)->setTextContent(text);
		}
	}
}