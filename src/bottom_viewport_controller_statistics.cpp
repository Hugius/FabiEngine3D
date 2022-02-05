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
		const auto textId = statisticsScreen->getTextField("fps")->getEntityId();
		const auto text = string("FPS: " + to_string(static_cast<unsigned int>(fps)));

		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));

		fpsList.clear();
	}
	else
	{
		fpsList.push_back(_fe3d->misc_getFPS());
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto textId = statisticsScreen->getTextField("cpuModel")->getEntityId();
		const auto text = string("CPU: " + _fe3d->misc_getCpuName());

		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto textId = statisticsScreen->getTextField("gpuModel")->getEntityId();
		const auto text = string("GPU: " + _fe3d->misc_getGpuName());

		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto textId = statisticsScreen->getTextField("openglVersion")->getEntityId();
		const auto text = string("OpenGL Version: " + _fe3d->misc_getOpenglVersion());

		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto textId = statisticsScreen->getTextField("cameraPositionYawPitch")->getEntityId();
		const auto text = string("Camera Position/Yaw/Pitch: " +
								 to_string(static_cast<int>(_fe3d->camera_getPosition().x)) + " " +
								 to_string(static_cast<int>(_fe3d->camera_getPosition().y)) + " " +
								 to_string(static_cast<int>(_fe3d->camera_getPosition().z)) + " " +
								 to_string(static_cast<int>(_fe3d->camera_getYaw())) + " " +
								 to_string(static_cast<int>(_fe3d->camera_getPitch())));

		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto textId = statisticsScreen->getTextField("cursorPosition")->getEntityId();
		const auto text = string("Raycast Direction: " +
								 to_string(static_cast<int>(_fe3d->raycast_getCursorRayDirection().x * 100.0f)) + "% " +
								 to_string(static_cast<int>(_fe3d->raycast_getCursorRayDirection().y * 100.0f)) + "% " +
								 to_string(static_cast<int>(_fe3d->raycast_getCursorRayDirection().z * 100.0f)) + "%");

		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 100)) == 0))
	{
		const auto textId = statisticsScreen->getTextField("triangleCount")->getEntityId();
		const auto text = string("Triangles: " + to_string(static_cast<int>(_fe3d->misc_getTriangleCount())));

		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto& entityId : _fe3d->model_getIds())
		{
			if(_fe3d->model_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto textId = statisticsScreen->getTextField("modelEntityCount")->getEntityId();
		const auto text = string("Model Entities: " + to_string(entityCount));
		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto& entityId : _fe3d->quad3d_getIds())
		{
			if(_fe3d->quad3d_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto textId = statisticsScreen->getTextField("quad3dEntityCount")->getEntityId();
		const auto text = string("Quad3d Entities: " + to_string(entityCount));
		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto& entityId : _fe3d->aabb_getIds())
		{
			if(_fe3d->aabb_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto textId = statisticsScreen->getTextField("aabbEntityCount")->getEntityId();
		const auto text = string("AABB Entities: " + to_string(entityCount));
		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto& entityId : _fe3d->pointlight_getIds())
		{
			if(_fe3d->pointlight_isVisible(entityId))
			{
				entityCount++;
			}
		}
		for(const auto& entityId : _fe3d->spotlight_getIds())
		{
			if(_fe3d->spotlight_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto textId = statisticsScreen->getTextField("lightEntityCount")->getEntityId();
		const auto text = string("Light Entities: " + to_string(entityCount));
		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto& entityId : _fe3d->reflection_getIds())
		{
			if(_fe3d->reflection_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto textId = statisticsScreen->getTextField("reflectionEntityCount")->getEntityId();
		const auto text = string("Reflection Entities: " + to_string(entityCount));
		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 10)) == 0))
	{
		unsigned int entityCount = 0;
		for(const auto& entityId : _fe3d->quad2d_getIds())
		{
			if(_fe3d->quad2d_isVisible(entityId))
			{
				entityCount++;
			}
		}
		for(const auto& entityId : _fe3d->text2d_getIds())
		{
			if(_fe3d->text2d_isVisible(entityId))
			{
				entityCount++;
			}
		}

		const auto textId = statisticsScreen->getTextField("quad2dEntityCount")->getEntityId();
		const auto text = string("GUI Entities: " + to_string(entityCount));
		_fe3d->text2d_setContent(textId, text);
		_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % _fe3d->misc_getUpdateCountPerSecond()) == 0))
	{
		auto updateStatistics = _fe3d->misc_getUpdateProfilingStatistics();

		for(const auto& [key, value] : updateStatistics)
		{
			const auto textId = statisticsScreen->getTextField(key)->getEntityId();
			const auto text = string(key + ": " + to_string(value) + "%");

			_fe3d->text2d_setContent(textId, text);
			_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
		}
	}

	if((_fe3d->misc_getPassedUpdateCount() == 0) || ((_fe3d->misc_getPassedUpdateCount() % _fe3d->misc_getUpdateCountPerSecond()) == 0))
	{
		auto renderStatistics = _fe3d->misc_getRenderProfilingStatistics();

		for(const auto& [key, value] : renderStatistics)
		{
			const auto textId = statisticsScreen->getTextField(key)->getEntityId();
			const auto text = string(key + ": " + to_string(value) + "%");

			_fe3d->text2d_setContent(textId, text);
			_fe3d->text2d_setSize(textId, fvec2(CHAR_SIZE.x * static_cast<float>(text.size()), CHAR_SIZE.y));
		}
	}

	if(_fe3d->input_isKeyPressed(InputType::KEY_C) && _gui->getBottomViewport()->getWindow("console")->isHovered())
	{
		if(!_scriptExecutor->isRunning() && !_gui->getOverlay()->isFocused() && !_scriptEditor->isWritingScript())
		{
			Logger::clearMessageQueue();

			for(const auto& [key, message] : _consoleMessageQueue)
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
		for(size_t i = 0; i < (loggerMessages.size() - static_cast<size_t>(MAX_CONSOLE_MESSAGES)); i++)
		{
			newMessages.push_back(loggerMessages[i]);
		}

		Logger::clearMessageQueue();

		for(const auto& [key, message] : _consoleMessageQueue)
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
		auto synchronizationCount = loggerMessages.size() - _consoleMessageQueue.size();

		for(size_t i = loggerMessages.size() - synchronizationCount; i < loggerMessages.size(); i++)
		{
			_addConsoleMessage(loggerMessages[i]);
		}
	}
}