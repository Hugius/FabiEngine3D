#include "EngineGuiManager.hpp"

EngineGuiManager::EngineGuiManager(FabiEngine3D& fe3d) : 
	_fe3d(fe3d)
{

}

void EngineGuiManager::load()
{
	// Global screen
	_globalScreen = make_shared<EngineGuiGlobalScreen>(_fe3d);

	// Viewports
	_viewports.push_back(make_shared<EngineGuiViewport>(_fe3d, "topViewport", vec2(-1.0f, 0.85f), vec2(0.75f, 0.15f)));

	// Top-viewport: mainWindow
	getViewport("topViewport")->addWindow("mainWindow", vec2(-1.0f), vec2(2.0f));
	getViewport("topViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	getViewport("topViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("newProject", vec2(-0.92f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "New project", vec3(1.0f));
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("loadProject", vec2(-0.44f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "Load project", vec3(1.0f));
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("playGame", vec2(0.04f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "Play game", vec3(1.0f));
	getViewport("topViewport")->getWindow("mainWindow")->getScreen("mainScreen")->addButton("stopGame", vec2(0.52f, -0.5f), vec2(0.4f, 1.0f), vec3(0.25f), "Stop game", vec3(1.0f));
}

void EngineGuiManager::update(float delta)
{
	// Update viewports
	if (!_isFocused)
	{
		for (auto& viewport : _viewports)
		{
			viewport->update(delta);
		}
	}
	
	// Update global screen
	_globalScreen->update(delta);
}

void EngineGuiManager::unload()
{

}

void EngineGuiManager::setFocus(bool focused)
{
	_isFocused = focused;
}

shared_ptr<EngineGuiGlobalScreen> EngineGuiManager::getGlobalScreen()
{
	return _globalScreen;
}

shared_ptr<EngineGuiViewport> EngineGuiManager::getViewport(const string& ID)
{
	for (auto& viewport : _viewports)
	{
		if (ID == viewport->getID())
		{
			return viewport;
		}
	}

	return nullptr;
}