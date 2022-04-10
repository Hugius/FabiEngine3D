#include "bottom_viewport_controller.hpp"
#include "logger.hpp"
#include "configuration.hpp"

using BVPC = BottomViewportController;

void BottomViewportController::_updateStatistics()
{
	const auto statisticsScreen = _gui->getBottomViewport()->getWindow("statistics")->getScreen("main");
	const auto consoleScreen = _gui->getBottomViewport()->getWindow("statistics")->getScreen("main");

	static vector<float> fpsList;
	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % _fe3d->misc_getUpdateCountPerSecond()) == 0))
	{
		sort(fpsList.begin(), fpsList.end());

		const auto fps = (fpsList.empty() ? 0.0f : fpsList[_fe3d->misc_getUpdateCountPerSecond() / 2]);
		const auto text = ("FPS: " + to_string(static_cast<unsigned int>(fps)));

		statisticsScreen->getTextField("fps")->setTextContent(text);

		fpsList.clear();
	}
	else
	{
		fpsList.push_back(1000.0f / _fe3d->misc_getTotalDeltaTime());
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto text = ("CPU: " + _fe3d->misc_getCpuName());

		statisticsScreen->getTextField("cpuModel")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto text = ("GPU: " + _fe3d->misc_getGpuName());

		statisticsScreen->getTextField("gpuModel")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto text = ("OpenGL Version: " + _fe3d->misc_getOpenglVersion());

		statisticsScreen->getTextField("openglVersion")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto text = ("Camera Position/Yaw/Pitch: " +
						   to_string(static_cast<int>(_fe3d->camera_getPosition().x)) + " " +
						   to_string(static_cast<int>(_fe3d->camera_getPosition().y)) + " " +
						   to_string(static_cast<int>(_fe3d->camera_getPosition().z)) + " " +
						   to_string(static_cast<int>(_fe3d->camera_getYaw())) + " " +
						   to_string(static_cast<int>(_fe3d->camera_getPitch())));

		statisticsScreen->getTextField("cameraPositionYawPitch")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto text = ("Raycast Direction: " +
						   to_string(static_cast<int>(_fe3d->raycast_getCursorRayDirection().x * 100.0f)) + "% " +
						   to_string(static_cast<int>(_fe3d->raycast_getCursorRayDirection().y * 100.0f)) + "% " +
						   to_string(static_cast<int>(_fe3d->raycast_getCursorRayDirection().z * 100.0f)) + "%");

		statisticsScreen->getTextField("cursorPosition")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto text = ("Triangles: " + to_string(static_cast<int>(_fe3d->misc_getTriangleCount())));

		statisticsScreen->getTextField("triangleCount")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto & entityId : _fe3d->model_getIds())
		{
			if(_fe3d->model_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto text = ("Model Entities: " + to_string(entityCount));

		statisticsScreen->getTextField("modelEntityCount")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto & entityId : _fe3d->quad3d_getIds())
		{
			if(_fe3d->quad3d_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto text = ("Quad3D Entities: " + to_string(entityCount));

		statisticsScreen->getTextField("quad3dEntityCount")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto & entityId : _fe3d->aabb_getIds())
		{
			if(_fe3d->aabb_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto text = ("AABB Entities: " + to_string(entityCount));

		statisticsScreen->getTextField("aabbEntityCount")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto & entityId : _fe3d->pointlight_getIds())
		{
			if(_fe3d->pointlight_isVisible(entityId))
			{
				entityCount++;
			}
		}
		for(const auto & entityId : _fe3d->spotlight_getIds())
		{
			if(_fe3d->spotlight_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto text = ("Light Entities: " + to_string(entityCount));

		statisticsScreen->getTextField("lightEntityCount")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto & entityId : _fe3d->reflection_getIds())
		{
			if(_fe3d->reflection_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto text = ("Reflection Entities: " + to_string(entityCount));

		statisticsScreen->getTextField("reflectionEntityCount")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto & entityId : _fe3d->quad2d_getIds())
		{
			if(_fe3d->quad2d_isVisible(entityId))
			{
				entityCount++;
			}
		}
		for(const auto & entityId : _fe3d->text2d_getIds())
		{
			if(_fe3d->text2d_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto text = ("GUI Entities: " + to_string(entityCount));

		statisticsScreen->getTextField("quad2dEntityCount")->setTextContent(text);
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % _fe3d->misc_getUpdateCountPerSecond()) == 0))
	{
		auto deltaTimes = _fe3d->misc_getUpdateDeltaTimes();
		float totalDeltaTime = 0.0f;

		for(auto & [key, deltaTime] : deltaTimes)
		{
			totalDeltaTime += deltaTime;
		}

		for(const auto & [key, deltaTime] : deltaTimes)
		{
			const auto percentage = static_cast<unsigned int>((deltaTime / totalDeltaTime) * 100.0f);
			const auto text = (key + ": " + to_string(percentage) + "%");

			statisticsScreen->getTextField(key)->setTextContent(text);
		}
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % _fe3d->misc_getUpdateCountPerSecond()) == 0))
	{
		auto deltaTimes = _fe3d->misc_getRenderDeltaTimes();
		float totalDeltaTime = 0.0f;

		for(auto & [key, deltaTime] : deltaTimes)
		{
			totalDeltaTime += deltaTime;
		}

		for(const auto & [key, deltaTime] : deltaTimes)
		{
			const auto percentage = static_cast<unsigned int>((deltaTime / totalDeltaTime) * 100.0f);
			const auto text = (key + ": " + to_string(percentage) + "%");

			statisticsScreen->getTextField(key)->setTextContent(text);
		}
	}

	if(_fe3d->input_isKeyboardPressed(KeyType::KEY_C) && _gui->getBottomViewport()->getWindow("console")->isHovered())
	{
		if(!_scriptExecutor->isRunning() && !_gui->getOverlay()->isFocused() && !_scriptEditor->isWritingScript())
		{
			Logger::clearMessageQueue();

			for(const auto & [key, message] : _consoleMessageQueue)
			{
				_deleteConsoleMessage(key);
			}

			_consoleMessageQueue.clear();
		}
	}

	auto loggerMessages = Logger::getMessageQueue();

	if(loggerMessages.size() > MAX_CONSOLE_MESSAGES)
	{
		reverse(loggerMessages.begin(), loggerMessages.end());

		vector<string> newMessages;
		for(unsigned int index = 0; index < (static_cast<unsigned int>(loggerMessages.size()) - MAX_CONSOLE_MESSAGES); index++)
		{
			newMessages.push_back(loggerMessages[index]);
		}

		Logger::clearMessageQueue();

		for(const auto & [key, message] : _consoleMessageQueue)
		{
			_deleteConsoleMessage(key);
		}

		_consoleMessageQueue.clear();

		reverse(newMessages.begin(), newMessages.end());

		Logger::setCustomMessageQueue(newMessages);
	}

	loggerMessages = Logger::getMessageQueue();

	if(_consoleMessageQueue.size() != loggerMessages.size())
	{
		auto synchronizationCount = (loggerMessages.size() - _consoleMessageQueue.size());

		for(unsigned int index = (static_cast<unsigned int>(loggerMessages.size()) - static_cast<unsigned int>(synchronizationCount)); index < static_cast<unsigned int>(loggerMessages.size()); index++)
		{
			_addConsoleMessage(loggerMessages[index]);
		}
	}
}