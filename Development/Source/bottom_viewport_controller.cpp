#include "bottom_viewport_controller.hpp"

void BottomViewportController::initialize()
{
	// Bottom-viewport: statistics
	_gui->getViewport("bottom")->addWindow("statistics", vec2(-0.25f, 0.0f), vec2(0.9875f, 1.8f), BottomViewportController::frameColor);
	_gui->getViewport("bottom")->getWindow("statistics")->addScreen("main");
	_gui->getViewport("bottom")->getWindow("statistics")->setActiveScreen("main");
	_statsScreen = _gui->getViewport("bottom")->getWindow("statistics")->getScreen("main");
	_statsScreen->addTextfield("fps", vec2(-1.0f, 0.85f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("gpuName", vec2(-1.0f, 0.7f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("openglVersion", vec2(-1.0f, 0.55f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("cameraPosition", vec2(-1.0f, 0.4f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("cameraYawPitch", vec2(-1.0f, 0.25f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);
	_statsScreen->addTextfield("cursorPosition", vec2(-1.0f, 0.1f), vec2(0.0f, 0.15f), "", vec3(1.0f), false);

	// Bottom-viewport: controls
	_gui->getViewport("bottom")->addWindow("controls", vec2(0.25f, 0.0f), vec2(0.9875f, 1.8f), BottomViewportController::frameColor);
	_gui->getViewport("bottom")->getWindow("controls")->addScreen("main");
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("main");
}

void BottomViewportController::update()
{
	// Update FPS
	if (_fe3d.misc_checkInterval("fps", 50))
	{
		string fpsTextID = _statsScreen->getTextfield("fps")->getEntityID();
		string text = "FPS: " + std::to_string(static_cast<int>(_fe3d.misc_getFPS()));
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
		string text = "Camera position: " + _fe3d.misc_vec2str(_fe3d.camera_getPosition());
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
	}

	// Update camera pitch & yaw
	if (_fe3d.misc_checkInterval("cameraYawPitch", 1))
	{
		string textID = _statsScreen->getTextfield("cameraYawPitch")->getEntityID();
		string text = "Camera yaw & pitch: " + std::to_string(_fe3d.camera_getYaw()) + " " + std::to_string(_fe3d.camera_getPitch());
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
	}

	// Update cursor position
	if (_fe3d.misc_checkInterval("cursorPosition", 1))
	{
		string textID = _statsScreen->getTextfield("cursorPosition")->getEntityID();
		string text = "Raycast position: " + _fe3d.misc_vec2str(_fe3d.terrainEntity_getMousePoint());
		_fe3d.textEntity_setTextContent(textID, text, 0.0125f);
	}
}