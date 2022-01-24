#include "bottom_viewport_controller.hpp"
#include "logger.hpp"

using BVPC = BottomViewportController;

void BottomViewportController::_updateStatistics()
{
	auto statisticsScreen = _gui->getBottomViewport()->getWindow("statistics")->getScreen("main");
	auto consoleScreen = _gui->getBottomViewport()->getWindow("statistics")->getScreen("main");

	static vector<float> fpsList;
	if(_fe3d->misc_checkInterval(100))
	{
		sort(fpsList.begin(), fpsList.end());
		float fps = fpsList.empty() ? -1.0f : fpsList[49];

		string fpsTextID = statisticsScreen->getTextField("fps")->getEntityId();
		string text = "FPS: " + to_string(static_cast<int>(fps));
		_fe3d->text2d_setContent(fpsTextID, text, CHAR_SIZE.x, CHAR_SIZE.y);
		fpsList.clear();
	}
	else
	{
		fpsList.push_back(_fe3d->misc_getFPS());
	}

	if(_fe3d->misc_checkInterval(100))
	{
		string textID = statisticsScreen->getTextField("cpuModel")->getEntityId();
		string text = ("CPU: " + _fe3d->misc_getCpuName());
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(100))
	{
		string textID = statisticsScreen->getTextField("gpuModel")->getEntityId();
		string text = ("GPU: " + _fe3d->misc_getGpuName());
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(100))
	{
		string textID = statisticsScreen->getTextField("openglVersion")->getEntityId();
		string text = "OpenGL Version: " + _fe3d->misc_getOpenglVersion();
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(1))
	{
		string textID = statisticsScreen->getTextField("cameraPositionYawPitch")->getEntityId();
		string text = ("Camera Position/Yaw/Pitch: " +
					   to_string(static_cast<int>(_fe3d->camera_getPosition().x)) + " " +
					   to_string(static_cast<int>(_fe3d->camera_getPosition().y)) + " " +
					   to_string(static_cast<int>(_fe3d->camera_getPosition().z)) + " " +
					   to_string(static_cast<int>(_fe3d->camera_getYaw())) + " " +
					   to_string(static_cast<int>(_fe3d->camera_getPitch())));
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(1))
	{
		string textID = statisticsScreen->getTextField("cursorPosition")->getEntityId();
		string text = "Raycast Direction: " +
			to_string(static_cast<int>(_fe3d->raycast_getCursorRay().getDirection().x * 100.0f)) + "% " +
			to_string(static_cast<int>(_fe3d->raycast_getCursorRay().getDirection().y * 100.0f)) + "% " +
			to_string(static_cast<int>(_fe3d->raycast_getCursorRay().getDirection().z * 100.0f)) + "%";
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(10))
	{
		string textID = statisticsScreen->getTextField("triangleCount")->getEntityId();
		string text = "Triangles: " + to_string(static_cast<int>(_fe3d->misc_getTriangleCount()));
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(10))
	{
		unsigned int entityCount = 0;
		for(const auto& entityId : _fe3d->model_getIds())
		{
			if(_fe3d->model_isVisible(entityId))
			{
				entityCount++;
			}
		}

		string textID = statisticsScreen->getTextField("modelEntityCount")->getEntityId();
		string text = "Model Entities: " + to_string(entityCount);
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(10))
	{
		unsigned int entityCount = 0;
		for(const auto& entityId : _fe3d->quad3d_getIds())
		{
			if(_fe3d->quad3d_isVisible(entityId))
			{
				entityCount++;
			}
		}

		string textID = statisticsScreen->getTextField("quad3dEntityCount")->getEntityId();
		string text = "Quad3d Entities: " + to_string(entityCount);
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(10))
	{
		unsigned int entityCount = 0;
		for(const auto& entityId : _fe3d->aabb_getIds())
		{
			if(_fe3d->aabb_isVisible(entityId))
			{
				entityCount++;
			}
		}

		string textID = statisticsScreen->getTextField("aabbEntityCount")->getEntityId();
		string text = "AABB Entities: " + to_string(entityCount);
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(10))
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

		string textID = statisticsScreen->getTextField("lightEntityCount")->getEntityId();
		string text = "Light Entities: " + to_string(entityCount);
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(10))
	{
		unsigned int entityCount = 0;
		for(const auto& entityId : _fe3d->reflection_getIds())
		{
			if(_fe3d->reflection_isVisible(entityId))
			{
				entityCount++;
			}
		}

		string textID = statisticsScreen->getTextField("reflectionEntityCount")->getEntityId();
		string text = "Reflection Entities: " + to_string(entityCount);
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(10))
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

		string textID = statisticsScreen->getTextField("quad2dEntityCount")->getEntityId();
		string text = "GUI Entities: " + to_string(entityCount);
		_fe3d->text2d_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	if(_fe3d->misc_checkInterval(50))
	{
		auto updateStatistics = _fe3d->misc_getUpdateProfilingStatistics();
		for(const auto& [key, value] : updateStatistics)
		{
			string textID = statisticsScreen->getTextField(key)->getEntityId();
			_fe3d->text2d_setContent(textID, key + ": " + to_string(value) + "%", CHAR_SIZE.x, CHAR_SIZE.y);
		}
	}

	if(_fe3d->misc_checkInterval(50))
	{
		auto renderStatistics = _fe3d->misc_getRenderProfilingStatistics();
		for(const auto& [key, value] : renderStatistics)
		{
			string textID = statisticsScreen->getTextField(key)->getEntityId();
			_fe3d->text2d_setContent(textID, key + ": " + to_string(value) + "%", CHAR_SIZE.x, CHAR_SIZE.y);
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