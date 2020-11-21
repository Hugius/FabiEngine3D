#include "bottom_viewport_controller.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.04f, 2.0f)

void BottomViewportController::initialize()
{
	// Bottom-viewport: statistics
	_gui.getViewport("bottom")->addWindow("statistics", Vec2(-0.25f, 0.0f), Vec2(0.9875f, 1.8f), BottomViewportController::frameColor);
	_gui.getViewport("bottom")->getWindow("statistics")->addScreen("main");
	_gui.getViewport("bottom")->getWindow("statistics")->setActiveScreen("main");
	_statsScreen = _gui.getViewport("bottom")->getWindow("statistics")->getScreen("main");

	// General statistics
	_statsScreen->addTextfield("fps", Vec2(-1.0f, 0.85f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("gpuName", Vec2(-1.0f, 0.7f), Vec2(0.0f), "", Vec3(1.0f), false, false);
	_statsScreen->addTextfield("openglVersion", Vec2(-1.0f, 0.55f), Vec2(0.0f), "", Vec3(1.0f), false, false);
	_statsScreen->addTextfield("cameraPosition", Vec2(-1.0f, 0.4f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("cameraYawPitch", Vec2(-1.0f, 0.25f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("cursorPosition", Vec2(-1.0f, 0.1f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("triangleCount", Vec2(-1.0f, -0.05f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("gameEntityCount", Vec2(-1.0f, -0.2f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("billboardEntityCount", Vec2(-1.0f, -0.35f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("lightEntityCount", Vec2(-1.0f, -0.5f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("aabbEntityCount", Vec2(-1.0f, -0.65f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("guiEntityCount", Vec2(-1.0f, -0.8f), Vec2(0.0f), "", Vec3(1.0f), false, true);

	// Performance profiling
	auto performanceStats = _fe3d.misc_getPerformanceProfilingStatistics();
	int counter = 1;
	for (auto& [key, value] : performanceStats)
	{
		_statsScreen->addTextfield(key, Vec2(-0.25f, 1.0f - (static_cast<float>(counter) * 0.15f)), Vec2(0.0f, 0.15f), "", Vec3(1.0f), false, false);
		counter++;
	}

	// Console window
	_gui.getViewport("bottom")->addWindow("console", Vec2(0.25f, 0.0f), Vec2(0.9875f, 1.8f), BottomViewportController::frameColor);
	_gui.getViewport("bottom")->getWindow("console")->addScreen("main");
	_gui.getViewport("bottom")->getWindow("console")->setActiveScreen("main");
}

void BottomViewportController::update()
{
	// Update FPS
	static float totalFPS = 0.0f;
	static int fpsCount = 0;
	if (_fe3d.misc_checkInterval("fps", 50))
	{
		string fpsTextID = _statsScreen->getTextfield("fps")->getEntityID();
		string text = "FPS: " + to_string(static_cast<int>(totalFPS / fpsCount));
		_fe3d.textEntity_setTextContent(fpsTextID, text, _charSize.x, _charSize.y);
		totalFPS = 0.0f;
		fpsCount = 0;
	}
	else
	{
		totalFPS += _fe3d.misc_getFPS();
		fpsCount++;
	}

	// Update GPU stats
	if (_fe3d.misc_checkInterval("gpuName", 10000))
	{
		string textID = _statsScreen->getTextfield("gpuName")->getEntityID();
		string text = "GPU: " + _fe3d.misc_getGpuName();
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update OpenGL version
	if (_fe3d.misc_checkInterval("openglVersion", 10000))
	{
		string textID = _statsScreen->getTextfield("openglVersion")->getEntityID();
		string text = "OpenGL version: " + _fe3d.misc_getOpenglVersion();
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update camera position
	if (_fe3d.misc_checkInterval("cameraPosition", 1))
	{
		string textID = _statsScreen->getTextfield("cameraPosition")->getEntityID();
		string text = "Camera position: " + 
			to_string(static_cast<int>(_fe3d.camera_getPosition().x)) + " " +
			to_string(static_cast<int>(_fe3d.camera_getPosition().y)) + " " +
			to_string(static_cast<int>(_fe3d.camera_getPosition().z));
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update camera pitch & yaw
	if (_fe3d.misc_checkInterval("cameraYawPitch", 1))
	{
		string textID = _statsScreen->getTextfield("cameraYawPitch")->getEntityID();
		string text = "Camera yaw & pitch: " + 
			to_string(static_cast<int>(_fe3d.camera_getYaw())) + " " + to_string(static_cast<int>(_fe3d.camera_getPitch()));
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update cursor position
	if (_fe3d.misc_checkInterval("cursorPosition", 1))
	{
		string textID = _statsScreen->getTextfield("cursorPosition")->getEntityID();
		string text = "Raycast position: " +
			to_string(static_cast<int>(_fe3d.terrainEntity_getMousePoint().x)) + " " +
			to_string(static_cast<int>(_fe3d.terrainEntity_getMousePoint().y)) + " " +
			to_string(static_cast<int>(_fe3d.terrainEntity_getMousePoint().z));
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update triangle count
	if (_fe3d.misc_checkInterval("triangleCount", 10))
	{
		string textID = _statsScreen->getTextfield("triangleCount")->getEntityID();
		string text = "Triangles: " + to_string(static_cast<int>(_fe3d.misc_getTriangleCount()));
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update game entity count
	if (_fe3d.misc_checkInterval("gameEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("gameEntityCount")->getEntityID();

		int total = 0;
		for (auto& ID : _fe3d.gameEntity_getAllIDs())
		{
			if (_fe3d.gameEntity_isVisible(ID))
			{
				total++;
			}
		}

		string text = "Game entities: " + to_string(total);
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update billboard entity count
	if (_fe3d.misc_checkInterval("billboardEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("billboardEntityCount")->getEntityID();

		int total = 0;
		for (auto& ID : _fe3d.billboardEntity_getAllIDs())
		{
			if (_fe3d.billboardEntity_isVisible(ID))
			{
				total++;
			}
		}

		string text = "Billboard entities: " + to_string(total);
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update LIGHT entity count
	if (_fe3d.misc_checkInterval("lightEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("lightEntityCount")->getEntityID();

		int total = 0;
		for (auto& ID : _fe3d.lightEntity_getAllIDs())
		{
			if (_fe3d.lightEntity_isVisible(ID))
			{
				total++;
			}
		}

		string text = "Light entities: " + to_string(total);
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update AABB entity count
	if (_fe3d.misc_checkInterval("aabbEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("aabbEntityCount")->getEntityID();

		int total = 0;
		for (auto& ID : _fe3d.aabbEntity_getAllIDs())
		{
			total++;
		}

		string text = "AABB entities: " + to_string(total);
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update GUI entity count
	if (_fe3d.misc_checkInterval("guiEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("guiEntityCount")->getEntityID();

		int total = 0;

		// Count GUI entities
		for (auto& ID : _fe3d.guiEntity_getAllIDs())
		{
			if (_fe3d.guiEntity_isVisible(ID))
			{
				total++;
			}
		}

		// Count text entities
		for (auto& ID : _fe3d.textEntity_getAllIDs())
		{
			if (_fe3d.textEntity_isVisible(ID))
			{
				total++;
			}
		}

		string text = "GUI entities: " + to_string(total);
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update performance profiling
	if (_fe3d.misc_checkInterval("performanceProfiling", 50))
	{
		auto performanceStats = _fe3d.misc_getPerformanceProfilingStatistics();
		for (auto& [key, value] : performanceStats)
		{
			string textID = _statsScreen->getTextfield(key)->getEntityID();
			_fe3d.textEntity_setTextContent(textID, key + ": " + to_string(value) + "%", _charSize.x, _charSize.y);
		}
	}

	// Synchronize console text with core logger
	auto loggerMessages = _fe3d.logger_getMessageStack();
	if (_consoleMessageStack.size() != loggerMessages.size())
	{
		auto synchronizationCount = loggerMessages.size() - _consoleMessageStack.size();

		// Synchronize messages
		for (size_t i = loggerMessages.size() - synchronizationCount; i < loggerMessages.size(); i++)
		{
			_addConsoleMessage(loggerMessages[i]);
		}
	}

	// Update console window
	_updateConsoleScrolling();
}