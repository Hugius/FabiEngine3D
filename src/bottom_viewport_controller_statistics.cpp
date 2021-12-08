#include "bottom_viewport_controller.hpp"
#include "logger.hpp"

using BVPC = BottomViewportController;

void BottomViewportController::_updateStatistics()
{
	// Temporary values
	auto statisticsScreen = _gui.getViewport("bottom")->getWindow("statistics")->getScreen("main");
	auto consoleScreen = _gui.getViewport("bottom")->getWindow("statistics")->getScreen("main");

	// Update fps display
	static vector<float> fpsList;
	if(_fe3d.misc_checkInterval(100))
	{
		// Calculate median
		sort(fpsList.begin(), fpsList.end());
		float fps = fpsList.empty() ? -1.0f : fpsList[49];

		// Display FPS
		string fpsTextID = statisticsScreen->getTextField("fps")->getEntityID();
		string text = "FPS: " + to_string(static_cast<int>(fps));
		_fe3d.text_setContent(fpsTextID, text, CHAR_SIZE.x, CHAR_SIZE.y);
		fpsList.clear();
	}
	else
	{
		fpsList.push_back(_fe3d.misc_getFPS());
	}

	// Update CPU stats
	if(_fe3d.misc_checkInterval(100))
	{
		string textID = statisticsScreen->getTextField("cpuModel")->getEntityID();
		string text = ("CPU: " + _fe3d.misc_getCpuModel());
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update GPU stats
	if(_fe3d.misc_checkInterval(100))
	{
		string textID = statisticsScreen->getTextField("gpuModel")->getEntityID();
		string text = ("GPU: " + _fe3d.misc_getGpuModel());
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update OpenGL version
	if(_fe3d.misc_checkInterval(100))
	{
		string textID = statisticsScreen->getTextField("openglVersion")->getEntityID();
		string text = "OpenGL Version: " + _fe3d.misc_getOpenglVersion();
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update camera position/yaw/pitch
	if(_fe3d.misc_checkInterval(1))
	{
		string textID = statisticsScreen->getTextField("cameraPositionYawPitch")->getEntityID();
		string text = ("Camera Position/Yaw/Pitch: " +
					   to_string(static_cast<int>(_fe3d.camera_getPosition().x)) + " " +
					   to_string(static_cast<int>(_fe3d.camera_getPosition().y)) + " " +
					   to_string(static_cast<int>(_fe3d.camera_getPosition().z)) + " " +
					   to_string(static_cast<int>(_fe3d.camera_getYaw())) + " " +
					   to_string(static_cast<int>(_fe3d.camera_getPitch())));
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update cursor position
	if(_fe3d.misc_checkInterval(1))
	{
		string textID = statisticsScreen->getTextField("cursorPosition")->getEntityID();
		string text = "Raycast Direction: " +
			to_string(static_cast<int>(_fe3d.raycast_getCursorRay().getDirection().x * 100.0f)) + "% " +
			to_string(static_cast<int>(_fe3d.raycast_getCursorRay().getDirection().y * 100.0f)) + "% " +
			to_string(static_cast<int>(_fe3d.raycast_getCursorRay().getDirection().z * 100.0f)) + "%";
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update triangle count
	if(_fe3d.misc_checkInterval(10))
	{
		string textID = statisticsScreen->getTextField("triangleCount")->getEntityID();
		string text = "Triangles: " + to_string(static_cast<int>(_fe3d.misc_getTriangleCount()));
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update model entity count
	if(_fe3d.misc_checkInterval(10))
	{
		// Count visible models
		unsigned int entityCount = 0;
		for(const auto& entityID : _fe3d.model_getAllIDs())
		{
			if(_fe3d.model_isVisible(entityID))
			{
				entityCount++;
			}
		}

		// Set text content
		string textID = statisticsScreen->getTextField("modelEntityCount")->getEntityID();
		string text = "Model Entities: " + to_string(entityCount);
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update billboard entity count
	if(_fe3d.misc_checkInterval(10))
	{
		// Count visible entities
		unsigned int entityCount = 0;
		for(const auto& entityID : _fe3d.billboard_getAllIDs())
		{
			if(_fe3d.billboard_isVisible(entityID))
			{
				entityCount++;
			}
		}

		// Set text content
		string textID = statisticsScreen->getTextField("billboardEntityCount")->getEntityID();
		string text = "Billboard Entities: " + to_string(entityCount);
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update AABB entity count
	if(_fe3d.misc_checkInterval(10))
	{
		// Count visible entities
		unsigned int entityCount = 0;
		for(const auto& entityID : _fe3d.aabb_getAllIDs())
		{
			if(_fe3d.aabb_isVisible(entityID))
			{
				entityCount++;
			}
		}

		// Set text content
		string textID = statisticsScreen->getTextField("aabbEntityCount")->getEntityID();
		string text = "AABB Entities: " + to_string(entityCount);
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update light entity count
	if(_fe3d.misc_checkInterval(10))
	{
		// Count visible entities
		unsigned int entityCount = 0;
		for(const auto& entityID : _fe3d.pointlight_getAllIDs())
		{
			if(_fe3d.pointlight_isVisible(entityID))
			{
				entityCount++;
			}
		}
		for(const auto& entityID : _fe3d.spotlight_getAllIDs())
		{
			if(_fe3d.spotlight_isVisible(entityID))
			{
				entityCount++;
			}
		}

		// Set text content
		string textID = statisticsScreen->getTextField("lightEntityCount")->getEntityID();
		string text = "Light Entities: " + to_string(entityCount);
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update reflection entity count
	if(_fe3d.misc_checkInterval(10))
	{
		// Count visible entities
		unsigned int entityCount = 0;
		for(const auto& entityID : _fe3d.reflection_getAllIDs())
		{
			if(_fe3d.reflection_isVisible(entityID))
			{
				entityCount++;
			}
		}

		// Set text content
		string textID = statisticsScreen->getTextField("reflectionEntityCount")->getEntityID();
		string text = "Reflection Entities: " + to_string(entityCount);
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update GUI entity count
	if(_fe3d.misc_checkInterval(10))
	{
		// Count visible entities
		unsigned int entityCount = 0;
		for(const auto& entityID : _fe3d.image_getAllIDs())
		{
			if(_fe3d.image_isVisible(entityID))
			{
				entityCount++;
			}
		}
		for(const auto& entityID : _fe3d.text_getAllIDs())
		{
			if(_fe3d.text_isVisible(entityID))
			{
				entityCount++;
			}
		}

		// Set text content
		string textID = statisticsScreen->getTextField("imageEntityCount")->getEntityID();
		string text = "GUI Entities: " + to_string(entityCount);
		_fe3d.text_setContent(textID, text, CHAR_SIZE.x, CHAR_SIZE.y);
	}

	// Update update-profiling
	if(_fe3d.misc_checkInterval(50))
	{
		auto updateStatistics = _fe3d.misc_getUpdateProfilingStatistics();
		for(const auto& [key, value] : updateStatistics)
		{
			string textID = statisticsScreen->getTextField(key)->getEntityID();
			_fe3d.text_setContent(textID, key + ": " + to_string(value) + "%", CHAR_SIZE.x, CHAR_SIZE.y);
		}
	}

	// Update render-profiling
	if(_fe3d.misc_checkInterval(50))
	{
		auto renderStatistics = _fe3d.misc_getRenderProfilingStatistics();
		for(const auto& [key, value] : renderStatistics)
		{
			string textID = statisticsScreen->getTextField(key)->getEntityID();
			_fe3d.text_setContent(textID, key + ": " + to_string(value) + "%", CHAR_SIZE.x, CHAR_SIZE.y);
		}
	}

	// Clear console messages if user wants to
	if(_fe3d.input_isKeyPressed(InputType::KEY_C) && _gui.getViewport("bottom")->getWindow("console")->isHovered())
	{
		// Validate
		if(!_topViewportController.isScriptRunning() && !_gui.getGlobalScreen()->isFocused() && !_scriptEditor.isWritingScript())
		{
			Logger::clearMessageQueue();
			for(const auto& [ID, message] : _consoleMessageQueue)
			{
				_deleteConsoleMessage(ID);
			}
			_consoleMessageQueue.clear();
		}
	}

	// Clear console messages if it overflows
	auto loggerMessages = Logger::getMessageQueue();
	if(loggerMessages.size() > MAX_CONSOLE_MESSAGES)
	{
		// Save most recent messages
		reverse(loggerMessages.begin(), loggerMessages.end());
		vector<string> newMessages;
		for(size_t i = 0; i < (loggerMessages.size() - static_cast<size_t>(MAX_CONSOLE_MESSAGES)); i++)
		{
			newMessages.push_back(loggerMessages[i]);
		}

		// Remove old messages
		Logger::clearMessageQueue();
		for(const auto& [ID, message] : _consoleMessageQueue)
		{
			_deleteConsoleMessage(ID);
		}
		_consoleMessageQueue.clear();

		// Set new messages
		reverse(newMessages.begin(), newMessages.end());
		Logger::setCustomMessageQueue(newMessages);
	}

	// Synchronize console text with core logger
	loggerMessages = Logger::getMessageQueue();
	if(_consoleMessageQueue.size() != loggerMessages.size())
	{
		auto synchronizationCount = loggerMessages.size() - _consoleMessageQueue.size();

		// Synchronize messages
		for(size_t i = loggerMessages.size() - synchronizationCount; i < loggerMessages.size(); i++)
		{
			_addConsoleMessage(loggerMessages[i]);
		}
	}
}