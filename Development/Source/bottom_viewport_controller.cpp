#include "bottom_viewport_controller.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.04f, 2.0f)

void BottomViewportController::initialize()
{
	// Bottom-viewport: statistics
	_gui->getViewport("bottom")->addWindow("statistics", vec2(-0.25f, 0.0f), vec2(0.9875f, 1.8f), BottomViewportController::frameColor);
	_gui->getViewport("bottom")->getWindow("statistics")->addScreen("main");
	_gui->getViewport("bottom")->getWindow("statistics")->setActiveScreen("main");
	_statsScreen = _gui->getViewport("bottom")->getWindow("statistics")->getScreen("main");

	// General statistics
	_statsScreen->addTextfield("fps", vec2(-1.0f, 0.85f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("gpuName", vec2(-1.0f, 0.7f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("openglVersion", vec2(-1.0f, 0.55f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("cameraPosition", vec2(-1.0f, 0.4f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("cameraYawPitch", vec2(-1.0f, 0.25f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("cursorPosition", vec2(-1.0f, 0.1f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("triangleCount", vec2(-1.0f, -0.05f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("gameEntityCount", vec2(-1.0f, -0.2f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("billboardEntityCount", vec2(-1.0f, -0.35f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("lightEntityCount", vec2(-1.0f, -0.5f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);

	// Performance profiling
	auto performanceStats = _fe3d.misc_getPerformanceProfilingStatistics();
	int counter = 1;
	for (auto& [key, value] : performanceStats)
	{
		_statsScreen->addTextfield(key, vec2(0.0f, 1.0f - (static_cast<float>(counter) * 0.15f)), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
		counter++;
	}

	// Bottom-viewport: controls
	_gui->getViewport("bottom")->addWindow("controls", vec2(0.25f, 0.0f), vec2(0.9875f, 1.8f), BottomViewportController::frameColor);
	_gui->getViewport("bottom")->getWindow("controls")->addScreen("mainMenu");
	_gui->getViewport("bottom")->getWindow("controls")->addScreen("worldEditor");
	_gui->getViewport("bottom")->getWindow("controls")->addScreen("modelEditor");
	_gui->getViewport("bottom")->getWindow("controls")->addScreen("billboardEditor");
	_gui->getViewport("bottom")->getWindow("controls")->addScreen("sceneEditor");
	_gui->getViewport("bottom")->getWindow("controls")->addScreen("scriptEditor");
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("mainMenu");

	// Positioning values
	vec2 keySize = vec2(0.125f, 0.5f);
	const float keyX = -0.9f;
	const float yOne = 0.6f;
	const float yTwo = 0.0f;
	const float yThree = -0.6f;
	const float textX = keyX + (keySize.x / 1.5f);
	const float charHeight = 0.25f;
	const float textOffset = (keySize.y / 4.0f);
	const float xOffset = 0.75f;

	// Lambda for engine-global key functions
	auto addBasicKeys = [&](shared_ptr<EngineGuiScreen> screen)
	{
		screen->addRectangle("f", vec2(keyX, yOne), keySize, "f.png");
		screen->addTextfield("f", vec2(textX, yOne - textOffset), vec2(GW("Wireframe"), charHeight), "Wireframe", vec3(1.0f), false);
		screen->addRectangle("h", vec2(keyX, yTwo), keySize, "h.png");
		screen->addTextfield("h", vec2(textX, yTwo - textOffset), vec2(GW("Debug render"), charHeight), "Debug render", vec3(1.0f), false);
	};

	// Main menu screen
	auto mainScreen = _gui->getViewport("bottom")->getWindow("controls")->getScreen("mainMenu");
	addBasicKeys(mainScreen);

	// World editor screen
	auto worldScreen = _gui->getViewport("bottom")->getWindow("controls")->getScreen("worldEditor");
	addBasicKeys(worldScreen);
	worldScreen->addRectangle("mouse", vec2(keyX, yThree), keySize, "mouse.png");
	worldScreen->addTextfield("mouse", vec2(textX, yThree - textOffset), vec2(GW("Camera"), charHeight), "Camera", vec3(1.0f), false);

	// Model editor screen
	auto modelScreen = _gui->getViewport("bottom")->getWindow("controls")->getScreen("modelEditor");
	addBasicKeys(modelScreen);
	modelScreen->addRectangle("r", vec2(keyX, yThree), keySize, "r.png");
	modelScreen->addTextfield("r", vec2(textX, yThree - textOffset), vec2(GW("Reference box"), charHeight), "Reference box", vec3(1.0f), false);
	modelScreen->addRectangle("mouse", vec2(keyX + xOffset, yOne), keySize, "mouse.png");
	modelScreen->addTextfield("mouse", vec2(textX + xOffset, yOne - textOffset), vec2(GW("Camera & resize"), charHeight), "Camera & resize", vec3(1.0f), false);

	// Billboard editor screen
	auto billboardScreen = _gui->getViewport("bottom")->getWindow("controls")->getScreen("billboardEditor");
	addBasicKeys(billboardScreen);
	billboardScreen->addRectangle("mouse", vec2(keyX, yThree), keySize, "mouse.png");
	billboardScreen->addTextfield("mouse", vec2(textX, yThree - textOffset), vec2(GW("Camera"), charHeight), "Camera", vec3(1.0f), false);

	// Scene editor screen
	auto sceneScreen = _gui->getViewport("bottom")->getWindow("controls")->getScreen("sceneEditor");
	addBasicKeys(sceneScreen);
	sceneScreen->addRectangle("mouse", vec2(keyX, yThree), keySize, "mouse.png");
	sceneScreen->addTextfield("mouse", vec2(textX, yThree - textOffset), vec2(GW("Camera"), charHeight), "Camera", vec3(1.0f), false);
	sceneScreen->addRectangle("w", vec2(keyX + xOffset, yOne), keySize, "w.png");
	sceneScreen->addTextfield("w", vec2(textX + xOffset, yOne - textOffset), vec2(GW("Forward"), charHeight), "Forward", vec3(1.0f), false);
	sceneScreen->addRectangle("a", vec2(keyX + xOffset, yTwo), keySize, "a.png");
	sceneScreen->addTextfield("a", vec2(textX + xOffset, yTwo - textOffset), vec2(GW("Left"), charHeight), "Left", vec3(1.0f), false);
	sceneScreen->addRectangle("s", vec2(keyX + xOffset, yThree), keySize, "s.png");
	sceneScreen->addTextfield("s", vec2(textX + xOffset, yThree - textOffset), vec2(GW("Backward"), charHeight), "Backward", vec3(1.0f), false);
	sceneScreen->addRectangle("d", vec2(keyX + xOffset * 2.0f, yOne), keySize, "d.png");
	sceneScreen->addTextfield("d", vec2(textX + xOffset * 2.0f, yOne - textOffset), vec2(GW("Right"), charHeight), "Right", vec3(1.0f), false);
	sceneScreen->addRectangle("shift", vec2(keyX + xOffset * 2.0f, yTwo), keySize, "shift.png");
	sceneScreen->addTextfield("shift", vec2(textX + xOffset * 2.0f, yTwo - textOffset), vec2(GW("Down"), charHeight), "Down", vec3(1.0f), false);
	sceneScreen->addRectangle("space", vec2(keyX + xOffset * 2.0f, yThree), keySize, "space.png");
	sceneScreen->addTextfield("space", vec2(textX + xOffset * 2.0f, yThree - textOffset), vec2(GW("Up"), charHeight), "Up", vec3(1.0f), false);

	// Scripting editor screen
	auto scriptingScreen = _gui->getViewport("bottom")->getWindow("controls")->getScreen("scriptEditor");
	addBasicKeys(scriptingScreen);
	scriptingScreen->addRectangle("mouse", vec2(keyX, yThree), keySize, "mouse.png");
	scriptingScreen->addTextfield("mouse", vec2(textX, yThree - textOffset), vec2(GW("Scrolling"), charHeight), "Scrolling", vec3(1.0f), false);
	scriptingScreen->addRectangle("a", vec2(keyX + xOffset, yOne), keySize, "a.png");
	scriptingScreen->addTextfield("a", vec2(textX + xOffset, yOne - textOffset), vec2(GW("Left"), charHeight), "Left", vec3(1.0f), false);
	scriptingScreen->addRectangle("d", vec2(keyX + xOffset, yTwo), keySize, "d.png");
	scriptingScreen->addTextfield("d", vec2(textX + xOffset, yTwo - textOffset), vec2(GW("Right"), charHeight), "Right", vec3(1.0f), false);
	scriptingScreen->addRectangle("backspace", vec2(keyX + xOffset, yThree), keySize, "backspace.png");
	scriptingScreen->addTextfield("backspace", vec2(textX + xOffset, yThree - textOffset), vec2(GW("Remove"), charHeight), "Remove", vec3(1.0f), false);
}

void BottomViewportController::update()
{
	// Update FPS
	if (_fe3d.misc_checkInterval("fps", 50))
	{
		string fpsTextID = _statsScreen->getTextfield("fps")->getEntityID();
		string text = "FPS: " + to_string(static_cast<int>(_fe3d.misc_getFPS()));
		_fe3d.textEntity_setTextContent(fpsTextID, text, 0.0125f);
	}

	// Update GPU stats
	if (_fe3d.misc_checkInterval("gpuName", 10000))
	{
		string textID = _statsScreen->getTextfield("gpuName")->getEntityID();
		string text = "GPU: " + _fe3d.misc_getGpuName();
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
	}

	// Update OpenGL version
	if (_fe3d.misc_checkInterval("openglVersion", 10000))
	{
		string textID = _statsScreen->getTextfield("openglVersion")->getEntityID();
		string text = "OpenGL version: " + _fe3d.misc_getOpenglVersion();
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
	}

	// Update camera position
	if (_fe3d.misc_checkInterval("cameraPosition", 1))
	{
		string textID = _statsScreen->getTextfield("cameraPosition")->getEntityID();
		string text = "Camera position: " + _fe3d.misc_vec2str(ivec3(_fe3d.camera_getPosition()));
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
	}

	// Update camera pitch & yaw
	if (_fe3d.misc_checkInterval("cameraYawPitch", 1))
	{
		string textID = _statsScreen->getTextfield("cameraYawPitch")->getEntityID();
		string text = "Camera yaw & pitch: " + 
			to_string(static_cast<int>(_fe3d.camera_getYaw())) + " " + to_string(static_cast<int>(_fe3d.camera_getPitch()));
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
	}

	// Update cursor position
	if (_fe3d.misc_checkInterval("cursorPosition", 1))
	{
		string textID = _statsScreen->getTextfield("cursorPosition")->getEntityID();
		string text = "Raycast position: " + _fe3d.misc_vec2str(ivec3(_fe3d.terrainEntity_getMousePoint()));
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
	}

	// Update triangle count
	if (_fe3d.misc_checkInterval("triangleCount", 10))
	{
		string textID = _statsScreen->getTextfield("triangleCount")->getEntityID();
		string text = "Triangles: " + to_string(static_cast<int>(_fe3d.misc_getTriangleCount()));
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
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
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
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
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
	}

	// Update light entity count
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
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
	}

	// Update performance profiling
	if (_fe3d.misc_checkInterval("lightEntityCount", 50))
	{
		auto performanceStats = _fe3d.misc_getPerformanceProfilingStatistics();
		for (auto& [key, value] : performanceStats)
		{
			string textID = _statsScreen->getTextfield(key)->getEntityID();
			_fe3d.textEntity_setTextContent(textID, key + ": " + to_string(value) + "%", 0.0125f);
		}
	}
}