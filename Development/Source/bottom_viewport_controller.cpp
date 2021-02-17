#include "bottom_viewport_controller.hpp"
#include "left_viewport_controller.hpp"

#include <algorithm>

#define GW(text) LVPC::calcTextWidth(text, 0.04f, 2.0f)

BottomViewportController::BottomViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui, 
	TopViewportController& topViewportController, ScriptEditor& scriptEditor) :
	ViewportController(fe3d, gui),
	_topViewportController(topViewportController),
	_scriptEditor(scriptEditor)
{

}

void BottomViewportController::initialize()
{
	// Bottom-viewport: statistics
	_gui.getViewport("bottom")->addWindow("statistics", Vec2(-0.25f, 0.0f), Vec2(0.9875f, 1.8f), BottomViewportController::FRAME_COLOR);
	_gui.getViewport("bottom")->getWindow("statistics")->addScreen("main");
	_gui.getViewport("bottom")->getWindow("statistics")->setActiveScreen("main");
	_statsScreen = _gui.getViewport("bottom")->getWindow("statistics")->getScreen("main");

	// General statistics
	_statsScreen->addTextfield("fps", Vec2(-1.0f, 0.85f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("cpuName", Vec2(-1.0f, 0.7f), Vec2(0.0f), "", Vec3(1.0f), false, false);
	_statsScreen->addTextfield("gpuName", Vec2(-1.0f, 0.55f), Vec2(0.0f), "", Vec3(1.0f), false, false);
	_statsScreen->addTextfield("openglVersion", Vec2(-1.0f, 0.4f), Vec2(0.0f), "", Vec3(1.0f), false, false);
	_statsScreen->addTextfield("cameraPosition", Vec2(-1.0f, 0.25f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("cameraYawPitch", Vec2(-1.0f, 0.1f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("cursorPosition", Vec2(-1.0f, -0.05f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("triangleCount", Vec2(-1.0f, -0.2f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("gameEntityCount", Vec2(-1.0f, -0.35f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("billboardEntityCount", Vec2(-1.0f, -0.5f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("lightEntityCount", Vec2(-1.0f, -0.65f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("aabbEntityCount", Vec2(-1.0f, -0.8f), Vec2(0.0f), "", Vec3(1.0f), false, true);
	_statsScreen->addTextfield("guiEntityCount", Vec2(-1.0f, -0.95f), Vec2(0.0f), "", Vec3(1.0f), false, true);

	// Update profiling
	auto updateStatistics = _fe3d.misc_getUpdateProfilingStatistics();
	int counter = 1;
	for (auto& [key, value] : updateStatistics)
	{
		_statsScreen->addTextfield(key, Vec2(-0.2f, 1.0f - (static_cast<float>(counter) * 0.15f)), Vec2(0.0f, 0.15f), "", Vec3(1.0f), false, false);
		counter++;
	}

	// Render profiling
	auto renderStatistics = _fe3d.misc_getRenderProfilingStatistics();
	counter = 1;
	for (auto& [key, value] : renderStatistics)
	{
		_statsScreen->addTextfield(key, Vec2(0.4f, 1.0f - (static_cast<float>(counter) * 0.15f)), Vec2(0.0f, 0.15f), "", Vec3(1.0f), false, false);
		counter++;
	}

	// Console window
	_gui.getViewport("bottom")->addWindow("console", Vec2(0.25f, 0.0f), Vec2(0.9875f, 1.8f), BottomViewportController::FRAME_COLOR);
	_gui.getViewport("bottom")->getWindow("console")->addScreen("main");
	_gui.getViewport("bottom")->getWindow("console")->setActiveScreen("main");
}

void BottomViewportController::update()
{
	// Update fps display
	static vector<float> fpsList;
	if (_fe3d.misc_checkInterval("fps", 50))
	{
		// Calculate median
		std::sort(fpsList.begin(), fpsList.end());
		float fps = fpsList.empty() ? -1.0f : fpsList[24];

		// Display FPS
		string fpsTextID = _statsScreen->getTextfield("fps")->getEntityID();
		string text = "FPS: " + to_string(static_cast<int>(fps));
		_fe3d.textEntity_setTextContent(fpsTextID, text, _charSize.x, _charSize.y);
		fpsList.clear();
	}
	else
	{
		fpsList.push_back(_fe3d.misc_getFPS());
	}

	// Update CPU stats
	if (_fe3d.misc_checkInterval("cpuName", 10000))
	{
		string textID = _statsScreen->getTextfield("cpuName")->getEntityID();
		string text = "CPU: " + _fe3d.misc_getCpuName();
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
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
			to_string(static_cast<int>(_fe3d.terrainEntity_getCursorPosition3D().x)) + " " +
			to_string(static_cast<int>(_fe3d.terrainEntity_getCursorPosition3D().y)) + " " +
			to_string(static_cast<int>(_fe3d.terrainEntity_getCursorPosition3D().z));
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
		string text = "Game entities: " + to_string(_fe3d.gameEntity_getAllIDs().size());
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update billboard entity count
	if (_fe3d.misc_checkInterval("billboardEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("billboardEntityCount")->getEntityID();
		string text = "Billboard entities: " + to_string(_fe3d.billboardEntity_getAllIDs().size());
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update LIGHT entity count
	if (_fe3d.misc_checkInterval("lightEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("lightEntityCount")->getEntityID();
		string text = "Light entities: " + to_string(_fe3d.lightEntity_getAllIDs().size());
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update AABB entity count
	if (_fe3d.misc_checkInterval("aabbEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("aabbEntityCount")->getEntityID();
		string text = "AABB entities: " + to_string(_fe3d.aabbEntity_getAllIDs().size());
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update GUI entity count
	if (_fe3d.misc_checkInterval("guiEntityCount", 10))
	{
		string textID = _statsScreen->getTextfield("guiEntityCount")->getEntityID();
		string text = "GUI entities: " + to_string(_fe3d.guiEntity_getAllIDs().size() + _fe3d.textEntity_getAllIDs().size());
		_fe3d.textEntity_setTextContent(textID, text, _charSize.x, _charSize.y);
	}

	// Update update-profiling
	if (_fe3d.misc_checkInterval("updateProfiling", 50))
	{
		auto updateStatistics = _fe3d.misc_getUpdateProfilingStatistics();
		for (auto& [key, value] : updateStatistics)
		{
			string textID = _statsScreen->getTextfield(key)->getEntityID();
			_fe3d.textEntity_setTextContent(textID, key + ": " + to_string(value) + "%", _charSize.x, _charSize.y);
		}
	}

	// Update render-profiling
	if (_fe3d.misc_checkInterval("renderProfiling", 50))
	{
		auto renderStatistics = _fe3d.misc_getRenderProfilingStatistics();
		for (auto& [key, value] : renderStatistics)
		{
			string textID = _statsScreen->getTextfield(key)->getEntityID();
			_fe3d.textEntity_setTextContent(textID, key + ": " + to_string(value) + "%", _charSize.x, _charSize.y);
		}
	}

	// Clear console messages if user wants to
	if (_fe3d.input_getKeyPressed(InputType::KEY_C) && _gui.getViewport("bottom")->getWindow("console")->isHovered())
	{
		// Validate
		if (!_topViewportController.isScriptRunning() && !_gui.getGlobalScreen()->isFocused() && !_scriptEditor.isWritingScript())
		{
			_fe3d.logger_clearMessageStack();
			for (const auto& [ID, message] : _consoleMessageStack)
			{
				_deleteConsoleMessage(ID);
			}
			_consoleMessageStack.clear();
		}
	}

	// Clear console messages if it overflows
	auto loggerMessages = _fe3d.logger_getMessageStack();
	if (loggerMessages.size() > _maxConsoleMessages)
	{
		// Save most recent messages
		std::reverse(loggerMessages.begin(), loggerMessages.end());
		vector<string> newMessages;
		for (unsigned int i = 0; i < (loggerMessages.size() - _maxConsoleMessages); i++)
		{
			newMessages.push_back(loggerMessages[i]);
		}
		
		// Remove old messages
		_fe3d.logger_clearMessageStack();
		for (const auto& [ID, message] : _consoleMessageStack)
		{
			_deleteConsoleMessage(ID);
		}
		_consoleMessageStack.clear();

		// Set new messages
		_fe3d.logger_setMessageStack(newMessages);
	}

	// Synchronize console text with core logger
	loggerMessages = _fe3d.logger_getMessageStack();
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
	if (!_topViewportController.isScriptRunning())
	{
		_updateConsoleScrolling();
	}
}